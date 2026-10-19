# N10 — GPU and Runtime PCG

GPU execution and PIE/runtime-world control are separate capability tracks. A GPU transfer/inspection flag is not proof that GPU work completed or that returned data is correct. The existing editor-world resolver must never silently act on the editor world when a caller asked for PIE. Packaged-runtime MCP is a separate architecture decision, not an implicit extension of the Editor-only plugin.

## Current boundary and related plans

- Current operation tracking and diagnostics live in [`McpPCGExecActions.cpp`](../../plugins/EngineWire/Source/EngineWire/Private/Domains/PCG/Execution/McpPCGExecActions.cpp), [`McpPCGObserver.cpp`](../../plugins/EngineWire/Source/EngineWire/Private/Domains/PCG/Execution/McpPCGObserver.cpp), and [`McpPCGExecDiagnostics.cpp`](../../plugins/EngineWire/Source/EngineWire/Private/Domains/PCG/Execution/McpPCGExecDiagnostics.cpp). Their use does not establish a GPU completion fence or validated GPU readback contract.
- [`McpPCGExecContext.cpp`](../../plugins/EngineWire/Source/EngineWire/Private/Domains/PCG/Execution/McpPCGExecContext.cpp) intentionally resolves the current editor world. Runtime targeting must add explicit world/session identity rather than weaken that resolver.
- Reuse [`McpPCGExecution.h`](../../plugins/EngineWire/Source/EngineWire/Private/Domains/PCG/Execution/McpPCGExecution.h), the existing operation store/observer, bounded discovery helpers, and [`McpPCGOperationStore.cpp`](../../plugins/EngineWire/Source/EngineWire/Private/Domains/PCG/Execution/McpPCGOperationStore.cpp). Do not add a second queue, durable job service, unbounded strong references, or blanket GC disabling.
- Related plans: [`README.md`](README.md), [`coverage-matrix.md`](coverage-matrix.md), [`00-baseline-and-validation.md`](00-baseline-and-validation.md), [`validation-and-evidence.md`](validation-and-evidence.md), [`N05-data-observability.md`](N05-data-observability.md), [`N06-generic-authoring.md`](N06-generic-authoring.md), [`N07-instances-and-parameters.md`](N07-instances-and-parameters.md), [`N08-scene-inputs-and-output-assets.md`](N08-scene-inputs-and-output-assets.md), and [`N09-partitioned-and-hierarchical.md`](N09-partitioned-and-hierarchical.md).

## Tickets

## Work-package slicing

**N10-01 real-RHI spike work units**
1. Enumerate target engine versions and the exact PCG/GPU modules enabled for each build.
2. Identify the smallest public completion and synchronization API available per version.
3. Compile and link a minimal probe against public headers; record each stage separately.
4. Run a small deterministic graph on an actual supported RHI, not NullRHI or CPU mock.
5. Capture when completion becomes observable and how GPU resources are released.
6. Exercise device/world teardown and repeated runs for leaked callbacks or resources.
7. Verify missing module/API cases fail closed without attempting alternate private APIs.
8. Record whether transfer flags, inspection, and actual completion are distinct signals.
9. Stop if the real-RHI completion contract cannot be demonstrated publicly.

**N10-02 completion/readback work units**
1. Define operation states for scheduled, GPU pending, completed, failed, and observation lost.
2. Name the explicit readback request and enforce byte, sample, and time limits.
3. Keep readback opt-in and avoid blocking the editor/game thread on transfer completion.
4. Bind returned bytes/summaries to the exact component, graph, and operation revisions.
5. Mark data unavailable when the required fence or revision check is missing.
6. Test timeout and observation cancellation without claiming native GPU work stopped.
7. Verify over-budget requests refuse before an expensive transfer begins.
8. Report transfer requested separately from transfer completed and data returned.
9. Stop before downloading data whenever synchronization or ownership remains ambiguous.

**N10-03 correctness/diagnostic work units**
1. Choose a small known fixture with expected bounded geometry or attribute summaries.
2. Define justified numeric tolerance and document any RHI-dependent nondeterminism.
3. Capture native node errors and diagnostic availability separately from completion.
4. Exercise mismatch, device loss, timeout, and diagnostics-unavailable paths.
5. Tie every diagnostic to principal, operation ID, component, and input revision.
6. Bound output size and redact credentials, arbitrary machine paths, and private payloads.
7. Compare saved/cold-loaded output only in a separate persistence assertion.
8. Re-run cancellation and world teardown to detect stale diagnostic association.
9. Stop on unexplained mismatch; never relax tolerance solely to turn a failure green.

**N10-04 PIE identity work units**
1. Define a world/session identity that is explicit in every runtime request.
2. Resolve the requested PIE world without using the editor-world resolver as fallback.
3. Test multiple concurrent PIE sessions and verify operations remain isolated.
4. Bind each handle and operation to principal, world, session, and component identity.
5. Invalidate all handles when PIE stops, restarts, or replaces the world.
6. Exercise late observer callbacks after teardown and ensure they cannot retarget.
7. Keep PIE persistence distinct from editor asset/world save semantics.
8. Require exact scope and envelope consent again for every runtime mutation.
9. Stop if the public engine API cannot provide stable session identity.

**N10-05 mode decision work units**
1. Assemble separate matrix rows for editor CPU, editor GPU, PIE, partitioned, and packaged modes.
2. Link each claimed row to its own implementation and real validation evidence.
3. Record unsupported, partial, unknown, and not-run states without converting them to percentages.
4. Reconcile the packaged-MCP requirement recorded early in PRE-01; do not wait until this final join to discover that product decision.
5. If required, request a separate architecture/implementation decision before expanding scope.
6. Do not equate optional native editor transport with a packaged runtime service.
7. Verify security identity, scope, consent, concurrency, cancellation, and persistence per mode.
8. List excluded modes as explicit remaining gaps when authorization says they are required.
9. Stop short of architecture or implementation work without separate authorization.

## N10-01 — Prove GPU capability and public API on a real RHI

**Depends on:** `PRE-03`.
**Priority:** P2 · **Owner:** Unassigned · **Workflow:** PLANNED
**Implementation:** PARTIAL · **Validation:** NOT_RUN

- **User outcome:** Know which engine versions, public APIs, PCG modules, and real RHIs can safely execute and observe GPU-backed graphs.
- **Existing evidence / reuse:** UE 5.7 public inspection exposes execution state and capture-related declarations, including `FPCGGraphExecutionInspection` and `FExtraCapture::CalculateCallTreeInfo`; declarations and transfer flags do not prove synchronization, correctness, or linkage. Start from [`EngineWire.Build.cs`](../../plugins/EngineWire/Source/EngineWire/EngineWire.Build.cs) and existing execution feature gates.
- **Scope / non-goals:** A minimal capability/API spike on an actual supported RHI. NullRHI, CPU mocks, or a compile-only path are not acceptance. No private engine-class copies or engine-source modifications.
- **Steps / target / API gate:** Record public symbols, module dependencies, async/fence semantics, transfer support, link/runtime proof, and teardown. Candidate `gpuCapability` is **PROPOSAL / NOT CALLABLE** pending approved records, route, and tests.
- **Contract:** Availability is explicit by engine, module and RHI. Read/none capability metadata queries are bounded and do not schedule work. The spike's actual GPU generation is a separate, explicitly authorized Write operation with the normal principal, target and applicable envelope-consent checks; probing must not hide that mutation.
- **Acceptance:** Positive: live RHI completes a small known graph. Negative: missing API/module and NullRHI are reported unsupported, never successful. Lifecycle: repeated runs and world shutdown release resources. Security: denied scope/consent performs no generation. Persistence: no save or data transfer is implicit.
- **Evidence / DoD / stop:** Capture engine/RHI/driver-neutral capability summary, compile/link, real-RHI run and teardown. Stop if no public completion mechanism can be demonstrated; do not label inspection flags as proof.

## N10-02 — Define GPU completion and explicit bounded readback

**Depends on:** `N10-01`, `N05-04`.
**Priority:** P3 · **Owner:** Unassigned · **Workflow:** PLANNED
**Implementation:** NOT_IMPLEMENTED · **Validation:** NOT_RUN

- **User outcome:** Receive a result only after the required GPU completion point, with any GPU-to-CPU transfer explicitly requested and bounded.
- **Existing evidence / reuse:** Reuse completion observation and operation ownership in [`McpPCGObserver.cpp`](../../plugins/EngineWire/Source/EngineWire/Private/Domains/PCG/Execution/McpPCGObserver.cpp), plus N05-04's snapshot consistency contract. Existing managed-result summaries are bounded; they do not authorize silent expensive readback.
- **Scope / non-goals:** Specify the smallest public completion/fence and explicit readback path proved by N10-01. No synchronous unbounded download, implicit transfer, or claim that an inspection flag is a fence.
- **Steps / target / API gate:** Separate generation completion, transfer requested, transfer completed, byte/sample limits, truncation, and timeout. Candidate `request_pcg_gpu_readback` (explicit state/transfer request) and `get_pcg_gpu_readback` (existing status/data read) are **PROPOSALS / NOT CALLABLE**; route them through canonical records and the existing queue.
- **Contract:** Require exact component and result provenance plus authenticated principal. Execution/transfer acquisition is a separate Write capability, with any stronger native effects separately reviewed; querying already captured status/data is Read and never starts a transfer. Neither scope implies the other. Apply envelope consent where required. Readback is opt-in, non-blocking to the editor and refused over budget before transfer. A changed generation/data identity invalidates the view rather than mixing snapshots.
- **Acceptance:** Positive: explicitly requested bounded readback matches the completion revision. Negative: absent fence, over-budget transfer, timeout, or changed revision is explicit and cannot return partial data as complete. Lifecycle: canceling observation does not claim GPU cancellation. Security: another principal cannot read an operation. Persistence: no hidden disk cache or save.
- **Evidence / DoD / stop:** Record fence/completion evidence, requested and transferred bytes, sample bounds, data revision, elapsed time, and failure state. Stop before readback if public synchronization is unclear; avoid costly transfer and report unavailable.

## N10-03 — Validate GPU correctness and diagnostics

**Depends on:** `N10-02`, `N05-06`.
**Priority:** P3 · **Owner:** Unassigned · **Workflow:** PLANNED
**Implementation:** NOT_IMPLEMENTED · **Validation:** NOT_RUN

- **User outcome:** Distinguish successful GPU output from completion-only signals and expose bounded actionable diagnostics on supported hardware.
- **Existing evidence / reuse:** Reuse [`McpPCGExecDiagnostics.cpp`](../../plugins/EngineWire/Source/EngineWire/Private/Domains/PCG/Execution/McpPCGExecDiagnostics.cpp), the observer's native completion/error distinction, and N05-06's bounded capture/profile implementation and N05-05's feasibility boundaries.
- **Scope / non-goals:** Validate known deterministic fixtures, failure modes, and bounded diagnostic fields. Do not demand bitwise equality where the engine/RHI contract does not guarantee it, and do not claim generic support from one fixture.
- **Steps / target / API gate:** Add a new, explicitly labeled real-RHI test under `tests/mcp-tools/world/` and/or `plugins/EngineWire/Source/EngineWire/Private/Tests/PCG/` only in approved implementation work; compare expected geometry/data summaries and error classes.
- **Contract:** Diagnostics are principal-bound, redacted, budgeted, and tied to the exact operation/revision. They must not leak tokens, arbitrary machine paths, or unbounded GPU payloads. A diagnostic-unavailable terminal state is not success.
- **Acceptance:** Positive: known fixture output and documented tolerance match after verified completion. Negative: node error, mismatch, device loss, timeout, or unavailable diagnostics never reports success. Lifecycle: cancellation/world teardown cannot attach stale diagnostics to a later run. Security: unauthorized read is denied. Persistence: cold-load checks separately prove only what was saved.
- **Evidence / DoD / stop:** Store RHI/engine, fixture revision, expected/actual bounded summaries, diagnostic status, tolerances, and teardown result. Stop on unknown data ownership or nondeterministic unexplained mismatch; retain evidence and avoid widening tolerances to force green.

## N10-04 — Scope PIE/runtime operations to the requested world

**Depends on:** `N07-03`, `N05-04`.
**Priority:** P3 · **Owner:** Unassigned · **Workflow:** PLANNED
**Implementation:** NOT_IMPLEMENTED · **Validation:** NOT_RUN

- **User outcome:** Address an explicitly selected PIE/runtime world and session without accidentally operating on the editor world or another PIE instance.
- **Existing evidence / reuse:** [`McpPCGExecContext.cpp`](../../plugins/EngineWire/Source/EngineWire/Private/Domains/PCG/Execution/McpPCGExecContext.cpp) resolves only the current editor-world component. Reuse the existing request principal, operation store, bounded snapshot, and queue; do not change editor-world resolution as an implicit fallback.
- **Scope / non-goals:** PIE/session-scoped identity and lifecycle, independently of GPU and N09. Partitioned PIE additionally depends on N09; packaged server/runtime is not smuggled into this ticket.
- **Steps / target / API gate:** Prove world/session resolution and canonical original-map versus PIE object-path authorization without textual prefix stripping or a second authority. Add bounded world-aware target/operation adapters and invalidation; do not merely remove the current runtime-managed refusal. Exercise native runtime generation-source registration, trigger/policy/radius updates and dynamic scheduling through public APIs, with correlation of repeated native work to the requested observation. Candidate `worldSessionId` is **PROPOSAL / NOT CALLABLE** until records, routing, safe mode policy and lifecycle are implemented.
- **Contract:** Runtime targeting requires explicit session identity and exact `Read`/`Write`/`Destructive` scope with applicable envelope consent. Handles are invalidated on PIE stop/restart and world replacement. No editor-world default when runtime was requested. Concurrent sessions never share operation state.
- **Acceptance:** Positive: selected PIE worlds and native runtime-managed source movement/trigger changes produce expected current output; test CPU runtime independently of GPU. Negative: stale/ambiguous sessions, unauthorized original/PIE paths and wrong source ownership fail closed; editor and other PIE worlds remain untouched. Lifecycle: source removal, repeated scheduler work, PIE stop and late callbacks preserve lease/identity semantics without retargeting. Security: exact scopes, principal and consent are rechecked. Persistence: runtime state is not presented as a saved editor asset or map.
- **Evidence / DoD / stop:** Record session/world identity, principal class, before/after revisions, invalidation, and no-fallback tests. Stop if the engine cannot provide a stable public session identity; do not add packaged runtime by implication.

## N10-05 — Decide the mode matrix and packaged-runtime scope

**Depends on:** `N10-03`, `N10-04`, `N09-05`.
**Priority:** P3 · **Owner:** Unassigned · **Workflow:** PLANNED
**Implementation:** NOT_IMPLEMENTED · **Validation:** NOT_RUN

- **User outcome:** Make an explicit authorized decision about which editor, GPU, PIE, partitioned, and packaged-runtime modes are in the full goal before claiming coverage.
- **Existing evidence / reuse:** [`EngineWire.uplugin`](../../plugins/EngineWire/EngineWire.uplugin) and [`EngineWire.Build.cs`](../../plugins/EngineWire/Source/EngineWire/EngineWire.Build.cs) define an editor-only plugin boundary; native `/mcp` is optional transport within that architecture, not a packaged runtime service.
- **Scope / non-goals:** Publish a mode-by-engine/module/RHI/world matrix with supported, partial, unsupported, and unvalidated states. Packaged MCP is an unapproved architecture proposal, not automatically implemented and not silently excluded if the user's full goal includes it.
- **Steps / target / API gate:** Reconcile real-RHI findings, PIE lifecycle, N09 fixture, platform/version capability evidence, and explicit product authorization. If packaged MCP is required, define and approve a separate architecture and implementation plan before claiming full coverage; do not fold it into the editor plugin by assumption.
- **Contract:** Each supported mode states principal identity, scopes/consent, availability, concurrency, cancellation, failure, persistence, and teardown. No mode inherits another mode's authorization or evidence.
- **Acceptance:** Positive: every claimed mode has its own passing live evidence and explicit support bounds. Negative: no packaged mode can be marked covered based only on editor transport tests; omitted-required mode remains an open gap. Lifecycle/security/persistence cases are explicit for each mode.
- **Evidence / DoD / stop:** Record who authorized the scope decision, matrix changes, uncovered modes, evidence links, and next approval gate. Stop before packaged architecture or implementation absent separate authorization; do not use a green editor test as packaged acceptance.

## Recommended order and batch boundary

Run N10-01 and N10-04 as independent tracks: the former needs a real RHI and proves public GPU capability; the latter proves PIE world/session isolation. N10-02 and N10-03 extend only the GPU branch. N10-05 waits for both tracks and the real N09 fixture, then makes the explicit mode-scope decision. Keep packaged-runtime MCP unresolved until separately authorized; if it is part of the full goal, it remains an unimplemented gap. N11 continuous contract/security gates apply during every batch; N11 final matrix regression is the later delivery gate.
