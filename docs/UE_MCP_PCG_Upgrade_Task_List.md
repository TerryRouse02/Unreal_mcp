# UE MCP / PCG Capability Upgrade Task List

> Purpose: The sole local task ledger and cross-agent handoff entry point. A successor should be able to understand the goal, constraints, evidence, outstanding work, and acceptance criteria without the original chat history.
>
> This file is internal handoff material and contains local project paths and workspace information. On 2026-10-16 the user explicitly requested its inclusion in the local checkpoint commit; this does not authorize uploading it to the author repository or copying it into a public PR. Review and remove internal material before external publication.

## 0. Current Status and Next Steps

- Registration date: 2026-10-15.
- Current phase: The implementation plan has been approved; M0 is complete, M1/M2 functionality and first-round native verification are in progress, and T10–T12 are not yet closed out.
- Completed: Isolated native 5.7.4 project; F01–F04 baseline reproduction; first-hand testing of reliable editing, graph UI, batch operations, and graph parameters; and generation changing from 100 to 25, repeated generation not accumulating, managed-resource cleanup, and regeneration.
- The earlier linked-runtime checkpoint is complete, not the overall upgrade. N1 now implements scoped component-object-path confinement and WS project-refusal propagation. Latest focused native results are authorization 4/4, PCG 8/8 and Requests 2/2; the owned native-Wait security fixture passes ten native/WS check groups. Final regression, credential cleanup and original-baseline comparison outcomes are recorded in the N1 acceptance section below. A separate custom-delay revision/crash observation remains unresolved; no blanket completion claim.
- Current feature branch: `feat/pcg-reliable-authoring`; user-created checkpoint commit `501fc0ed00e777facd1d701b5d2a150ae11f1105` includes 80 files and this ledger under `docs/`. Verification fixes, tests and documentation remain uncommitted: eight modified tracked files and one new native parameter test at assessment start. Do not overwrite or hide these changes when preparing the next batch.
- Both explicitly requested Sonnet assignments for N1 are complete; no delegated work remains. Main owns implementation review and serial runtime acceptance. The user separately approved this round's isolated normal close/restarts and temporary scoped profiles; those approvals do not extend to FY, forced termination, unrelated credentials or publication.
- On handoff, first verify the current branch, deployment identity, and progress log, then continue the approved plan; do not repeat T00 planning or restart investigation agents.
- This ledger is not unlimited authorization. Any additional scope, engine modification, breaking compatibility change, or external publication remains subject to the permissions and user authorization of the current session.

## 1. User Goal and Confirmed Decisions

### Final Goal

Enhance the existing Unreal MCP's control of PCG without breaking or unilaterally changing the author's design. The goal is not to pile on more node aliases, but to provide a complete loop for discoverability, readback, reliable editing, parameterization, execution, and result acceptance.

The final contribution to the author repository must be made as **one consolidated PR**. Work and acceptance may proceed in stages and groups, but do not unilaterally split this into multiple external PRs.

### Confirmed by the User

1. Preserve the author's existing architecture, public entry point, layering, permissions, and contract-generation workflow.
2. Deliver the final work as one consolidated PR.
3. A native UE 5.7.4 isolated C++ validation project may be created to compile the plugin and launch an independent editor for acceptance testing.
4. Isolated project root: `D:\UE_MCP_PCG_Validation`. It was created and verified by this upgrade work; subsequent deployment must preserve its ownership markers and reject unrelated changes. Do not overwrite a preexisting project or other content.
5. Do not close, restart, or overwrite the existing FY editor / plugin deployment, and do not affect production assets.
6. The user and author have no additional Issues, design opinions, or contribution agreements yet; proceed under repository conventions for now.
7. The user prepared the first commit personally and explicitly included the English ledger; HEAD was verified as `501fc0ed00e777facd1d701b5d2a150ae11f1105`. There is no authorization for the assistant to create/amend commits, push, publish an Issue/PR, or trigger remote workflows.
8. On 2026-10-16 the user approved testing and subagent assistance. When the normal close was blocked, the user separately and explicitly approved gracefully closing and restarting only the verified PCGValidation editor (then PID29680); no forced termination or FY editor operation is authorized.
9. On 2026-10-17 the user separately approved six temporary scoped test credentials in this isolated project's configuration, with exact Read/Write/Destructive scopes, no Admin, path/project restrictions, and removal plus restart after testing. This does not authorize credential changes elsewhere.

### Scope Awaiting Implementation-Plan Confirmation

The following are upgrade directions discussed so far; do not treat the discussion draft as approval of every interface detail:

- Structured discovery/readback for PCG node types, settings, pins, and the entire graph.
- Connection validation, reliable configuration, failure recovery, disconnect, delete, move, and batch editing.
- Synchronization and consistency checks between the background PCG graph and the editor graph.
- Graph Parameters schema, default values, graph/component-instance overrides and reset.
- Generation, cleanup, current-execution state, diagnostics, and managed-output statistics.
- Corresponding automation, failure paths, persistence, permissions, and compatibility regression tests.

Not currently in scope: business-scenario templates, GPU PCG, large World Partition scenes, Runtime Generation, and unrelated Blueprint / transport / permission-framework refactors. The spline editing-marker issue may be considered as a small PCG-workflow-related fix candidate; it must be explicitly included in the plan and must not expand into all of Spline.

## 2. Paths, Versions, and Workspace

| Item | Path / Status |
| --- | --- |
| Standalone MCP Git repository | `D:\hutianle_ArtStream_UGS\Dev_FTY\Unreal_mcp` |
| Branch at registration | `dev`, tracking `origin/dev` |
| HEAD at registration | `afc8287d88a9edcf518ef8749fbdc507e5f87b0e` |
| Git status at registration | Clean; recheck later and do not overwrite newly appearing user changes |
| Author repository | `https://github.com/ChiR24/Unreal_mcp` |
| PR target branch / fork | Not yet verified; check remotes and the author's actual target branch before publication; do not assume `origin` is the user's fork |
| Repository plugin | `plugins/EngineWire`, not the old name McpAutomationBridge |
| Plugin version | `EngineWire.uplugin`: `0.6.0-beta-e` |
| Native engine | `D:\UE_5.7` |
| Actual native engine version | 5.7.4, Changelist 51494982, Branch `++UE5+Release-5.7` |
| Native PCG source | `D:\UE_5.7\Engine\Plugins\PCG\Source` |
| FY project used for earlier tests | `D:\hutianle_ArtStream_UGS\UnrealEngine\FYGame` |
| Earlier FY test report | `D:\hutianle_ArtStream_UGS\UnrealEngine\FYGame\Saved\MCP_PCG_Test\Run_20261015_01\TestReport.md` |
| This task ledger | `D:\hutianle_ArtStream_UGS\Dev_FTY\Unreal_mcp\docs\UE_MCP_PCG_Upgrade_Task_List.md` |

**Git note:** `D:\hutianle_ArtStream_UGS` is also the root of another Git repository. All upgrade Git operations must target the standalone MCP repository to avoid adding the entire engine / project tree of untracked files to a commit.

**P4 note:** The actual FY editor client is `hutianle_ArtStream_UGS`; the terminal's default P4 configuration may connect to another client. An initial query without an explicit client misread another workspace; this was later corrected. Do not run reconcile / revert / submit against an unverified client. When verifying P4, explicitly specify the client; do not substitute the root-directory default configuration for the editor's actual workspace.

## 3. Author Conventions: Required Reading on Handoff

Continue by reading the AGENTS.md closest to the relevant directory; this document does not replace those conventions.

1. Repository root `AGENTS.md`.
2. `plugins/EngineWire/AGENTS.md`.
3. `plugins/EngineWire/Source/EngineWire/Private/Domains/AGENTS.md`.
4. `plugins/EngineWire/Source/EngineWire/Private/Foundation/AGENTS.md`.
5. `src/tools/AGENTS.md`, `src/tools/catalog/AGENTS.md`.
6. `tests/AGENTS.md`; when working on source-contract tests, also read the applicable subdirectory conventions.
7. `CONTRIBUTING.md`, `.github/pull_request_template.md`.
8. `docs/editor-plugin-extension.md`, `docs/testing-guide.md`, `docs/security-and-receipts.md`, `docs/protocol.md`.
9. `docs/Roadmap.md`: completion claims must include the exact version, command, result, and observable evidence; a static check is not runtime verification.

Some scripts / structural descriptions in CONTRIBUTING.md may be outdated. Treat package.json and the current implementation as authoritative for actual scripts; do not blindly use obsolete commands.

If later touching `D:\hutianle_ArtStream_UGS\UnrealEngine`, follow that directory's CLAUDE.md requirement to prioritize its knowledge base; an earlier attempt to read `UnrealEngine\.AIDB\README.md` found that it did not exist. Do not create or modify that knowledge base for this task.

## 4. Non-Negotiable Design Boundaries

- Preserve the single public tool `unreal`: search / describe / execute / configure.
- Preserve the existing internal canonical parents; PCG capabilities remain under `manage_pcg` and the existing layering; do not create a parallel MCP service.
- New capabilities must follow the single source of truth: capability records → generator → TS / native registry information. Do not hand-edit generated files.
- Preserve existing aliases / folded families; group new read / write / destructive capabilities by effect, scope, and consent. Do not hide deletion in ordinary write batches.
- Both transports must pass through the same security gate and game-thread queue; do not add another execution or queue-consumer path.
- Preserve the names, parameters, default values, save behavior, and existing return fields of valid old calls as far as possible. If an invalid call changes from falsely reporting success to explicit rejection, explain it as a bug fix and provide regression evidence.
- Preserve optional-module and version-compatibility gates. The fact that only 5.7.4 can be tested does not justify deleting other version branches or claiming an unknown version is verified.
- Do not modify native engine source, hard-code FY types, or depend on FY assets.
- Reuse Foundation reflection, nested-property paths, object resolution, responses, path validation, and transaction tools; do not duplicate generic infrastructure in PCG.
- Use safety wrappers such as McpSafeAssetSave / McpSafeLevelSave / McpSafeLoadMap; direct `UPackage::SavePackage` calls are prohibited.
- Observe source-contract constraints such as 250 pure lines per file and at most 25 source files per directory; split by responsibility, not with filler names such as Part1 / Common.
- Do not manually bump the plugin version; the author has a version workflow.
- Do not rely on “opening an FScopedTransaction makes it automatically roll back atomically.” Editor Undo, explicit failure recovery, disk save, and asynchronous generation have different semantics; responses must describe them truthfully.
- Do not work around unexported APIs with global Undo, memory offsets, or copied engine-private classes.
- Local machine tokens, account credentials, and internal asset contents must not enter logs, test evidence, or the PR.

## 5. Earlier Test Findings: What Is Proven and What Cannot Yet Be Concluded

Earlier runtime evidence came from a customized FY UE 5.7.4 build; it was not verification of the new repository HEAD on the native engine. Reproduce in the new isolated project first; do not present any of the historical results below as tests passing after the upgrade.

### Capabilities That Worked

- Actor BP component hierarchy with Scene / Box / Spline / PCGComponent.
- Default values for Integer, Vector, Array<Integer>, and PCGGraphInterface object references.
- Pure functions, functions with return values, custom events, and ForEachLoop.
- `RecordProbe(35)` actually returned 42; the custom event set the instance value to 91.
- Grid → Transform → StaticMeshSpawner: initially 100 Cubes, changed to 25 after adjusting spacing, and repeated generation did not accumulate duplicates.
- Spline sampling → MCPDistance attribute range filtering → subgraph random transform → custom PCG Blueprint Element → Spawner.
- Two instances sharing a PCG graph ended up with 8 / 5 Cubes respectively; after changing and restoring Seed, the first instance's transforms were reproducible.
- Generic `set_property` could directly write the Weighted Selector struct array. With Cube weight 0 / Sphere weight 1, the actual result was 25 Spheres. Only deterministic 0/1 selection was verified, not random-distribution statistics.
- BP wrappers around UPCGGraph UFunctions could disconnect edges and delete nodes; a wrapped Cleanup could clear component-managed resources and allow regeneration.
- After saving and reloading a different map, instance counts remained 25 / 8 / 5. No editor restart cold-load test was performed.

### Confirmed Failure Boundaries

| ID | Actual observation | What the upgrade must verify |
| --- | --- | --- |
| F01 | Connecting PCG Point output to Polyline input returned success; readback showed the same Edge at both ends | Incompatible types must be rejected, with no graph change |
| F02 | A settings write containing Seed=999 and a nonexistent property returned failure, but Seed had already changed from 123 to 999 | Pre-validate and recover reliably; leave no partial write |
| F03 | Creating a Spawner with a nonexistent Mesh returned failure, but left a node in the graph | Invalid resources must not contaminate the real graph; failure must leave no orphan node |
| F04 | After edit_spline changed points, bSplineHasBeenEdited remained false; compiling the host BP restored the instance spline to its template | Preserve the instance edit marker; data must survive compile / reload |
| F05 | A Blueprint batch with top-level success=true may also have compiled=false and compilation errors | Acceptance must check compile state / diagnostics, not only top-level success |

The F04 workaround was verified in the old tests: after changing points, use the generic property interface to set bSplineHasBeenEdited=true; then compilation and level reload preserved the spline. The native tool implementation itself has not been fixed.

### Not Yet Fully Accepted / Cause Not Finally Confirmed

- A background Spline PCG graph had 6 ordinary / subgraph nodes, including a valid custom BP node, and generated data carried the MCP_CustomNode tag; however, the graph window did not show the custom node, and some nodes overlapped. Differences remained after closing and reopening and setting the node again.
- This means background-graph / graph-UI consistency acceptance failed; do not infer from a screenshot alone that the node was permanently lost or that all source-level root causes have been identified. A structured comparison of EditorGraph and UPCGGraph is required.
- When attempting to call ForceNotificationForEditor through a BP wrapper, its ChangeType enum pin (underlying type larger than byte) was rejected, and the function did not actually execute. The leftover empty test function was deleted.
- Creating a new Graph Parameters schema and graph-instance parameter overrides was not made to work; node properties or successful component Seed use do not constitute graph-parameter support.
- It has not been verified whether the plugin binary loaded in the old runtime session matched the current repository HEAD.

The old test's failed nodes / invalid connections have been cleaned up. Do not delete the entire old test directory on your own; the user may still want to inspect it or roll back.

## 6. Source Investigation References

All plugin paths below are relative to the MCP Git repository root.

### Plugin Implementation

| File | Confirmed information |
| --- | --- |
| `plugins/EngineWire/Source/EngineWire/Private/Domains/PCG/McpPCGNodeActions.cpp` | :69 calls AddNodeOfType before configuration; around :110, connection handling only checks whether an Edge exists and does not check type compatibility; there is no recovery path when configuration fails |
| `.../PCG/McpPCGSettings.cpp` | Starting at :62, ApplySettingsObject writes properties one by one and returns immediately on an error in a later property; FindPropertyByName does not support nested paths across objects |
| `.../PCG/McpPCGGraph.cpp` | :220 already calls PostEditChange / MarkPackageDirty / ForceNotificationForEditor(Structural), so simply adding another notification is not a graph-UI fix |
| `.../PCG/McpPCGAssetActions.cpp` | Graph / subgraph creation and attachment; also consider boundaries around saving multiple assets and mid-operation failure |
| `.../PCG/McpPCGComponentActions.cpp` | Starting at :57, modifies the component, calls SetGraphLocal and GenerateLocalGetTaskId; :83 returns a bare taskId, which means scheduling started, not that outputs are complete |
| `.../PCG/McpPCGSpawnerSettings.cpp` | Checks / mutation path for convenient Spawner settings |
| `.../PCG/McpPCGHandlers.cpp`, `McpPCGPrivate.h` | PCG dispatch and shared declarations |
| `plugins/EngineWire/Source/EngineWire/EngineWire.Build.cs` | :49-54 PCG conditional compilation gate; the isolated project must explicitly enable PCG to prevent a successful build with MCP_HAS_PCG=0 |
| `plugins/EngineWire/Source/EngineWire/Private/Foundation/McpScopedEditorTransaction.h` | Existing transaction and durability classification; reuse it; do not wrap save / external / asynchronous operations as fake Undoable transactions |
| `plugins/EngineWire/Source/EngineWire/Private/Foundation/BridgeHelpers/Properties/` | Generic property lookup, nested paths, and writing; prioritize reuse |

### Contracts and Tests

- `src/tools/catalog/capabilities/records/world/manage-pcg.graph.data.ts`
- `src/tools/catalog/capabilities/records/world/manage-pcg.async.data.ts`
- `src/tools/catalog/capabilities/records/world/manage-pcg.index.ts`
- `src/tools/catalog/capabilities/records/folds/manage-pcg.folds.ts`
- `tests/mcp-tools/world/manage-pcg.test.mjs`
- Source-contract tests under `tests/unit/plugin/`.

Current PCG has about 29 synchronous actions plus one execute action, folded into a small number of capability records; “only 3 records” does not mean only 3 kinds of operations are possible. Do not break the folded design merely to increase the surface count.

Existing PCG tests have positive assertions, but cases such as invalid properties only assert an error and do not verify that the graph is unchanged afterward. Existing tests also contain steps using a fixed BASIC_TEST_FOLDER, whole-directory cleanup, and saveDirtyPackages=true; do not run them directly in the shared FY project.

### Native UE 5.7.4 Reference Locations

Root: `D:\UE_5.7\Engine\Plugins\PCG\Source`

- `PCGEditor\Private\PCGEditorGraphSchema.cpp:116`: native connection validation.
- Same file, :158: GetCompatibilityWithOtherPin; distinguishes Compatible / RequireFilter / RequireConversion / incompatible. Do not substitute a homegrown simple type-name comparison.
- `PCGEditor\Private\PCGEditorGraph.cpp:69`: rebuilding EditorGraph from the background graph.
- `PCGEditor\Private\PCGEditorGraph.h:36`: states that the UI should be rebuilt after modifying the background graph outside the UI; this class / method is Private and not exported. Being able to read the source does not mean the installed engine can call it across DLLs.
- `PCGEditor\Private\PCGEditor.cpp:164`: initialization can reuse an existing EditorGraph.
- Same file, :3241: OnGraphChanged is not equivalent to a complete graph-UI rebuild.
- `PCGEditor\Public\PCGEditor.h:87`: exported entry point to obtain the editor graph; feasibility of the specific synchronization implementation still needs verification.
- `PCG\Public\PCGGraph.h:630`: AddUserParameters.
- Same file, :638: UpdateUserParametersStruct.
- Same file, :191-237: typed Get / SetGraphParameter and RenameUserParameter.
- Same file, :716-722: GraphInstance creation, override, and reset.
- `PCG\Public\PCGComponent.h`: GetGraphInstance, generation / cleanup APIs, generation and cancel / cleanup delegates, GetGeneratedGraphOutput, IsGenerating.

## 7. Implementation Strategy and Milestones

These are planning inputs, not implemented interfaces. Specific action names, fields, and permissions must be aligned with existing records / folds in the implementation plan.

### M0: Establish a Trustworthy Baseline

Verify that source, binary, engine, project, and connection all point to the same identities; reproduce the historical issues in the native project and add before / after state assertions.

### M1: Reliable Graph-Authoring Loop

Discover / read back → pre-validate → modify → synchronize graph UI → structured validation → save as needed.

Prioritize F01 / F02 / F03 and graph-UI consistency, then add native disconnect, delete, move, and per-graph batch editing. Do not start by expanding a large number of node aliases.

### M2: Parameterization and Execution-Acceptance Loop

Graph parameter schema, default values, instance override / reset, and generation / cleanup / status / output statistics. Distinguish graph defaults from instance values, and this request from old results.

### M3: Prepare the Consolidated PR

Regress old calls, verify both transports and permissions, add English documentation / CHANGELOG, and organize general-purpose test evidence. Only after user confirmation proceed with committing / pushing / creating one consolidated PR.

## 8. Work-Package Overview

Status rules: TODO / READY / IN_PROGRESS / BLOCKED / NEEDS_VALIDATION / DONE. These are registration statuses only; “read the source” does not count as implementation complete.

| ID | Work package | Dependencies | Initial status | Owner |
| --- | --- | --- | --- | --- |
| T00 | Handoff registration, read conventions, verify baseline, approve formal implementation plan | None | DONE | Claude Opus 5 / this session |
| T01 | Native isolated project, toolchain, plugin build, and connection-identity verification | T00 approved | DONE | Claude Opus 5 / this session |
| T02 | Reproduce F01-F04 natively and add before / after failure-state assertions | T01 | DONE | Claude Opus 5 / this session |
| T03 | Structured readback of PCG types / settings / pins / entire graph | T00; runtime acceptance requires T01 | IN_PROGRESS | Claude Opus 5 / this session |
| T04 | Safe connections, configuration pre-validation, recovery from create / modify failures | T02, T03 | IN_PROGRESS | Claude Opus 5 / this session |
| T05 | Feasibility and consistency implementation for background graph / graph-UI synchronization | Investigate early; runtime requires T01, T03 | IN_PROGRESS | Claude Opus 5 / this session |
| T06 | Native disconnect / delete / move, per-graph batch modification | T04, T05 | NEEDS_VALIDATION | Claude Opus 5 / this session |
| T07 | Graph Parameters schema and instance override / reset | T03, reliable-change foundation | NEEDS_VALIDATION | Claude Opus 5 / this session |
| T08 | Generation / cleanup / current status / diagnostics / output statistics | T01, T03 | IN_PROGRESS | Claude Opus 5 / this session |
| T09 | Minimal relevant fix for spline instance-edit marker (include after plan confirmation) | T02 | DONE: reproduced point-edit marker survives compile, save, reload and cold restart in the owned fixture | Claude Opus 5 / this session |
| T10 | Contracts, generation, both transports, permissions, tests, and English documentation | In parallel with all work packages | IN_PROGRESS | Claude Opus 5 / this session |
| T11 | Integration, save/reload / cold load, old-call and surrounding regression | T03-T10 | IN_PROGRESS | Claude Opus 5 / this session |
| T12 | Consolidated PR materials and user confirmation | T11 | TODO | Unclaimed |

### Completion Requirements for Each Work Package

**T00**
- Recheck Git status, HEAD, and remotes; do not overwrite subsequent user changes.
- Register the owner, time, scope, and next step in this ledger.
- Propose clear interfaces, compatibility boundaries, tests, and rollback plan; obtain user confirmation before implementation.
- During development, use a dedicated feature branch in the MCP repository. Do not create a worktree unless the user or project conventions explicitly require one.

**T01**
- Check whether the candidate directory is empty; if it contains anything, choose a new directory or ask; do not overwrite.
- Use a native 5.7.4 isolated C++ project and explicitly enable PCG.
- Deploy only the current repository plugin to the isolated project; do not overwrite FY or engine plugins.
- Verify Node / npm, VS / Windows SDK / UE build tools; report missing components specifically rather than asking the user to guess the toolchain state first.
- Record the build command, exit code, loaded plugin version / source, and whether MCP_HAS_PCG is actually enabled.
- Use independent ports / connection configuration; verify projectDir, engineVersion, and plugin identity before allowing asset changes.
- Do not assume an existing MCP session is connected to the correct editor. Read credentials only from the local machine; do not write them into this ledger or evidence.

**T02-T04**
- For failure cases, compare normalized graph structure and settings, not only the error string.
- Reuse native compatibility semantics for connections. When filtering / conversion is required, explicitly return that requirement; whether explicit automatic insertion is allowed is a planned policy decision—do not silently insert nodes.
- Validate resources, classes, and all settings before creation, or validate on staged objects; after failure, leave no real-graph node / settings contamination.
- Distinguish an in-memory commit failure from a disk-save failure; do not claim that the whole operation fully rolled back if saving failed.
- Reuse existing Foundation support for nested setting paths. Validate class changes, Instanced subobjects, dynamic pins, and effects on old connections.
- Readback must be paginated / limited to avoid outputting huge point data for an entire package.

**T05-T06**
- Verify early that the native exported APIs are usable; if engine changes or an un-linkable interface would be required, report the blocker and alternatives first; do not bypass it unilaterally.
- Check correspondence between visible background PCG nodes and EditorNodes and the mapping of connections; explicitly account for Input / Output, hidden nodes, and comments. Do not simply require the two arrays to have equal counts.
- Cover three states: graph window not open, already open, and closed then reopened.
- Prefer atomic batch editing limited to one graph; do not currently promise atomic submission across multiple assets and asynchronous world outputs.
- Batch operations should support temporary-ID references and read back change results; a new generic graph-editing framework is not required for this.
- Prevent overwriting user edits made between two requests; reuse the existing revision mechanism or design a minimal graph-snapshot check.
- Handle delete / disconnect under the existing permission model; do not mix them into low-permission write actions.

**T07**
- Use native parameter APIs; do not modify an Unsafe property bag directly to bypass propagation and notification.
- Distinguish graph defaults from component / graph-instance overrides.
- For parameter renaming, consider preserving reference relationships; define a clear policy and diagnostics for deleting a parameter that is in use.
- Cover adding, reading back, changing values, renaming, instance override, reset, and save/reload.

**T08**
- A scheduled taskId does not mean successful completion. Do not determine that the current request succeeded solely from an old bGenerated or old output.
- Correlate the current operation, target component, and graph version; cover success, cancellation, failure, timeout / target disappearance.
- Prefer integration with the author's existing task / response mechanism; do not create a duplicate asynchronous service; do not block the game thread while waiting for generation.
- Cleanup must target resources managed by that PCGComponent only; do not scan and delete the scene by Actor class / global Tag.
- Count all relevant managed ISM / HISM, Actors, and output data; do not read only the first ISM.

**T09-T12**
- The Spline fix must address only the reproduced instance-marker / persistence issue and add compile and reload regression tests.
- Update implementation, records, folds (when needed), generated artifacts, and coverage tests together for every new action.
- Record each test category separately; mark engine / platform tests that were not run as NOT RUN.
- The PR must contain only general-purpose source, tests, and English documentation; do not submit generated-scene binaries, internal reports, or this desktop ledger.
- Do not commit / push / publish without user confirmation. Follow the session / project requirements in effect at that time for commit attribution and PR text.

## 9. Acceptance-Test Checklist

All statuses below refer to “the upgraded version in the native isolated environment”; at registration they were all NOT RUN. Historical FY results are not passing evidence here.

| Case | Acceptance content | Required observation | Status |
| --- | --- | --- | --- |
| A01 | Grid → Transform → Spawner | 100 instances; count and specified first / last transforms are correct | PASS: exact 100-count, first/last world positions, rotations and nonuniform scale asserted; latest-linked authoring regression |
| A02 | Change spacing and repeat generation | 100 → 25; repeated execution does not accumulate | PASS: deployed native and TS/WS |
| A03 | Incompatible connection | Explicit rejection; node / pin / connection snapshot unchanged | PASS: deployed native and TS/WS |
| A04 | Mixed valid / invalid settings | After the whole operation fails, original settings are unchanged | PASS: deployed native and TS/WS |
| A05 | Create with invalid Mesh / class | Clear error, no orphan node or instance-subobject contamination | NEEDS_VALIDATION: invalid Mesh and complete revision assertion PASS; class / subobject edge cases remain |
| A06 | Disconnect / delete / batch | Background graph and graph UI correspond correctly; failure handling and permissions are clear | NEEDS_VALIDATION: standard suite and native recovery / comment tests PASS; extended Undo / failure paths remain |
| A07 | Dynamic pins / type changes | Connection effects are explicitly reported; no silently retained invalid connection | PARTIAL: Switch refuses removal of a connected output without mutation, permits explicit disconnect then edit, and Integer-to-String pins/editor mapping pass; other node/selector types remain |
| A08 | Three UI-open states | Visible nodes and connection mappings are consistent; manual follow-up editing is possible | NEEDS_VALIDATION: three-state mapping and comment preservation PASS; complex nodes / manual follow-up editing remain to be verified |
| A09 | Spline attribute filtering / subgraph / custom BP | Actual non-empty, correct output and custom-output tag | NOT RUN |
| A10 | Graph parameters for two instances | Default propagation, independent override, reset, rename preserves reference relationships | PARTIAL: standard getter/reference/instance suite, separate component overrides/defaults, reset and stable GUID pass; saved getter and asset/component overrides survive cold load. Broader type/propagation failures remain |
| A11 | Managed-resource cleanup | Empty after cleanup, non-managed resources preserved, regeneration works | PASS: deployed native and TS/WS simple ISM workflow; additional output types still need coverage |
| A12 | Current execution status | Success / cancellation / failure / timeout distinguishable; old results not misread | NEEDS_VALIDATION: native terminal states / error clearing / empty output / target deletion and latest-linked native/TS long calls PASS; superseded / target-moved / diagnostics-unavailable and retention boundaries remain |
| A13 | Save / map-switch reload / independent editor restart | Configuration, references, instance overrides, and generated results persist as specified | PASS for owned simple fixture: graph/node IDs and getter GUID/reference, graph-instance and two component parameter values/overrides, 100 generated instances per owner and edited spline survive save, map switch and a new editor process. Cold-load batch node-loss bug was reproduced, fixed and retested |
| A14 | Project with PCG disabled | Plugin does not fail to build / start due to missing optional module; capability is clearly unavailable | PASS at the previous checkpoint: separate PCGDisabledValidation project compiles with MCP_HAS_PCG=0/MCP_HAS_PCG_EDITOR=0, starts, exposes one public tool, refuses PCG_PLUGIN_NOT_AVAILABLE and closes normally. Not rebuilt after N1; PCG enabled without PCGEditor is also not tested |
| A15 | Native and TS/WS entry points, permissions | Corresponding operation results agree; scope / consent / path rejection causes no mutation | PASS for the owned N1 native-Wait fixture: ten native/WS check groups cover exact scopes, path/project/consent refusals with unchanged state, component parameter write/read/reset, actual generation/results/cleanup and principal+component operation binding. Active cross-principal cancellation is refused without stopping work; same-principal cross-transport cancellation succeeds in both directions. WS project refusal retains PROJECT_NOT_PERMITTED. This does not accept every custom execution/revision interaction |
| A16 | Valid old calls / representative non-PCG regression | Compatible behavior and defaults unchanged, no surrounding regression | NEEDS_VALIDATION: old execute numeric ID and aliases PASS; surrounding live tests remain |

Use a unique RunRoot for every actual asset test. Check that production projects / existing assets are unchanged before and after testing; do not save all dirty packages or run cleanup against a fixed root directory in a shared project.

## 10. Check Commands and Evidence Requirements

The following are check entry points in the repository's current conventions. Verify package.json before running; do not claim to have run scripts that do not exist or are obsolete:

- `npx eslint . --max-warnings=0`
- `npm run type-check`
- `npm run test:unit`
- After contract changes: `npm run registry:generate`, then run `registry:check` / `manifest:check`
- `npm run headers:check`
- `npm run test:params`
- `npm run eval:check`
- `npm run build`, then `npm run test:smoke`
- Record actual native plugin builds, native C++ automation tests, and PCG live integration tests separately.

`node tests/mcp-tools/world/manage-pcg.test.mjs` depends on build artifacts and a live editor, and older cases create / delete assets and save. Run it only in the confirmed isolated project, after checking isolation and cleanup scope; do not run it directly in the FY production project.

For each evidence item record: source SHA / working-tree changes, engine version, platform, plugin deployment identity, project path (in the local record), command, exit code, actual assertions, failure-path result, and residual / cleanup status.

Passing TypeScript / source-text tests does not mean C++ compilation passed; passing C++ compilation does not mean PCG was compiled into the plugin; obtaining a taskId does not mean generation succeeded; saving and switching maps does not mean cold-start verification.

## 11. Deliverables for the Single Consolidated PR

- [ ] PCG implementation consistent with the author's architecture, with no unrelated refactor.
- [ ] Existing valid calls remain compatible; explain each necessary bug-fix behavior change.
- [ ] Records / folds / generated artifacts updated together, with no hand-edited generated files.
- [ ] New feature and failure-path tests with actual state assertions.
- [ ] Native UE 5.7.4 Windows build and runtime evidence.
- [ ] Clearly list unverified items on other engines / platforms; do not claim all versions were tested.
- [ ] English documentation and an Unreleased entry in CHANGELOG.md.
- [ ] Organize Summary / Changes / Testing / Compatibility / Known limits according to the author's PR template.
- [ ] Describe minimal general-purpose reproductions for invalid connections, failure rollback, graph-UI synchronization, and parameter propagation fixes.
- [ ] No FY assets, internal logs, keys, personal paths, or this desktop ledger.
- [ ] User has confirmed commit / push / PR creation; target remote and target branch have been verified.

## 12. Handoff and Transfer Process

### Requirements for the Successor

1. First read sections 0–4 of this ledger and the relevant AGENTS files; do not depend on historical chat or old memory of plugin paths.
2. Recheck MCP repository Git status / HEAD; if there are uncommitted changes, first identify their owner and scope; do not reset, clean, or overwrite them.
3. Register the successor and work package in the table below. An IN_PROGRESS status must have a clearly named owner.
4. If there is no record approving the implementation plan, complete T00 plan confirmation first; this ledger does not automatically authorize coding.
5. Complete only the claimed scope; do not automatically start multiple sub-agents just because the ledger says “any agent.”
6. On completion of each acceptable work package or when blocked, update its status and evidence location in this ledger.
7. At handoff, state what actually changed, what was run, what was not run, remaining issues, and the next executable step.

### Handoff Registration

| Time | Agent / session identifier | Work package | Status | Branch / HEAD | Notes |
| --- | --- | --- | --- | --- | --- |
| 2026-10-15 | Ledger created | T00 preliminary investigation | READY | dev / afc8287d88a9edcf518ef8749fbdc507e5f87b0e | Read-only investigation and document registration only; upgrade implementation not started |
| 2026-10-15 | Claude Opus 5 / this session | T00; continue with T01 | IN_PROGRESS | feat/pcg-reliable-authoring / afc8287d88a9edcf518ef8749fbdc507e5f87b0e | T00 plan approved; dependency installation complete; native isolated-project creation and baseline plugin build in progress; no submission or publication without authorization |

### Implementation-Plan Approval Record

- Status: Approved (2026-10-15, this session's ExitPlanMode approval passed).
- Approved scope: Formal T00–T12 implementation plan; reliable single-graph editing, feasibility verification for public graph-UI synchronization APIs, parameters and completed-state generation, isolated validation, and materials for one consolidated PR; excludes commit / push / Issue / PR publication and remote workflows.
- Plan location: `C:\Users\hutianle\.claude\plans\iterative-seeking-hopper.md`; feature branch `feat/pcg-reliable-authoring`, baseline `afc8287d88a9edcf518ef8749fbdc507e5f87b0e`.
- If the user explicitly changes scope later, record a summary of their exact words, the time, and the impact; do not fabricate approval.

### Template to Fill In at Each Handoff

- Successor / time:
- Current branch / HEAD / uncommitted changes:
- Completed work packages and evidence:
- Test commands, exit codes, actual environment, and deployment identity:
- Verifications not yet run:
- Current blockers / decisions still needed from the user:
- Native test project, RunRoot, and residual assets:
- Any configuration / P4 changes outside source code:
- Specific next action:
- Commit / push / PR authorization status:

## 13. Current Progress Log

### 2026-10-15: Ledger Created

- User confirmed: one consolidated PR, create a native isolated test project, no additional author agreements yet.
- Checked the author's contribution conventions and extension mechanism; located validation / partial-write issues in the PCG implementation.
- Checked native engine 5.7.4 and key PCG APIs; graph-UI synchronization is constrained by Private / exported API boundaries and its feasibility must be verified first.
- MCP Git workspace was clean at registration; no upgrade development branch was created; no build or new-upgrade test was run.
- Old FY isolated-test assets remain: `/Game/Developers/MCP_PCG_Test/Run_20261015_01/`, 8 newly added assets. They are not submission content for this code upgrade; do not clean them up or include them in the PR on your own.
- Next: successor agent to carry out T00, propose the formal implementation plan, and obtain approval.

### 2026-10-16: M0 Complete; T03/T04/T05/T09 In Progress

- Plan approved in this session; branch `feat/pcg-reliable-authoring`; no commit / push / PR authorization.
- T01 complete: independent project `D:\UE_MCP_PCG_Validation\PCGValidation.uproject`, with PCG explicitly enabled; current repository plugin copied independently, without overwriting FY / engine plugins. Native baseline build exited 0; UBT actually used VS2022 14.44.35226 and Windows SDK 10.0.22621; the native PCG actions successfully proved that it did not mistakenly run with MCP_HAS_PCG=0.
- Verified through native MCP: projectName=PCGValidation, projectDir, 5.7.4-51494982, plugin version 0.6.0-beta-e; only public tool is unreal. Loopback only; token authentication remains enabled, and its value was not written to evidence. After the user changed the native port to 3000, it was restored to 13000 as requested and re-verified; WS remains 18090/18091.
- Baseline npm ci (including the first TS build), type-check, registry:check, and manifest:check all exited 0; npm reported 0 vulnerabilities.
- Reproduced all native baseline T02 F01-F04: incompatible Point→Polyline returned success and Edge changed from 0 to 1; mixed valid / invalid settings errored but Seed changed from 123 to 999; creating with an invalid Mesh errored but node count changed from 5 to 6 (including Input/Output); after Spline points were changed to 333/444/555, edited remained false, and compiling the host BP restored the spline to 100/0/0.
- Baseline runtime evidence: isolated project `Saved/PCGValidation/baseline-deployment.json` (hashes for 1611 files), `baseline-build.log`, `baseline-ts-checks.log`, `baseline-failures.json`, `baseline-spline.json`, and raw event receipts; these are not post-upgrade passing evidence and must not be submitted to the author repository.
- T03 has started adding paginated type/schema/whole-graph/graph-UI readback, content revision, and native pin diagnostics; the new Read action uses a separate family fold and preserves old aliases; the first contract-generation pass succeeded, but full regression remains.
- T04 has started adding staged pre-validation, shared reflection nested-path / ownership protection, native connection compatibility, explicit object-state restoration, and truthful save receipts; it has not been marked verified.
- The installed-version external probe module can now be built for T05; first runtime test found that PCGEditorGraph members are not UPROPERTY and therefore cannot be accessed via field reflection. It was changed to use public UObject owned-object enumeration as a candidate and awaits another runtime validation; no Private header, unexported function, pointer offset, or global Undo was used. Graph-UI synchronization is not complete.
- T09 added the instance-edit marker to the reproduced point edit/transform path; still awaiting post-upgrade compile and save/reload validation.
- Terminal Git Bash encountered the pre-existing fatal add_item crash; subsequent builds/commands used PowerShell and file operations used dedicated tools; no terminal system configuration or UniAccess was modified.
- Next: complete current source / generated-artifact gates, rebuild and redeploy; verify T03 readback, T04 unchanged-on-failure / GC recovery, T05 public-schema route; continue T06-T12.

### 2026-10-16: First M1 / Parameter Feature Runtime Results

- Feature branch remains `feat/pcg-reliable-authoring`; not committed / pushed / published; isolated project native=13000, WS=18090/18091; no effect on FY.
- A native build and runtime regression covering discovery, reliable editing, graph-UI synchronization, and batch operations passed (`bsxbpc22p.output` build log, temporary local-session log; to be organized under the isolated project's Saved evidence directory). After F01/F02/F03 failures, the full graph-snapshot revision remained unchanged; stale-revision writes were explicitly rejected; nested Weighted Selector array write succeeded; 4 native PCG tests passed (including recovery after GC, precision, and revision stability).
- The public route for graph-UI synchronization was compiled, linked, and tested at runtime: used only Public schema actions and Public virtual functions; native action selected the correct EditorNode class, rebound the original model after removing the temporary model, and preserved model-object identity. No engine Private header / unexported rebuild function / memory offset / global Undo was used; engine was not modified.
- First-round PASS for all three states—window not open / already open / close and reopen—and node add, position, and connection correspondence: `Saved/PCGValidation/ui-sync-results.json`. Extended regressions for comments, dynamic pins, failure recovery, and Undo remain; this does not mean T05 is DONE overall.
- First-round PASS for batch tempId, full preflight failure not affecting the real graph, write entry rejecting deletion, deletion rejected without consent, disconnect / delete with explicit consent, and final graph-UI consistency: `Saved/PCGValidation/batch-results.json`.
- After Spline edits, edited=true and coordinates remained 333/444/555 after compilation: `Saved/PCGValidation/spline-regression.json`. Level save/reload and cold start are not complete; do not mark T09 DONE.
- Found that revision changed while readable content did not; a local external C++ probe traced this to unstable historical binary serialization of FText. Changed to stable native export text plus exact numeric bits; did not weaken before/after failure assertions. Evidence: `state-probe-differences.json`; subsequent stability and tiny floating-point-change native regressions PASS.
- T07 first independent native build and runtime PASS: Double/Int32/array/Vector/Object default values and edits, invalid types leave state unchanged, independent overrides and default propagation across two components, reset, rename preserving GUID and instance inheritance, and deleting an unreferenced parameter. Evidence `Saved/PCGValidation/parameters-results.json`. Referenced nodes, instance assets, save/reload, cold load, and cross-transport tests remain; do not mark the whole work package complete.
- First-round ESLint and full unit suite PASS; type / generation / source-contract first round PASS. Found that registry:generate does not rewrite the gateway manifest; ran the actual additional script `node --loader ts-node/esm scripts/generate-gateway-manifest.ts`, then parameter audit PASS; generated files were not manually modified.
- No result obtained from TS/WS-specific tests: one background command hung with no output and was stopped; startup/environment will be diagnosed again. Native results cannot be used as WS passing evidence.
- Continue T08 completed-state execution / cleanup / operation correlation; T10 continues throughout; remaining save cold-load, disabled combinations, two-transport permissions, and old-call tests are to be closed in T11.

### 2026-10-16: T08 Normal Workflow Passed; Extended Failure-Path Verification in Progress

- `node tmp/pcg-validation/verify-execution.mjs` exited 0: 100→25 instances, repeated generation did not accumulate, current-completion signal and diagnostics, cleanup of managed resources while preserving unmanaged Actor, and regeneration all PASS. Evidence `Saved/PCGValidation/execution-results.json` and `execution-events.json`. This is not all of T08 DONE.
- Graph-setting changes trigger native auto-refresh; the test explicitly waited for the component to become idle before the next generation, preserving the tool's actual BUSY semantics.
- The running binary is an isolated binary from a previously successful build. The latest parameterName/bindings source and new project-local delay/error probes have not been rebuilt natively.
- The automated permission system denied closing the isolated editor process PID29680, whose prior-session startup and identity had been verified; no bypass, force-kill, or other editor was touched. The latest native build/restart is temporarily blocked by this permission boundary; continue native Wait/Print failure verification that does not depend on restart, along with static / standard tests.
- The isolated editor uses project-local file DDC to avoid a shared Zen startup stall; no engine / FY configuration was modified and shared Zen was not terminated.

### 2026-10-16: Dual-Transport Standard Suites, Execution Failures, and Gate Checkpoint

- TS/WS standard suites passed in practice: `manage-pcg-reliability.test.mjs` 30/30, `manage-pcg-execution.test.mjs` 20/20. Receipts at `tests/reports/manage_pcg_reliability-test-results-2026-10-16T09-31-55.562Z.json`, `manage_pcg_execution-test-results-2026-10-16T09-32-03.697Z.json`. Fixed tests treating errorPattern as a regex and the asset-deletion consent-level mismatch; did not relax the existing evaluator or permissions.
- All 7 native PCG automation tests in the currently loaded binary PASS, including new tempId / permission, explicit restoration of deletion / edge / ordering after GC, comment and model-identity / close-reopen consistency tests. Only these 7 have completed runtime testing; new principal lifecycle / eviction tests have not been loaded or run.
- Native execution-failure verification PASS: retain lease and reject a second generation when timed_out while native execution is still running; late completion does not rewrite the original terminal state; explicit native cancellation; input changes during generation; node-error diagnostics with real inputs; clear old error then succeed; valid empty output; target Actor deletion. Evidence `Saved/PCGValidation/execution-failures-1792143003758.json`.
- Native HTTP long-call PASS: approximately 27-second running receipt, MCP taskId string distinct from PCG operationId, `get_task_result` retrieves final result, MCP observes cancellation while native continues and retains lease. Found that the existing native keepalive still gives an early answer at 27 seconds even when options.timeoutMs is set, unlike TS explicit timeout which does not return early; did not change the global protocol without authorization, documented it, and asserted the actual semantics.
- TS/WS observation-cancel test PASS: with observation_cancelled, engineStillRunning=true, second generation is BUSY, and later native completion preserves the original observation terminal state.
- **Issue found and source fix made in runtime testing, but awaits rerun verification:** a 32-second TS/WS long call exhausted the global 10-deferral limit due to PCG “wait” progress emitted every second, falsely reporting deadlock. PCG now emits only actual terminal-state progress, leaving the global guard unchanged; the internal per-second input-revision checks remain. The currently running old binary still contains this defect; do not report the TS long call as PASS.
- To avoid touching the process-termination action that was denied, ran UBT `-NoLink`: latest source (parameterName/bindings, terminal-progress fix, principal lifecycle/eviction tests) **compile PASS only, not linked or loaded**. No editor was closed or restarted in this round. The isolated project's delay/error probes were also compiled only; do not claim they were run.
- All latest whole-tree gates exited 0: type-check, ESLint, unit 232 files / 2763 cases, test:params optional 2281/2281 with no missing action / extra param, registry:check, manifest:check, headers:check, eval:check 50 cases, build and built-dist smoke, git diff --check.
- Search-regression handling: added PCG parameter topics to avoid taking over existing generalized material-instance parameter queries; `generate pcg` does have new completed-state generation capability, and the probe accepts both old scheduling and new generation as valid results, without lowering the existing 544 floor. Generated artifacts were updated using the generator.
- Added standard parameter suite (including native graph-instance factory fixture, getter references, rename / reject-delete assertions) and English `docs/pcg-authoring.md`, README entry, and Unreleased entry. Standard parameter suite **NOT RUN**: latest getter convenience binding and bindings need to be relinked / loaded.
- Unified local evidence index: `D:/UE_MCP_PCG_Validation/Saved/PCGValidation/checkpoint-summary.json` and `checkpoint-*.log`, explicitly distinguishing running the deployed binary, compiling latest source with -NoLink, and static gates. Internal paths / evidence are not part of the PR.
- Not closed out: atomic-preflight side-effect boundary for custom Blueprint wrappers; native special connection rules; dynamic pins / selector switching; Undo/Redo; actual save failure and partial receipts for multi-asset subgraphs; per-value limits / full-revision cost for large reflected values; two-instance references / instance assets / persistence and cold load; multiple ISM/HISM/Actor and A09; scoped/path/cross-principal security runtime tests; disabled / PCGEditor-unavailable combinations; surrounding live regression and consolidated PR materials.
- Next key step: after authorized stopping and restarting **this isolated validation editor**, run a normal full UBT link (remove -NoLink), restart and verify the new binary identity; first retest the TS/WS 32-second long call, then run the new parameter suite and Requests native tests. Do not treat -NoLink success as link/runtime success and do not bypass the process-close permission boundary.
- Git remains uncommitted changes on the feature branch; no commit/push/Issue/PR/remote-workflow authorization; the overall task is not complete.

### 2026-10-16/17: User Checkpoint Commit and Linked Runtime Validation

- Verified the user-created commit `501fc0ed00e777facd1d701b5d2a150ae11f1105`, 80 files, including the English ledger at `docs/UE_MCP_PCG_Upgrade_Task_List.md`; working tree clean at test start. No assistant commit, amend, push, Issue, PR, or remote workflow was executed. The earlier 79-file staging record was not the final commit's file set.
- User approved testing and subagent assistance. One Sonnet subagent ran the static gates and authored an ignored persistence harness; main reviewed and corrected the harness and ran all editor work serially. No delegated work is pending. Git Bash still fails at startup; used PowerShell/dedicated file tools, without altering system security settings.
- After a separate explicit user approval, gracefully closed only PCGValidation, completed normal UBT linking (not -NoLink), launched a new isolated process, and verified the actual loaded `UnrealEditor-EngineWire.dll` path, binary hash, project, engine, source-file hashes, and ownership of loopback ports 13000/18090/18091. FY and engine source/deployments were not modified.
- The 32-second TS/WS long-call fix now passes at runtime: default running receipt and retained final outcome, distinct MCP/PCG IDs, explicit timeout waiting for completion, and observation-cancellation lease behavior. Native long-call and failure-state regression also pass; per-build results are indexed under `Saved/PCGValidation/postcommit-runtime-*.json`, with separate logs and loaded-module identities.
- Parameter-suite runtime testing found a real defect: malformed floating-point strings became zero through the shared reflection importer. Fixed full numeric-string parsing and finite/float-range checks while preserving valid scientific/numeric strings. New parameter-array staging applies shared typed validation per element rather than permissive numeric-array casts. Added `EngineWire.PCG.ParameterNumbersRejectInvalidValues` to cover malformed strings, embedded NUL, nonfinite/overflow and invalid array elements without source-bag changes.
- The initial graph-instance test fixture failed because factory ParentGraph is protected in Python. It now creates via the default native factory and uses the instance's public editable Graph property; independent runtime inheritance probe passed. Standard parameter tests retain strict failure/revision assertions and now also cover an invalid array element.
- Cold-load testing reproduced a second implementation defect: batch add_node copied RF_Transient preflight settings, so newly added nodes were omitted on disk/rejected when loading. Changed batch commit to native AddNodeOfType and application of already-prevalidated settings, not copying transient flags. The native batch regression checks node/settings ownership and persistence flags. A fresh fixture then passed save, owned-map switch/reload, and a new-process cold load with its grid/spawner nodes, stable getter reference, graph-instance/two-component parameter values and 100 generated instances per component, plus spline coordinates 333/444/555 and edited=true.
- PCG-disabled compatibility: a distinct `Variants/PCGDisabled/PCGDisabledValidation.uproject` built and started with actual definitions MCP_HAS_PCG=0 and MCP_HAS_PCG_EDITOR=0, exposes only unreal, and explicitly refuses PCG_PLUGIN_NOT_AVAILABLE. Its headless CloseMainWindow attempt could not close a window that did not exist; the supported native graceful-close action succeeded. Final variant source refresh/build/start/normal-close exited 0. PCG enabled without PCGEditor and other engines/platforms remain NOT RUN.
- After separate user approval, six temporary scoped profiles were used for both-transport checks. Exact scope sets (write/destructive do not imply read), read/write positive controls, missing/wrong consent, outside/nested resource paths, project restriction and unchanged graph snapshots pass. **Remaining real blocker:** full component paths contain a colon, but shared path confinement rejects all colons as noncanonical, so path-restricted generate_pcg_graph fails before handler dispatch; cross-principal operation-store runtime acceptance is blocked. No path restriction was removed and the shared gate was not weakened. WS wrong-project authentication is fail-closed but loses the typed reason, surfacing NOT_CONNECTED; this is documented, not reported as transport error-code parity.
- Whole-plugin native automation is not green: the first broad run was 93/99, with six failures outside the PCG change files: Sequence.MovieRender.NativeTimeoutPolicy; Diagnostics.HookSequenceTerminalInPrevious; Foundation.Diagnostics.RotationPromotesCrashedSession; Foundation.Diagnostics.CorruptAndOversizedIgnored; Foundation.LiveStateRevisions.Snapshot; Foundation.PrequeueGate.ScanTruncationFailsClosed. Their unchanged source files do not prove baseline behavior; no baseline binary comparison or unrelated source fix is claimed. Preserve exact results and do not report complete native acceptance.
- Latest whole-tree static gates after the fixes exit 0: ESLint, type-check, unit 232 files/2763 tests, registry/manifest/headers checks, static parameter audit 3610 cases and optional 2281/2281, 50 retrieval evals, build, built-dist smoke and git diff --check. Evidence `tmp/pcg-validation/postfix-static-1792235012392.json` and its per-command logs. Static audit coverage is not 3610 live tests.
- Final linked PCG regression: native PCG 8/8 and Requests 2/2; WS reliable editing 30/30, execution 20/20, parameters 23/23. The expanded parameter suite initially used reference equality for an array assertion (reported equal-looking arrays as different); changed that test to assert length and all three elements, retaining the full revision-equality assertion, then reran 23/23. Latest full-plugin native run is 94/100 with the same six failures; no blanket all-tests-pass claim.
- Final scoped tests deliberately exit 1: both transports pass graph scope/consent/path/project controls and record the component-path positive-control failures, rather than broadening the profiles to bypass the refusal. The WS wrong-project refusal is distinguished from exact error-code parity. Temporary profiles and credential file were removed after the tests, original DefaultGame.ini bytes restored, editor restarted, and an old test credential rejected with HTTP 401. Exact known-token scan over 209 local evidence/test files found zero matches outside designated temporary credential/config storage; this is not a comprehensive secret audit.
- Final isolated editor PID40908 loads the current linked binary; final cold-load recheck passes again after credential removal. The disabled-variant editor is closed. Source fixes/tests/docs remain uncommitted (8 modified tracked files plus new McpPCGParameterTests.cpp); user checkpoint HEAD remains 501fc0ed. No FY editor command/write/save/restart was performed.
- Consolidated local index: `D:/UE_MCP_PCG_Validation/Saved/PCGValidation/postcommit-validation-summary.json`; it links original failed batches and later passing reruns, static gates, loaded source/binary identities, persistence and disabled profiles, native failures, scoped limitations, credential removal and exact-token scan. Raw internal evidence is not publication material.
- Further work remains: A09 spline-filter/subgraph/custom-BP output/tag acceptance; broader selector/custom-wrapper side-effect boundaries and native special connection rules; PCG-specific Undo/Redo; real save failures and multi-asset subgraph partial receipts; reflection/revision size-cost limits; the scoped-component-path blocker and cross-principal execution proof; broad type/failure and peripheral compatibility coverage. This checkpoint is not full T00–T12 completion.

### 2026-10-17: Next-Batch Preparation and Assessment (No Implementation)

#### Request, Baseline and Work Performed

- User request: prepare and assess the next batch. Owner: Claude Opus 5 / main session. This assessment is complete; the proposed implementation and live tests below have not started and are not new authorizations.
- Rechecked the standalone repository: branch `feat/pcg-reliable-authoring`, HEAD `501fc0ed00e777facd1d701b5d2a150ae11f1105`, eight modified tracked files plus one new native test. Preserved all previous fixes. No worktree, branch switch, checkout, reset, staging, commit or publication.
- Reviewed the local checkpoint index, current path scan/canonicalizer/authorization predicates, exact PCG component resolvers and operation ownership, both sides of WS authentication, TS connection/error propagation, and direct source/test pairs for the six native failures.
- Offline preflight command: `npx.cmd vitest run src/automation/handshake.test.ts tests/unit/automation/bridge_not_connected_reason.test.ts src/tools/catalog/capabilities/semantic/semantic-paths.test.ts tests/unit/plugin/prequeue-gate-contracts.test.ts`. Result: exit 0, four files / 83 tests passed. These are existing TS/source-contract tests, not new coverage or native runtime acceptance.
- Compared the six failures' direct implementation/test paths against `afc8287d88a9edcf518ef8749fbdc507e5f87b0e` using `git diff --exit-code`: no differences in the selected paths. This strengthens source-level attribution only; it does not replace a baseline-binary run or establish that the whole dependency graph is unchanged.
- Git Bash still fails before executing a command (`add_item ... failed, errno 1`); used PowerShell and dedicated file tools. No system-security configuration changes. No editor calls, deployment, process actions or credentials were needed; the old PID/deployment identity was not revalidated as a live identity during this assessment.

#### Recommended Immediate Batch: N1 — Unblock A15, Then Attribute the Six Failures

| Slice | Proposed scope | Readiness / effort / risk | Exit condition |
| --- | --- | --- | --- |
| N1a | Canonical component-object-path confinement and its negative controls | Ready for implementation review; medium effort, high security impact | An exact in-prefix component is usable on both transports; malformed/outside paths are still refused before mutation |
| N1b | Preserve wrong-project WS refusal through native handshake and TS gateway | Ready for implementation review; medium effort, cross-layer compatibility risk | Authenticated wrong-project calls report PROJECT_NOT_PERMITTED; real disconnection remains NOT_CONNECTED; no raw peer text or credential leaks |
| N1c | Cross-principal operation and active-cancellation acceptance | Test design ready; depends on N1a and approved temporary profiles | Owner/other-principal and cross-transport cases pass with actual operation/lease/native-state assertions |
| N1d | Baseline attribution and targeted reproduction of the six non-PCG native failures | Source triage complete; runtime attribution not run | Classify each failure as baseline behavior, changed behavior, fixture/contract drift or environment-specific; record evidence without unrelated fixes |

Order: N1a -> N1b -> N1c. N1d source triage is independent; its runtime work must use a separate owned baseline variant rather than replacing the current plugin or checking out the working tree. Do not hold all PCG work for an unrelated framework rewrite, but do not label the whole-plugin native run green while failures remain.

**N1a: Path semantics and minimum change boundary**

- Confirmed two refusal sites, not one: `Foundation/BridgeHelpers/Security/McpAssetPathCanonical.h:146` rejects any colon; `Foundation/McpCapabilityPathScan.cpp:43` then retains the raw rooted candidate; `Foundation/McpCapabilityAuthorization.cpp:199` refuses it. Removing the last colon check alone would let an unvalidated raw object string reach prefix matching and is not an acceptable fix.
- Proposed approach: reuse the Foundation path boundary and distinguish ordinary content paths from validated absolute UObject subobject addresses. Validate the entire object address before deriving its owning package for folder/package confinement. Keep the original full locator for exact game-thread resolution; never turn a malformed suffix into an authorized package merely by stripping at the first colon.
- Keep the generic asset/file sanitizer's current behavior and existing valid asset-prefix comparisons. Do not globally allow colons, introduce actor-name fallback, turn content-prefix grants into actor/subobject ACLs, or add a PCG-only permission bypass. `/Content` alias handling stays in the existing shared map. Any accepted alias must resolve identically in the gate and handler; otherwise refuse it.
- Socket-thread predicates remain pure string checks: no UObject lookup, asset loading, editor-world access or engine-private APIs there. Game-thread resolution must still match the actual current-world component's full path. Parameter targets and execution currently normalize differently (`McpPCGParamTarget.cpp:30` versus `McpPCGExecContext.cpp:13`); explicitly test this, rather than promising all aliases already work.
- Native change candidates: shared path helper, `McpCapabilityPathScan.cpp`, `McpCapabilityAuthorization.cpp`, focused native authorization tests; only change PCG resolvers if canonical-form parity requires it. Respect the capped Foundation root directory and use a responsibility subdirectory for any new helper/test.
- TS review candidates: `semantic/paths.ts` and the dispatch argument boundary. TS has root/syntax checks, not a disclosed copy of each principal's allowed prefixes; do not export those prefixes or build a parallel client-side authority. Add matched positive/negative syntax tests and keep plugin enforcement authoritative.
- Proposed matrix: real current-world component; in-prefix and same-text sibling-prefix maps; existing exact asset-prefix behavior; nested/array values under unusual keys; mixed allowed target plus disallowed reference; traversal; drive/UNC/host paths; control/NUL characters; malformed/multiple-colon or empty subobject suffix; unknown mount; supported `/Content`/separator variants versus exact locator resolution; payload scan depth/node exhaustion with a shallow positive control. Refusal assertions include unchanged graph revision, parameter values and managed products; no new operation may be admitted.

**N1b: The WS typed-reason gap starts in C++, not just in TS**

- Source-level refinement of the previous checkpoint wording: `Transport/Connection/McpConnectionManagerAuthority.cpp:39` computes a project refusal but returns only `false`; `McpConnectionManagerMessages.cpp:172` maps every authentication failure to INVALID_CAPABILITY_TOKEN. The TS client therefore does not currently receive PROJECT_NOT_PERMITTED to preserve.
- Further loss sites: `src/automation/handshake.ts:82` accepts only bridge_ack; bridge-client/events carry a reason string; `connection-lifecycle.ts:60` deliberately sanitizes failures; `bridge.ts:177` reduces connection failure to a boolean; `server/gateway/gateway-execute.ts:83` emits NOT_CONNECTED. Fixing the handshake listener alone cannot close parity.
- Proposed approach: carry a closed-set non-secret refusal code from token/project decision through the native bridge_error and TS connection outcome into the existing gateway refusal envelope. Preserve token validation, project rejection before socket registration, constant-time comparison, listener/timer cleanup, retry behavior and exactly-once settlement.
- Accept no arbitrary peer string as an authority code, message, path or suggestion. Unknown/malformed bridge_error and old plugins fall back safely. Preserve NOT_CONNECTED for a missing listener, timeout, TLS/socket failure or generic unavailability; invalidate an old authentication refusal when a later connection attempt succeeds or fails differently. No second connect/dispatch path and no broad reconnect/protocol redesign.
- Change candidates also include `Public/McpConnectionManager.h`, WS authority/messages, TS handshake/schema/events/state, connection lifecycle, bridge/server connection boundary and gateway receipt tests. This is wider than a one-file error-string fix, so keep it a distinct reviewable slice.

**N1c: Prove operation ownership, not an invented world-resource ACL**

- Same-principal generation/status must succeed using exact allowed paths, on native and WS. Exercise native-created operation -> WS status/cancel and WS-created operation -> native status/cancel; verify the same trusted principal is used on both transports.
- A second principal with the same path/scope grants must receive PCG_OPERATION_NOT_FOUND for the first principal's operation status and cancellation. Use an active delay probe to prove the rejected cancellation did not cancel native work or release its lease; also test completed operations and a real other component, not only an invented missing path.
- Recheck the owner's operation and native generation after every refusal. Preserve missing/wrong-consent checks, exact scope sets and no-mutation path controls. A request-supplied identity must not replace the trusted request registry identity.
- Managed inventory is a path/scope-authorized current-world read, not a principal-private job record. Do not require all inventory reads by the second principal to fail or invent a new ACL; assert that another principal's activeOperationId/retained receipt is not exposed.
- Previous temporary credentials were removed and revoked. A new live scoped run requires explicit authorization for that new temporary installation; this preparation does not reuse the old grant. Require no Admin in the scoped profiles, loopback/token protection unchanged, secret-free evidence, restore original configuration and verify old test tokens are invalid after cleanup.

#### N1d: Six-Failure Source Triage — Not Final Runtime Attribution

All plugin paths below are relative to `plugins/EngineWire/Source/EngineWire/Private/`.

| Failure(s) | Verified source observation | Next evidence required; avoid |
| --- | --- | --- |
| Sequence.MovieRender.NativeTimeoutPolicy | Test `Domains/Sequence/MovieRender/McpSeqMRQTests.cpp:28` sets renderTimeoutMs=3600000 and expects 3635s; policy `MCP/Transport/McpNativeTransportTimeoutPolicy.cpp:23` reads timeoutMs. Current record `src/tools/catalog/capabilities/records/manage-sequence/mrq.ts:154` caps renderTimeoutMs at 300000. | Trace accepted params through the real timeout call site and compare baseline. Do not increase the five-minute contract or alter transport-wide deadlines to satisfy an old test. |
| Foundation.LiveStateRevisions.Snapshot | `Foundation/McpLiveStateRevisions.cpp:19` adds serverInstanceId metadata to four revision counters; test expects exactly four JSON keys. | Validate the intended five-field output and stable per-process identity. Do not delete restart metadata or add serverInstanceId to the four accepted expectedRevisions keys just to make the test pass. |
| Foundation.PrequeueGate.ScanTruncationFailsClosed | `Tests/McpPrequeueGateCoverageTests.cpp:108` nests 12 levels, while `Foundation/McpCapabilityPathScan.cpp:27` has a depth limit of 24. The claimed over-limit fixture is inside the current limit. | Exercise real below/at/above depth boundaries and node exhaustion, then CheckPaths plus CheckPathCoverage. Do not lower the production limit merely to preserve the stale fixture or infer a proven gate bypass from this assertion alone. |
| Diagnostics.HookSequenceTerminalInPrevious; Foundation.Diagnostics.RotationPromotesCrashedSession; Foundation.Diagnostics.CorruptAndOversizedIgnored | All involve replacing current-session.json. `Foundation/Diagnostics/McpDiagnosticsSnapshot.cpp:234` uses IPlatformFile::MoveFile with an existing target; native Windows `D:/UE_5.7/Engine/Source/Runtime/Core/Private/Windows/WindowsPlatformFile.cpp:1218` calls MoveFileW. Rotation's fresh-current write does not check its result. This is a strong replacement-failure candidate, not a new runtime proof. | Reproduce first-write versus replacement under an owned temp root, capture move/write results and preserved files, then run the three tests alone and together on baseline/current binaries. Do not delete prior crash evidence or weaken assertions to obtain green. |

- If a clean baseline reproduces an unrelated defect, record it separately for disposition; no automatic diagnostics/MRQ/framework refactor in the PCG batch. If a PCG change is causally responsible, fix that smallest dependency and rerun its regression. Test-only corrections require evidence of the intended contract, not just matching the current implementation.
- A baseline variant must be independently owned, use the same native engine/configuration and direct test names, carry its own ports/binary/source identity, and never replace the current validation deployment. A source archive in a new directory is preferable to changing branches or creating an unrequested worktree. No baseline variant has been created in this assessment.

#### Gate, Effort and Stop Conditions

- N1a and N1b are each medium-sized, security-sensitive changes; N1c needs one serial live validation window after a full link. N1d is small-to-medium for controlled attribution, but its remediation cost is unknown. These are planning estimates, not elapsed-time promises or guaranteed pass counts.
- First add failing focused behavioral tests, then the minimal fix; use source-contract tests only for security wiring/structure. Run type-check, targeted tests and structural budgets before deployment. At batch close run full static gates/build/smoke, normal native compile+link, revalidate loaded source/binary/project identity, focused native authorization/PCG/Requests tests, both-transport scoped matrix and existing PCG suites. Preserve original failed evidence.
- Any editor close/restart or temporary-credential grant remains limited to a separately verified isolated target and its explicit permission boundary. No FY actions, force kill, engine-source changes, generic asset-path weakening, generated-file edits, version bump, commit or external publication.
- Stop the affected slice if a correct fix needs broader permission semantics, incompatible object-path behavior or unrelated transport redesign; retain the failing tests and document the boundary. Complete independent assessment work rather than weakening the security policy.
- N1 is complete only when A15's positive controls and principal-isolation cases actually run and pass, WS refusal parity is explicit, and all six native failures have individual evidence/disposition. Attribution alone does not turn 94/100 into 100/100 or mark T00–T12 DONE.

#### Following Batches (Not Folded Into N1)

1. **N2: Real PCG workflow and parameter breadth** — A09 spline sampling -> attribute filter -> subgraph -> custom PCG Blueprint -> spawner, with nonempty counts/transforms and the expected custom output tag; expand parameter types/propagation failures and multiple ISM/HISM/managed-actor output checks. Confirm native exported/Blueprint API feasibility first; no new generic Blueprint framework or FY fixtures.
2. **N3: Reliability boundaries** — selector/custom-wrapper side-effect preflight, native special pin rules, PCG-specific Undo/Redo and caller transactions, true save failures/ROLLBACK_FAILED, honest multi-asset partial receipts, and reflected-value/revision resource budgets. Treat each failure mode separately, not as an undifferentiated regression run.
3. **N4: Compatibility and consolidated delivery** — PCG enabled without PCGEditor feasibility/build, supported-version/platform evidence where available, representative old/non-PCG live calls, then sanitized single-PR materials. Other engines/platforms remain NOT RUN until tested. Publication and any additional commit still require authorization.

Assessment deliverable: this ledger section and the corrected WS limitation explanation in `docs/pcg-authoring.md`. Only documentation changed in this preparation round; the prior source/test fixes remain untouched and uncommitted.

### 2026-10-17: N1 Implementation and Acceptance

- The user explicitly requested starting the next batch and permitted Sonnet assistance, with main-session acceptance. Two bounded Sonnet assignments completed: WS refusal propagation plus focused tests, and an independently owned original-baseline source/build variant. Neither agent accessed a live editor. Main reviewed the WS diff and added malformed-frame/schema/listener-cleanup tests before runtime acceptance.
- A separate explicit user choice approved this round's normal PCGValidation close/restarts and six temporary confined profiles: reader/write/destructive exact single scopes, ownerA/B Read+Write+Destructive, wrongProject Read+Write; no scoped Admin. The original one-off credential approval was not silently reused. Main owns configuration restoration, revocation and serial live testing.
- N1a implementation: new shared lexical subobject validator under Foundation/BridgeHelpers/Security; path scan retains the validated full address; confinement checks its owning package. Generic content/file canonicalizers were not changed to accept arbitrary colons. Exact PCG parameter/execution/status/cancel resolvers reuse the same validator. TS uses the existing shared root policy, and its existing Content alias normalizer was extracted for reuse rather than duplicated. Legacy short component names in the old execution interface remain accepted. The generated-request unit fixture now uses an actual component address, not a package-only string.
- N1b implementation: native WS authentication returns a closed-set refusal discriminator; valid-token project refusal stays PROJECT_NOT_PERMITTED before socket registration, while token failure remains INVALID_CAPABILITY_TOKEN. TS propagates only the known project refusal through the normal connection/gateway path, retains NOT_CONNECTED for ordinary unavailability, clears stale refusal on later attempts, validates malformed frames through the existing schema and closes rejected handshakes. No peer message/path/credential is reflected into the typed cause.
- Full normal native compile/link and loaded-module/source/loopback identity checks passed. The first new native run was 3/4: the NUL test used AppendChar(0), which did not establish the intended embedded-NUL fixture. Changed the fixture to insert into its character array, asserted that it actually contains NUL, and added an explicit full-length check to the validator. Rebuilt/reloaded: authorization 4/4, PCG 8/8 and Requests 2/2 pass. Original failed evidence is retained.
- Complete static gate batch exited 0 (11 commands): ESLint, type-check, unit, registry/manifest/headers checks, parameter audit, retrieval evals, build, built-dist smoke and git diff --check. Additional main-session malformed-handshake tests were run before that final batch. These remain separate from native/runtime evidence.
- Live security harness corrections are not implementation fixes: parameter/graph changes can trigger native auto-regeneration, so wait for native idle before beginning the lease test; WS failed execution state may be under result.result, so unwrap its actual receipt rather than weaken the cancellation-state assertion.
- An additional mixed custom PCGValidationDelaySettings -> spawner fixture returned PCG_INPUT_CHANGED during an intended unchanged run. Attribution remains UNRESOLVED; no revision/ownership assertion or production safeguard was relaxed. Failed receipt: `Saved/PCGValidation/n1-security-1792240416182.json`; disposition and reproduction context: `tmp/pcg-validation/n1-custom-probe-unresolved.json`. Native PCGWaitSettings is used for the deterministic security fixture, still asserting real generation, cross-principal rejection, lease, native cancellation and 100-instance output. Do not treat a passing authority test as acceptance of every custom execution/revision interaction.
- Original baseline variant source/build ownership: `Variants/OriginalBaseline/PCGOriginalBaseline.uproject`, original commit afc8287d88a9edcf518ef8749fbdc507e5f87b0e, 1611 source files with hashes, same native UE 5.7.4/toolchain, MCP_HAS_PCG=1. Normal build exited 0; no current plugin replacement, branch switch or worktree. Runtime baseline comparison is owned by main, not inferred from the build.
- Direct Win32 mechanism probe in a fresh owned directory: first MoveFileW succeeds, replacement of an existing target fails with error 183, old target survives and pending file remains. Evidence `Saved/PCGValidation/FileReplace_31486f81c8cd426c931c8e4c0ea6b3d0/result.json`. This supports the diagnostics replacement candidate; it is not a substitute for the actual plugin/baseline runs.
- Final targeted N1 core acceptance: PASS, with the unresolved custom-probe observation explicitly excluded from any all-workflows claim. All code remains uncommitted; no assistant commit, push or publication.

#### N1 Final Outcomes

- **Implementation and focused runtime:** normal UE 5.7.4 Win64 Development compile/link PASS; verified final loaded DLL SHA-256 `b0839cb70d7285cde27dc80b0996900fccdf232778900381046341613226c0fa`, isolated project/module/source identity and loopback ports. Focused native authorization 4/4, PCG 8/8 and Requests 2/2. Final recorded PCGValidation PID25852 is historical identity evidence, not a future process-control authorization; recheck before acting.
- **Scoped authority:** the final owned native-Wait fixture exits 0 with ten PASS groups, five per transport. It proves actual in-prefix component parameter writes/read/reset, generation, 100-instance managed results and cleanup, native/WS same-principal operation access and cancellation in both directions, other-principal/wrong-real-component refusal, retained completed-operation isolation, and preserved lease/native execution after rejected cancellation. Reader/write/destructive exact-set tests, nested/outside/sibling path, project and missing/wrong consent controls preserve state. The original failures and corrected harness runs are retained, not overwritten.
- **Full regression:** all seven serial groups exit 0: WS long calls, focused PCG/Requests native automation, WS parameters 23/23, reliability 30/30, execution 20/20, native execution-failure states and native long calls. The existing simple persistence fixture passes another independent-process cold verification after temporary-profile removal, including getter GUID/reference, component/asset overrides, 100 products per owner and spline points/edited marker.
- **Static gates:** 11/11 commands exit 0; unit 233 files / 2793 tests, parameter audit 3610 definitions / optional 2281/2281, retrieval evals 50, build and built-dist smoke, and format/registry/manifest/header checks. No records/generated artifacts or plugin version were manually changed in N1.
- **Whole native is still not green:** current source is 96/102 with six failures. An independently built/loaded original-commit project is 84/90 with exactly the same six failure names AND assertion messages. Each of the six also fails when rerun individually on the original binary. This establishes that these observed failures also exist in the original baseline on this native engine/platform; it is not a claim that the failures are harmless or fixed.
- **Original-baseline startup correction:** its first startup timed out before MCP initialization while using an empty local shader cache; the process was closed normally, and the failure report remains. Aligned only the owned baseline renderer/cache settings with the main project's ray-tracing-disabled, read-only engine-pak plus project-local file-DDC setup. Preserved the previous config/manifest, verified all original plugin file hashes and loaded variant DLL path, then reran successfully. No plugin-source or native-engine edit, current deployment replacement, branch switch or worktree. The final original-baseline editor closed normally.
- **Disposition of the six:** MRQ timeout field/limit mismatch, stale four-key snapshot expectation and stale depth-12 truncation fixture retain their concrete source evidence; the three diagnostics failures reproduce on baseline and have the direct Windows replacement mechanism probe as supporting evidence. No unrelated framework or test-threshold changes were made to turn these red results green. Remediation is separate from this attribution slice.
- **Additional failure retained:** the earlier custom-delay/spawner run returned an unexplained input-revision change. Its failed cleanup attempted graph deletion after busy cleanup; the editor later crashed at GetInputSettings in the local PCGValidation delay probe. The causal link is not conclusively established. Retained log/crash context at `Saved/Crashes/UECC-Windows-8D7763724FE8B5CDAB22D3BF092785AD_0000` and `Saved/Logs/PCGValidation-backup-2026.10.17-12.34.42.log`. Updated the harness to wait for native idle before deleting owned objects, recovered the editor, and passed the native-Wait security fixture plus subsequent full regression/cold load. This does NOT close the custom-probe/revision/lifetime issue. Binary crash dumps may contain credentials and must remain private, not be committed or used as PR evidence.
- **Credential cleanup:** six temporary profiles removed, original DefaultGame.ini byte hash restored, credential file deleted, isolated editor restarted, and a removed credential receives HTTP401. The final batch scanned 346 selected text evidence files against its known active main/scoped credentials with zero matches; after the successful baseline rerun and build-log archiving a supplemental main/baseline exact-token scan checked 357 selected text files with zero matches. This is not a comprehensive audit; credential/config storage and binary dumps are excluded. No FY write/save/close/restart action occurred.
- **Evidence:** `D:/UE_MCP_PCG_Validation/Saved/PCGValidation/n1-validation-summary.json` is the final index, with `n1CoreAcceptance=true` and `finalAcceptance=false`. It links failed security/native/startup attempts, later passing runs, source/binary identities, original-baseline broad/individual results, credential revocation, text scans and the unresolved custom-probe disposition. The first final-batch report deliberately retains its failed baseline-startup exit; the independent successful rerun is indexed separately.
- **Next priority:** investigate the isolated custom-probe cleanup/lifetime and unchanged-input revision observation with explicit before/after snapshots and safe idle cleanup before expanding A09 custom-node acceptance. Do not suppress revision checks, disable GC or weaken failure assertions as a workaround. Then continue the remaining N2/N3/N4 work: complex workflow/tag/output types, parameter/selector breadth, Undo/real save/rollback and resource limits, optional-module/engine/platform/old-call compatibility and sanitized single-PR preparation. PCG-disabled was not rebuilt after N1, and PCG-enabled/no-PCGEditor remains NOT RUN. Overall T00–T12 and PR readiness remain incomplete.
