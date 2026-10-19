# Validation and Evidence Contract

[Package index](README.md) · [Prerequisites](00-baseline-and-validation.md) · [Coverage matrix](coverage-matrix.md)

This protocol applies to every work order. Ticket-specific assertions are additional requirements, not permission to weaken these rules. Commands listed here are future validation steps, not results from creating the documents.

## 1. Accept a bounded ticket

Record its ID, owner, scope, non-goals, exact dependencies and target engine/mode/transport. Verify the cited source still matches the current implementation. Do not treat a proposed action name, public declaration, agent report or old checkpoint as implementation evidence.

Keep workflow, implementation coverage and validation layers independent. An owner may document a blocking public-API result without claiming that the corresponding user workflow is supported. Unavailable, skipped and unrun cases do not count as positive coverage.

Only the main coordinator may directly dispatch agents. Subagents cannot delegate or invoke agent-spawning skills/workflows. Parallel work must have distinct file ownership; only one owner mutates a live world/deployment at a time.

## 2. Implementation and contract gate

Preserve the single public `unreal` tool, the `manage_pcg` parent, the shared prequeue gate and one game-thread dequeuer. Reuse the existing PCG observer/lease mechanisms and other domain tools. Do not add a second queue or a generic job service.

For a new or changed callable capability:

1. Author records under [world PCG records](../../src/tools/catalog/capabilities/records/world/manage-pcg.index.ts); fold only actions with matching effect, scope, consent, availability and family.
2. Add native dispatch and the [PCG routing allowlist](../../plugins/EngineWire/Source/EngineWire/Private/MCP/Routing/McpConsolidatedActionRoutingEnvironment.h). Confirm the action reaches its handler, not just discovery.
3. Declare every input consumed and every output required by callers; undeclared outputs can be filtered by the gateway. Reflection boundaries must not become arbitrary UObject serialization.
4. Run the existing generators; never hand-edit generated artifacts or version files.
5. Add native behavior tests and explicit native/WS integration cases, including the advertised folded form and legacy form where applicable. Do not rely on automatic replay of destructive or asynchronous twins.

Relevant existing implementation: [PCG execution context](../../plugins/EngineWire/Source/EngineWire/Private/Domains/PCG/Execution/McpPCGExecContext.cpp), [execution declarations](../../plugins/EngineWire/Source/EngineWire/Private/Domains/PCG/Execution/McpPCGExecution.h), [read budget](../../plugins/EngineWire/Source/EngineWire/Private/Domains/PCG/Discovery/McpPCGBudget.h), [edit state](../../plugins/EngineWire/Source/EngineWire/Private/Domains/PCG/Editing/McpPCGEditState.h) and [safe operations](../../plugins/EngineWire/Source/EngineWire/Private/Safety/McpSafeOperations.h).

Source remains within 250 pure lines per plugin file and 25 source files per Private directory. Split by responsibility, not numbered fragments. Do not introduce engine modifications, private class copies, offsets, global Undo recovery or blanket GC disabling.

## 3. Authorization gate

- Read, Write and Destructive are exact sets; Write does not imply Read, and Destructive does not imply either. Admin is the only wildcard.
- Consent is an execute-envelope sibling naming the capability, never a handler parameter or an assumption derived from loopback/idempotency.
- Both transports must reject insufficient scopes, missing/wrong consent, wrong project, malformed/outside target paths and exhausted path scans before mutation.
- Canonical component locators must resolve to the actual intended component and world. A content-prefix grant is not a new per-actor ACL.
- New data reads require authorized targets and must not expose foreign principal operation/session metadata. Legitimate path-authorized resource inventory is not automatically a principal-private job record.
- Returned object references are not permission to load or traverse other assets. No implicit soft-reference resolution or shared/CDO mutation.
- Installing scoped profiles requires separate permission, a restoration plan, no Admin grants and an actual post-run revocation check. Never record raw tokens, complete profile configuration or binary dumps.

## 4. Read/data identity gate

For each dataset, snapshot or inspection handle, specify:

- Component and world/session identity, original/local role when relevant, dataset/pin and node/stack identity.
- Execution/generation provenance when known. Data reused from cache or an external generation must not be attributed to an unrelated MCP operation.
- Authored graph and effective-instance revisions where useful; neither alone proves that world inputs or generated output remained unchanged.
- Process-local lifetime and invalidation after regeneration, cleanup, graph replacement, target movement/destruction, PIE exit, GC and server restart.
- Paging stability, ordering, exact numeric representation, metadata domains, defaults/inheritance and coordinates of returned transforms.
- Row, column, nesting, string, serialized-size, reference-count and retention limits. Limits must fit the strictest existing gateway/transport budget; pagination is not proof that full inventory traversal is bounded.

Use existing revision/budget helpers where they fit. `GetPCGInstanceRevision` currently takes a component; do not cast arbitrary graph instances into that API. A process-local revision or data UID is not a credential or a persistence ID.

Read actions must not silently enable capture, start generation, open editor windows, save assets, resolve unloaded references, convert a continuous Spatial dataset into all points, or trigger GPU readback. State-changing capture/readback requires an explicit capability and documented effect. Releasing a capture must preserve inspection state owned by the user or another observer.

Cooperative time checks cannot preempt one native call. Do not promise hard real-time or total-memory bounds without proving them. Refuse incomplete snapshots instead of returning a partial integrity token.

## 5. Mutation/lifecycle gate

Prevalidate then commit through the existing game-thread path. Preserve native pin compatibility and explicitly report connection effects. Invalid mixed values, selector changes and resource references must not leave partially authored state.

A staging copy is not a sandbox for arbitrary Blueprint callbacks. If isolation cannot be established, retain the refusal and open a design gate; never remove guards merely to increase apparent coverage.

A transaction is not explicit rollback, and an in-memory commit is not a durable save. Use `McpSafeAssetSave` / `McpSafeLevelSave` / `McpSafeLoadMap` as appropriate. Multi-package receipts must identify saved owners, unsaved owners, residuals and recovery boundaries; do not promise disk atomicity.

For native asynchronous work:

- Scheduling is not completion. Bind supported observation before starting work and use native evidence rather than artificial completion delegates.
- Timeout or MCP observation cancellation does not imply native work stopped. Retain the native lease until the real work is idle.
- Partitioned and runtime work need explicit identity/membership and aggregate semantics; one local task is not whole-world completion.
- Terminal operation records describe their original observation. Require current exact-target `generating: false` and `cleaning: false` before cleanup/deletion.
- Never poll by replaying a mutation. Preserve partial results and unknown outcomes honestly.

## 6. Test layers

| Layer | Required evidence | Does not establish |
| --- | --- | --- |
| Static/unit | Actual assertions and source fingerprint; TS behavior vs source-text checks identified | C++ compilation or real PCG results |
| Mock smoke | Serial built-dist initialization, one public tool, routing/discovery behavior | A live editor or real transport lifecycle |
| Native compile/link | Actual target, engine, optional-module macros, exit code and binary identity | Runtime correctness |
| Native automation | Exported registered test names, matched/passed/failed/not-run counts and errors | Unexecuted integration scenarios or other engines |
| Live native/WS | Exact structured assertions against owned fixtures and matching binaries | Cross-version/platform/GPU correctness not exercised |
| Cold/editor lifecycle | Independent process, saved owners, reload/regeneration and API-backed mapping assertions | Manual visual inspection or renderer certification |
| Real GPU/PIE/WP | Actual RHI/world/cell topology, lifecycle and output evidence | Equivalent behavior in NullRHI/mock or unrelated execution modes |

Static commands, run serially against the intended working tree when relevant:

```sh
npx eslint . --max-warnings=0
npm run type-check
npm run test:unit
npm run registry:check
npm run manifest:check
npm run headers:check
npm run test:params
npm run eval:check
npm run build
npm run test:smoke
git diff --check
```

Native and integration commands require the PRE authorization/identity gates. Use the existing [project generator](../../scripts/pcg-validation-project.mjs), [PCG parameter suite](../../tests/mcp-tools/world/manage-pcg-parameters.test.mjs), [workflow suite](../../tests/mcp-tools/world/manage-pcg-workflow.test.mjs) and [compatibility suite](../../tests/mcp-tools/world/manage-pcg-compatibility.test.mjs) as starting patterns. Label proposed new files as new; do not claim an absent suite is executable.

Inspect exported native reports: a process exit 0 is insufficient. A windowed graph-editor lifecycle case is not replaced by a failed NullRHI run. A forced copied-build conditional is not an actual installation without PCGEditor. Respect request/tool-call quotas instead of raising them for green tests.

## 7. Minimum scenario coverage

Each relevant ticket adds deterministic positive readback and explicit negative cases:

- Real nonempty output and valid empty output; field/type/count/value assertions, not just top-level success.
- Invalid values/resources/pins, stale revisions and unsupported types; unchanged source state on refused preflight.
- Numeric boundaries, default/inherited attributes, mixed arrays, unsupported/non-point data and truncation.
- Same/foreign principal, exact scope sets, wrong consent, wrong project and outside/malformed paths on both transports.
- Cache reuse, repeated generation, timeout, observation/native cancellation, target move/delete, cleanup and GC.
- Native/editor concurrent changes and correct stale-data behavior; loaded-cell changes for partitioned modes.
- Real disk-save failures, partial multi-owner outcomes and independent-process persistence where the ticket writes durable state.

Tests must not depend on production content, global dirty-package saves or shared fixed-folder cleanup. Expected failures must target exact errors; no `success|error` masking. Sampling output is not proof about all points or actors unless the complete expected set is explicitly checked.

## 8. Evidence record template

Use private run storage for raw evidence, with a sanitized portable summary for contribution materials. Required fields:

```text
ticketId / runId / recordedAt / owner
sourceCommit / dirtySourceFingerprint / sourceFileHashes
engineVersion / platform / nodeVersion / moduleGates
projectIdentityFingerprint / loadedPluginBinaryHash
transport / capabilityForm / targetMode / worldSession
fixtureOwnershipId / expectedScopeAndConsentWithoutSecrets
commandOrTestEntry / exitCode / exportedTestResults
assertions / observedValues / failureAndUnknownOutcomes
nativeIdleProof / residualAssets / cleanupAndRevocation
limitations / notRunCells / reviewerAcceptance
```

Do not invent run IDs for tests that have not run. Preserve failed evidence next to passing reruns; do not overwrite reports or change assertions solely to obtain green. Record six historical unrelated native failures separately and compare actual names/errors before attributing new failures to baseline.

## 9. Stop, compensation and delivery

Stop the affected slice for permission denial, wrong identity, unavailable/unexported required APIs, unsafe callbacks, incomplete snapshot integrity, source/binary mismatch or unprovable cleanup ownership. Complete independent read-only investigation rather than bypassing a gate.

Do not force-kill editors, remove unknown assets, delete old evidence or globally clear another user's inspection state. Restore only changes owned by the run; report residuals instead of pretending rollback succeeded. Process/profile/config operations need their own explicit permission.

A ticket is Done only when its bounded scope, actual implementation, relevant evidence and declared cleanup satisfy its acceptance. Batch/global completion additionally requires all required matrix cells. Known safe refusal is not delivery of the refused feature.

The final handoff is one consolidated contribution. A private file retained in old commits is not sanitized by excluding it from the current file list or deleting it in a later commit. Preserve local records and require a separately authorized clean-history/publication approach; no automatic staging, commits, history changes, pushes or remote PRs.
