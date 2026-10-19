# PCG Capability Coverage Matrix

[Package index](README.md) · [Baseline](00-baseline-and-validation.md) · [Evidence protocol](validation-and-evidence.md)

**Snapshot:** 2026-10-19. This is the initial capability inventory for the work packages, not measured percentage coverage. Extend it when discovery finds additional required node families or workflows; do not shrink the denominator to hide unsupported work.

Implementation states below describe the current capability, while ticket metadata describes its new deliverable. `HISTORICAL_REPORTED` runtime results need original source-matched artifacts or a fresh run. New tickets have no positive runtime evidence merely because they appear here.

## Capability inventory

| ID | Required workflow | Current implementation | Current evidence/limit | Owning work orders |
| --- | --- | --- | --- | --- |
| C01 | Identify exact source, binary, project and support target | PARTIAL | Current source/static results known; historical continuation evidence reconciliation open | PRE-01, PRE-03 |
| C02 | Reject unsafe Int64 numeric defaults/overrides without mutation | IMPLEMENTED | Uncommitted fix; static/build/mock pass, new native/live NOT_RUN | PRE-02 |
| C03 | Discover installed/loaded PCG classes and actual edit support | PARTIAL | Loaded-class discovery exists; no complete unloaded Blueprint/extension support inventory | N06-01, N11-01 |
| C04 | Inspect editable settings, owned objects and instance-dependent schema | PARTIAL | Class schema and graph settings exist; dependent selector/instance discovery needs work | N06-01, N06-02 |
| C05 | Create/read/edit native graph structure and validated edges | IMPLEMENTED | Existing generic path and historical selected editor workflows; broader families unverified | N06-03, N11-03 |
| C06 | Revision-checked atomic single-graph edits and explicit recovery | IMPLEMENTED | Native-only batch boundaries and non-atomic save limits remain intentional | N06-03, N06-04, N11-03 |
| C07 | Author subgraph boundaries and preserve native model/UI mapping | PARTIAL | Point-only input/output Pins already authored through MCP; richer interface propagation unverified | N06-03, N06-05 |
| C08 | Configure weighted and attribute-driven selectors, class changes and resources | PARTIAL | Single-mesh convenience and initialized MeshEntries writes exist; broader selectors and switch effects unverified | N06-02 |
| C09 | Author Branch/Switch/Select, dynamic interfaces and loop/nested stacks | PARTIAL | Generic native creation/settings exist; family-complete semantic tests absent | N06-03, N05-05 |
| C10 | Use controlled custom Blueprint Elements/settings | PARTIAL | Native wrapper fixture exists; arbitrary Blueprint-derived settings callbacks are not sandboxed | N06-04 |
| C11 | Author comments/layout/editor organization without losing authored state | PARTIAL | Positions and preservation/readback exist; full organization workflow not established | N06-05 |
| C12 | Discover/configure components and bind graphs without generating | PARTIAL | Existing generic component tools and legacy execute can create/bind; dedicated structured lifecycle is incomplete | N07-01 |
| C13 | Create/rebind graph-instance assets and preserve intended overrides | PARTIAL | Existing instance assets read/edit; current fixture creates assets through Python factory | N07-02 |
| C14 | Detect stale instance-override edits independently of parent graph revision | PARTIAL | Component observation fingerprint exists; setter contract exposes parent graph revision only | N07-03 |
| C15 | Use the target engine's supported native graph-parameter types | PARTIAL | Common scalar/array types; Struct limited to Vector/Rotator/Transform; extra native types need API/codec checks | N07-04 |
| C16 | Evolve schema/defaults/references across instances and save owners honestly | PARTIAL | Add/set/rename/remove/reset and loaded references exist; migration and complete propagation evidence missing | N07-04, N07-05 |
| C17 | Observe editor-local generation, timeout, cancellation and cleanup | IMPLEMENTED | Reliable path deliberately unpartitioned/non-runtime-managed; historical selected scenarios only | PRE-02, N11-03 |
| C18 | Enumerate root datasets, domains and attribute schema | NOT_IMPLEMENTED | Current root output is pin/class/count/tags, not typed dataset schema | N05-01, N05-02 |
| C19 | Read bounded typed Point/Param rows and effective attributes | NOT_IMPLEMENTED | Product transform samples are not point/metadata rows | N05-03 |
| C20 | Maintain data-page identity and invalidate stale snapshots safely | NOT_IMPLEMENTED | Authored revisions/operation leases exist but are not a generated-data paging service | N05-04 |
| C21 | Inspect node inputs/outputs by node and execution stack | NOT_IMPLEMENTED | UE public declarations identified; link, capture ownership and lifetime not proved | N05-05, N05-06 |
| C22 | Inspect warnings/errors, cache use and execution timing | PARTIAL | Visual-log warnings/errors exist; public inspection/timing APIs need supported implementation and evidence | N05-05, N05-06, N10-03, N11-01 |
| C23 | Validate Spline/Grid/Transform/filter/spawner workflows | PARTIAL | Strong historical owned fixture; not every node/type/mode or current-patch runtime verification | N06-03, N08-01, N11-03 |
| C24 | Validate Landscape/Surface/Texture/Mesh/Actor/Volume input families | PARTIAL | Node wrappers/generic authoring exist; complete quantitative scene-source workflows absent | N08-01 |
| C25 | Inspect managed resource identities, ownership and provenance | PARTIAL | Counts, actor descendants, mesh paths and bounded transforms exist; full resource-level provenance not exposed | N08-02 |
| C26 | Detach/bake/export intentionally durable generated products | PARTIAL | Engine/public asset tools are candidates; no complete PCG ownership/persistence workflow certified | N08-03, N08-05 |
| C27 | React correctly to world-source changes, tracking and regeneration | PARTIAL | Native refresh/dirty behavior exists; authored/instance revisions do not certify world-input freshness | N08-04 |
| C28 | Save/reload/cold-start graph, instance and generated-asset workflows | PARTIAL | Historical complex CPU editor acceptance; new types, modes and current follow-up need evidence | N07-05, N08-05, N11-03 |
| C29 | Discover original/local components, grids and loaded/unloaded cells | NOT_IMPLEMENTED | Grid-size writes and generic inventory are not a complete partition manifest | N09-01, N09-02 |
| C30 | Aggregate partitioned/HiGen generation, cancellation and cleanup | NOT_IMPLEMENTED | New completion path refuses partitioned components; legacy scheduling is insufficient | N09-03, N09-04, N09-05 |
| C31 | Execute and verify GPU/mixed CPU-GPU graphs with explicit readback | UNKNOWN | Not certified; transfer flags or native completion alone do not establish GPU correctness | N10-01, N10-02, N10-03 |
| C32 | Configure and observe PIE runtime generation in the intended world | NOT_IMPLEMENTED | Current exact resolver selects editor world; runtime-managed completion is refused | N10-04 |
| C33 | Offer MCP inside a packaged standalone application, if required | UNKNOWN | Editor-only architecture; explicit scope/architecture decision required | N10-05 |
| C34 | Preserve both transports, old calls, exact scopes and consent | PARTIAL | Shared implementation and historical authority tests; every new capability adds required cases | N11-02, N11-03 |
| C35 | Maintain engine/platform/optional-module support matrix | PARTIAL | Historical tested subset; no universal supported-version/platform certification | N11-01, N11-03 |
| C36 | Publish portable evidence and one clean consolidated contribution | PARTIAL | Private history/publication boundary unresolved; no publication authorized | N11-04, N11-05 |
| C37 | Reuse/duplicate a graph or extract a selected fragment with explicit interface mapping | PARTIAL | Generic whole-asset duplication and subgraph creation exist; selected-fragment extraction not certified | N06-06 |

## Required node/data family expansion

Keep families distinct from convenience action names. The generic class/settings path may cover a class without a bespoke action; discovery and deterministic behavior tests must establish that support.

| Family | Representative workflow | Planned evidence |
| --- | --- | --- |
| Point creation and transforms | Grid, transform, bounds, density, copy/merge | Exact fields/counts and fixed-seed repeat, typed pages |
| Spatial sampling and projection | Spline, surface, landscape, volume, mesh, texture | Owned sources with known geometry/masks; coordinate and tolerance assertions |
| Attributes and selectors | Create/copy/rename/filter/cast, property-vs-attribute, domains/defaults | Metadata schema and effective values, invalid conversions, no silent coercion |
| Flow control | Switch/branch/select, loops, multi-input and nested subgraphs | Native pins, inactive/executed distinction, stack identity and output assertions |
| Resource selection/spawning | Weighted/attribute selectors, ISM/HISM, actors and other supported products | Correct selected resource, ownership, no accumulation and cold persistence |
| Extensibility | Native extension settings, Blueprint Element wrapper and guarded custom settings | Discoverable supported boundary, no arbitrary callback sandbox claim |
| Execution grids | Unpartitioned, partitioned, hierarchical and changing loaded-cell sets | Per-mode native lifecycle and honest partial/unknown aggregation |
| Execution backends | CPU, GPU/mixed graphs, PIE runtime | Real backend/world evidence, explicit readback and teardown |

This is a seed inventory, not an assertion that every installed node was enumerated. N06-01/N11-01 must record class/module availability and unsupported reasons for the actual target installation.

## Matrix axes and evidence records

Expand a capability row into target cells as needed:

```text
capabilityId / nodeFamilyOrClass / dataTypeOrDomain
engineVersion / platform / optionalModules
mode(editor-local, partitioned, HiGen, GPU, PIE, packaged-decision)
transport(native HTTP/SSE, TypeScript stdio/WebSocket)
implementationState / static / nativeBuild / nativeTests / live / cold
sourceFingerprint / evidenceRunId / limitations / owner
```

Use a coverage record only for an actual cell. Do not populate all engine/platform combinations with a copied result. Older supported engines may legitimately expose an explicit availability refusal for a new API; that proves compatibility gating, not delivery of that API on the older engine.

Distinguish these facts:

- PCG disabled correctly starts/refuses: a module-compatibility assertion, not a positive PCG generation case.
- PCGEditor API forced off in a copied build: conditional branch evidence, not a real missing module or deterministic diagnostics-unavailable environment.
- Windowed editor API lifecycle: model/mapping evidence, not manual visual or GPU rendering certification.
- Root-output point count: summary, not all intermediate points or all generated resources.
- Int64 string round-trip: not proof that unsafe numeric input is rejected; PRE-02 supplies that missing evidence.

## Update and completion rules

1. Link a changed capability to a bounded work order and real source files; keep implementation and validation independent.
2. Add new rows when the target inventory reveals missing functionality. Never turn a known refusal into an implemented feature.
3. Keep historical/missing reports labeled, preserve failures and record reruns with new identities.
4. Require exact output/state assertions, relevant negative/security cases and persistence for durable mutations.
5. Final full-coverage claims require all agreed required cells, with explicit outstanding scope decisions. A negative spike may close research but cannot make the associated capability green.
6. Keep candidate interface names out of the callable-action count until the actual record/generator/route/handler chain exists.
