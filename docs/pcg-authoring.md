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
Referenced subgraph content participates in the parent revision. Transient runtime
children (including descendants of a transient cache) do not, while authored
selectors and their editable state do. Detached nodes/pins and disconnected edges
retained after native edits or Undo are not active authored model members. The
editor-only parameter presentation hierarchy is also excluded: opening its details
panel may lazily create presentation objects without editing native parameter
schema or values, which remain fingerprinted separately.
Reinstancing a settings Blueprint class
invalidates the token even if the class asset path stays the same. Never compare
revision strings across editor processes as proof of persistence.

Complete authored capture has a shared budget across referenced graphs: 65,536
reflected values, 8,192 objects, 4,096 ordinary nodes, 16,384 outgoing edges and
1,048,576 string/text characters; nesting and dependency depth are limited to 32,
and dependencies to 256 graphs. A cooperative 100 ms capture deadline is checked
throughout the walk and after serialization. It cannot interrupt one native
serializer call and is not a hard real-time bound. Exhaustion or an invalid/cyclic
dependency produces no partial revision. Query/observation receipts report
`PCG_SNAPSHOT_UNAVAILABLE`; mutating actions also require a complete capture even
when no expected revision was supplied. Reduce the authored state before retrying.
Pagination limits node/settings, parameter-value and managed-result row exports.
Revision integrity still requires a bounded complete capture; inventory totals
scan all related managed references. Inventory traversal itself is not made
constant-time or given a hard resource-count cap by page selection.

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
- `residualChanges`: a failed operation left changes or could not establish
  restoration, including a created child asset; inspect before continuing and do
  not assume a failure means nothing changed.
- `revision` and `editorGraph`: the observed resulting graph and UI consistency.
- `undo`: editor transaction availability, separate from explicit failure
  recovery and disk persistence.

A save failure may leave `committed: true, saved: false`. Disk writes are not
atomically rolled back. An editor transaction is not automatic failure recovery.
PCG mutations refuse an already-active caller editor transaction with `EDITOR_BUSY`;
read-only discovery remains available. Explicit authored-state recovery does not
use global Undo.

`create_pcg_subgraph` is a composite operation, not a multi-package transaction.
For a new child it creates/saves the child first, then attaches it to the parent
and optionally saves the parent. Read `subgraphSaved`, `parentCommitted`,
`parentSaved`, `partialSave`, `rolledBack`, `residualChanges` and `atomic: false`.
An attachment failure can restore captured parent authored state but does not
delete a created child or roll back saved bytes. A parent-save failure can leave
an attached in-memory parent and a saved child. Inspect both assets, resolve the
save cause, then explicitly save the intended owners or remove only proven-unused
residual assets. Retrying creation blindly can encounter the existing child or
attach it twice; the receipt is not an idempotency guarantee.

`sync_pcg_editor_graph` repairs an existing representation through native public
schema actions. Only `openEditor: true` allows it to open the graph when needed.
It preserves existing model identities and comments/layout rather than replacing
the graph with a new asset.

The native input/output boundary node IDs returned by graph reads can be reused
for settings writes as well as the `input`/`output` aliases. Their native
`UPCGGraphInputOutputSettings` are owned by the same graph rather than by the node;
this specific ownership is accepted without permitting edits to another graph
or shared settings. Configure point-only subgraph boundaries through
`set_pcg_node_settings` with `settings.Pins`, then connect the named pins through
the normal PCG edit actions. Preflight still refuses pin changes that would
silently remove existing edges, and boundary node removal remains protected.

For UE 5.7+, a point-only input boundary can be authored as follows. Replace the
node ID with the actual input ID returned by the graph read, and use its current
revision. Configure the output boundary similarly with label `Out`; do this
before connecting edges that depend on those labels.

```json
{
  "operation": "execute",
  "tool": "manage_pcg",
  "action": "set_pcg_node_settings",
  "params": {
    "graphPath": "/Game/PCG/PointTransform",
    "nodeId": "DefaultInputNode",
    "expectedGraphRevision": "<revision from get_pcg_graph>",
    "settings": {
      "Pins": [
        {
          "Label": "In",
          "AllowedTypes": {
            "Ids": [
              {
                "Struct": "/Script/PCG.PCGDataTypeInfoPoint"
              }
            ],
            "CustomSubtype": -1
          }
        }
      ]
    },
    "save": false
  }
}
```

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
`typeObject`. Int64 values outside the JSON safe-integer range
(`-9007199254740991` through `9007199254740991`) must be supplied as decimal
strings. Unsafe JSON numbers are refused before adding a parameter or establishing
an override, including individual array elements; they are not silently accepted
after floating-point rounding. Native Int64 defaults/effective values outside that
range are returned as exact decimal strings, including individual array elements. Values within
that range remain JSON numbers. For example, `"9223372036854775807"` round-trips
without double-precision rounding. Array writes are limited to 10,000 elements
and validated element by element. Floating-point inputs must be finite and fit their native type;
malformed numeric strings are refused rather than becoming zero. Bool values accept
JSON booleans, numeric 0/1, or case-insensitive `true`/`false` strings; other values
are rejected, including invalid elements in a Bool array. Unsupported
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
`superseded`, `target_gone`, `target_moved`, `input_unavailable`, `unknown`, `save_failed` and
`observation_cancelled`.

`superseded` requires observing another native generation start while the original
operation is still watched. An editor refresh can instead cancel the old native
task before scheduling its replacement; that original operation may correctly
remain `cancelled`. A later generation is not retroactively attributed to it.

A timeout or MCP request cancellation does not silently cancel native work.
The native lease remains until that work is idle; another operation on the same
component is refused as busy. `cancel_pcg_operation` explicitly requests native
generation cancellation; it is not rollback. Native cleanup cancellation is not
exposed. `cleanup_pcg_component` cleans only the selected component's managed
resources and waits for native cleanup. Nonmanaged world objects are not deleted.

A retained operation describes its original observation, not every future task on
the component. For example, renaming an actor can cancel the observed task and
then trigger a separate editor refresh. Before cleanup or fixture deletion, read
the current inventory at the component's current exact path and require native
`generating: false` and `cleaning: false`; an old terminal operation alone is not
a current-idle proof. If cleanup is refused as busy, it has not emptied the
resources, so a subsequent zero-resource assertion cannot stand in for cleanup.

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

### Reproducible complex and failure fixtures

Create a new isolated native `PCGValidation` project with the plugin and
source-only test elements:

```sh
node scripts/pcg-validation-project.mjs --engine "<UE_ROOT>" --project "<NEW_PROJECT_DIR>" --fixtures
```

The generator copies only source inputs into the new project. It refuses an existing target directory.
Build that project's Editor target with the selected engine; no engine source or
installed plugin is modified. Optional `--ws-ports` and `--native-port` keep test
listeners separate, loopback-only and authenticated.

The optional deferred-context and Blueprint fixtures require UE 5.7 or later.
Run graph-editor lifecycle automation in a normal windowed editor: UE 5.7.4
can fail in native Slate window restoration when closing a PCG tab under
`-NullRHI`. That incomplete run is not a passing test or a reason to skip the
editor assertions. If the installed Zen cache is unavailable,
`-ddc=InstalledNoZenLocalFallback` with a process-local `UE-LocalDataCachePath`
pointing inside the isolated project avoids changing engine/global cache settings.
Always inspect the exported automation report; the editor process exit code alone
does not establish that every assertion passed.

The additional suites are:

- `manage-pcg-lifecycle`: a deferred custom element creates a transient child
  while native generation is active; control/cache runs must keep the authored
  revision, and observation timeout must retain the lease until native idle.
  A fixture-only helper cancels and schedules a distinct real native task in one
  game-thread turn to test supersession deterministically. It is confined to the
  isolated project's lifecycle actors, uses public native APIs rather than
  broadcasting fake delegates, and verifies the replacement task ID, unchanged
  authored revision, all 100 products and eventual native idle.
- `manage-pcg-workflow`: a linear spline sampled every 100 units, inclusive
  `MCPDistance` filtering from 200 to 500, a seeded random-transform subgraph, a
  custom Blueprint element and three mesh/one actor spawner branches. Expected
  products are twelve instances across two ISMs and one HISM, four managed root
  actors and `MCP_CustomNode` **output-data** tags. All twelve instance transforms,
  random ranges and fixed-seed regeneration are checked with explicit tolerances.
- `manage-pcg-save-failure` (Windows): exclusively locks only its uniquely owned
  graph package, checks real save refusal and unchanged disk bytes, checks a
  saved-child/unsaved-parent receipt, releases the lock, and tests caller-transaction
  refusal. It does not fill a disk or alter global permissions.
- `manage-pcg-cold-load`: reads a manifest from the selected project's
  `Saved/PCGValidation`, loads the owned map in a fresh editor process, checks
  node IDs, settings, subgraph/mesh references, parameter GUID/default/override,
  and regenerates the complex products. Set `UNREAL_MCP_PCG_KEEP_FIXTURE=1` for the
  workflow run to save the map/assets and write its manifest, then normally exit
  the idle editor, start a new process and set
  `UNREAL_MCP_PCG_PERSISTENCE_MANIFEST` to that JSON file. Persistence evidence is
  intentionally retained rather than deleted by the cold-load suite.
- `manage-pcg-compatibility`: requires `UNREAL_MCP_PCG_VARIANT=disabled|noeditor`.
  The generator's `--pcg-disabled` builds the no-PCG branch.
  `--pcg-editor-disabled` forces the editor-API conditional **only in the copied
  test Build.cs**; it proves that conditional branch, not a real installation
  with the engine module absent.

The source test element forwards points and adds a data tag; it is not proof
that arbitrary Blueprint scripts have no external side effects. Tests poll only
explicit read actions. An observer finishing, timing out or cancelling is not
permission to delete fixtures: require native `generating: false` and
`cleaning: false` first, and preserve the scene if that cannot be established.
Native automation runners must inspect the exported JSON test results; editor
process exit status alone may not reflect failed assertions.

For native HTTP/SSE, point `UNREAL_MCP_SERVER_ARGS` at the built CLI followed by
`,proxy` and set `UNREAL_MCP_URL` to the selected editor's loopback `/mcp` endpoint.
Dense suites should set `UNREAL_MCP_TEST_THROTTLE_MS=1000`; bounded PCG read polling
uses a one-second interval. Respect the native session request/tool-call quotas
instead of disabling them for a green run. Native error receipts and the WS
forwarder's nested error receipts have different capture paths; tests explicitly
handle both without treating a timeout or missing capture as success.

`tests/pcg-authorization.mjs` accepts a private
`UNREAL_MCP_PCG_AUTH_MANIFEST` under the selected project's `Saved/PCGValidation`.
It expects uniquely owned map/graph/component/node locators and six distinct
non-Admin profile tokens (`read`, `write`, `destructive`, `owner`, `other`,
`wrongProject`). Only the test owner should provision these confined profiles;
never put that manifest or tokens in source control. The driver checks project
identity with the normal project token before mutations, then verifies exact
scopes, path/project refusals, envelope consent, principal-bound status and
cross-transport cancellation. Cancelling a WS request must retain the native busy
lease and preserve its observation-cancelled outcome after late native completion.
The driver never deletes fixtures or edits profiles. Restore the original config
and revoke temporary credentials after the owning editor exits normally.

`UNREAL_MCP_PCG_VERIFY_EDITOR=1` adds public-subsystem open/close/reopen and
follow-up edit checks to the cold-load suite, restoring its authored position and
Seed afterwards without saving those temporary edits. These are API-backed editor
lifecycle/mapping checks, not a claim of manual visual inspection or GPU rendering.
The native managed-result stress fixture uses unregistered test components and
real instance storage; it measures full-inventory counting with bounded on-page
transform exports, not performance of a production scene or its renderer.

## Planned coverage work packages

The [PCG coverage work packages](pcg-roadmap/README.md) define the remaining
implementation backlog, dependencies and acceptance gates. They are plans, not
additional callable actions or a claim that all PCG modes are supported. Use the
capability records and current guide above for the shipping contract.
