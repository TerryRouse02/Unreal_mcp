# PCG MCP Coverage Work Packages

This is the implementation backlog for completing PCG workflows through the existing MCP gateway. It is a planning package, not a list of newly callable actions or a claim of complete PCG support.

**Planning snapshot:** 2026-10-19, commit `7a6f928db`, with an uncommitted PCG Int64 input-validation follow-up. See the [baseline and prerequisites](00-baseline-and-validation.md) before assigning implementation work.

## Target outcome

A caller should be able to discover, author, configure, execute, inspect, correct, persist and clean up a supported PCG workflow using structured MCP calls. Core PCG mutations must not depend on ad hoc Python, manual graph-editor intervention, engine-source edits or private API copies. Existing structured tools for actors, Blueprints, assets, splines and levels remain valid building blocks; do not duplicate them under PCG.

Graph Parameters, Property Bags and PCG Metadata Attributes are different data models. Coverage of one does not establish coverage of another. Successful scheduling, successful observation, correct output and durable persistence are also separate claims.

The initial implementation targets are editor PCG on UE 5.7 and 5.8. The roadmap extends to partitioned/hierarchical generation, real GPU execution and PIE runtime generation. Packaged standalone MCP is an explicit architectural decision gate, not an implied extension of the current Editor-only plugin. Other engine/platform cells remain visible in the matrix; do not silently remove an unresolved required cell to declare completion.

## Package index

| Package | Deliverable | Initial workflow | Tickets |
| --- | --- | --- | --- |
| [PRE](00-baseline-and-validation.md) | Source/evidence reconciliation, pending Int64 native acceptance, isolated validation prerequisites | Mixed; native acceptance blocked | PRE-01–PRE-03 |
| [N05](N05-data-observability.md) | Root datasets, typed pages and snapshot lifetime; intermediate feasibility plus gated capture/profile delivery | PLANNED | N05-01–N05-06 |
| [N06](N06-generic-authoring.md) | Generic settings/selectors, dynamic interfaces, controlled Blueprints, editor fidelity and graph-fragment reuse | PLANNED | N06-01–N06-06 |
| [N07](N07-instances-and-parameters.md) | Component/graph-instance lifecycle, target revisions, native types and parameter propagation | PLANNED | N07-01–N07-05 |
| [N08](N08-scene-inputs-and-output-assets.md) | Scene-source families, resource provenance, detach/bake/export and persistence | PLANNED | N08-01–N08-05 |
| [N09](N09-partitioned-and-hierarchical.md) | Original/local components, cells/grids and aggregate lifecycle | PLANNED | N09-01–N09-05 |
| [N10](N10-gpu-and-runtime.md) | Independent GPU and PIE workstreams; packaged-runtime scope decision | PLANNED | N10-01–N10-05 |
| [N11](N11-compatibility-and-delivery.md) | Continuous compatibility/security gates and final single-contribution preparation | PLANNED | N11-01–N11-05 |

Supporting documents:

- [Coverage matrix](coverage-matrix.md): capability inventory, current gaps, required evidence and ticket ownership of each gap.
- [Validation and evidence](validation-and-evidence.md): common implementation contract, test layers, evidence fields and safe-stop rules.
- [Current PCG usage guide](../pcg-authoring.md): existing behavior, permissions and limitations.
- [Repository testing guide](../testing-guide.md): existing test infrastructure and commands.

There are **40 tickets**: three prerequisites, six tickets each in N05/N06, and five tickets each in N07–N11. Each implementation owner must accept a ticket explicitly; all unassigned future tickets remain unassigned. Documentation creation does not assign or implement them.

## Read and execute in this order

1. Read PRE, the coverage matrix and the shared validation protocol.
2. Select one bounded ticket and check its exact prerequisites. A dependency is an acceptance prerequisite; drafting or isolated source investigation may happen earlier without claiming readiness.
3. Inspect the current records, implementation and tests named by that ticket. Verify that the proposed gap still exists.
4. Agree the smallest contract and explicit support boundary. Candidate action names in these documents are **PROPOSALS / NOT CALLABLE** until records, generated outputs, native routing and implementation exist.
5. Add a failing behavioral test, implement the minimum change, then collect the required evidence. Record blocked/unrun layers honestly.
6. Update the ticket and its coverage rows together. A ticket being Done does not automatically complete a batch, execution mode or engine version.

## Dependency and parallelism rules

- PRE-01 establishes the source/evidence boundary. PRE-03 gates owned native fixtures and any necessary deployment authorization; PRE-02 closes the already-implemented Int64 follow-up.
- N05 provides typed data readers and snapshot rules used by later workflow assertions. N05-05 is an independent feasibility result; N05-06 is a separately gated production follow-up, not part of the first root-read delivery promise.
- N06 and N07 can have independent source work. Their runtime fixtures must not concurrently mutate the same world or deployment.
- N08 consumes data observation and authored workflows. N09 consumes component identity, data lifetime and resource ownership rather than starting another scheduler.
- GPU and PIE investigation are separate branches in N10. CPU-only PIE is not forced to wait for GPU implementation; partitioned runtime additionally needs the relevant N09 work.
- N11-01/N11-02 define continuous inventory and gate protocols. Refer to those protocols while implementing each batch, but do not make their final completion a circular prerequisite for every feature. N11-03 is the actual final regression join.
- Only the main coordinator may directly dispatch agents, including multiple independent Sonnet assignments. Subagents must not delegate, resume child agents or invoke skills/workflows that create agents. The coordinator owns acceptance.
- Parallel source work is not permission for concurrent builds that clean the same `dist/`, multiple live fixture owners or overlapping editor deployments.

Exact prerequisites are declared in each ticket's `Depends on` line. Do not substitute an entire batch dependency for the smaller listed dependency without explaining why.

## Status model

Keep three independent dimensions:

| Dimension | Values | Meaning |
| --- | --- | --- |
| Workflow | PLANNED, READY, IN_PROGRESS, NEEDS_VALIDATION, BLOCKED, DONE | Assignment and execution state of the bounded ticket |
| Implementation | IMPLEMENTED, PARTIAL, NOT_IMPLEMENTED, UNKNOWN | Whether the ticket's deliverable exists, not whether helpers exist |
| Validation | Separate static, mock, native build, live and cold-load results | PASS, FAIL, NOT_RUN, BLOCKED or HISTORICAL_REPORTED per relevant layer |

`Owner: Unassigned` is the default, never an implied assignment. P0 is a correctness/security/acceptance blocker; P1 is the next core workflow; P2 is broader completeness; P3 is a high-dependency execution-mode expansion.

A public header or method declaration is investigation evidence, not native linkage or runtime acceptance. A feasibility spike can be Done with a documented negative result; the corresponding production capability stays unavailable or unimplemented. `NOT_SUPPORTED`, missing capture, skipped tests and expired evidence are not positive feature coverage.

## Fixed architecture and safety boundaries

- Retain the single public `unreal` gateway and existing `manage_pcg` parent. Both transports use the same prequeue authorization and single game-thread dequeuer.
- Capability records and folds are the contract source of truth. Generate downstream artifacts; never edit generated files manually. New receipt fields must be declared or the gateway may remove them.
- Read, Write and Destructive are exact scope sets; only Admin is a wildcard. Consent is an execute-envelope sibling, never a parameter. Do not leak another principal's operation metadata through new reads.
- Reuse native compatibility checks, reflected property paths, owned-object validation, bounded snapshots, operation observation and safety-save wrappers.
- Do not introduce a second task queue, generic orchestration service or durable job database to complete a PCG ticket.
- Preserve old aliases, valid calls and save defaults. A single graph transaction does not promise cross-instance or disk atomicity.
- Do not relax Blueprint callback guards, copy private engine classes, use private offsets/global Undo, disable GC or retain unbounded datasets.
- New source respects the plugin's 250-pure-line and 25-files-per-directory budgets.
- Use owned isolated fixtures, never production assets. Build/deployment, process and temporary-profile permissions are separate from permission to edit source or documentation. Do not bypass a denied operation with another tool or agent.
- No automatic commit, push, history rewrite, branch/worktree creation, version bump, Issue/PR creation or external publication.

## Full-coverage completion rule

The denominator is an explicit inventory of target workflows, installed node families, data types, execution modes, engines and transports. General reflection plus alias counts is not that inventory. Static optional-parameter references are not runtime correctness evidence.

For each required matrix cell, record supported behavior, positive and relevant negative cases, permission boundaries, output readback and persistence where applicable. Use representative family cases plus explicit high-risk combinations rather than pretending an unmeasured Cartesian product was tested.

All required cells must have source-matched evidence before claiming full coverage. A scoped milestone may be completed while other cells remain open, but its scope must be named. Packaged-runtime architecture, arbitrary custom callback isolation and untested environments must never disappear behind a global green badge.

Final contribution remains one consolidated PR, prepared only after the relevant N11 gates and explicit publication authorization. Work packages are not separate external PR commitments.
