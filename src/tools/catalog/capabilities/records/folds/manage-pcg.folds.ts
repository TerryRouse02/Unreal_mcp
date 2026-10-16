// Fold specs for manage_pcg. Data only; see ../shared/fold.ts.
import { byTarget } from '../shared/fold-spec.js';
import type { FoldSpec } from '../shared/fold-types.js';

export const MANAGE_PCG_FOLDS: readonly FoldSpec[] = [
  {
    primary: 'control_pcg_execution', selector: 'control',
    summary: 'Explicit native PCG lifecycle control: clean one component managed resources or request cancellation of an owned generation operation.',
    topics: ['clean pcg generated resources', 'cancel pcg generation', 'pcg execution control'],
    members: { cleanup: 'cleanup_pcg_component', cancel: 'cancel_pcg_operation' },
  },
  {
    primary: 'edit_pcg_parameters', selector: 'parameterEdit',
    summary: 'Add graph parameter schema/defaults, change defaults or instance overrides, rename stable parameters, or reset an override.',
    topics: ['edit pcg parameters', 'pcg component overrides', 'rename graph parameter', 'reset pcg override'],
    members: { add: 'add_pcg_parameter', set: 'set_pcg_parameter', rename: 'rename_pcg_parameter', reset_override: 'reset_pcg_parameter_override' },
  },
  {
    primary: 'mutate_pcg_graph', selector: 'mutation',
    summary: 'Explicit destructive PCG graph edits: disconnect pins, remove a node, or apply an atomic batch with destructive steps.',
    topics: ['disconnect pcg pins', 'remove pcg node', 'destructive pcg batch'],
    members: { disconnect: 'disconnect_pcg_pins', remove_node: 'remove_pcg_node', batch: 'batch_edit_pcg_graph_destructive' },
  },
  {
    primary: 'inspect_pcg', selector: 'view',
    summary: 'Discover PCG settings classes and schemas, read backend or existing editor graphs, or validate native pin compatibility.',
    topics: ['inspect pcg graph', 'pcg node types', 'pcg settings schema', 'read pcg pins', 'validate pcg connections'],
    members: { node_types: 'list_pcg_node_types', settings_schema: 'get_pcg_settings_schema', graph: 'get_pcg_graph', editor_graph: 'get_pcg_editor_graph', validation: 'validate_pcg_graph', parameters: 'get_pcg_parameters', operation_status: 'get_pcg_operation_status', component_results: 'get_pcg_component_results' },
  },
  {
    primary: 'add_pcg_node', selector: 'nodeKind',
    summary: 'Add a node to a PCG graph: any settings class by name, or a typed node (samplers, spawners, filters, data nodes, point operations).',
    topics: ['pcg node', 'surface sampler', 'static mesh spawner', 'density filter', 'landscape data', 'spline sampler', 'transform points'],
    members: {
      node: 'add_pcg_node',
      ...byTarget('add_', ['add_surface_sampler', 'add_spline_sampler', 'add_mesh_sampler', 'add_volume_sampler', 'add_static_mesh_spawner', 'add_actor_spawner', 'add_spline_spawner',
        'add_density_filter', 'add_distance_filter', 'add_height_filter', 'add_slope_filter', 'add_bounds_filter', 'add_bounds_modifier',
        'add_landscape_data_node', 'add_spline_data_node', 'add_actor_data_node', 'add_texture_data_node', 'add_volume_data_node',
        'add_transform_points', 'add_copy_points', 'add_merge_points', 'add_project_to_surface', 'add_self_pruning']),
    },
  },
  {
    primary: 'edit_pcg_graph', selector: 'edit',
    summary: 'Create a PCG graph or subgraph, connect pins, set node settings, or set the partition grid size.',
    topics: ['pcg graph', 'pcg subgraph', 'connect pcg pins', 'pcg node settings', 'partition grid size'],
    members: { create: 'create_pcg_graph', create_subgraph: 'create_pcg_subgraph', sync_editor: 'sync_pcg_editor_graph', move_node: 'move_pcg_node', connect_pins: 'connect_pcg_pins', set_node_settings: 'set_pcg_node_settings', set_partition_grid_size: 'set_pcg_partition_grid_size' },
  },
];
