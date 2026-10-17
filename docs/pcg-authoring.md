# PCG authoring and execution

PCG actions use the existing `unreal` gateway and the `manage_pcg` parent on both
TypeScript stdio/WebSocket and native HTTP/SSE. There is no separate PCG server.
The PCG plugin must be enabled in the connected editor.

## Discover before editing

Use `list_pcg_node_types` to discover loaded, concrete settings classes, then
`get_pcg_settings_schema` for editable property types and defaults. This is a
loaded-class inventory, not a scan that loads every Blueprint in the project.

`get_pcg_graph` returns stable node object names, settings classes, positions,
input/output pins, native connection restrictions, edges and a graph `revision`.
Use the returned pin labels rather than assuming all nodes use `In` and `Out`.
`includeSettings: true` includes authored settings and their owned subobjects.
Node/schema pages default to 50 rows (maximum 100). Edges have independent
`edgeOffset`/`edgeLimit` pagination, default 500 and maximum 1000.

```json
{
  "operation": "execute",
  "tool": "manage_pcg",
  "action": "get_pcg_graph",
  "params": {
    "graphPath": "/Game/PCG/Example",
    "includeSettings": true,
    "offset": 0,
    "limit": 50,
    "edgeOffset": 0,
    "edgeLimit": 500
  }
}
```

`get_pcg_editor_graph` inspects an existing editor representation; it never opens
a window or creates that representation. `validate_pcg_graph` checks native pin
compatibility and reports editor consistency separately. It is **not** proof
that generation will succeed or that assets have been saved.

## Revision-checked edits

Existing add/connect/settings actions retain their names, aliases and default
save behavior. They accept an optional `expectedGraphRevision`; stale state is
refused before mutation. A revision reflects authored graph content, including
settings and parameters, rather than an MCP-only edit counter. It is a
process-local optimistic concurrency token, not a durable ID or credential.

Settings are prevalidated on staged data. Nested paths may traverse settings'
owned objects, not shared assets or class defaults. Invalid mixed settings and
invalid spawner resources must not leave a partially edited node behind.
Incompatible pins, required conversions/filters and connections that would
silently replace existing links are refused rather than implicitly breaking
links. Disconnect explicitly through a destructive action when intended.

New single-graph actions include `move_pcg_node`, `disconnect_pcg_pins` and
`remove_pcg_node`. Input/output nodes cannot be removed.

`batch_edit_pcg_graph` accepts 1–100 `operations` and **requires** the current
nonempty `expectedGraphRevision`. Operations are `add_node`, `set_settings`,
`move_node` and `connect`. An add may name `tempId`; later steps may use that ID
where a node ID is expected. The reply's `nodeIds` maps temporary IDs to real
node names. Numeric node indices are not accepted in a batch.

The separate `batch_edit_pcg_graph_destructive` also permits `disconnect` and
`remove_node`. A write-only batch refuses these operations, even if a caller has
other scopes. Batches do not include generation, parameter-schema propagation,
world settings or multi-asset creation. Staging is not a general sandbox for
arbitrary custom Blueprint callbacks; unsupported isolation must be refused.

### Read the entire edit receipt

- `committed`: the in-memory edit was applied.
- `saved`: the selected package was saved; this does not mean every dirty package
  or dependent instance was saved.
- `rolledBack`: explicit failure recovery restored the captured state.
- `residualChanges`: recovery could not establish restoration; inspect before
  continuing, and do not assume a failure means nothing changed.
- `revision` and `editorGraph`: the observed resulting graph and UI consistency.
- `undo`: editor transaction availability, separate from explicit failure
  recovery and disk persistence.

A save failure may leave `committed: true, saved: false`. Disk writes are not
atomically rolled back. An editor transaction is not automatic failure recovery.

`sync_pcg_editor_graph` repairs an existing representation through native public
schema actions. Only `openEditor: true` allows it to open the graph when needed.
It preserves existing model identities and comments/layout rather than replacing
the graph with a new asset.

## Graph parameters and instance overrides

`get_pcg_parameters` returns native schema, stable parameter IDs, graph defaults,
effective values and `overridden`. Choose exactly one target:

| `target` | Matching locator |
| --- | --- |
| `graph` (default) | `graphPath` |
| `graphInstance` | `graphInstancePath` |
| `component` | exact absolute `componentPath` |

Do not mix locators or substitute an actor name for a component object path.
Schema add/rename/remove operations target the graph, not an instance.

Use `add_pcg_parameter`, `set_pcg_parameter`, `rename_pcg_parameter`,
`reset_pcg_parameter_override` and `remove_pcg_parameter`. Supported new schema
kinds are Bool, Byte, Int32, Int64, Float, Double, Name, String, Enum, Struct,
Object, Class, SoftObject and SoftClass, as scalars or a single array container.
Struct support is Vector, Rotator and Transform. Enum/struct/reference types use
`typeObject`. Array writes are limited to 10,000 elements and validated element
by element. Floating-point inputs must be finite and fit their native type;
malformed numeric strings are refused rather than becoming zero. Unsupported
existing bag types are explicitly refused instead of silently coerced.

Setting an instance parameter establishes an override. Reset clears that one
override and resumes inheritance. Rename uses the native API and retains the
parameter GUID. A `PCGUserParameterGetSettings` node can bind through
`parameterName`, and graph node reads expose its binding metadata.

Removal refuses references in loaded PCG nodes instead of cascading node
deletion. `loadedReferencesOnly: true` is not proof that no unloaded asset in the
project references a parameter. Native parameter propagation crosses instances;
its receipt explicitly does not promise single-graph atomic rollback. Save the
owners required by the workflow; saving the graph does not save all instances.

## Scheduling is not completion

The existing `execute_pcg_graph` still starts native work and returns a numeric
`taskId`. Its legacy `saved` field describes the save at scheduling time, **not**
persistence of future generated products. Supported components additionally
return an `operationId`; this is a separate identifier with separate lifetime.

For an already assigned, unpartitioned editor component, use
`generate_pcg_graph` with its exact `componentPath`. It awaits this native
execution and inspects captured node diagnostics. `force` defaults to true,
`timeoutSeconds` to 60 (0.1–600), and `save` to false. It does not implicitly
create a component or reassign its graph. A generated delegate alone is not
success; unavailable diagnostics yield `unknown`. Zero output can be valid.

`get_pcg_operation_status` reads a retained operation using **both** its
`operationId` and original `componentPath`, for its authenticated principal.
`completed` means the observation ended. Inspect `state`, `succeeded`,
`operationErrorCode`, `engineStillRunning` and native delegate flags. Outcomes
include `succeeded`, `failed`, `cancelled`, `timed_out`, `graph_changed`,
`superseded`, `target_gone`, `target_moved`, `unknown`, `save_failed` and
`observation_cancelled`.

A timeout or MCP request cancellation does not silently cancel native work.
The native lease remains until that work is idle; another operation on the same
component is refused as busy. `cancel_pcg_operation` explicitly requests native
generation cancellation; it is not rollback. Native cleanup cancellation is not
exposed. `cleanup_pcg_component` cleans only the selected component's managed
resources and waits for native cleanup. Nonmanaged world objects are not deleted.

The PCG operation store is current-process only, bounded to 64 active leases and
128 completed operations with a 30-minute completed TTL. Active native work is
not evicted. It is not a durable job service. Restarted/expired operations return
`PCG_OPERATION_NOT_FOUND`.

The gateway may answer a long call after about 27 seconds with its own
`task.state: running` or `queued`. Retrieve that **string MCP task ID** through
`manage_tools.get_task_result`. Do not pass a numeric engine `taskId` or a PCG
`operationId` to that API. The gateway's bounded long-call result store is
independent of PCG operation retention. The existing native keepalive answers at
that threshold even when execution options include an explicit timeout; the
TypeScript gateway suppresses its early answer for an explicit `timeoutMs`.
Transport deadlines still apply independently of the PCG observation timeout;
in particular, the WebSocket tracker retains its five-minute absolute cap.
Waiting is not a measured percentage, so PCG emits terminal progress rather than
periodic artificial percentages or timeout-extending wait heartbeats.

## Inspect managed products

`get_pcg_component_results` is a current inventory, **not** a completion signal.
It counts all related managed ISM/HISM components and instances, managed actors
and owned child-actor descendants. It does not scan global tags or load unresolved
soft actor references. `unresolvedResourceReferences` records those omissions.

`offset`/`limit` page components, actors and root-output summaries (maximum 100
rows per category). `sampleLimit` is 0–16, default 2; two samples select first and
last world transforms. Output summaries contain pin/class/tags/counts, not full
point arrays. Root-output point counts are not counts of all intermediate graph
data. A failed operation's inventory may contain preexisting or partial products;
`resourceSnapshotFromSuccessfulOperation` distinguishes it from confirmed output.

## Permissions and compatibility

Read, write and destructive scopes are exact sets: write does not imply read.
PCG cleanup/cancellation, disconnect, deletion and destructive batches require
explicit consent. The grant is an execute-envelope sibling, never a handler
parameter. Folded family selectors retain the same permission boundaries:
`inspect_pcg` (`view`), `edit_pcg_graph` (`edit`), `mutate_pcg_graph` (`mutation`),
`edit_pcg_parameters` (`parameterEdit`) and `control_pcg_execution` (`control`).
Existing leaf names remain callable.

Component addresses such as `Map.Map:PersistentLevel.Actor.PCGComponent` are
validated as complete subobject paths before their owning package is checked
against the principal's allowed content prefixes. A valid prefix cannot rescue a
malformed suffix, traversal or host-filesystem path. Asset/file sanitizers are
not made permissive toward arbitrary colons. This is package/folder confinement,
not a new per-actor ACL; the handler still resolves the exact current-world
component. Supported `/Content` and separator aliases use the same canonical form
at authorization and resolution, while legacy short-name execution calls retain
their existing unrestricted behavior.

An authenticated profile refused for the editor project receives
`PROJECT_NOT_PERMITTED` on native MCP and through the WS gateway. Unknown or
malformed handshake failures do not forward peer text; ordinary connection
unavailability remains `NOT_CONNECTED`. The typed project refusal is cleared
before another connection attempt and on success, rather than being reused as a
stale cause for a later socket failure. Operation ownership remains bound to the
trusted principal and exact original component, independently of these path
checks; inventory access does not grant access to another principal's retained
operation or expose their active operation ID.

New graph-parameter and completion-observation implementations require the
native APIs available in UE 5.7 or later; older supported engine branches return
`NOT_SUPPORTED` for those operations. PCG remains optional. Partitioned/runtime
generation and GPU validation are not covered by the new completion flow.
Cross-version/platform and disabled-module combinations need their own build and
runtime evidence; a Windows UE 5.7.4 result does not establish those combinations.

## Isolated integration tests

The new `manage-pcg-reliability`, `manage-pcg-parameters` and
`manage-pcg-execution` suites require explicit isolated-project identity settings:
`UNREAL_MCP_TEST_PROJECT_NAME`, `UE_PROJECT_PATH` and `UE_EDITOR_BASE_DIR` (to
resolve Unreal's relative project-directory responses). An optional
`UNREAL_MCP_TEST_ENGINE_VERSION` pins the engine prefix. Set
`MCP_AUTOMATION_WS_PORTS` for that editor, build the server, then run the selected
suite under `tests/mcp-tools/world/`.

The parameter suite additionally requires the editor Python plugin for creating
its uniquely owned graph-instance fixture. Identity is checked before fixtures
are mutated. These suites use unique run roots, disable shared-fixture cleanup
and do not repeat mutating folded twins implicitly. Never point the legacy PCG
suite's fixed-folder cleanup at a production editor.
