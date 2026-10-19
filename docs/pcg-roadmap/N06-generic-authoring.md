# N06 — Generic Authoring Completeness

[Package index](README.md) · [Coverage matrix](coverage-matrix.md) · [Shared validation](validation-and-evidence.md)

**Goal:** Make supported PCG nodes discoverable and reliably configurable, rather than adding a bespoke action for each class. Generic native add/set/batch, owned nested writes, dynamic pin refresh, native edge checks and real input/output boundary settings already exist.

Preserve those implementations. New names are **PROPOSALS / NOT CALLABLE**; prefer extending a coherent existing contract over adding redundant aliases. Native Blueprint wrappers and guarded Blueprint-derived settings are different support categories.

## N06-01 — Discover actual class and instance capabilities

**Priority:** P1 · **Owner:** Unassigned · **Workflow:** PLANNED

**Implementation:** PARTIAL · **Validation:** New discovery coverage NOT_RUN.

**Depends on:** `PRE-03`.

**User outcome:** Find a node and learn which properties, subobjects, pins and editing operations are actually supported without guessing serialized strings.

**Reuse:** [Query/schema discovery](../../plugins/EngineWire/Source/EngineWire/Private/Domains/PCG/Discovery/McpPCGQuery.cpp), [settings resolution and nested paths](../../plugins/EngineWire/Source/EngineWire/Private/Domains/PCG/McpPCGSettings.cpp), [read records](../../src/tools/catalog/capabilities/records/world/manage-pcg.read.data.ts). Current discovery is loaded-class-only and schema queries take a settings class, not a complete instance-specific subobject context.

**Steps/targets:** Inventory native/extension/Blueprint node families for the installed modules. Extend class/instance schema discovery with actual editable-property support, enum/reference/selector representation, owned subobject class and read-only/atomic-edit restrictions. Identify default-vs-instance-dependent pins and properties. Any explicit asset/class loading must be bounded, path-authorized and separately assessed for effects; ordinary inventory must not load/compile every Blueprint.

**Proposal/policy:** Read/none capability/schema variants; if explicit loading has native side effects, give it a separate reviewed effect rather than hiding it in a read. Return supported/unsupported reasons instead of listing an unsafe class as freely editable.

**Acceptance/DoD:** Native class, initialized selector and controlled Blueprint fixtures expose sufficient schema to construct valid calls; unavailable classes, read-only properties, wrong targets and unsupported callbacks are honest. Native/WS schema results agree, pages/truncation are correct and reads preserve dirty/revision/inspection state. Follow PRE-03 before native fixtures. Stop if discovery would require unbounded loads or private engine metadata.

## N06-02 — Validate selectors, packers and instanced setting changes

**Priority:** P1 · **Owner:** Unassigned · **Workflow:** PLANNED

**Implementation:** PARTIAL · **Validation:** Extended selector workflows NOT_RUN.

**Depends on:** `N06-01`.

**User outcome:** Configure more than a single mesh, switch supported selector/packer types and understand the resulting dependent schema.

**Reuse:** [Spawner convenience settings](../../plugins/EngineWire/Source/EngineWire/Private/Domains/PCG/McpPCGSpawnerSettings.cpp), [preflight](../../plugins/EngineWire/Source/EngineWire/Private/Domains/PCG/Editing/McpPCGPreflight.cpp), [mutation implementation](../../plugins/EngineWire/Source/EngineWire/Private/Domains/PCG/Editing/McpPCGMutations.cpp), existing workflow HISM `MeshEntries` configuration. The `meshPath` convenience field intentionally resets to one weighted entry; this does not prove generic multi-entry writes are absent.

**Steps:** First prove/document the existing generic path for multi-entry weighted selection, attribute selection and actual installed packer classes. Add a typed selector representation only where current reflection cannot safely express native class initialization and dependent values. Apply class changes before resolving dependent paths on staged owned objects; validate resources and ownership, native notifications and pin/edge consequences before commit.

**Contract/policy:** Write/none for non-destructive edits; any required edge deletion must remain explicit through destructive capabilities. Preserve old convenience semantics, object identities where required and declared save defaults. Do not write through shared objects/CDOs or make arbitrary UObject replacement a PCG escape hatch.

**Acceptance:** Deterministic zero/one weights, multiple entries, attribute-driven selection, ISM/HISM/material descriptors and supported instance-data packing. Invalid class/resource/array element and a failed post-switch property leave authored snapshots unchanged. Verify output selection, repeated regeneration, GC, Undo where supported and cold-load selector persistence on both transports.

**DoD/stop:** Source-matched native and live cases plus discoverable working recipes. Stop on unrecoverable callback side effects or unexported initialization APIs; no generic raw-property workaround that skips preflight.

## N06-03 — Cover dynamic pins, flow control and subgraph interfaces

**Priority:** P1 · **Owner:** Unassigned · **Workflow:** PLANNED

**Implementation:** PARTIAL · **Validation:** Extended family/propagation coverage NOT_RUN.

**Depends on:** `N06-01`.

**User outcome:** Author Switch/Branch/Select, nested/loop graphs and multi-pin interfaces while seeing connection effects explicitly.

**Reuse:** [Native connection checks](../../plugins/EngineWire/Source/EngineWire/Private/Domains/PCG/Editing/McpPCGConnect.cpp), preflight/mutations, [subgraph attachment](../../plugins/EngineWire/Source/EngineWire/Private/Domains/PCG/McpPCGSubgraphActions.cpp), [MCP-authored boundary fixture](../../tests/mcp-tools/world/manage-pcg-workflow.test.mjs). Boundary `settings.Pins` writes and protected boundary-node identities already exist; do not add a duplicate interface action solely because the operation lacks a dedicated name.

**Steps:** Inventory actual native special pins/restrictions. Add deterministic recipes and tests for setting-driven pin changes, extra inputs/outputs, subgraph parameter/data interfaces, nested and loop execution identities. Check parent references when a child interface changes, with bounded impact diagnostics and explicit package/propagation boundaries. Add narrow interface operations only for proven gaps in the existing settings path.

**Contract/policy:** Non-destructive settings/connect changes remain Write; disconnect/removal/replacement remain Destructive with explicit consent. Native conversion/filter requirements stay explicit: callers may author conversion nodes through the generic path rather than the tool silently inserting them. No single-graph batch claim extends to parent/child disk atomicity.

**Acceptance:** Native pin labels/types/multiplicity match readback and editor mapping; valid flow produces expected branch/loop outputs; incompatible edges and connected-pin removal are refused unchanged. Explicit disconnect then edit succeeds. Verify parent interface propagation, stable identities, stale revisions and no silent dropped edges, including saved/cold graphs.

**DoD/stop:** Per-family fixtures, reference-impact readback and failure snapshots, not an alias count. If cross-graph side effects cannot be bounded or restored, refuse that atomic form and document an explicit non-atomic workflow rather than weakening safety.

## N06-04 — Establish controlled Blueprint authoring boundaries

**Priority:** P2 · **Owner:** Unassigned · **Workflow:** PLANNED

**Implementation:** PARTIAL · **Validation:** Broader custom-callback support NOT_RUN.

**Depends on:** `N06-01`, `N05-04`.

**User outcome:** Create/use supported custom PCG Blueprint Elements through structured Blueprint/PCG calls and discover unsupported editing modes before mutation.

**Reuse:** Native `PCGBlueprintSettings`, [existing controlled Blueprint workflow](../../tests/mcp-tools/world/manage-pcg-workflow.test.mjs), [source fixtures](../../tests/fixtures/pcg/PCGValidationElements.cpp), current Blueprint graph authoring tools and PCG callback guards. Existing fixture inheritance from a native test element does not certify arbitrary user-authored Blueprint behavior.

**Steps:** Separate native wrapper, Blueprint Element logic and Blueprint-derived Settings. Construct a small actual Blueprint logic fixture through existing structured Blueprint tools, including compile diagnostics. Identify callbacks during duplication/notification and define supported isolation, recovery and non-atomic boundaries. Expand PCG editing only after a public/native experiment establishes the necessary boundary.

**Contract/policy:** Keep unsupported atomic forms refused. Any explicit non-atomic custom-code operation needs a separate reviewed contract/effect, residual-state receipt and scope decision; no implicit elevation or Python fallback. Do not remove `CLASS_CompiledFromBlueprint` guards as a substitute for a design.

**Acceptance:** Real Blueprint compile state, output-data tag/attribute transformation, default/instance differences, graph save/cold-load and meaningful negative callback cases. N05 data checks inspect actual outputs; foreign/shared/CDO writes remain refused. Failure must identify committed state/residuals, not claim universal rollback.

**DoD/stop:** A supported custom-Blueprint capability matrix and working structured recipe with native/live evidence. Universal arbitrary callback sandboxing is not promised; if a required custom workflow remains unsupported, its coverage row remains open.

## N06-05 — Author graph/node organization with model fidelity

**Priority:** P2 · **Owner:** Unassigned · **Workflow:** PLANNED

**Implementation:** PARTIAL · **Validation:** Extended organization/property coverage NOT_RUN.

**Depends on:** `N06-01`, `N06-03`.

**User outcome:** Organize and configure supported graph/node metadata without losing model identities, comments, native pin mapping or concurrency guarantees.

**Reuse:** Existing move/title fields, [editor sync](../../plugins/EngineWire/Source/EngineWire/Private/Domains/PCG/Editor/McpPCGEditorSync.cpp), [editor mapping](../../plugins/EngineWire/Source/EngineWire/Private/Domains/PCG/Editor/McpPCGEditorMap.cpp), authored snapshot/revision and generic graph-editor tools where available.

**Steps:** Inventory supported graph-level properties and node enabled/debug/layout/comment states. First verify what existing structured tools can author safely. Add only missing PCG-specific operations through public schema/virtual APIs; ensure genuinely authored graph/node fields participate in revision/recovery, while runtime caches and native parameter-presentation objects remain excluded. Review notifications and busy-state requirements for any graph-mode change.

**Contract/policy:** Read operations never create an editor graph. Organization edits use Write/none unless they delete graph content; destructive edits stay explicit. Enabling debug/inspection must not be smuggled into metadata reads or unrelated layout changes.

**Acceptance:** Unopened/open/reopened editor states, comments and visible native node/pin mapping, model follow-up edits, real Undo/Redo where supported, stale-token refusal and independent-process persistence. Assert API-backed state separately from manual visual checks. Changing authored flags must invalidate the token; lazy UI presentation alone must not.

**DoD/stop:** A documented editable-metadata surface and source-matched tests. Stop at unexported editor APIs; no private class copies, global Undo compensation or wholesale graph replacement.

## N06-06 — Reuse and extract graph fragments safely

**Priority:** P2 · **Owner:** Unassigned · **Workflow:** PLANNED

**Implementation:** PARTIAL · **Validation:** Selected-fragment extraction NOT_RUN.

**Depends on:** `N06-03`, `N07-03`.

**User outcome:** Reuse an existing graph or selected native nodes as a subgraph without manually reconstructing every node.

**Reuse:** Generic asset duplication for whole-asset copies, current graph reads/temp IDs, native graph creation/subgraph attachment, edit-state recovery and safety saves. Do not introduce a duplicate-PCG wrapper when the existing asset action suffices.

**Steps/contract:** Separate clone/create from explicit destructive replacement of the parent fragment. Capture source/target revisions and selected stable IDs; classify inbound/outbound edges, owned subobjects, resource references and parameter bindings. Create an owned child and boundary mapping through supported native APIs, then explicitly replace parent nodes/edges only after validation. Parameter-dependent extraction additionally requires N07-05's reference/propagation evidence or a precise refusal.

**Policy:** Clone-only creation is Write; removal/replacement is a separately authorized Destructive/explicit phase. One scope does not grant the other action. Return child/parent committed/saved/residual states; do not promise cross-package atomicity or silently delete a successfully saved child after parent failure.

**Acceptance:** Original unchanged for clone-only; equivalent point/attribute output for extraction; preserved/remapped parameter bindings and positions; fan-in/fan-out and nested references; invalid selection, stale source/parent, invalid resources and real parent-save failure. Cold-load both assets and verify reference/identity mapping on both transports.

**DoD/stop:** Working reuse recipe and explicit two-phase partial-outcome evidence. Stop if a class cannot be safely duplicated or interface ownership cannot be established; preserve known owned residuals for explicit cleanup.

## Implementation order and exit

Start with instance-capability discovery, then selector and dynamic-pin slices. Controlled Blueprint and organization are independent bounded extensions after their prerequisites; fragment extraction also consumes N07 target concurrency. Shared N11 contracts/security checks apply continuously without creating a cyclic final-gate dependency.

Complete the batch only for declared node/property families with actual behavior and persistence evidence. Do not equate generic reflection, a new alias, a compiled test fixture or a safe refusal with all PCG authoring workflows being supported.
