# N05 — Data and Attribute Observability

[Package index](README.md) · [Coverage matrix](coverage-matrix.md) · [Shared validation](validation-and-evidence.md)

**Goal:** Let an MCP caller inspect actual PCG data instead of inferring it from generated instance counts. The first delivery slice is root dataset/schema/paged-value reading. Intermediate capture has its own feasibility gate and a separate gated implementation ticket; it is not silently included in the first slice.

**Current boundary:** [Managed results](../../plugins/EngineWire/Source/EngineWire/Private/Domains/PCG/Execution/McpPCGManagedResults.cpp) expose root pin/class/count/tags and resource transform samples. They do not expose Metadata domains/schema, point attributes, intermediate datasets or profiling. Preserve that existing summary API and its semantics.

All candidate names below are **PROPOSALS / NOT CALLABLE**. Keep new read variants in `manage_pcg` and fold only with matching policy. No UI clones, second queues, durable dataset service or automatic native regeneration.

## N05-01 — Prove public data access and snapshot prerequisites

**Priority:** P1 · **Owner:** Unassigned · **Workflow:** PLANNED

**Implementation:** UNKNOWN · **Validation:** NOT_RUN.

**Depends on:** `PRE-03`.

**User outcome:** Data queries have an explicit supported type/version and consistency contract before an API is advertised.

**Reuse/evidence:** [Execution declarations](../../plugins/EngineWire/Source/EngineWire/Private/Domains/PCG/Execution/McpPCGExecution.h), [exact target/principal helpers](../../plugins/EngineWire/Source/EngineWire/Private/Domains/PCG/Execution/McpPCGExecContext.cpp), [read budget](../../plugins/EngineWire/Source/EngineWire/Private/Domains/PCG/Discovery/McpPCGBudget.h). Investigated engine headers, relative to engine root: `Engine/Plugins/PCG/Source/PCG/Public/PCGData.h`, `Data/PCGBasePointData.h`, `Metadata/PCGMetadata.h` and `Metadata/PCGMetadataDomain.h`.

**Scope/steps:** Compile/link a tiny owned Point/Param fixture using public const point ranges and metadata accessors on each target engine. Inventory supported metadata domains/types, defaults and inherited entry-key mapping. Determine whether native generated data is immutable for the intended read window, how cache reuse affects identity, and which events invalidate a page token. Measure the strictest existing output budget before choosing row/column/byte limits.

**Target changes:** A bounded native test under `Private/Tests/PCG/`; planned domain-local typed data adapter declarations under `Domains/PCG/Discovery/`, reusing reflection/value codecs where their exact semantics fit. Do not rely solely on object UID or graph revision as a data-content version.

**Contract/permissions:** Investigation starts read-only; native fixture setup requires PRE-03. No proposed read may load soft references, mutate point storage or convert Spatial data to points. Availability is established per API/type/engine, not inferred from PCG being enabled.

**Acceptance/DoD:** Actual native API linkage, exact scalar/vector/transform/Int64 attribute reads, default/inherited values and valid empty data are demonstrated. Unsupported domains/types are explicit. Produce a supported-adapter and identity/lifetime decision record; a negative spike may close research but leaves dependent feature tickets BLOCKED.

**Stop:** No private offsets, engine edits, mutable point allocation for a read or unbounded copying to conceal the absence of a stable view.

## N05-02 — Enumerate root datasets and metadata schema

**Priority:** P1 · **Owner:** Unassigned · **Workflow:** PLANNED

**Implementation:** NOT_IMPLEMENTED · **Validation:** NOT_RUN.

**Depends on:** `N05-01`.

**User outcome:** Discover which datasets, pins, tags, domains and attributes exist before requesting values.

**Proposal:** `list_pcg_data` and `get_pcg_data_schema`, or equivalent read variants of `inspect_pcg`; exact component plus dataset locator, offset/limit and optional domain filter. Return dataset identity/provenance, data kind/class, available row-count semantics, domains, attribute types/defaults and explicit truncation. A Spatial dataset may provide bounds/capabilities without pretending to have a finite point table.

**Implementation:** Extend the PCG Discovery layer with dataset descriptors from current generated output; use `ResolveExactPCGComponent` and native type adapters from N05-01. Add records/folds, native routing and generated outputs through the normal pipeline. Keep operation IDs, graph revisions and dataset tokens distinct. Do not serialize arbitrary UObject properties into rows.

**Permissions/lifecycle:** Read/none on the authorized component; no capture, generation, saves or implicit asset loads. If a generation is active, label any earlier data as earlier/unknown provenance or refuse the requested current-generation claim. Foreign retained-operation metadata stays private.

**Acceptance:** Native and WS fixtures cover multiple root pins/datasets, tags, Point/Param/Spatial types, domains/defaults, empty output, wrong dataset/component, stale locator, unsupported schema and page boundaries. Querying must leave revision, dirty state, products and inspection state unchanged.

**DoD/stop:** Declared output fields survive both gateways; schema and total/truncation semantics match native readback. Stop rather than return a misleading empty schema for an unsupported type or unvisited domain.

## N05-03 — Read typed point and attribute pages

**Priority:** P1 · **Owner:** Unassigned · **Workflow:** PLANNED

**Implementation:** NOT_IMPLEMENTED · **Validation:** NOT_RUN.

**Depends on:** `N05-02`.

**User outcome:** Check the values that caused a filter, transform or selector outcome.

**Proposal:** `read_pcg_data` with dataset token, explicit built-in fields/attribute columns/domain and bounded offset/limit. Return typed rows, coordinate-space declarations, exact integer strings where needed, and clear per-field/type availability. Fit limits to N05-01's strictest gateway budget; a requested limit is not permission to exceed serialization bounds.

**Implementation:** Reuse the descriptor/type adapters and native const ranges/accessors, not the legacy convenience `GetPointsCopy()` or a full reflected export. Add explicit codecs for actual metadata types and defaults/inheritance. Keep Metadata Attributes separate from the graph-parameter property-bag serializer. Preserve existing aggregate `get_pcg_component_results` behavior.

**Permissions/failure:** Read/none; invalid column/domain, unsupported type, exhausted budget and stale token are explicit errors or declared unavailable fields, never silently coerced zero/empty values. No GPU readback or automatic Spatial sampling in this action.

**Acceptance:** Exact deterministic rows before/after attribute filtering; built-in transform/density/seed/bounds and selected user attributes; large positive/negative integers; default/inherited values; mixed domains, missing attributes, invalid ranges and byte/string limits. Assert real values, not only row count. Native and WS receipts must match.

**DoD/stop:** New native typed-codec tests and a proposed new data integration suite pass under the shared protocol. Stop on lossy numeric export, hidden full-table materialization or incomplete paging integrity.

## N05-04 — Enforce data identity, bounds and safe lifetime

**Priority:** P1 · **Owner:** Unassigned · **Workflow:** PLANNED

**Implementation:** NOT_IMPLEMENTED · **Validation:** NOT_RUN.

**Depends on:** `N05-03`.

**User outcome:** Pages refer to one valid dataset view and never mix executions or dereference deleted native data.

**Implementation:** Complete N05-01's identity design with current world/component, generation provenance when available, dataset/pin identity and process-local invalidation. Reuse graph/instance fingerprints without claiming they cover world inputs. Prefer safe native const views; if retention metadata is necessary, keep it bounded and non-durable. No second scheduler, global data registry or unbounded strong references.

**Contract:** Tokens are opaque process-local locators, not credentials or cold-load IDs. Define regeneration/cache-hit, cleanup, graph reassignment, target rename/delete, GC and restart behavior. A query for an old operation must not silently return a newer run's data. Unknown provenance must remain unknown.

**Acceptance:** Interleave pages with regeneration, cache reuse, native/external edits, cleanup, target destruction and GC; obtain stable same-view rows or deterministic stale/unavailable results. Exercise handle/row/column/text/retention exhaustion without weakening limits. Verify principal metadata isolation and exact Read-only grants on both transports.

**DoD/stop:** Native lifetime/stress regressions plus live interleaving cases, with source/binary-matched evidence and no residual capture/retention state. Stop on dangling views or an inability to establish consistency; do not disable GC or hash/export the entire scene to fake a cheap token.

## N05-05 — Spike intermediate inspection and timing APIs

**Priority:** P1 · **Owner:** Unassigned · **Workflow:** PLANNED

**Implementation:** UNKNOWN · **Validation:** NOT_RUN.

**Depends on:** `N05-01`.

**User outcome:** Establish whether supported public APIs can safely expose node inputs/outputs and native execution metrics.

**Investigated API:** UE 5.7's public route is `Component->GetExecutionState().GetInspection()`. `FPCGGraphExecutionInspection` declares enable/disable, inspection data and executed stacks; `PCGUtils::FExtraCapture` declares `CalculateCallTreeInfo`. The `GetInspection()` overrides in `PCGComponent.h` belong to the execution-state class, not a direct component method. Public declarations do not prove target-version linkage or correct capture lifetime.

**Steps:** Compile/link the nondeprecated execution-state route; capture a real owned graph/subgraph and identify node/stack/pin inputs and outputs. Check inspection reference-count ownership, cache behavior, missing capture, native logs, timing meaning and whether reading can be side-effect-free. Compare a genuinely available vs unavailable diagnostic source; a forced module conditional is not that environment.

**Permissions:** Acquisition/release are explicit state changes; data reads remain separate Read capabilities. Never steal the user's inspection state or globally clear another observer's cache. Native capture may retain substantial data even when MCP export is paged; measure and declare that cost.

**Acceptance/DoD:** A documented positive or negative feasibility result for each engine, with actual exported test evidence and restored initial inspection state. Disambiguate nested/loop stacks, inactive nodes, empty data and cached execution. This ticket does not itself ship a production debugger.

**Stop:** Unexported/private APIs, irreconcilable shared ownership or unbounded retention block N05-06; they are not reasons to remove safety checks.

## N05-06 — Deliver owned intermediate capture and bounded profiling

**Priority:** P2 · **Owner:** Unassigned · **Workflow:** PLANNED

**Implementation:** NOT_IMPLEMENTED · **Validation:** NOT_RUN.

**Depends on:** `N05-05`, `N05-04`.

**User outcome:** Inspect a specific node's input/output by execution stack and understand supported native timing/cache information through MCP. This is a separately activated follow-up after a positive N05-05 result, not part of the initial root-read delivery promise.

**Proposals:** Explicit begin/end inspection capabilities with Write/none where their verified effects permit; separate Read/none stack/node-data/profile queries. Final effect/consent classification must be reviewed if release would erase shared state. A Write-only profile must not gain full data reads through a begin-capture receipt.

**Implementation:** Reuse the proven public inspection/execution-state route, N05 typed readers, principal resolution and the existing game-thread path. Bind bounded capture metadata to owner/component/world and native stack identity. Preserve pre-existing native inspection ownership, release only this session's acquisition and invalidate views on session/target end. Report execution/prepare/wall time and cache information only with defined native meanings; do not fabricate progress or GPU completion from timing fields.

**Acceptance:** Real input/output rows in main/subgraph/loop contexts; distinct cached/inactive/not-captured/empty states; warnings/errors and bounded metrics; foreign handle refusal, exact scopes, timeout/disconnect, target GC and cleanup, user inspection coexistence and both transports. Compare a known transformation/filter's intermediate values against its final output.

**DoD/stop:** Owned capture lifecycle and metric semantics have native/live evidence, no inspection-counter leak and no accidental scene save. A public-API failure remains BLOCKED; do not silently replace real captures with test-generated data or a generic Python bridge.

## Implementation order and batch exit

First deliver N05-01 → N05-02 → N05-03 → N05-04. N05-05 can investigate independently after N05-01, with one serial live owner. N05-06 requires a positive supported API/lifetime decision and separate scoped implementation acceptance.

Root-data coverage and intermediate-debug coverage are separate matrix cells. Mark the first slice complete without claiming the second; global full coverage remains open until the required intermediate workflow is delivered. No GPU/runtime/partition semantics are inferred from this editor-local batch.
