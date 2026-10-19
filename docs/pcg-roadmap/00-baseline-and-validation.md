# Baseline and Validation Prerequisites

[Package index](README.md) · [Coverage matrix](coverage-matrix.md) · [Evidence protocol](validation-and-evidence.md)

This document separates existing implementation from the evidence still required before expanding or certifying it. It does not authorize deployment, profile installation or editor process operations.

## Investigated baseline

Snapshot date: **2026-10-19**. Source baseline: `7a6f928db`, feature branch `feat/pcg-reliable-authoring`, plus an uncommitted follow-up that rejects unsafe JSON numbers in typed PCG Int64 setters.

At registration, six tracked files were modified: the PCG parameter staging implementation, its native integer regression, the parameter integration suite, the changelog, the PCG usage guide and a private historical ledger. Preserve those changes. A clean HEAD alone cannot identify the tested working tree; retain file hashes or a sanitized patch fingerprint as well.

### Existing capability baseline

- Generic native node discovery/editing, nested owned settings, native connection compatibility, authored revisions, permission-separated batches and explicit in-memory recovery.
- Native editor mapping/synchronization, including real input/output boundary settings. Point-only subgraph interfaces are already authored through MCP in the workflow fixture.
- Common graph-parameter types, graph-instance/component overrides, reset and stable getter binding.
- Principal-bound observation of unpartitioned, non-runtime-managed editor generation; cleanup, cancellation, native-busy leases and retained terminal records.
- Managed ISM/HISM/actor and root-output summaries, not full point/attribute/intermediate data reads.
- Explicit preservation of shared authority, queue, scope/consent and safe-save contracts.

The earlier T00–T12 implementation history is not a new backlog to restart. Inspect the current [usage guide](../pcg-authoring.md) and code before proposing replacement facilities.

### Evidence freshness

| Evidence | Recorded result | What it establishes |
| --- | --- | --- |
| Latest post-Int64-follow-up static/build/mock batch | Eleven commands passed; 234 unit files / 2,801 tests; 3,831 static parameter cases; optional 2,281/2,281 with no extras; 50 retrieval tests | TypeScript/source contracts, generated-artifact checks, serial build and built-dist mock smoke at that working tree |
| New native Int64 test and extended live parameter cases | NOT_RUN | The C++ regression is present, but its compilation/execution and transport-level acceptance are not established |
| Earlier UE 5.7.4 / 5.8.3 complex editor acceptance | HISTORICAL_REPORTED | Prior continuation records describe passing selected scenarios; original referenced continuation reports are not available in the current workspace |
| Whole-plugin native tests | Six unrelated failures historically matched baseline | No green whole-plugin claim; attribution is not remediation or a waiver |
| Partitioned, GPU, PIE runtime and genuinely missing-PCGEditor environment | Not certified by the editor-local baseline | Separate work packages and actual environments are required |

The combined existing isolated-deployment/build action for the Int64 follow-up was denied before execution because it would overwrite a pre-existing deployment outside the repository. Do not retry through another tool or ask an agent to perform it. PRE-02 remains blocked until an explicitly authorized route is established.

## PRE-01 — Reconcile source, scope and evidence

**Priority:** P0 · **Owner:** Unassigned · **Workflow:** PLANNED

**Implementation:** PARTIAL · **Validation:** Static baseline recorded; evidence reconciliation NOT_RUN.

**Depends on:** None.

**User outcome:** A new owner can identify exactly what exists, what was tested, which reports are available and which remaining target modes must be delivered.

**Investigated reuse:** The current [PCG guide](../pcg-authoring.md), [repository testing guide](../testing-guide.md), [coverage matrix](coverage-matrix.md), current Git state and existing PCG integration/native test files. Historical summaries are leads, not replacement test artifacts.

**Scope and steps:**
1. Record HEAD, branch, worktree file hashes and relevant dirty changes without modifying or committing them.
2. Inventory evidence by source fingerprint, engine/platform, transport, fixture ownership, command and outcome. Reconcile original historical reports if supplied; otherwise retain HISTORICAL_REPORTED and specify a fresh rerun requirement.
3. Freeze the intended coverage denominator. Record Editor, PIE, partitioned/HiGen, GPU, engine/platform and packaged-runtime requirements separately.
4. Classify each gap as absent, partial or unverified; identify existing generic tools that already cover it. Mark candidate interfaces as proposals.

**Contract/permissions:** Documentation and read-only source/evidence work. No live mutation, profile installation or process authorization is implied. Never collect raw credentials or binary crash dumps into portable evidence.

**Acceptance:** Source identity and dirty changes are reproducible; available and missing evidence are distinguishable; no old result is attributed to a later patch; all required modes remain represented in the matrix. Keep the six unrelated native failures separate from new failures.

**Deliverable/DoD:** A source-matched evidence index and updated matrix with scope decisions or explicit open decision gates. Stop if source identity or report provenance cannot be established; do not manufacture a passing baseline.

## PRE-02 — Close the unsafe-number Int64 regression

**Priority:** P0 · **Owner:** Unassigned · **Workflow:** BLOCKED

**Implementation:** IMPLEMENTED · **Validation:** Static/build/mock PASS; native build/live NOT_RUN, deployment authorization blocked.

**Depends on:** `PRE-01`, `PRE-03`.

**User outcome:** Unsafe JSON numbers cannot silently become rounded Int64 defaults or overrides, while safe numbers and exact decimal strings still work.

**Existing implementation and tests:**
- [PCG value staging](../../plugins/EngineWire/Source/EngineWire/Private/Domains/PCG/Parameters/McpPCGParamValue.cpp): `ValidateScalar` rejects out-of-safe-range Int64 numbers before the shared importer.
- [Native integer tests](../../plugins/EngineWire/Source/EngineWire/Private/Tests/PCG/McpPCGIntegerTests.cpp): `EngineWire.PCG.Int64RejectsUnsafeJsonNumbers` and exact readback/storage tests.
- [Parameter integration suite](../../tests/mcp-tools/world/manage-pcg-parameters.test.mjs): scalar/array refusal, no schema/revision change and preserved instance inheritance.

**Scope and steps:** Obtain approval naming the owned deployment/project and permitted build/process operations; verify destination ownership and unrelated edits before copying. Record the source bundle and actual loaded binary identity. Compile and run focused native tests, then the parameter suite through both transports using the same bundle. Preserve the previously denied action as a boundary, not a passed build.

**Contract:** No new action or shared reflection behavior change. Existing typed parameter actions must return `INVALID_PARAMETER_VALUE` before native mutation for unsafe numeric Int64 inputs. Do not weaken the declared decimal-string requirement or widen unrelated tools' numeric semantics.

**Acceptance:** Positive/negative unsafe scalars and mixed arrays are refused; defaults, full array contents, parameter schema and graph revision stay unchanged; failed overrides do not set the override flag. Numeric safe endpoints and exact string MIN/MAX round-trip. The C++ test must actually register and execute; a shell exit alone is insufficient.

**Deliverable/DoD:** Source-matched native build and focused test reports plus passing native/WS parameter reports, with fixture cleanup recorded. No commit or publication is part of this ticket.

**Stop/compensation:** If deployment ownership, permission, source parity or native idle cannot be proved, remain BLOCKED. Do not overwrite an unknown deployment, force-kill an editor, fall back to production, or label unrun tests green. Preserve owned residual assets and failed evidence.

## PRE-03 — Establish the owned validation envelope

**Priority:** P0 · **Owner:** Unassigned · **Workflow:** PLANNED

**Implementation:** PARTIAL · **Validation:** New-batch environment acceptance NOT_RUN.

**Depends on:** `PRE-01`.

**User outcome:** Future API spikes and integration runs have a known project, engine, binary, transport and cleanup owner before any mutation.

**Reuse:** [Source-only project generator](../../scripts/pcg-validation-project.mjs), [isolated runner checks](../../tests/test-runner-isolation.mjs), [PCG fixtures](../../tests/fixtures/pcg/PCGValidationElements.h), existing native/WS integration runner and [shared evidence protocol](validation-and-evidence.md).

**Scope and steps:**
1. Verify a new or explicitly approved owned project; never infer ownership from an old PID or folder name. Preserve existing files and manifests.
2. Verify engine Build.version, actual PCG/PCGEditor compile gates, loaded plugin binary path/hash and matching source bundle. Allocate unused loopback ports; keep capability-token protection enabled.
3. Define a unique asset RunRoot, project-identity assertions, serial live owner and native-idle checks before cleanup or deletion. Do not use global dirty-package saving.
4. Obtain separate permission for any existing-deployment overwrite, normal editor close/restart or temporary scoped profiles. Define restoration/revocation and proof before installation.
5. Record real-RHI requirements for GPU, windowed-editor requirements for graph-tab lifecycle and explicit world identities for later PIE tests.

**Contract:** This is a validation envelope, not a new server, scheduler or permission bypass. Scopes remain exact; tokens are not recorded in logs or evidence. Source investigation can proceed while deployment permission is blocked, but native acceptance cannot.

**Acceptance:** Wrong project/binary/engine/ports are refused before fixtures; no shared cleanup runs; temporary grants, if approved, are restored and revoked; failed startup/test reports survive. A forced PCGEditor-off copied build is labeled a conditional test, not a genuinely missing module.

**Deliverable/DoD:** An owned environment manifest, approved operation boundary, commands/configuration identifiers without secrets, and a verified cleanup protocol. Stop on identity drift, port conflict, unapproved external writes or unknown residual ownership.

## Implementation order and exit

Run PRE-01 first, then establish PRE-03's explicitly approved validation envelope before PRE-02 native/live execution. Evidence/source preparation may proceed independently, but each ticket retains its own outcome. Source planning may proceed while native permission is blocked; source-matched native/live acceptance and the final N11 join must not bypass PRE-02.

No future batch is authorized merely because these documents exist. Follow the shared [validation and evidence](validation-and-evidence.md) contract and retain every unrun layer as NOT_RUN.
