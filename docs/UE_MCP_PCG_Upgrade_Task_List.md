# UE MCP / PCG Capability Upgrade Task List

> Purpose: The sole local task ledger and cross-agent handoff entry point. A successor should be able to understand the goal, constraints, evidence, outstanding work, and acceptance criteria without the original chat history.
>
> This file is internal handoff material and contains local project paths and workspace information; do not submit it as-is, upload it to the author repository, or copy it into a public PR.

## 0. Current Status and Next Steps

- Registration date: 2026-10-15.
- Current phase: The implementation plan has been approved; M0 is complete, M1/M2 functionality and first-round native verification are in progress, and T10–T12 are not yet closed out.
- Completed: Isolated native 5.7.4 project; F01–F04 baseline reproduction; first-hand testing of reliable editing, graph UI, batch operations, and graph parameters; and generation changing from 100 to 25, repeated generation not accumulating, managed-resource cleanup, and regeneration.
- Source changes are still awaiting a new native rebuild; both transports, security failure paths, persistence/cold start, compatibility combinations, and consolidated PR materials are not yet complete. Do not treat first-round results as full acceptance.
- The initial baseline had only the local task ledger untracked; the current feature branch is `feat/pcg-reliable-authoring`, with uncommitted source changes for this task.
- There is no started or pending-to-recover sub-agent work; a successor must not assume background development results exist.
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
4. Recommended isolated project root: `D:\UE_MCP_PCG_Validation`. Before using it, check whether it already contains anything; do not overwrite an existing project. This directory has not been created by this upgrade work, and whether it already exists has not yet been confirmed.
5. Do not close, restart, or overwrite the existing FY editor / plugin deployment, and do not affect production assets.
6. The user and author have no additional Issues, design opinions, or contribution agreements yet; proceed under repository conventions for now.
7. There is currently no authorization to commit automatically, push, publish an Issue, create a PR, or trigger a remote workflow; obtain separate confirmation before any such action.

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
| This task ledger | `D:\hutianle_ArtStream_UGS\Dev_FTY\Unreal_mcp\UE_MCP_PCG_Upgrade_Task_List.md` |

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
| T09 | Minimal relevant fix for spline instance-edit marker (include after plan confirmation) | T02 | NEEDS_VALIDATION | Claude Opus 5 / this session |
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
| A01 | Grid → Transform → Spawner | 100 instances; count and specified first / last transforms are correct | NEEDS_VALIDATION: count and first/last sample readback PASS; specified transform-value assertions remain to be added |
| A02 | Change spacing and repeat generation | 100 → 25; repeated execution does not accumulate | PASS: deployed native and TS/WS |
| A03 | Incompatible connection | Explicit rejection; node / pin / connection snapshot unchanged | PASS: deployed native and TS/WS |
| A04 | Mixed valid / invalid settings | After the whole operation fails, original settings are unchanged | PASS: deployed native and TS/WS |
| A05 | Create with invalid Mesh / class | Clear error, no orphan node or instance-subobject contamination | NEEDS_VALIDATION: invalid Mesh and complete revision assertion PASS; class / subobject edge cases remain |
| A06 | Disconnect / delete / batch | Background graph and graph UI correspond correctly; failure handling and permissions are clear | NEEDS_VALIDATION: standard suite and native recovery / comment tests PASS; extended Undo / failure paths remain |
| A07 | Dynamic pins / type changes | Connection effects are explicitly reported; no silently retained invalid connection | NOT RUN |
| A08 | Three UI-open states | Visible nodes and connection mappings are consistent; manual follow-up editing is possible | NEEDS_VALIDATION: three-state mapping and comment preservation PASS; complex nodes / manual follow-up editing remain to be verified |
| A09 | Spline attribute filtering / subgraph / custom BP | Actual non-empty, correct output and custom-output tag | NOT RUN |
| A10 | Graph parameters for two instances | Default propagation, independent override, reset, rename preserves reference relationships | NEEDS_VALIDATION: two-component propagation / override / reset / GUID rename PASS; getter and instance assets await the latest binary |
| A11 | Managed-resource cleanup | Empty after cleanup, non-managed resources preserved, regeneration works | PASS: deployed native and TS/WS simple ISM workflow; additional output types still need coverage |
| A12 | Current execution status | Success / cancellation / failure / timeout distinguishable; old results not misread | NEEDS_VALIDATION: native terminal states / error clearing / empty output / target deletion PASS; TS long-call fix awaits loading |
| A13 | Save / map-switch reload / independent editor restart | Configuration, references, instance overrides, and generated results persist as specified | NOT RUN: latest linkage / restart permission blocked |
| A14 | Project with PCG disabled | Plugin does not fail to build / start due to missing optional module; capability is clearly unavailable | NOT RUN |
| A15 | Native and TS/WS entry points, permissions | Corresponding operation results agree; scope / consent / path rejection causes no mutation | NEEDS_VALIDATION: normal dual-entry flow / consent rejection PASS; scoped/path/cross-principal remain to be verified |
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
