import { randomUUID } from 'node:crypto';
import { runToolTests } from '../../test-runner.mjs';

const runRoot = `/Game/MCP_PCG_Validation/Parameters_${Date.now()}_${randomUUID().replaceAll('-', '')}`;
const graphPath = `${runRoot}/Graph`;
const instancePath = `${runRoot}/Instance`;
const captured = key => '${captured:' + key + '}';
const read = (scenario, name, extra = {}) => ({ scenario, toolName: 'manage_pcg',
  arguments: { action: 'get_pcg_parameters', target: 'graph', graphPath, name, offset: 0, limit: 1 }, expected: 'success', ...extra });
const instanceFixture = `import unreal
assert unreal.SystemLibrary.get_game_name() == 'PCGValidation'
assert not unreal.EditorAssetLibrary.does_asset_exist('${instancePath}')
factory = unreal.PCGGraphInstanceFactory()
factory.set_editor_property('ParentGraph', unreal.load_asset('${graphPath}'))
instance = unreal.AssetToolsHelpers.get_asset_tools().create_asset('Instance', '${runRoot}', unreal.PCGGraphInstance, factory)
assert instance is not None
assert instance.get_path_name() == '${instancePath}.Instance'
`;
const cases = [
  { scenario: 'Setup: create an exclusively owned parameter graph', toolName: 'manage_pcg',
    arguments: { action: 'create_pcg_graph', graphPath, save: false }, expected: 'success',
    assertions: [{ path: 'structuredContent.result.created', equals: true }],
    captureResult: [{ key: 'ownedGraph', fromField: 'result.graphPath' }] },
  { scenario: 'Add a typed graph default with the explicit parameter family selector', toolName: 'manage_pcg',
    arguments: { action: 'edit_pcg_parameters', parameterEdit: 'add', target: 'graph', graphPath, name: 'Spacing', type: 'Double', container: 'none', value: 100, save: false }, expected: 'success' },
  read('Read the stable parameter ID and exact default', 'Spacing', {
    assertions: [{ path: 'structuredContent.result.parameters.0.value', equals: 100 }],
    captureResult: [{ key: 'spacingId', fromField: 'result.parameters.0.id' }, { key: 'before', fromField: 'result.revision' }],
  }),
  { scenario: 'Set a graph default against its observed revision', toolName: 'manage_pcg',
    arguments: { action: 'set_pcg_parameter', target: 'graph', graphPath, name: 'Spacing', value: 200, expectedGraphRevision: captured('before'), save: false }, expected: 'success' },
  { scenario: 'Add a bounded native array default', toolName: 'manage_pcg',
    arguments: { action: 'add_pcg_parameter', graphPath, name: 'Seeds', type: 'Int32', container: 'array', value: [1, 2, 3], save: false }, expected: 'success' },
  { scenario: 'Add a native Vector parameter using typeObject', toolName: 'manage_pcg',
    arguments: { action: 'add_pcg_parameter', graphPath, name: 'Offset', type: 'Struct', typeObject: '/Script/CoreUObject.Vector', value: { x: 1, y: 2, z: 3 }, save: false }, expected: 'success' },
  read('Capture state before a rejected value', 'Spacing', { captureResult: [{ key: 'beforeInvalid', fromField: 'result.revision' }] }),
  { scenario: 'A bad value cannot partially change a graph default', toolName: 'manage_pcg',
    arguments: { action: 'set_pcg_parameter', graphPath, name: 'Spacing', value: 'invalid-double', save: false },
    expected: { condition: 'error', errorPattern: 'INVALID_PARAMETER_VALUE' } },
  read('Verify the failed parameter edit left the graph unchanged', 'Spacing', { assertions: [
    { path: 'structuredContent.result.revision', equals: captured('beforeInvalid') },
    { path: 'structuredContent.result.parameters.0.value', equals: 200 },
  ] }),
  { scenario: 'Setup: create an exclusively owned graph-instance asset with the native factory', toolName: 'system_control',
    arguments: { action: 'execute_python', code: instanceFixture }, expected: 'success' },
  { scenario: 'Read graph-instance inheritance by its exact asset path', toolName: 'manage_pcg',
    arguments: { action: 'get_pcg_parameters', target: 'graphInstance', graphInstancePath: instancePath, name: 'Spacing', offset: 0, limit: 1 }, expected: 'success',
    assertions: [{ path: 'structuredContent.result.parameters.0.value', equals: 200 }, { path: 'structuredContent.result.parameters.0.overridden', equals: false }] },
  { scenario: 'Override a single graph instance without changing the default', toolName: 'manage_pcg',
    arguments: { action: 'set_pcg_parameter', target: 'graphInstance', graphInstancePath: instancePath, name: 'Spacing', value: 333, save: false }, expected: 'success' },
  { scenario: 'Reset the instance override and resume inheritance', toolName: 'manage_pcg',
    arguments: { action: 'reset_pcg_parameter_override', target: 'graphInstance', graphInstancePath: instancePath, name: 'Spacing', save: false }, expected: 'success',
    assertions: [{ path: 'structuredContent.result.parameters', includesObject: { name: 'Spacing', value: 200, overridden: false } }] },
  { scenario: 'Bind a native getter to the stable graph parameter', toolName: 'manage_pcg',
    arguments: { action: 'add_pcg_node', graphPath, settingsClass: 'PCGUserParameterGetSettings', parameterName: 'Spacing', save: false }, expected: 'success',
    captureResult: [{ key: 'getter', fromField: 'result.nodeId' }] },
  { scenario: 'Rename through the native API while retaining references', toolName: 'manage_pcg',
    arguments: { action: 'rename_pcg_parameter', graphPath, name: 'Spacing', newName: 'PointSpacing', save: false }, expected: 'success' },
  read('Rename keeps the parameter GUID', 'PointSpacing', { assertions: [{ path: 'structuredContent.result.parameters.0.id', equals: captured('spacingId') }],
    captureResult: [{ key: 'beforeRemoval', fromField: 'result.revision' }] }),
  { scenario: 'A referenced parameter cannot be removed implicitly', toolName: 'manage_pcg',
    arguments: { action: 'remove_pcg_parameter', target: 'graph', graphPath, name: 'PointSpacing', expectedGraphRevision: captured('beforeRemoval'), save: false },
    consent: { capability: 'manage_pcg.remove_pcg_parameter', acknowledge: 'explicit' },
    expected: { condition: 'error', errorPattern: 'PARAMETER_IN_USE' } },
  read('Refused removal leaves the entire graph unchanged', 'PointSpacing', { assertions: [{ path: 'structuredContent.result.revision', equals: captured('beforeRemoval') }] }),
  { scenario: 'Remove an unused parameter without cascading nodes', toolName: 'manage_pcg',
    arguments: { action: 'remove_pcg_parameter', graphPath, name: 'Seeds', save: false }, expected: 'success',
    consent: { capability: 'manage_pcg.remove_pcg_parameter', acknowledge: 'explicit' } },
  { scenario: 'Cleanup: delete only the uniquely named instance created above', toolName: 'manage_asset',
    arguments: { action: 'delete', path: instancePath }, expected: 'success',
    consent: { capability: 'asset.delete', acknowledge: 'elevated' } },
  { scenario: 'Cleanup: delete only the graph proven created by this run', toolName: 'manage_asset',
    arguments: { action: 'delete', path: captured('ownedGraph') }, expected: 'success',
    consent: { capability: 'asset.delete', acknowledge: 'elevated' } },
];

runToolTests('manage_pcg_parameters', cases, {
  isolatedProject: { projectName: process.env.UNREAL_MCP_TEST_PROJECT_NAME, projectDir: process.env.UE_PROJECT_PATH,
    editorBaseDir: process.env.UE_EDITOR_BASE_DIR, engineVersionPrefix: process.env.UNREAL_MCP_TEST_ENGINE_VERSION },
  foldTwins: false,
});
