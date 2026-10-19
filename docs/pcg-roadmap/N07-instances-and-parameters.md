# N07 — Instances, Components and Parameters

[Package index](README.md) · [Coverage matrix](coverage-matrix.md) · [Shared validation](validation-and-evidence.md)

**Goal:** Complete structured component/graph-instance setup and concurrent parameter workflows without using execution or Python as an asset-creation side channel.

Common graph parameter reads, scalar/array writes, reset, stable rename/getter bindings and existing-instance overrides already exist. This batch extends their missing lifecycle/type/concurrency boundaries rather than reimplementing them. Metadata Attributes remain N05 data, not graph parameters.

## N07-01 — Discover and configure exact PCG components without execution

**Priority:** P1 · **Owner:** Unassigned · **Workflow:** PLANNED

**Implementation:** PARTIAL · **Validation:** Extended setup/binding workflow NOT_RUN.

**Depends on:** `PRE-03`.

**User outcome:** Locate/create a component and bind its intended graph without triggering generation merely to obtain a component path.

**Reuse:** [Component helpers](../../plugins/EngineWire/Source/EngineWire/Private/Domains/PCG/McpPCGWorld.cpp), [legacy execution setup](../../plugins/EngineWire/Source/EngineWire/Private/Domains/PCG/McpPCGComponentActions.cpp), [exact resolver/principal](../../plugins/EngineWire/Source/EngineWire/Private/Domains/PCG/Execution/McpPCGExecContext.cpp), existing actor/SCS/component tools. Blueprint templates must remain owned by SCS nodes.

**Steps/targets:** Inventory existing structured creation/binding tools and add only a missing PCG read/configuration surface. Return exact component/world/map, graph/interface, generation mode and native busy state. Require a provable authorized target for scoped inventory, or apply existing trusted native path predicates to enumeration; do not invent a TS authority mirror. Separate placed instances from Blueprint templates/CDOs.

**Proposal/policy:** Component inventory Read/none; explicit graph/mode/bounds/seed configuration Write/none only where effects remain non-destructive. No implicit generate/cleanup. If native reassignment releases resources, require a separately explicit destructive phase or refuse until the caller performs cleanup. Respect active native work/leases and declare affected owner/save behavior.

**Acceptance:** Empty actor, multiple PCG components, existing graph/interface and Blueprint template/placed instance; exact locator and path refusals; binding without task scheduling; busy reassignment; no accidental CDO/shared mutation. Save/compile/reload the appropriate owners and prove old valid execution calls still work on both transports.

**DoD/stop:** Structured setup recipe with native/live identity and persistence evidence. Stop if an existing tool can already satisfy the workflow and only add its missing tests/documentation; never add a duplicate component framework.

## N07-02 — Create and rebind graph-instance assets

**Priority:** P1 · **Owner:** Unassigned · **Workflow:** PLANNED

**Implementation:** PARTIAL · **Validation:** Structured factory/rebind workflow NOT_RUN.

**Depends on:** `N07-01`.

**User outcome:** Create a reusable graph-instance asset and choose how overrides behave when its parent changes.

**Reuse:** [Parameter targets](../../plugins/EngineWire/Source/EngineWire/Private/Domains/PCG/Parameters/McpPCGParamTarget.cpp), [parameter integration factory fixture](../../tests/mcp-tools/world/manage-pcg-parameters.test.mjs), generic asset tools and safe-save helpers. Current tests create the graph instance through Python factory; existing read/edit support does not supply a structured creation contract.

**Steps:** Prove public native factory/construction and parent-assignment APIs. Add a bounded creation/rebind capability only if existing asset tools cannot express it. Validate the new owner and parent graph/interface before creation; reject cycles/incompatible parent types. Define inheritance chain, root default, immediate inherited effective value and local override distinctly while preserving old `defaultValue` meaning.

**Contract/policy:** Candidate create/bind operations are PROPOSALS / NOT CALLABLE. Write for additive/non-destructive work; classify override loss or resource release explicitly, never infer a grant from another scope. Rebind requires an explicit override policy, such as reset or preserve compatible GUID-matched values; do not silently match by a reused parameter name. Report created/committed/saved/residual state and selected save owner.

**Acceptance:** Fresh asset, duplicate destination, invalid parent/class/cycle, reset/preserve policy, compatible/incompatible GUID/schema, nested inheritance where natively supported, independent component bindings and real save failure. No Python asset creation in the new positive workflow; cold-load the asset and verify effective values and override flags.

**DoD/stop:** Public-API linkage plus native/WS structured creation and rebind evidence. Stop on unavailable APIs or unprovable override migration; do not use private property offsets, copy internal factory implementations or claim cross-owner rollback.

## N07-03 — Add target-specific optimistic concurrency

**Priority:** P1 · **Owner:** Unassigned · **Workflow:** PLANNED

**Implementation:** PARTIAL · **Validation:** Setter target-token behavior NOT_RUN.

**Depends on:** `N07-02`.

**User outcome:** Detect conflicting edits to an instance even when its parent graph's authored revision did not change.

**Reuse:** [Current execution fingerprint](../../plugins/EngineWire/Source/EngineWire/Private/Domains/PCG/Execution/McpPCGExecContext.cpp), [parameter action preflight](../../plugins/EngineWire/Source/EngineWire/Private/Domains/PCG/Parameters/McpPCGParamActions.cpp), reflection fingerprints/read budgets. `GetPCGInstanceRevision` currently accepts a component and includes effective parameter hashes, override flags, seed and grid; it is not a general graph-instance API.

**Steps:** Define a bounded target fingerprint for graph/interface/component identity, native schema IDs, effective values and override flags, with component-specific authored inputs where applicable. Generalize reusable helpers by responsibility instead of duplicating serialization. Expose a clearly named target token alongside the existing parent graph token and optionally compare it before native mutation.

**Contract:** Proposed `expectedTargetRevision`/returned target revision are not callable fields yet. Preserve existing `expectedGraphRevision` and valid old calls; do not add graph/instance keys to the global `expectedRevisions` protocol. No partial token on budget exhaustion. Tokens are process-local integrity checks, not authentication or durable IDs.

**Acceptance:** Two clients read the same instance, one changes an override and the other's token is refused without change; parent-default propagation, reset flags, schema/class reinstancing and same-name GUID replacement invalidate appropriately. Compare independent instance assets and components, active observations, stale world/target and exhausted capture on native/WS. Cross-principal operation records remain isolated.

**DoD/stop:** Native fingerprint and live conflict tests establish the intended token semantics. Stop rather than publish a hash of only parent state or silently accept incomplete captures.

## N07-04 — Extend proven native types and controlled schema evolution

**Priority:** P2 · **Owner:** Unassigned · **Workflow:** PLANNED

**Implementation:** PARTIAL · **Validation:** Additional type/migration matrix NOT_RUN.

**Depends on:** `N07-03`.

**User outcome:** Use the actual target engine's supported graph-parameter types and make explicit, validated schema changes.

**Reuse:** [Descriptor builder](../../plugins/EngineWire/Source/EngineWire/Private/Domains/PCG/Parameters/McpPCGParamSchema.cpp), [typed staging/commit](../../plugins/EngineWire/Source/EngineWire/Private/Domains/PCG/Parameters/McpPCGParamValue.cpp), [exact readback](../../plugins/EngineWire/Source/EngineWire/Private/Domains/PCG/Parameters/McpPCGParamTarget.cpp). Current types cover common scalars/one array and Vector/Rotator/Transform structs; native Property Bag enums alone do not establish usable PCG/UI/setter support for every type/container.

**Steps:** Inventory actual native PCG parameter type/container support first, including Text/unsigned or further structs only where public APIs and round-trip semantics are proven. Add lossless codecs and unsupported diagnostics. For type/container/schema evolution, first produce a bounded conversion/reference-impact preview and decide GUID continuity; validate affected effective values/overrides before explicit commit. Preserve existing exact Int64 and finite-number rules.

**Policy/receipt:** Non-destructive parameter changes retain Write; lossy replacement/removal needs an explicitly reviewed destructive operation/consent, never hidden coercion. Use target/graph preconditions and selected-owner saves. Cross-instance propagation can be non-atomic; report per-owner outcomes/residuals rather than pretending a graph transaction rolls back all instances.

**Acceptance:** Every added scalar/container has exact defaults, instance/component override, reset, empty and invalid-element cases plus cold-load. Numeric extrema, enum underlying values, reference restrictions, localization/struct semantics and rejected lossy conversion are explicit. Required unsupported types remain uncovered rather than being counted as a passed refusal.

**DoD/stop:** A real supported-type matrix, codecs and source-matched native/live/persistence reports. Stop if native setters cannot represent the type or bounded migration cannot establish affected state; no unsafe bag mutation or shared reflection widening for convenience.

## N07-05 — Verify propagation, references and selected-owner persistence

**Priority:** P2 · **Owner:** Unassigned · **Workflow:** PLANNED

**Implementation:** PARTIAL · **Validation:** Broader propagation/reference matrix NOT_RUN.

**Depends on:** `N07-04`.

**User outcome:** Understand which instances and getter references a default/schema edit affects, without silent GUID breakage or undocumented save requirements.

**Reuse:** `FindPCGParameterReferences`, native rename/reset/override APIs in the [parameter actions](../../plugins/EngineWire/Source/EngineWire/Private/Domains/PCG/Parameters/McpPCGParamActions.cpp), [parameter suite](../../tests/mcp-tools/world/manage-pcg-parameters.test.mjs), [real-save suite](../../tests/mcp-tools/world/manage-pcg-save-failure.test.mjs) and [cold-load suite](../../tests/mcp-tools/world/manage-pcg-cold-load.test.mjs). Current reference diagnosis is loaded-graphs-only.

**Steps:** Cover multiple assets/components and inherited-vs-local values after add/change/rename/remove/reset. Design bounded, path-authorized dependency discovery for unloaded candidates using public asset APIs only where safe; package dependency is not proof of a specific parameter GUID reference. Never claim project-wide unused status from a loaded scan. Define honest diagnostics/strict modes when completeness cannot be established.

**Contract/policy:** Reference reads require authorized targets; no automatic whole-project loading or saving all dirty packages. Removal remains explicit Destructive/consent. Preserve backward-compatible loaded-reference semantics unless a separately approved change is required. Return which owners were changed/saved/unknown and identify partial propagation, not global rollback.

**Acceptance:** Two independent instances and components, inherited overrides, renamed/deleted/recreated same-name GUIDs, getter references in subgraphs, unloaded candidate handling, source budget/authority limits and save failure on one owner. Cold-load each intended owner independently and assert defaults/effective values/flags, stable getter GUID and graph output.

**DoD/stop:** Source-matched propagation and persistence matrix plus a documented reference-completeness boundary. Stop on unapproved traversal, ambiguous reference proof or failed propagation; preserve residuals and do not silently cascade delete nodes.

## Implementation order and exit

Complete exact setup → structured instances → target revisions before broad schema evolution. Reference/persistence closure follows the actual added types and interfaces, not every hypothetical Property Bag enum. New standalone-asset behavior is never inferred from the component-only fingerprint helper.

The batch completes only when the selected lifecycle/type/reference rows have actual native, two-transport and relevant cold-load evidence. Existing basic parameter reads are not a new feature delivery, and no multi-instance disk transaction is promised.
