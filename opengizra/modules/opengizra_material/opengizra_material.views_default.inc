<?php
/**
 * @file
 * opengizra_material.views_default.inc
 */

/**
 * Implements hook_views_default_views().
 */
function opengizra_material_views_default_views() {
  $export = array();

  $view = new view;
  $view->name = 'material';
  $view->description = '';
  $view->tag = 'default';
  $view->base_table = 'field_collection_item';
  $view->human_name = 'Material';
  $view->core = 7;
  $view->api_version = '3.0';
  $view->disabled = FALSE; /* Edit this to true to make a default view disabled initially */

  /* Display: Master */
  $handler = $view->new_display('default', 'Master', 'default');
  $handler->display->display_options['title'] = 'Bill of Materials';
  $handler->display->display_options['access']['type'] = 'none';
  $handler->display->display_options['cache']['type'] = 'none';
  $handler->display->display_options['query']['type'] = 'views_query';
  $handler->display->display_options['query']['options']['query_comment'] = FALSE;
  $handler->display->display_options['exposed_form']['type'] = 'basic';
  $handler->display->display_options['pager']['type'] = 'full';
  $handler->display->display_options['style_plugin'] = 'default';
  $handler->display->display_options['row_plugin'] = 'fields';
  /* No results behavior: Global: Text area */
  $handler->display->display_options['empty']['area']['id'] = 'area';
  $handler->display->display_options['empty']['area']['table'] = 'views';
  $handler->display->display_options['empty']['area']['field'] = 'area';
  $handler->display->display_options['empty']['area']['empty'] = FALSE;
  $handler->display->display_options['empty']['area']['content'] = 'No Bill of Materials are referencing this Material.';
  $handler->display->display_options['empty']['area']['format'] = 'filtered_html';
  $handler->display->display_options['empty']['area']['tokenize'] = 0;
  /* Relationship: Field collection item: Entity with the Info (field_bom_info) */
  $handler->display->display_options['relationships']['field_bom_info_node']['id'] = 'field_bom_info_node';
  $handler->display->display_options['relationships']['field_bom_info_node']['table'] = 'field_collection_item';
  $handler->display->display_options['relationships']['field_bom_info_node']['field'] = 'field_bom_info_node';
  $handler->display->display_options['relationships']['field_bom_info_node']['required'] = 0;
  /* Field: Content: Title */
  $handler->display->display_options['fields']['title']['id'] = 'title';
  $handler->display->display_options['fields']['title']['table'] = 'node';
  $handler->display->display_options['fields']['title']['field'] = 'title';
  $handler->display->display_options['fields']['title']['relationship'] = 'field_bom_info_node';
  $handler->display->display_options['fields']['title']['label'] = '';
  $handler->display->display_options['fields']['title']['alter']['alter_text'] = 0;
  $handler->display->display_options['fields']['title']['alter']['make_link'] = 0;
  $handler->display->display_options['fields']['title']['alter']['absolute'] = 0;
  $handler->display->display_options['fields']['title']['alter']['external'] = 0;
  $handler->display->display_options['fields']['title']['alter']['replace_spaces'] = 0;
  $handler->display->display_options['fields']['title']['alter']['trim_whitespace'] = 0;
  $handler->display->display_options['fields']['title']['alter']['nl2br'] = 0;
  $handler->display->display_options['fields']['title']['alter']['word_boundary'] = 1;
  $handler->display->display_options['fields']['title']['alter']['ellipsis'] = 1;
  $handler->display->display_options['fields']['title']['alter']['more_link'] = 0;
  $handler->display->display_options['fields']['title']['alter']['strip_tags'] = 0;
  $handler->display->display_options['fields']['title']['alter']['trim'] = 0;
  $handler->display->display_options['fields']['title']['alter']['html'] = 0;
  $handler->display->display_options['fields']['title']['element_label_colon'] = FALSE;
  $handler->display->display_options['fields']['title']['element_default_classes'] = 1;
  $handler->display->display_options['fields']['title']['hide_empty'] = 0;
  $handler->display->display_options['fields']['title']['empty_zero'] = 0;
  $handler->display->display_options['fields']['title']['hide_alter_empty'] = 1;
  $handler->display->display_options['fields']['title']['link_to_node'] = 1;
  /* Contextual filter: Field collection item: Material (field_material) */
  $handler->display->display_options['arguments']['field_material_target_id']['id'] = 'field_material_target_id';
  $handler->display->display_options['arguments']['field_material_target_id']['table'] = 'field_data_field_material';
  $handler->display->display_options['arguments']['field_material_target_id']['field'] = 'field_material_target_id';
  $handler->display->display_options['arguments']['field_material_target_id']['default_action'] = 'not found';
  $handler->display->display_options['arguments']['field_material_target_id']['default_argument_type'] = 'fixed';
  $handler->display->display_options['arguments']['field_material_target_id']['default_argument_skip_url'] = 0;
  $handler->display->display_options['arguments']['field_material_target_id']['summary']['number_of_records'] = '0';
  $handler->display->display_options['arguments']['field_material_target_id']['summary']['format'] = 'default_summary';
  $handler->display->display_options['arguments']['field_material_target_id']['summary_options']['items_per_page'] = '25';
  $handler->display->display_options['arguments']['field_material_target_id']['break_phrase'] = 0;
  $handler->display->display_options['arguments']['field_material_target_id']['not'] = 0;

  /* Display: Content pane */
  $handler = $view->new_display('panel_pane', 'Content pane', 'panel_pane_1');
  $handler->display->display_options['argument_input'] = array(
    'field_material_target_id' => array(
      'type' => 'context',
      'context' => 'entity:node.nid',
      'context_optional' => 0,
      'panel' => '0',
      'fixed' => '',
      'label' => 'Field collection item: Material (field_material)',
    ),
  );
  $export['material'] = $view;

  return $export;
}
