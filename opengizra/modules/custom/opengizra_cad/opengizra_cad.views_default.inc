<?php
/**
 * @file
 * opengizra_cad.views_default.inc
 */

/**
 * Implements hook_views_default_views().
 */
function opengizra_cad_views_default_views() {
  $export = array();

  $view = new view;
  $view->name = 'pattern';
  $view->description = '';
  $view->tag = 'default';
  $view->base_table = 'node';
  $view->human_name = 'Pattern';
  $view->core = 7;
  $view->api_version = '3.0';
  $view->disabled = FALSE; /* Edit this to true to make a default view disabled initially */

  /* Display: Master */
  $handler = $view->new_display('default', 'Master', 'default');
  $handler->display->display_options['title'] = 'Patterns';
  $handler->display->display_options['access']['type'] = 'perm';
  $handler->display->display_options['cache']['type'] = 'none';
  $handler->display->display_options['query']['type'] = 'views_query';
  $handler->display->display_options['query']['options']['query_comment'] = FALSE;
  $handler->display->display_options['exposed_form']['type'] = 'basic';
  $handler->display->display_options['pager']['type'] = 'none';
  $handler->display->display_options['pager']['options']['offset'] = '0';
  $handler->display->display_options['style_plugin'] = 'default';
  $handler->display->display_options['row_plugin'] = 'fields';
  /* Field: Content: Title */
  $handler->display->display_options['fields']['title']['id'] = 'title';
  $handler->display->display_options['fields']['title']['table'] = 'node';
  $handler->display->display_options['fields']['title']['field'] = 'title';
  $handler->display->display_options['fields']['title']['label'] = '';
  $handler->display->display_options['fields']['title']['alter']['alter_text'] = 0;
  $handler->display->display_options['fields']['title']['alter']['make_link'] = 0;
  $handler->display->display_options['fields']['title']['alter']['absolute'] = 0;
  $handler->display->display_options['fields']['title']['alter']['word_boundary'] = 0;
  $handler->display->display_options['fields']['title']['alter']['ellipsis'] = 0;
  $handler->display->display_options['fields']['title']['alter']['strip_tags'] = 0;
  $handler->display->display_options['fields']['title']['alter']['trim'] = 0;
  $handler->display->display_options['fields']['title']['alter']['html'] = 0;
  $handler->display->display_options['fields']['title']['hide_empty'] = 0;
  $handler->display->display_options['fields']['title']['empty_zero'] = 0;
  $handler->display->display_options['fields']['title']['link_to_node'] = 1;
  /* Field: Content: Files */
  $handler->display->display_options['fields']['field_files_collection']['id'] = 'field_files_collection';
  $handler->display->display_options['fields']['field_files_collection']['table'] = 'field_data_field_files_collection';
  $handler->display->display_options['fields']['field_files_collection']['field'] = 'field_files_collection';
  $handler->display->display_options['fields']['field_files_collection']['alter']['alter_text'] = 0;
  $handler->display->display_options['fields']['field_files_collection']['alter']['make_link'] = 0;
  $handler->display->display_options['fields']['field_files_collection']['alter']['absolute'] = 0;
  $handler->display->display_options['fields']['field_files_collection']['alter']['external'] = 0;
  $handler->display->display_options['fields']['field_files_collection']['alter']['replace_spaces'] = 0;
  $handler->display->display_options['fields']['field_files_collection']['alter']['trim_whitespace'] = 0;
  $handler->display->display_options['fields']['field_files_collection']['alter']['nl2br'] = 0;
  $handler->display->display_options['fields']['field_files_collection']['alter']['word_boundary'] = 1;
  $handler->display->display_options['fields']['field_files_collection']['alter']['ellipsis'] = 1;
  $handler->display->display_options['fields']['field_files_collection']['alter']['more_link'] = 0;
  $handler->display->display_options['fields']['field_files_collection']['alter']['strip_tags'] = 0;
  $handler->display->display_options['fields']['field_files_collection']['alter']['trim'] = 0;
  $handler->display->display_options['fields']['field_files_collection']['alter']['html'] = 0;
  $handler->display->display_options['fields']['field_files_collection']['element_label_colon'] = 1;
  $handler->display->display_options['fields']['field_files_collection']['element_default_classes'] = 1;
  $handler->display->display_options['fields']['field_files_collection']['hide_empty'] = 0;
  $handler->display->display_options['fields']['field_files_collection']['empty_zero'] = 0;
  $handler->display->display_options['fields']['field_files_collection']['hide_alter_empty'] = 1;
  $handler->display->display_options['fields']['field_files_collection']['type'] = 'field_collection_table_view';
  $handler->display->display_options['fields']['field_files_collection']['settings'] = array(
    'edit' => 'Edit',
    'delete' => 'Delete',
    'add' => 'Add',
    'description' => 1,
    'view_mode' => 'full',
    'empty' => 1,
  );
  $handler->display->display_options['fields']['field_files_collection']['group_rows'] = 1;
  $handler->display->display_options['fields']['field_files_collection']['delta_offset'] = '0';
  $handler->display->display_options['fields']['field_files_collection']['delta_reversed'] = 0;
  $handler->display->display_options['fields']['field_files_collection']['delta_first_last'] = 0;
  $handler->display->display_options['fields']['field_files_collection']['field_api_classes'] = 0;
  /* Sort criterion: Content: Post date */
  $handler->display->display_options['sorts']['created']['id'] = 'created';
  $handler->display->display_options['sorts']['created']['table'] = 'node';
  $handler->display->display_options['sorts']['created']['field'] = 'created';
  $handler->display->display_options['sorts']['created']['order'] = 'DESC';
  /* Contextual filter: Content: Referencing Items (field_pattern_entity_reference) */
  $handler->display->display_options['arguments']['field_pattern_entity_reference_target_id']['id'] = 'field_pattern_entity_reference_target_id';
  $handler->display->display_options['arguments']['field_pattern_entity_reference_target_id']['table'] = 'field_data_field_pattern_entity_reference';
  $handler->display->display_options['arguments']['field_pattern_entity_reference_target_id']['field'] = 'field_pattern_entity_reference_target_id';
  $handler->display->display_options['arguments']['field_pattern_entity_reference_target_id']['default_action'] = 'not found';
  $handler->display->display_options['arguments']['field_pattern_entity_reference_target_id']['default_argument_type'] = 'fixed';
  $handler->display->display_options['arguments']['field_pattern_entity_reference_target_id']['default_argument_skip_url'] = 0;
  $handler->display->display_options['arguments']['field_pattern_entity_reference_target_id']['summary']['number_of_records'] = '0';
  $handler->display->display_options['arguments']['field_pattern_entity_reference_target_id']['summary']['format'] = 'default_summary';
  $handler->display->display_options['arguments']['field_pattern_entity_reference_target_id']['summary_options']['items_per_page'] = '25';
  $handler->display->display_options['arguments']['field_pattern_entity_reference_target_id']['break_phrase'] = 0;
  $handler->display->display_options['arguments']['field_pattern_entity_reference_target_id']['not'] = 0;
  /* Filter criterion: Content: Published */
  $handler->display->display_options['filters']['status']['id'] = 'status';
  $handler->display->display_options['filters']['status']['table'] = 'node';
  $handler->display->display_options['filters']['status']['field'] = 'status';
  $handler->display->display_options['filters']['status']['value'] = 1;
  $handler->display->display_options['filters']['status']['group'] = 1;
  $handler->display->display_options['filters']['status']['expose']['operator'] = FALSE;
  /* Filter criterion: Content: Type */
  $handler->display->display_options['filters']['type']['id'] = 'type';
  $handler->display->display_options['filters']['type']['table'] = 'node';
  $handler->display->display_options['filters']['type']['field'] = 'type';
  $handler->display->display_options['filters']['type']['value'] = array(
    'pattern' => 'pattern',
  );

  /* Display: Content pane */
  $handler = $view->new_display('panel_pane', 'Content pane', 'panel_pane_1');
  $handler->display->display_options['argument_input'] = array(
    'field_pattern_entity_reference_target_id' => array(
      'type' => 'context',
      'context' => 'entity:node.nid',
      'context_optional' => 0,
      'panel' => '0',
      'fixed' => '',
      'label' => 'Content: Referencing Items (field_pattern_entity_reference)',
    ),
  );
  $export['pattern'] = $view;

  return $export;
}
