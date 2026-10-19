# N08 — Scene Inputs and Durable Products

[Package index](README.md) · [Coverage matrix](coverage-matrix.md) · [Shared validation](validation-and-evidence.md)

**Goal:** Complete quantitative source-to-product workflows across actual scene inputs and make generated-resource ownership and persistence explicit.

Existing aliases for landscape, actor, mesh, texture and volume nodes are not evidence that their complete workflows work. Conversely, existing scene/asset tools should be reused rather than duplicated under PCG. This batch does not implement a new landscape, mesh or generic export framework.

## N08-01 — Build deterministic scene-source family fixtures

**Priority:** P2 · **Owner:** Unassigned · **Workflow:** PLANNED

**Implementation:** PARTIAL · **Validation:** Expanded scene-source matrix NOT_RUN.

**Depends on:** `N05-04`, `N06-03`.

**User outcome:** Sample real Landscape/Surface, Texture, Mesh, Actor, Spline and Volume inputs and verify the resulting points/attributes.

**Reuse:** [Current node aliases](../../plugins/EngineWire/Source/EngineWire/Private/Domains/PCG/McpPCGAssets.cpp), generic settings and native connection checks, [existing workflow](../../tests/mcp-tools/world/manage-pcg-workflow.test.mjs), N05 data reads and existing `build_environment`, actor, spline, texture and asset capabilities.

**Steps:** Inventory actual installed source/sampler/projection/filter classes and required modules. Author small uniquely owned sources with known geometry, transforms, masks/tags and sampling bounds through structured tools. Define expected coordinate space, sample count/ranges and tolerance per family. Add configuration changes and regenerate rather than merely asserting that a source node was added.

**Contract/policy:** Existing operations remain preferred. Add only proven PCG-specific contract gaps after verifying their native APIs and availability. Input selection must be explicit and path-authorized; no production content, global tag scans or implicit scene-wide mutation. GPU and partitioned sampling remain separately gated.

**Acceptance:** Each required family has nonempty quantitative output and valid empty/no-match cases; verify projection/normal/density/attribute values, actor filters, texture addressing and local/world transforms where applicable. Invalid resources, unavailable modules and out-of-bounds inputs produce honest failures/empty semantics. Verify both transports, repeatability and owned-source persistence.

**DoD/stop:** Family-specific fixtures and data assertions, not one test per alias. Stop if a scene API or native sampler cannot be used safely; do not substitute synthetic point data for the actual requested source family.

## N08-02 — Expose bounded managed-resource identity and provenance

**Priority:** P1 · **Owner:** Unassigned · **Workflow:** PLANNED

**Implementation:** PARTIAL · **Validation:** Resource-level provenance NOT_RUN.

**Depends on:** `N05-04`.

**User outcome:** Know which component owns each product and distinguish managed, unresolved and nonmanaged objects before cleanup or baking.

**Reuse:** [Managed result inventory](../../plugins/EngineWire/Source/EngineWire/Private/Domains/PCG/Execution/McpPCGManagedResults.cpp), exact component/principal helpers and existing ISM/HISM/actor summaries. Existing counts and paged transform samples remain backward-compatible.

**Proposal:** Extend the current result contract or add a matching Read/none variant with bounded resource-level identity/type, owning component, resolved product references and explicit provenance confidence. Native generation/node provenance is returned only when actually available; never infer it from a tag, object name or unrelated operation record.

**Steps/targets:** Read supported public managed-resource classes through their ownership APIs. Define ordering, per-category pages, traversal/reference limits and unresolved counts. Avoid loading soft actor references. Keep native resource identity separate from operation IDs and from N05 dataset views; all are process/lifecycle-scoped as documented.

**Acceptance:** Multiple ISM/HISM/actor resources, child actor hierarchies, nonmanaged objects with the same mesh/tag, unresolved references, zero products and pagination/stress boundaries. Assert exact ownership and totals; repeat after regeneration/cleanup/GC. Foreign job metadata remains private, while legitimate path-authorized inventory does not gain an invented principal-private resource ACL.

**DoD/stop:** Native inventory tests and native/WS result assertions with truthful truncation and traversal limitations. Stop on ambiguous ownership or unsafe reference traversal; never treat every tagged world object as a PCG product.

## N08-03 — Detach or bake products with explicit ownership transfer

**Priority:** P2 · **Owner:** Unassigned · **Workflow:** PLANNED

**Implementation:** UNKNOWN · **Validation:** Transfer/bake workflow NOT_RUN.

**Depends on:** `N08-02`.

**User outcome:** Intentionally convert selected generated products into independently owned durable scene/asset content without future PCG cleanup deleting them.

**Investigated candidate/reuse:** The public target-engine component API declares `ClearPCGLink(UClass* TemplateActor)`; that declaration is not a proof of all bake or disk semantics. Reuse native resource APIs, generic actor/asset tools and safety-save wrappers. Prove supported behavior per engine before advertising a capability.

**Steps:** Spike public detach/bake behavior on an idle owned component; inspect whether resources are moved, duplicated, unregistered or released. Define a precise selected-product scope and destination ownership. Reuse existing structured conversion/asset operations where sufficient; add only the missing PCG ownership-transfer step. Preserve native transforms, materials, supported instance custom data and actor hierarchy or explicitly report unsupported fields.

**Contract/policy:** Candidate detach/bake is a PROPOSAL / NOT CALLABLE. Ownership transfer and cleanup effects require reviewed Destructive scope and explicit envelope consent; separate any additive asset-creation phase rather than assuming Destructive grants another Write action. Require current native-idle proof and authorized destinations. Do not silently save all packages or clean unrelated products.

**Acceptance:** Regenerating/cleaning the source leaves detached products intact; pre-existing world objects remain untouched. Check ISM/HISM/actor variants, unresolved resources, busy/moved/deleted target, missing consent, outside destinations and partial native/save failure. Saved detached content survives an independent process.

**DoD/stop:** Actual ownership/readback and per-owner commit/save receipts with residual inventory. Stop if transfer cannot be safely scoped or compensated; no fake atomic rollback of moved resources or previously saved bytes.

## N08-04 — Track source changes and output freshness

**Priority:** P2 · **Owner:** Unassigned · **Workflow:** PLANNED

**Implementation:** PARTIAL · **Validation:** Source-change family matrix NOT_RUN.

**Depends on:** `N08-01`, `N07-03`.

**User outcome:** Distinguish output for the current source state from cached/previous output after scene or input changes.

**Reuse:** Native PCG dependency/dirty/refresh behavior, [operation observation](../../plugins/EngineWire/Source/EngineWire/Private/Domains/PCG/Execution/McpPCGObserver.cpp), graph/instance fingerprints and N05 snapshot invalidation. Authored revisions and instance tokens do not hash all world inputs and must not be described as doing so.

**Steps:** Prove public dirty/dependency/provenance signals per source family. Test spline edits, actor moves/tags/properties, supported landscape/texture/mesh changes and component bounds/seed changes. Decide when native auto-refresh, explicit regeneration, cancellation or supersession occurs; expose unknown freshness if evidence cannot identify the consumed source state. No hardcoded business-asset rules.

**Contract/policy:** Read status must not silently regenerate or mark sources dirty. Explicit refresh/regenerate uses the appropriate Write capability; cancellation/cleanup remain separately authorized. Preserve native lease semantics when source changes cancel or replace work, and keep earlier terminal operation records unchanged.

**Acceptance:** Before/after values change as expected and unchanged/fixed-seed repeats are stable. Exercise edits during active work, deferred replacement, no-op edits, cached output and stale page tokens. Assert actual current native idle before cleanup; one observed terminal operation is not sufficient. Native/WS results must label the same freshness/provenance facts.

**DoD/stop:** Source-specific change/refresh and data-identity evidence. Stop rather than claim freshness from only graph revision, task ID or delegate arrival.

## N08-05 — Persist and export the supported product workflows

**Priority:** P2 · **Owner:** Unassigned · **Workflow:** PLANNED

**Implementation:** PARTIAL · **Validation:** Expanded durable/export matrix NOT_RUN.

**Depends on:** `N08-03`, `N08-04`, `N07-05`.

**User outcome:** Save or explicitly export supported output content and verify it remains usable after restart.

**Reuse:** [Cold-load suite](../../tests/mcp-tools/world/manage-pcg-cold-load.test.mjs), [real-save/caller-transaction suite](../../tests/mcp-tools/world/manage-pcg-save-failure.test.mjs), native data-asset/factory APIs only after a public serialization spike, and existing asset export/conversion tools where available. Do not serialize transient PCG caches as if they were durable assets.

**Steps:** Define which graph/instance/map/detached product/data-asset owners must be saved. Distinguish regeneration after reload from persistence of a cached data object. If a structured PCG data export is needed, explicitly scope its format/destination and reuse shared path/size controls; keep arbitrary filesystem export out of graph editing. Save or export only selected owned content and report every partial outcome.

**Policy/receipt:** Additive output writes and destructive replacement/ownership effects remain distinct capabilities/scopes. Never overwrite an unverified destination. Use safety package saves, no raw `UPackage::SavePackage`, global dirty-package save or implied cross-package disk rollback. Data export must preserve exact typed values and authorized references without embedding unrelated asset contents.

**Acceptance:** Independent-process load of intended owners, source/parameter references, detached product transforms/materials, exported data/schema where supported and deterministic regeneration. Real file-lock/save failure, invalid/occupied/outside destination, unsupported output classes, missing references and partial multi-owner failure remain explicit. Preserve failed evidence and owned residuals.

**DoD/stop:** A durable-product matrix with exact save owners, export limits and source-matched cold/live reports on both transports. Stop on unavailable public persistence APIs or ambiguous ownership; do not claim all output data classes are persistent from one point-data fixture.

## Implementation order and exit

Scene-source fixtures and resource inventory can proceed independently after their prerequisites. Ownership transfer follows proven resource identity; input freshness precedes expanded persistence. N09 later extends these rules to local components/cells rather than reusing unpartitioned success as partition evidence.

Batch completion requires quantitative real-source and durable-product evidence for the agreed families. Aliases, synthetic inventory stress tests, renderer-free source setup or generated tags alone do not establish production scene/rendering scale.
