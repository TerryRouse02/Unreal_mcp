# N11 — Compatibility and Delivery

N11 establishes continuous compatibility/security discipline and a final evidence-based delivery gate. It does not turn unrun checks into passes, erase unrelated native failures, authorize deployment, or make branch history private. Proposed contracts remain **PROPOSAL / NOT CALLABLE** until implemented through the canonical capability records and approved routes.

## Current boundary and related plans

- The support baseline is documented in [`00-baseline-and-validation.md`](00-baseline-and-validation.md) and [`coverage-matrix.md`](coverage-matrix.md). Historical UE 5.7.4/5.8.3 acceptance is separate from current patch evidence; referenced original reports are absent here.
- The current snapshot reports 11 static/build/mock commands passing, but the new native/live patch was not run because overwriting an existing isolated deployment was denied. Six unrelated native baseline failures remain; do not rewrite tests to green or demand unrelated refactoring as a PCG deliverable.
- Reuse the canonical PCG capability entry point [`manage-pcg.index.ts`](../../src/tools/catalog/capabilities/records/world/manage-pcg.index.ts), execution record [`manage-pcg.execution.data.ts`](../../src/tools/catalog/capabilities/records/world/manage-pcg.execution.data.ts), and generated registry/checks. The generated action reference is output, not an edit target. A public API change must preserve the single `unreal` gateway, `manage_pcg` routing, pre-queue security gate, and single game-thread dequeuer.
- Related plans: [`README.md`](README.md), [`validation-and-evidence.md`](validation-and-evidence.md), [`N05-data-observability.md`](N05-data-observability.md), [`N06-generic-authoring.md`](N06-generic-authoring.md), [`N07-instances-and-parameters.md`](N07-instances-and-parameters.md), [`N08-scene-inputs-and-output-assets.md`](N08-scene-inputs-and-output-assets.md), [`N09-partitioned-and-hierarchical.md`](N09-partitioned-and-hierarchical.md), and [`N10-gpu-and-runtime.md`](N10-gpu-and-runtime.md).

## Continuous protocol for N11-02 through N11-04

Treat N11-02 as a continuous gate, not a dependency that blocks implementation tickets. Refer to this section as the **N11 protocol**: preserve canonical records and generated-output discipline; exact scopes (`Read`, `Write`, `Destructive`, with `Admin` only as wildcard); envelope consent; source-size/folder budgets; real missing-module checks; both transport/old-call parity; and ticket-specific validation in [`validation-and-evidence.md`](validation-and-evidence.md). N11-03 remains the final integrated matrix gate.

## Tickets

## Work-package slicing

**N11-01 inventory work units**
1. Enumerate engine versions and optional module combinations actually targeted by the plugin.
2. Map each PCG operation to its canonical record, route, implementation, and test.
3. Separate editor, PIE, GPU, partitioned, and packaged mode rows.
4. Record transport coverage independently for WebSocket and native MCP.
5. Mark implementation status separately from static, build, live, and cold-load validation.
6. Preserve unknown and not-run rows where evidence is absent or inaccessible.
7. Identify historical evidence as historical and list missing report references plainly.
8. Record the exact availability and failure behavior expected per capability row.
9. Stop before publishing a supported label without source and validation evidence.

**N11-02 continuous-gate work units**
1. Confirm every proposed operation originates in the canonical capability record source.
2. Regenerate native and TypeScript contract outputs; never hand-edit generated artifacts.
3. Run contract parity checks for both supported transports and old-call compatibility.
4. Test exact scope membership and envelope consent, including explicit denial cases.
5. Verify principal-bound operation identity, quotas, and path/value checks remain intact.
6. Exercise unknown actions and absent optional modules as fail-closed outcomes.
7. Enforce pure-source line and private-folder file-count budgets during implementation.
8. Keep the one pre-queue gate and the one game-thread dequeuer invariant.
9. Treat any security or transport mismatch as a stop condition, not a warning.

**N11-03 final matrix work units**
1. Build a test list from every matrix row marked as a coverage claim.
2. Include actual source, generated-contract, static, compile, and live evidence as applicable.
3. Exercise WebSocket and native MCP separately; do not transfer a pass across transports.
4. Include failure, denied-scope, consent, cancellation, target-loss, and retry behavior.
5. Run real-RHI tests for GPU claims and real missing-module configurations for optionality claims.
6. Run persistence, save-failure, and cold-load checks where the feature changes durable state.
7. Include the N05-06 intermediate inspection/delivery gate and N06-06 multi-asset boundary.
8. Keep unrelated baseline failures listed without rewriting assertions or hiding failures.
9. Stop when an unapproved destructive environment or deployment overwrite would be required.

**N11-04 documentation/privacy work units**
1. Search user-facing examples for route names that remain proposal or not callable.
2. Verify each asserted behavior has a matching implementation and matrix row.
3. Check all Markdown source links are repository-relative and resolve to committed sources.
4. Remove machine-specific absolute paths, private reports, crash data, and production identifiers.
5. Scan for raw tokens, credentials, account names, and sensitive environment values.
6. Preserve caveats for unsupported, unknown, partial, and unvalidated modes.
7. Make evidence references useful without copying private source reports into public docs.
8. Confirm the usage guide describes scopes, consent, failure, ownership, and persistence honestly.
9. Stop publication if privacy or authorization cannot be established.

**N11-05 handoff work units**
1. Inventory the intended file allowlist and verify no unrelated files are included.
2. Review current branch history for internal ledger or private content exposure.
3. Recognize that deleting or excluding a ledger file does not sanitize past history.
4. Record tests, evidence, unresolved failures, and exact support claims for the reviewer.
5. Ask for explicit authorization before any commit, push, PR, or history operation.
6. If history remediation is required, prepare a separate preservation and recovery proposal.
7. Keep the existing local ledger and user changes intact until separately instructed.
8. Make the final go/no-go decision based on privacy, evidence, and destination authorization.
9. Stop at local preparation; do not perform remote or history changes under this roadmap alone.

## N11-01 — Inventory supported versions and capabilities

**Depends on:** `PRE-01`.
**Priority:** P1 · **Owner:** Unassigned · **Workflow:** PLANNED
**Implementation:** PARTIAL · **Validation:** NOT_RUN

- **User outcome:** See exactly which engine versions, optional modules, transports, PCG modes, and data types have implementation and validation evidence.
- **Existing evidence / reuse:** [`EngineWire.uplugin`](../../plugins/EngineWire/EngineWire.uplugin), [`EngineWire.Build.cs`](../../plugins/EngineWire/Source/EngineWire/EngineWire.Build.cs), canonical [`manage-pcg.index.ts`](../../src/tools/catalog/capabilities/records/world/manage-pcg.index.ts) and [`manage-pcg.execution.data.ts`](../../src/tools/catalog/capabilities/records/world/manage-pcg.execution.data.ts), and existing compatibility tests such as [`manage-pcg-compatibility.test.mjs`](../../tests/mcp-tools/world/manage-pcg-compatibility.test.mjs).
- **Scope / non-goals:** Maintain a capability inventory with separate implementation and validation status. Do not infer support from version numbers, declarations, old reports, or another transport's test.
- **Steps / target / API gate:** Update the coverage matrix using confirmed engine/module/transport/RHI/world evidence. Candidate capability labels are documentation-only and are not public callable names.
- **Contract:** For each row state availability, exact scope, consent needs, concurrency, failure behavior, ownership, and persistence. Unknown capability means fail closed and report unknown/unsupported; no version-based optimistic fallback.
- **Acceptance:** Positive: every claimed row identifies its code and test evidence. Negative: unsupported optional modules and untested modes remain explicit. Lifecycle/security/persistence claims have named tests and evidence, not a single global checkbox.
- **Evidence / DoD / stop:** Preserve evidence date, engine/module/transport and test layer. Stop if evidence cannot be located; retain `UNKNOWN` or `NOT_RUN` rather than guessing.

## N11-02 — Keep contract, security, and old-call gates continuous

**Depends on:** `N11-01`.
**Priority:** P1 · **Owner:** Unassigned · **Workflow:** PLANNED
**Implementation:** PARTIAL · **Validation:** NOT_RUN

- **User outcome:** Prevent new PCG routes from bypassing the established contract generator, security boundary, compatibility behavior, or existing caller protections.
- **Existing evidence / reuse:** Root [`AGENTS.md`](../../AGENTS.md) describes canonical records, generated artifacts, and plugin authorization. Reuse [`McpPCGExecActions.cpp`](../../plugins/EngineWire/Source/EngineWire/Private/Domains/PCG/Execution/McpPCGExecActions.cpp), [`McpPCGExecution.h`](../../plugins/EngineWire/Source/EngineWire/Private/Domains/PCG/Execution/McpPCGExecution.h), existing manage-pcg tests, and the compatibility/parameter checks in the repository.
- **Scope / non-goals:** Add targeted regression gates for every approved new contract; keep old calls and unknown actions fail-closed. Do not make an unrelated refactor or rewrite existing assertions to obtain green results.
- **Steps / target / API gate:** Extend canonical records, regenerate through project tooling, and add tests for both WebSocket and native MCP plus old-call compatibility. Any new symbol or route is **PROPOSAL / NOT CALLABLE** until generated and authorized end-to-end.
- **Contract:** Recheck exact scope membership, envelope consent, principal binding, path/value validation, quotas and generated native registry parity. Read/Write/Destructive never imply one another; Admin alone is the wildcard. Failures and unknown routes do not mutate or expose prior receipts. Explicitly verify Node 20/26 versus a local Node 24 result, the intended engine/platform cells, and generated-output fidelity instead of inheriting claims from package metadata.
- **Acceptance:** Positive: approved calls behave consistently on each supported transport. Negative: denied scopes, missing consent, malformed/unknown actions, old removed calls, and missing optional modules fail closed. Lifecycle: retry/cancel/target loss cannot duplicate work. Persistence: save failure and cold-load behavior retain their separate assertions.
- **Evidence / DoD / stop:** N11 protocol gates pass for changed contracts, or blockers are listed with exact known baseline boundary. Stop on a parity/security regression; do not bypass generated checks or suppress historical failures.

## N11-03 — Run final source-parity and actual matrix regression

**Depends on:** `PRE-02`, `N11-02`, `N05-04`, `N05-06`, `N06-05`, `N06-06`, `N07-05`, `N08-05`, `N09-05`, `N10-05`.
**Priority:** P1 · **Owner:** Unassigned · **Workflow:** PLANNED
**Implementation:** PARTIAL · **Validation:** NOT_RUN

- **User outcome:** Decide completion from actual source, contract, and live matrix evidence rather than from planning status or aggregate percentages.
- **Existing evidence / reuse:** Reuse existing cases in [`tests/mcp-tools/world/`](../../tests/mcp-tools/world/), native tests under [`Private/Tests/PCG/`](../../plugins/EngineWire/Source/EngineWire/Private/Tests/PCG/), [`tests/fixtures/pcg/`](../../tests/fixtures/pcg/), and [`scripts/pcg-validation-project.mjs`](../../scripts/pcg-validation-project.mjs). See baseline snapshot details above and in `00-baseline-and-validation.md`.
- **Scope / non-goals:** Run the approved matrix for each claimed version, module, transport, mode, security scope, and lifecycle. This does not authorize plugin deployment, overwrite of existing isolated installations, or unrelated native cleanup.
- **Steps / target / API gate:** Reconcile every matrix row with source/record/generated parity; execute relevant static, build, mocked, live, cold-load, save-failure, old-call, and transport checks. Distinguish NOT_RUN from failed, unsupported, or not applicable.
- **Contract:** Matrix cases use the documented principal, exact scope and consent, bounded budgets, and operation identities. Tests must not leak credentials or use unspecified projects. Concurrent mutation and partial failures must produce truthful receipts.
- **Acceptance:** Positive: each claimed mode has required real-engine/live evidence. Negative: mocks cannot satisfy real RHI, actual missing-module, or live persistence rows; the artificial no-PCGEditor conditional is not a missing-module test. Lifecycle/security/persistence pass per row. Historical 5.7.4/5.8.3 evidence remains historical unless re-run.
- **Evidence / DoD / stop:** Produce a local per-row result, environment class, exact command/test, timestamps, receipts/log references and known baseline failures; external sharing requires separate authorization. Stop on an unapproved destructive setup or deployment overwrite; record blocked checks as NOT_RUN and do not claim full coverage.

## N11-04 — Freeze portable usage, evidence, and privacy

**Depends on:** `N11-03`.
**Priority:** P2 · **Owner:** Unassigned · **Workflow:** PLANNED
**Implementation:** NOT_IMPLEMENTED · **Validation:** NOT_RUN

- **User outcome:** Provide portable user guidance that describes only callable, validated behavior and shares evidence without leaking secrets or private environment details.
- **Existing evidence / reuse:** Roadmap pages [`README.md`](README.md), [`coverage-matrix.md`](coverage-matrix.md), [`00-baseline-and-validation.md`](00-baseline-and-validation.md), and shared [`validation-and-evidence.md`](validation-and-evidence.md) separate plans from support claims. Public usage should also align with [`docs/pcg-authoring.md`](../pcg-authoring.md).
- **Scope / non-goals:** Review source links, current API examples, evidence references, privacy/redaction, and unsupported-mode warnings. No external publication, generated-reference edits, private report copying, or machine-specific paths.
- **Steps / target / API gate:** Remove or label every proposed/not-callable example; link only portable repository sources and approved evidence. Confirm no credentials, raw tokens, private reports/crash dumps, or named production projects/accounts.
- **Contract:** Only implemented, authorized, validated operations may be presented as usable. Any sample states scope/consent, availability, concurrency, failure, ownership, and persistence behavior. Examples contain no real secrets.
- **Acceptance:** Positive: each usage statement maps to a callable record and validation row. Negative: proposed route, unsupported mode, unrun test, or missing report is never described as supported. Lifecycle/security/persistence caveats are visible. Portability checks catch machine paths and sensitive identifiers.
- **Evidence / DoD / stop:** Record reviewed files, link check, privacy scan, and unresolved caveats. Stop and remove a claim from publication if evidence or authorization is missing; do not manufacture replacement evidence.

## N11-05 — Prepare an authorized clean-history single-PR handoff

**Depends on:** `N11-04`.
**Priority:** P2 · **Owner:** Unassigned · **Workflow:** PLANNED
**Implementation:** NOT_IMPLEMENTED · **Validation:** NOT_RUN

- **User outcome:** Prepare one reviewable, privacy-checked handoff only after explicit authorization for the destination and history state.
- **Existing evidence / reuse:** The PCG roadmap is the local planning/evidence source; existing local branch history may include an internal old task ledger. Excluding a file from the current file list or deleting it later does not sanitize published Git history.
- **Scope / non-goals:** Local inventory and handoff checklist only until separately approved. No commit, push, PR creation, branch deletion, history rewrite, worktree creation, automatic ledger removal, or remote action is authorized by this plan.
- **Steps / target / API gate:** Check intended changed-file allowlist, portable links, sensitive-content scan, tests/evidence summary, and history exposure with the authorized reviewer. If history cleanup is required, obtain a separate explicit authorization and follow an approved preservation/recovery plan before any rewrite or remote publication.
- **Contract:** The handoff states exact support claims, security scope/consent, availability, concurrency/failure semantics, lifecycle, and persistence. Only public approved callable APIs may be described. No private reports or tokens enter the PR.
- **Acceptance:** Positive: reviewer can reproduce the stated checks and verify one bounded set of files. Negative: any unexpected file, exposed ledger/history content, missing authorization, or unresolved critical evidence blocks publication. No commit/push/PR occurs without the user's additional explicit authorization.
- **Evidence / DoD / stop:** Produce a local checklist, reviewed file list, evidence inventory, and go/no-go decision. Stop before remote publication if history cannot be made acceptably private without a separately authorized history operation; preserve existing local work and ledger.

## Recommended order and batch boundary

N11-01 establishes the capability inventory; N11-02 then runs continuously as the **N11 protocol** while N05–N10 work proceeds, but is not a hard prerequisite for those implementation tickets. N11-03 is the final integrated gate after all named feature tickets and PRE-02. N11-04 documents only results that survive that gate. N11-05 remains local preparation until separate explicit authorization for commits, push, PR, or any history operation. Stop a batch at missing evidence, privacy, security, or authorization boundaries; never convert `NOT_RUN` or unrelated baseline failures into success.
