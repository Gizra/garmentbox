<?php
/**
 * @file
 * opengizra_task.views_default.inc
 */

/**
 * Implements hook_views_default_views().
 */
function opengizra_task_views_default_views() {
  $export = array();

  $view = new view;
  $view->name = 'task_list';
  $view->description = '';
  $view->tag = 'default';
  $view->base_table = 'node';
  $view->human_name = 'Task list';
  $view->core = 7;
  $view->api_version = '3.0';
  $view->disabled = FALSE; /* Edit this to true to make a default view disabled initially */

  /* Display: Master */
  $handler = $view->new_display('default', 'Master', 'default');
  $handler->display->display_options['access']['type'] = 'perm';
  $handler->display->display_options['cache']['type'] = 'none';
  $handler->display->display_options['query']['type'] = 'views_query';
  $handler->display->display_options['query']['options']['query_comment'] = FALSE;
  $handler->display->display_options['exposed_form']['type'] = 'basic';
  $handler->display->display_options['pager']['type'] = 'full';
  $handler->display->display_options['style_plugin'] = 'table';
  $handler->display->display_options['style_options']['columns'] = array(
    'title' => 'title',
  );
  $handler->display->display_options['style_options']['default'] = '-1';
  $handler->display->display_options['style_options']['info'] = array(
    'title' => array(
      'sortable' => 0,
      'default_sort_order' => 'asc',
      'align' => '',
      'separator' => '',
      'empty_column' => 0,
    ),
  );
  $handler->display->display_options['style_options']['override'] = 1;
  $handler->display->display_options['style_options']['sticky'] = 0;
  $handler->display->display_options['style_options']['empty_table'] = 0;
  /* Field: Content: New comments */
  $handler->display->display_options['fields']['new_comments']['id'] = 'new_comments';
  $handler->display->display_options['fields']['new_comments']['table'] = 'node';
  $handler->display->display_options['fields']['new_comments']['field'] = 'new_comments';
  $handler->display->display_options['fields']['new_comments']['label'] = '';
  $handler->display->display_options['fields']['new_comments']['exclude'] = TRUE;
  $handler->display->display_options['fields']['new_comments']['alter']['alter_text'] = 0;
  $handler->display->display_options['fields']['new_comments']['alter']['make_link'] = 0;
  $handler->display->display_options['fields']['new_comments']['alter']['absolute'] = 0;
  $handler->display->display_options['fields']['new_comments']['alter']['external'] = 0;
  $handler->display->display_options['fields']['new_comments']['alter']['replace_spaces'] = 0;
  $handler->display->display_options['fields']['new_comments']['alter']['trim_whitespace'] = 0;
  $handler->display->display_options['fields']['new_comments']['alter']['nl2br'] = 0;
  $handler->display->display_options['fields']['new_comments']['alter']['word_boundary'] = 1;
  $handler->display->display_options['fields']['new_comments']['alter']['ellipsis'] = 1;
  $handler->display->display_options['fields']['new_comments']['alter']['more_link'] = 0;
  $handler->display->display_options['fields']['new_comments']['alter']['strip_tags'] = 0;
  $handler->display->display_options['fields']['new_comments']['alter']['trim'] = 0;
  $handler->display->display_options['fields']['new_comments']['alter']['html'] = 0;
  $handler->display->display_options['fields']['new_comments']['element_label_colon'] = FALSE;
  $handler->display->display_options['fields']['new_comments']['element_default_classes'] = 1;
  $handler->display->display_options['fields']['new_comments']['hide_empty'] = 0;
  $handler->display->display_options['fields']['new_comments']['empty_zero'] = 0;
  $handler->display->display_options['fields']['new_comments']['hide_alter_empty'] = 1;
  $handler->display->display_options['fields']['new_comments']['format_plural'] = 0;
  $handler->display->display_options['fields']['new_comments']['link_to_comment'] = 1;
  /* Field: Content: Nid */
  $handler->display->display_options['fields']['nid']['id'] = 'nid';
  $handler->display->display_options['fields']['nid']['table'] = 'node';
  $handler->display->display_options['fields']['nid']['field'] = 'nid';
  $handler->display->display_options['fields']['nid']['label'] = 'ID';
  $handler->display->display_options['fields']['nid']['alter']['alter_text'] = 0;
  $handler->display->display_options['fields']['nid']['alter']['make_link'] = 0;
  $handler->display->display_options['fields']['nid']['alter']['absolute'] = 0;
  $handler->display->display_options['fields']['nid']['alter']['external'] = 0;
  $handler->display->display_options['fields']['nid']['alter']['replace_spaces'] = 0;
  $handler->display->display_options['fields']['nid']['alter']['trim_whitespace'] = 0;
  $handler->display->display_options['fields']['nid']['alter']['nl2br'] = 0;
  $handler->display->display_options['fields']['nid']['alter']['word_boundary'] = 1;
  $handler->display->display_options['fields']['nid']['alter']['ellipsis'] = 1;
  $handler->display->display_options['fields']['nid']['alter']['more_link'] = 0;
  $handler->display->display_options['fields']['nid']['alter']['strip_tags'] = 0;
  $handler->display->display_options['fields']['nid']['alter']['trim'] = 0;
  $handler->display->display_options['fields']['nid']['alter']['html'] = 0;
  $handler->display->display_options['fields']['nid']['element_label_colon'] = 1;
  $handler->display->display_options['fields']['nid']['element_default_classes'] = 1;
  $handler->display->display_options['fields']['nid']['hide_empty'] = 0;
  $handler->display->display_options['fields']['nid']['empty_zero'] = 0;
  $handler->display->display_options['fields']['nid']['hide_alter_empty'] = 1;
  $handler->display->display_options['fields']['nid']['link_to_node'] = 0;
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
  /* Field: Content: Status */
  $handler->display->display_options['fields']['field_task_status']['id'] = 'field_task_status';
  $handler->display->display_options['fields']['field_task_status']['table'] = 'field_data_field_task_status';
  $handler->display->display_options['fields']['field_task_status']['field'] = 'field_task_status';
  $handler->display->display_options['fields']['field_task_status']['alter']['alter_text'] = 0;
  $handler->display->display_options['fields']['field_task_status']['alter']['make_link'] = 0;
  $handler->display->display_options['fields']['field_task_status']['alter']['absolute'] = 0;
  $handler->display->display_options['fields']['field_task_status']['alter']['external'] = 0;
  $handler->display->display_options['fields']['field_task_status']['alter']['replace_spaces'] = 0;
  $handler->display->display_options['fields']['field_task_status']['alter']['trim_whitespace'] = 0;
  $handler->display->display_options['fields']['field_task_status']['alter']['nl2br'] = 0;
  $handler->display->display_options['fields']['field_task_status']['alter']['word_boundary'] = 1;
  $handler->display->display_options['fields']['field_task_status']['alter']['ellipsis'] = 1;
  $handler->display->display_options['fields']['field_task_status']['alter']['more_link'] = 0;
  $handler->display->display_options['fields']['field_task_status']['alter']['strip_tags'] = 0;
  $handler->display->display_options['fields']['field_task_status']['alter']['trim'] = 0;
  $handler->display->display_options['fields']['field_task_status']['alter']['html'] = 0;
  $handler->display->display_options['fields']['field_task_status']['element_label_colon'] = 1;
  $handler->display->display_options['fields']['field_task_status']['element_default_classes'] = 1;
  $handler->display->display_options['fields']['field_task_status']['hide_empty'] = 0;
  $handler->display->display_options['fields']['field_task_status']['empty_zero'] = 0;
  $handler->display->display_options['fields']['field_task_status']['hide_alter_empty'] = 1;
  $handler->display->display_options['fields']['field_task_status']['settings'] = array(
    'link' => 0,
  );
  $handler->display->display_options['fields']['field_task_status']['field_api_classes'] = 0;
  /* Field: Content: Assignee */
  $handler->display->display_options['fields']['field_task_assignee']['id'] = 'field_task_assignee';
  $handler->display->display_options['fields']['field_task_assignee']['table'] = 'field_data_field_task_assignee';
  $handler->display->display_options['fields']['field_task_assignee']['field'] = 'field_task_assignee';
  $handler->display->display_options['fields']['field_task_assignee']['alter']['alter_text'] = 0;
  $handler->display->display_options['fields']['field_task_assignee']['alter']['make_link'] = 0;
  $handler->display->display_options['fields']['field_task_assignee']['alter']['absolute'] = 0;
  $handler->display->display_options['fields']['field_task_assignee']['alter']['external'] = 0;
  $handler->display->display_options['fields']['field_task_assignee']['alter']['replace_spaces'] = 0;
  $handler->display->display_options['fields']['field_task_assignee']['alter']['trim_whitespace'] = 0;
  $handler->display->display_options['fields']['field_task_assignee']['alter']['nl2br'] = 0;
  $handler->display->display_options['fields']['field_task_assignee']['alter']['word_boundary'] = 1;
  $handler->display->display_options['fields']['field_task_assignee']['alter']['ellipsis'] = 1;
  $handler->display->display_options['fields']['field_task_assignee']['alter']['more_link'] = 0;
  $handler->display->display_options['fields']['field_task_assignee']['alter']['strip_tags'] = 0;
  $handler->display->display_options['fields']['field_task_assignee']['alter']['trim'] = 0;
  $handler->display->display_options['fields']['field_task_assignee']['alter']['html'] = 0;
  $handler->display->display_options['fields']['field_task_assignee']['element_label_colon'] = 1;
  $handler->display->display_options['fields']['field_task_assignee']['element_default_classes'] = 1;
  $handler->display->display_options['fields']['field_task_assignee']['hide_empty'] = 0;
  $handler->display->display_options['fields']['field_task_assignee']['empty_zero'] = 0;
  $handler->display->display_options['fields']['field_task_assignee']['hide_alter_empty'] = 1;
  $handler->display->display_options['fields']['field_task_assignee']['settings'] = array(
    'link' => 1,
  );
  $handler->display->display_options['fields']['field_task_assignee']['field_api_classes'] = 0;
  /* Field: Content: Comment count */
  $handler->display->display_options['fields']['comment_count']['id'] = 'comment_count';
  $handler->display->display_options['fields']['comment_count']['table'] = 'node_comment_statistics';
  $handler->display->display_options['fields']['comment_count']['field'] = 'comment_count';
  $handler->display->display_options['fields']['comment_count']['label'] = 'Replies';
  $handler->display->display_options['fields']['comment_count']['alter']['alter_text'] = 1;
  $handler->display->display_options['fields']['comment_count']['alter']['text'] = '[comment_count]
[new_comments]';
  $handler->display->display_options['fields']['comment_count']['alter']['make_link'] = 0;
  $handler->display->display_options['fields']['comment_count']['alter']['absolute'] = 0;
  $handler->display->display_options['fields']['comment_count']['alter']['external'] = 0;
  $handler->display->display_options['fields']['comment_count']['alter']['replace_spaces'] = 0;
  $handler->display->display_options['fields']['comment_count']['alter']['trim_whitespace'] = 0;
  $handler->display->display_options['fields']['comment_count']['alter']['nl2br'] = 0;
  $handler->display->display_options['fields']['comment_count']['alter']['word_boundary'] = 1;
  $handler->display->display_options['fields']['comment_count']['alter']['ellipsis'] = 1;
  $handler->display->display_options['fields']['comment_count']['alter']['more_link'] = 0;
  $handler->display->display_options['fields']['comment_count']['alter']['strip_tags'] = 0;
  $handler->display->display_options['fields']['comment_count']['alter']['trim'] = 0;
  $handler->display->display_options['fields']['comment_count']['alter']['html'] = 0;
  $handler->display->display_options['fields']['comment_count']['element_label_colon'] = 1;
  $handler->display->display_options['fields']['comment_count']['element_default_classes'] = 1;
  $handler->display->display_options['fields']['comment_count']['empty'] = '0';
  $handler->display->display_options['fields']['comment_count']['hide_empty'] = 0;
  $handler->display->display_options['fields']['comment_count']['empty_zero'] = 0;
  $handler->display->display_options['fields']['comment_count']['hide_alter_empty'] = 1;
  $handler->display->display_options['fields']['comment_count']['format_plural'] = 0;
  /* Field: Content: Last comment time */
  $handler->display->display_options['fields']['last_comment_timestamp']['id'] = 'last_comment_timestamp';
  $handler->display->display_options['fields']['last_comment_timestamp']['table'] = 'node_comment_statistics';
  $handler->display->display_options['fields']['last_comment_timestamp']['field'] = 'last_comment_timestamp';
  $handler->display->display_options['fields']['last_comment_timestamp']['label'] = 'Last updated';
  $handler->display->display_options['fields']['last_comment_timestamp']['alter']['alter_text'] = 0;
  $handler->display->display_options['fields']['last_comment_timestamp']['alter']['make_link'] = 0;
  $handler->display->display_options['fields']['last_comment_timestamp']['alter']['absolute'] = 0;
  $handler->display->display_options['fields']['last_comment_timestamp']['alter']['external'] = 0;
  $handler->display->display_options['fields']['last_comment_timestamp']['alter']['replace_spaces'] = 0;
  $handler->display->display_options['fields']['last_comment_timestamp']['alter']['trim_whitespace'] = 0;
  $handler->display->display_options['fields']['last_comment_timestamp']['alter']['nl2br'] = 0;
  $handler->display->display_options['fields']['last_comment_timestamp']['alter']['word_boundary'] = 1;
  $handler->display->display_options['fields']['last_comment_timestamp']['alter']['ellipsis'] = 1;
  $handler->display->display_options['fields']['last_comment_timestamp']['alter']['more_link'] = 0;
  $handler->display->display_options['fields']['last_comment_timestamp']['alter']['strip_tags'] = 0;
  $handler->display->display_options['fields']['last_comment_timestamp']['alter']['trim'] = 0;
  $handler->display->display_options['fields']['last_comment_timestamp']['alter']['html'] = 0;
  $handler->display->display_options['fields']['last_comment_timestamp']['element_label_colon'] = 1;
  $handler->display->display_options['fields']['last_comment_timestamp']['element_default_classes'] = 1;
  $handler->display->display_options['fields']['last_comment_timestamp']['hide_empty'] = 0;
  $handler->display->display_options['fields']['last_comment_timestamp']['empty_zero'] = 0;
  $handler->display->display_options['fields']['last_comment_timestamp']['hide_alter_empty'] = 1;
  $handler->display->display_options['fields']['last_comment_timestamp']['date_format'] = 'raw time ago';
  /* Field: Content: Post date */
  $handler->display->display_options['fields']['created']['id'] = 'created';
  $handler->display->display_options['fields']['created']['table'] = 'node';
  $handler->display->display_options['fields']['created']['field'] = 'created';
  $handler->display->display_options['fields']['created']['label'] = 'Created';
  $handler->display->display_options['fields']['created']['alter']['alter_text'] = 0;
  $handler->display->display_options['fields']['created']['alter']['make_link'] = 0;
  $handler->display->display_options['fields']['created']['alter']['absolute'] = 0;
  $handler->display->display_options['fields']['created']['alter']['external'] = 0;
  $handler->display->display_options['fields']['created']['alter']['replace_spaces'] = 0;
  $handler->display->display_options['fields']['created']['alter']['trim_whitespace'] = 0;
  $handler->display->display_options['fields']['created']['alter']['nl2br'] = 0;
  $handler->display->display_options['fields']['created']['alter']['word_boundary'] = 1;
  $handler->display->display_options['fields']['created']['alter']['ellipsis'] = 1;
  $handler->display->display_options['fields']['created']['alter']['more_link'] = 0;
  $handler->display->display_options['fields']['created']['alter']['strip_tags'] = 0;
  $handler->display->display_options['fields']['created']['alter']['trim'] = 0;
  $handler->display->display_options['fields']['created']['alter']['html'] = 0;
  $handler->display->display_options['fields']['created']['element_label_colon'] = 1;
  $handler->display->display_options['fields']['created']['element_default_classes'] = 1;
  $handler->display->display_options['fields']['created']['hide_empty'] = 0;
  $handler->display->display_options['fields']['created']['empty_zero'] = 0;
  $handler->display->display_options['fields']['created']['hide_alter_empty'] = 1;
  $handler->display->display_options['fields']['created']['date_format'] = 'raw time ago';
  /* Sort criterion: Content: Post date */
  $handler->display->display_options['sorts']['created']['id'] = 'created';
  $handler->display->display_options['sorts']['created']['table'] = 'node';
  $handler->display->display_options['sorts']['created']['field'] = 'created';
  $handler->display->display_options['sorts']['created']['order'] = 'DESC';
  /* Contextual filter: Content: Reference (field_entity_reference) */
  $handler->display->display_options['arguments']['field_entity_reference_target_id']['id'] = 'field_entity_reference_target_id';
  $handler->display->display_options['arguments']['field_entity_reference_target_id']['table'] = 'field_data_field_entity_reference';
  $handler->display->display_options['arguments']['field_entity_reference_target_id']['field'] = 'field_entity_reference_target_id';
  $handler->display->display_options['arguments']['field_entity_reference_target_id']['default_action'] = 'not found';
  $handler->display->display_options['arguments']['field_entity_reference_target_id']['default_argument_type'] = 'fixed';
  $handler->display->display_options['arguments']['field_entity_reference_target_id']['default_argument_skip_url'] = 0;
  $handler->display->display_options['arguments']['field_entity_reference_target_id']['summary']['number_of_records'] = '0';
  $handler->display->display_options['arguments']['field_entity_reference_target_id']['summary']['format'] = 'default_summary';
  $handler->display->display_options['arguments']['field_entity_reference_target_id']['summary_options']['items_per_page'] = '25';
  $handler->display->display_options['arguments']['field_entity_reference_target_id']['break_phrase'] = 0;
  $handler->display->display_options['arguments']['field_entity_reference_target_id']['not'] = 0;
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
    'task' => 'task',
  );

  /* Display: Content pane */
  $handler = $view->new_display('panel_pane', 'Content pane', 'panel_pane_1');
  $handler->display->display_options['argument_input'] = array(
    'field_entity_reference_target_id' => array(
      'type' => 'context',
      'context' => 'entity:node.nid',
      'context_optional' => 0,
      'panel' => '0',
      'fixed' => '',
      'label' => 'Content: Reference (field_entity_reference)',
    ),
  );
  $export['task_list'] = $view;

  return $export;
}