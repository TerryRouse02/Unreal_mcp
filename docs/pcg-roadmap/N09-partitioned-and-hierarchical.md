# N09 — Partitioned and Hierarchical PCG

This batch targets partitioned and hierarchical editor PCG after public API proof. Runtime-managed generation is a separate N10 workstream that consumes N09 when partitioned. A grid-size value alone is not evidence of partition support. Current bounded execution explicitly refuses partitioned/runtime-managed components; this roadmap does not claim they work.

## Current boundary and related plans

- The existing execution route refuses `IsPartitioned()` and `IsManagedByRuntimeGenSystem()` in [`McpPCGExecActions.cpp`](../../plugins/EngineWire/Source/EngineWire/Private/Domains/PCG/Execution/McpPCGExecActions.cpp). The older [`McpPCGComponentActions.cpp`](../../plugins/EngineWire/Source/EngineWire/Private/Domains/PCG/McpPCGComponentActions.cpp) may schedule work but does not provide the current operation tracking for those modes.
- Reuse [`McpPCGExecution.h`](../../plugins/EngineWire/Source/EngineWire/Private/Domains/PCG/Execution/McpPCGExecution.h), [`McpPCGObserver.cpp`](../../plugins/EngineWire/Source/EngineWire/Private/Domains/PCG/Execution/McpPCGObserver.cpp), [`McpPCGOperationStore.cpp`](../../plugins/EngineWire/Source/EngineWire/Private/Domains/PCG/Execution/McpPCGOperationStore.cpp), and [`McpPCGExecContext.cpp`](../../plugins/EngineWire/Source/EngineWire/Private/Domains/PCG/Execution/McpPCGExecContext.cpp). Preserve the one pre-queue authorization gate and one game-thread dequeuer.
- For data snapshots, reuse the bounded discovery and revision helpers rather than treating loaded cells as the full world. See [`McpPCGRead.h`](../../plugins/EngineWire/Source/EngineWire/Private/Domains/PCG/Discovery/McpPCGRead.h), [`McpPCGBudget.cpp`](../../plugins/EngineWire/Source/EngineWire/Private/Domains/PCG/Discovery/McpPCGBudget.cpp), and [`McpPCGRevision.cpp`](../../plugins/EngineWire/Source/EngineWire/Private/Domains/PCG/Discovery/McpPCGRevision.cpp).
- The existing editor operation, scene-input, authoring, validation, and shared evidence plans are linked from [`N06-generic-authoring.md`](N06-generic-authoring.md), [`N07-instances-and-parameters.md`](N07-instances-and-parameters.md), [`N08-scene-inputs-and-output-assets.md`](N08-scene-inputs-and-output-assets.md), [`N05-data-observability.md`](N05-data-observability.md), [`coverage-matrix.md`](coverage-matrix.md), [`00-baseline-and-validation.md`](00-baseline-and-validation.md), [`validation-and-evidence.md`](validation-and-evidence.md), and [`README.md`](README.md).

## Tickets

## Work-package slicing

**N09-01 spike work units**
1. Identify target UE versions, PCG modules, and exported public symbols before coding.
2. Compile the smallest probe against public headers only; record required module dependencies.
3. Link the probe into the plugin/module configuration used by the supported build.
4. Resolve original/local components and bounded registered-cell membership without creation/loading side effects.
5. Exercise public grid-aware scheduling, completion/cancellation and child destruction; repeat to detect stale callbacks.
6. Separate declaration, compile, link, and runtime results for every version row.
7. Verify unavailable optional modules produce explicit unsupported status.
8. Record which API ownership belongs to engine, plugin, or operation state.
9. Stop at any private-header dependency or unstable teardown; do not ship a copied class.

**N09-02 inventory work units**
1. Resolve the source component from exact world and component identity, not a fuzzy actor search.
2. Record original/local relationship and distinguish a local generated child from its source.
3. Enumerate only public grid and cell identifiers within a strict item/time budget.
4. Capture cell loaded/unloaded state without triggering a load or generation side effect.
5. Include grid configuration separately from observed cell coverage and generated state.
6. Compare inventory revisions before and after a controlled streaming change.
7. Verify unload/reload invalidates a prior cell handle rather than resolving a replacement.
8. Return truncation and unavailable fields explicitly; an empty list is not proof of no cells.
9. Stop if stable public identity is missing or the observed world changes mid-snapshot.

**N09-03 aggregate observation work units**
1. Create one parent lease in the existing operation store and preserve principal ownership.
2. Freeze the initial bounded target inventory used to interpret child observations.
3. Correlate each reported event to the original target identity and operation generation.
4. Keep requested, scheduled, native-completed, failed, and observer-lost states distinct.
5. Detect externally started work and refuse to attribute it to the current request.
6. Recheck graph, component, parameter, and cell-set revisions before success.
7. Emit bounded per-target outcomes and a truthful partial aggregate when cells disappear.
8. End observation independently of native work; retain the bounded native lease until all affected native work is actually idle, then release owned references.
9. Stop rather than infer completion from idle state, a progress heartbeat, or loaded cells alone.

**N09-04 cancellation and cleanup work units**
1. Bind each cancellation request to the original principal, parent operation, and target set.
2. Re-resolve every target before native cancellation or managed-resource cleanup.
3. Distinguish observation cancelled, native cancellation requested, and native stop observed.
4. Clean only matching managed resources; never sweep a world or newly streamed replacement.
5. Bound target count, time, and result detail; report any unvisited targets as residual.
6. Allow retry only for explicitly listed residual identities after fresh authorization.
7. Report save failure separately; do not present failed persistence as cleanup rollback.
8. Confirm no blanket GC suppression or indefinite strong references were introduced.
9. Stop on identity drift and preserve the partial receipt for a deliberate follow-up.

**N09-05 real-fixture work units**
1. Create a small, reproducible World Partition fixture with bounded cells and a known graph.
2. Record engine version, module availability, cell layout, graph revision, and input identity.
3. Exercise inventory and generation through the actual approved transport and authorization gate.
4. Observe completion, then test a controlled streaming transition and repeat the read.
5. Exercise cancellation, partial cleanup, save failure, cold load, and teardown as separate cases.
6. Include a real editor HiGen case after its API gate; runtime-managed extensions belong to N10-04.
7. Keep new test filenames labeled proposed until an implementation task creates them.
8. Verify a real initialized World Partition world; mocks/compile-only runs are insufficient. NullRHI may cover CPU-only assertions, never GPU/rendering or unexecuted window-lifecycle cases.
9. Preserve residual-resource and failure evidence; do not broaden support claims from one fixture.

## N09-01 — Prove public partitioned execution API

**Depends on:** `PRE-03`.
**Priority:** P2 · **Owner:** Unassigned · **Workflow:** PLANNED
**Implementation:** PARTIAL · **Validation:** NOT_RUN

- **User outcome:** Establish a version-specific public API basis before claiming any partitioned execution or observation capability.
- **Existing evidence / reuse:** Investigated UE 5.7 public headers, relative to engine root: `Engine/Plugins/PCG/Source/PCG/Public/PCGComponent.h` declares `GetOriginalComponent`, `IsLocalComponent`, grid-aware local task APIs and original `Generate`/`Cleanup`; `Public/Subsystems/PCGSubsystem.h` declares `ForAllRegisteredLocalComponents`, `GetLocalComponent` and cell traversal. Some cell APIs can create actors, so read-only inventory cannot use their mutation defaults. These declarations are not aggregate-completion or linkage proof. N05 inspection APIs can supply diagnostics but are not the partition scheduling API. See [`McpPCGExecActions.cpp`](../../plugins/EngineWire/Source/EngineWire/Private/Domains/PCG/Execution/McpPCGExecActions.cpp) for the current execution gate.
- **Scope / non-goals:** Make a minimal public-API spike for supported engine versions and module combinations. Do not copy private engine classes, modify engine source, or report the spike as implemented feature support.
- **Steps / target / API gate:** Record includes, module dependencies, compile/link/runtime results, ownership and teardown. Proposed API names remain **PROPOSAL / NOT CALLABLE** until capability records, route registration, and tests are approved separately.
- **Contract:** Any eventual request must resolve a precise component and authenticated principal; require the existing exact `Read`, `Write`, or `Destructive` scope and applicable envelope consent. Availability is explicit per engine/module/mode; no fallback to private API or editor-only behavior.
- **Acceptance:** Positive: original/local mapping and grid-aware public scheduling/completion APIs link and run on each declared target engine. Negative: optional-module absence or unprovable aggregate membership remains unavailable. Lifecycle: repeated generation, child unload and cancellation leave no stale callback or premature lease release. Security: absent scope/required consent performs no execution; read inventory creates/loads nothing. Persistence: no state is claimed durable by the spike.
- **Evidence / DoD / stop:** Attach engine/API symbol, module, compile/link, and runtime evidence per [`validation-and-evidence.md`](validation-and-evidence.md). Stop at the first unavailable or unstable public API; do not add private copies or promote the feature to supported.

## N09-02 — Inventory original/local components and cells

**Depends on:** `N09-01`, `N07-01`.
**Priority:** P3 · **Owner:** Unassigned · **Workflow:** PLANNED
**Implementation:** PARTIAL · **Validation:** NOT_RUN

- **User outcome:** Identify a partitioned source component, its original/local relationship, grid identity, and observed cells without confusing a configured grid size with generated coverage.
- **Existing evidence / reuse:** [`McpPCGExecContext.cpp`](../../plugins/EngineWire/Source/EngineWire/Private/Domains/PCG/Execution/McpPCGExecContext.cpp) resolves an exact component in the current editor world and fingerprints seed, generation grid size, and parameters. [`McpPCGComponentActions.cpp`](../../plugins/EngineWire/Source/EngineWire/Private/Domains/PCG/McpPCGComponentActions.cpp) is legacy scheduling evidence only.
- **Scope / non-goals:** Read-only inventory and identity semantics first. No implicit cell load, world traversal without budget, grid mutation, or assertion that loaded cells represent unloaded regions.
- **Steps / target / API gate:** Inventory public component/cell relationships, stable identifiers, grid bounds, load state, source/original component, and revisions. Add bounded discovery/result shape only after N09-01 proves public access. Proposed `partitionInventory` is **PROPOSAL / NOT CALLABLE**.
- **Contract:** Reads require exact component identity and `Read`; mutations require `Write` plus explicit consent as required by the envelope. Report availability and truncation. Concurrent streaming changes invalidate the snapshot; never silently substitute a local child for its original.
- **Acceptance:** Positive: a small fixture reports distinct source/local identities and grid/cell states. Negative: missing cells, changed world, ambiguity, and exhausted budget are explicit, not empty-success. Lifecycle: unload/reload invalidates stale identity. Security: unauthorized path/world access is refused. Persistence: no mutation or save occurs.
- **Evidence / DoD / stop:** Capture bounded inventory, revision-before/after, and cell load events. Stop on ambiguous ownership or unavailable public identity; do not infer support from `GetGenerationGridSize()` alone.

## N09-03 — Observe aggregate generation honestly

**Depends on:** `N09-02`, `N05-04`.
**Priority:** P3 · **Owner:** Unassigned · **Workflow:** PLANNED
**Implementation:** NOT_IMPLEMENTED · **Validation:** NOT_RUN

- **User outcome:** Distinguish requested, observed, completed, failed, and unavailable work across the identified partition set.
- **Existing evidence / reuse:** Use the bounded operation lease/store and observer in [`McpPCGExecution.h`](../../plugins/EngineWire/Source/EngineWire/Private/Domains/PCG/Execution/McpPCGExecution.h), [`McpPCGOperationStore.cpp`](../../plugins/EngineWire/Source/EngineWire/Private/Domains/PCG/Execution/McpPCGOperationStore.cpp), and [`McpPCGObserver.cpp`](../../plugins/EngineWire/Source/EngineWire/Private/Domains/PCG/Execution/McpPCGObserver.cpp); current status distinguishes native completion from observation loss.
- **Scope / non-goals:** Aggregate bounded, identified child observations. Do not create another queue, a durable job service, or a second dequeuer. Do not claim that unseen/unloaded cells finished.
- **Steps / target / API gate:** After N09-01 and N09-02, correlate each source/local target to one parent operation and a bounded cell snapshot; add cancellation-safe aggregation and diagnostics. Proposed `partitionOperationStatus` is **PROPOSAL / NOT CALLABLE**.
- **Contract:** Require authenticated principal, exact component/world identity, `Write` for generation, and envelope consent where required. A changed cell set or revision is reported as partial/unknown. Concurrent requests use the existing busy lease; do not attribute another operation's products.
- **Acceptance:** Positive: all observed targets reach a terminal aggregate with per-target outcomes. Negative: missing observer, partial loads, native errors, timeout, revision change, and external generation cannot become success. Lifecycle: destroyed/replaced children detach without retargeting. Security: status is principal-bound. Persistence: an optional save is reported separately from generation and uses the existing safe save wrapper.
- **Evidence / DoD / stop:** Record target identities, initial/final inventory, observed native events, aggregate counts, and terminal reason. Stop on identity drift; never convert observation cancellation into native-stop or rollback claims.

## N09-04 — Bound aggregate cancellation and cleanup

**Depends on:** `N09-03`, `N08-02`.
**Priority:** P3 · **Owner:** Unassigned · **Workflow:** PLANNED
**Implementation:** NOT_IMPLEMENTED · **Validation:** NOT_RUN

- **User outcome:** Cancel observation or request native cancellation only for the original, explicitly identified targets, then report residual managed resources honestly.
- **Existing evidence / reuse:** [`McpPCGExecActions.cpp`](../../plugins/EngineWire/Source/EngineWire/Private/Domains/PCG/Execution/McpPCGExecActions.cpp) calls native generation cancellation for its tracked unpartitioned target and explicitly refuses cleanup cancellation. [`McpPCGObserver.cpp`](../../plugins/EngineWire/Source/EngineWire/Private/Domains/PCG/Execution/McpPCGObserver.cpp) states observation cancellation does not imply native work stopped.
- **Scope / non-goals:** Define bounded per-target cancellation and cleanup receipts; no global cleanup, blanket GC disabling, forced object retention, implicit regeneration, or whole-world sweep.
- **Steps / target / API gate:** Re-resolve exact original/local identities before each operation; use existing lease and cleanup behavior where public APIs permit. Proposed `cancelPartitionOperation` and `cleanupPartitionResults` are **PROPOSAL / NOT CALLABLE**.
- **Contract:** Require `Destructive` for cleanup and any destructive cancellation, exact scope and consent; report whether request was accepted, native stop observed, cleanup completed, or residuals remain. Concurrency conflicts fail closed. Never hold unbounded strong references.
- **Acceptance:** Positive: partial cleanup identifies remaining targets and can be safely retried. Negative: reloaded replacement, ambiguous source, timeout, or missing cell never triggers a broad cleanup. Lifecycle: streaming/unload during cancellation preserves a truthful partial receipt. Security: no cross-principal cancellation. Persistence: save failure is distinct and does not roll back or fabricate cleanup success.
- **Evidence / DoD / stop:** Include requested/observed cancellation, each cleanup outcome, residual count, revision, and save result. Stop at target drift; compensation is limited to explicit cleanup of still-matching targets after renewed authorization.

## N09-05 — Exercise a small World Partition and HiGen fixture

**Depends on:** `N09-04`, `N08-04`.
**Priority:** P3 · **Owner:** Unassigned · **Workflow:** PLANNED
**Implementation:** NOT_IMPLEMENTED · **Validation:** NOT_RUN

- **User outcome:** Demonstrate an end-to-end bounded lifecycle in a real, small World Partition fixture before any broader support claim.
- **Existing evidence / reuse:** Extend [`tests/mcp-tools/world/manage-pcg-execution.test.mjs`](../../tests/mcp-tools/world/manage-pcg-execution.test.mjs), [`manage-pcg-lifecycle.test.mjs`](../../tests/mcp-tools/world/manage-pcg-lifecycle.test.mjs), and [`scripts/pcg-validation-project.mjs`](../../scripts/pcg-validation-project.mjs); fixture conventions live under [`tests/fixtures/pcg/`](../../tests/fixtures/pcg/).
- **Scope / non-goals:** A bounded editor test fixture covering a small set of cells and an actual hierarchical multi-grid case only after its public API gate passes; runtime-managed behavior is deferred to N10-04. This is not broad production scale, all grid modes, or packaged MCP.
- **Steps / target / API gate:** Add clearly labeled new fixture/test files only under a separately approved implementation task; test discovery, generate, observe, cancel, cleanup, unload/reload, save-failure, and cold-load receipts. No production API is callable until its record, generated metadata, route, and transport coverage are implemented.
- **Contract:** Use the shared authorization gate, exact `Read`/`Write`/`Destructive` scope, explicit envelope consent, principal-bound operation IDs, and bounded budgets. Concurrent streaming and world teardown return partial/unknown rather than success.
- **Acceptance:** Positive: real editor fixture observes expected cells and managed resources. Negative: mocks, unexecuted assertions, absent optional modules, unrelated external work and unseen cells cannot pass as full acceptance. CPU NullRHI results apply only to the assertions actually run, not rendering/GPU or window lifecycle. Lifecycle: editor world/cell teardown and restart do not rebind stale handles. Security: run denied-scope/consent cases. Persistence: save, save failure, and cold load independently verify actual persisted state.
- **Evidence / DoD / stop:** Keep fixture description, engine version, transport, scope/consent class, target/revision snapshots, logs, and cleanup receipts. Stop and preserve evidence on unexpected residuals; do not erase failure artifacts or claim untested scale.

## Recommended order and batch boundary

Run N09-01 first and stop if public API/link/lifecycle proof fails. Then N09-02 inventory can proceed; N09-03 depends on that inventory and N05-04 consistency semantics. N09-04 is a separate destructive-safety gate; N09-05 is the final real-fixture acceptance, not a substitute for the earlier gates. Keep each batch bounded to one validated step, preserve partial state/evidence for diagnosis, and require separate authorization before implementation or deployment. N11 continuous contract/security gates apply throughout, while N11 final matrix regression remains the later delivery gate.
