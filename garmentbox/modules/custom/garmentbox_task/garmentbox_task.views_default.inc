<?php
/**
 * @file
 * garmentbox_task.views_default.inc
 */

/**
 * Implements hook_views_default_views().
 */
function garmentbox_task_views_default_views() {
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
  $handler->display->display_options['title'] = 'Task list / Item %1';
  $handler->display->display_options['access']['type'] = 'perm';
  $handler->display->display_options['cache']['type'] = 'none';
  $handler->display->display_options['query']['type'] = 'views_query';
  $handler->display->display_options['query']['options']['query_comment'] = FALSE;
  $handler->display->display_options['exposed_form']['type'] = 'basic';
  $handler->display->display_options['pager']['type'] = 'full';
  $handler->display->display_options['pager']['options']['items_per_page'] = '20';
  $handler->display->display_options['pager']['options']['offset'] = '0';
  $handler->display->display_options['pager']['options']['id'] = '0';
  $handler->display->display_options['pager']['options']['expose']['items_per_page_options_all'] = 0;
  $handler->display->display_options['style_plugin'] = 'table';
  $handler->display->display_options['style_options']['columns'] = array(
    'new_comments' => 'new_comments',
    'title' => 'title',
    'field_task_status' => 'field_task_status',
    'field_task_assignee' => 'field_task_assignee',
    'comment_count' => 'comment_count',
    'last_comment_timestamp' => 'last_comment_timestamp',
    'created' => 'created',
    'edit_node' => 'edit_node',
  );
  $handler->display->display_options['style_options']['default'] = '-1';
  $handler->display->display_options['style_options']['info'] = array(
    'new_comments' => array(
      'align' => '',
      'separator' => '',
      'empty_column' => 0,
    ),
    'title' => array(
      'sortable' => 1,
      'default_sort_order' => 'asc',
      'align' => '',
      'separator' => '',
      'empty_column' => 0,
    ),
    'field_task_status' => array(
      'sortable' => 1,
      'default_sort_order' => 'asc',
      'align' => '',
      'separator' => '',
      'empty_column' => 0,
    ),
    'field_task_assignee' => array(
      'sortable' => 1,
      'default_sort_order' => 'asc',
      'align' => '',
      'separator' => '',
      'empty_column' => 0,
    ),
    'comment_count' => array(
      'sortable' => 1,
      'default_sort_order' => 'asc',
      'align' => '',
      'separator' => '',
      'empty_column' => 0,
    ),
    'last_comment_timestamp' => array(
      'sortable' => 1,
      'default_sort_order' => 'asc',
      'align' => '',
      'separator' => '',
      'empty_column' => 0,
    ),
    'created' => array(
      'sortable' => 1,
      'default_sort_order' => 'asc',
      'align' => '',
      'separator' => '',
      'empty_column' => 0,
    ),
    'edit_node' => array(
      'align' => '',
      'separator' => '',
      'empty_column' => 0,
    ),
  );
  $handler->display->display_options['style_options']['override'] = 1;
  $handler->display->display_options['style_options']['sticky'] = 0;
  $handler->display->display_options['style_options']['empty_table'] = 0;
  /* Footer: Global: Result summary */
  $handler->display->display_options['footer']['result']['id'] = 'result';
  $handler->display->display_options['footer']['result']['table'] = 'views';
  $handler->display->display_options['footer']['result']['field'] = 'result';
  $handler->display->display_options['footer']['result']['empty'] = FALSE;
  $handler->display->display_options['footer']['result']['content'] = 'Total open tasks: @total';
  /* No results behavior: Global: Text area */
  $handler->display->display_options['empty']['area']['id'] = 'area';
  $handler->display->display_options['empty']['area']['table'] = 'views';
  $handler->display->display_options['empty']['area']['field'] = 'area';
  $handler->display->display_options['empty']['area']['empty'] = FALSE;
  $handler->display->display_options['empty']['area']['content'] = 'No tasks assigned.';
  $handler->display->display_options['empty']['area']['format'] = 'filtered_html';
  $handler->display->display_options['empty']['area']['tokenize'] = 0;
  /* Relationship: Entity Reference: Referenced Entity */
  $handler->display->display_options['relationships']['field_task_status_target_id']['id'] = 'field_task_status_target_id';
  $handler->display->display_options['relationships']['field_task_status_target_id']['table'] = 'field_data_field_task_status';
  $handler->display->display_options['relationships']['field_task_status_target_id']['field'] = 'field_task_status_target_id';
  $handler->display->display_options['relationships']['field_task_status_target_id']['label'] = 'field_task_status';
  $handler->display->display_options['relationships']['field_task_status_target_id']['required'] = 0;
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
  /* Field: Content: Title */
  $handler->display->display_options['fields']['title']['id'] = 'title';
  $handler->display->display_options['fields']['title']['table'] = 'node';
  $handler->display->display_options['fields']['title']['field'] = 'title';
  $handler->display->display_options['fields']['title']['label'] = 'Summary';
  $handler->display->display_options['fields']['title']['alter']['alter_text'] = 0;
  $handler->display->display_options['fields']['title']['alter']['make_link'] = 0;
  $handler->display->display_options['fields']['title']['alter']['absolute'] = 0;
  $handler->display->display_options['fields']['title']['alter']['external'] = 0;
  $handler->display->display_options['fields']['title']['alter']['replace_spaces'] = 0;
  $handler->display->display_options['fields']['title']['alter']['trim_whitespace'] = 0;
  $handler->display->display_options['fields']['title']['alter']['nl2br'] = 0;
  $handler->display->display_options['fields']['title']['alter']['word_boundary'] = 0;
  $handler->display->display_options['fields']['title']['alter']['ellipsis'] = 0;
  $handler->display->display_options['fields']['title']['alter']['more_link'] = 0;
  $handler->display->display_options['fields']['title']['alter']['strip_tags'] = 0;
  $handler->display->display_options['fields']['title']['alter']['trim'] = 0;
  $handler->display->display_options['fields']['title']['alter']['html'] = 0;
  $handler->display->display_options['fields']['title']['element_label_colon'] = 1;
  $handler->display->display_options['fields']['title']['element_default_classes'] = 1;
  $handler->display->display_options['fields']['title']['hide_empty'] = 0;
  $handler->display->display_options['fields']['title']['empty_zero'] = 0;
  $handler->display->display_options['fields']['title']['hide_alter_empty'] = 1;
  $handler->display->display_options['fields']['title']['link_to_node'] = 1;
  /* Field: Field: Status */
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
  /* Field: Field: Assignee */
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
  /* Field: Node: Edit link */
  $handler->display->display_options['fields']['edit_node']['id'] = 'edit_node';
  $handler->display->display_options['fields']['edit_node']['table'] = 'views_entity_node';
  $handler->display->display_options['fields']['edit_node']['field'] = 'edit_node';
  $handler->display->display_options['fields']['edit_node']['label'] = 'Actions';
  $handler->display->display_options['fields']['edit_node']['alter']['alter_text'] = 0;
  $handler->display->display_options['fields']['edit_node']['alter']['make_link'] = 0;
  $handler->display->display_options['fields']['edit_node']['alter']['absolute'] = 0;
  $handler->display->display_options['fields']['edit_node']['alter']['replace_spaces'] = 0;
  $handler->display->display_options['fields']['edit_node']['alter']['trim_whitespace'] = 0;
  $handler->display->display_options['fields']['edit_node']['alter']['nl2br'] = 0;
  $handler->display->display_options['fields']['edit_node']['alter']['word_boundary'] = 1;
  $handler->display->display_options['fields']['edit_node']['alter']['ellipsis'] = 1;
  $handler->display->display_options['fields']['edit_node']['alter']['more_link'] = 0;
  $handler->display->display_options['fields']['edit_node']['alter']['strip_tags'] = 0;
  $handler->display->display_options['fields']['edit_node']['alter']['trim'] = 0;
  $handler->display->display_options['fields']['edit_node']['alter']['html'] = 0;
  $handler->display->display_options['fields']['edit_node']['element_label_colon'] = 1;
  $handler->display->display_options['fields']['edit_node']['element_default_classes'] = 1;
  $handler->display->display_options['fields']['edit_node']['hide_empty'] = 0;
  $handler->display->display_options['fields']['edit_node']['empty_zero'] = 0;
  $handler->display->display_options['fields']['edit_node']['hide_alter_empty'] = 1;
  /* Sort criterion: Content: Updated date */
  $handler->display->display_options['sorts']['changed']['id'] = 'changed';
  $handler->display->display_options['sorts']['changed']['table'] = 'node';
  $handler->display->display_options['sorts']['changed']['field'] = 'changed';
  /* Sort criterion: Content: Title */
  $handler->display->display_options['sorts']['title']['id'] = 'title';
  $handler->display->display_options['sorts']['title']['table'] = 'node';
  $handler->display->display_options['sorts']['title']['field'] = 'title';
  /* Contextual filter: Content: Reference hierarchy (field_reference_hierarchy) */
  $handler->display->display_options['arguments']['field_reference_hierarchy_target_id']['id'] = 'field_reference_hierarchy_target_id';
  $handler->display->display_options['arguments']['field_reference_hierarchy_target_id']['table'] = 'field_data_field_reference_hierarchy';
  $handler->display->display_options['arguments']['field_reference_hierarchy_target_id']['field'] = 'field_reference_hierarchy_target_id';
  $handler->display->display_options['arguments']['field_reference_hierarchy_target_id']['default_action'] = 'not found';
  $handler->display->display_options['arguments']['field_reference_hierarchy_target_id']['default_argument_type'] = 'fixed';
  $handler->display->display_options['arguments']['field_reference_hierarchy_target_id']['default_argument_skip_url'] = 0;
  $handler->display->display_options['arguments']['field_reference_hierarchy_target_id']['summary']['number_of_records'] = '0';
  $handler->display->display_options['arguments']['field_reference_hierarchy_target_id']['summary']['format'] = 'default_summary';
  $handler->display->display_options['arguments']['field_reference_hierarchy_target_id']['summary_options']['items_per_page'] = '25';
  $handler->display->display_options['arguments']['field_reference_hierarchy_target_id']['break_phrase'] = 0;
  $handler->display->display_options['arguments']['field_reference_hierarchy_target_id']['not'] = 0;
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
  /* Filter criterion: Taxonomy term: Status is considered closed (field_status_closed) */
  $handler->display->display_options['filters']['field_status_closed_value']['id'] = 'field_status_closed_value';
  $handler->display->display_options['filters']['field_status_closed_value']['table'] = 'field_data_field_status_closed';
  $handler->display->display_options['filters']['field_status_closed_value']['field'] = 'field_status_closed_value';
  $handler->display->display_options['filters']['field_status_closed_value']['relationship'] = 'field_task_status_target_id';
  $handler->display->display_options['filters']['field_status_closed_value']['value'] = array(
    0 => '0',
  );

  /* Display: Content pane */
  $handler = $view->new_display('panel_pane', 'Content pane', 'panel_pane_1');
  $handler->display->display_options['argument_input'] = array(
    'field_reference_hierarchy_target_id' => array(
      'type' => 'context',
      'context' => 'entity:node.nid',
      'context_optional' => 0,
      'panel' => '0',
      'fixed' => '',
      'label' => 'Content: Reference hierarchy (field_reference_hierarchy)',
    ),
  );
  $export['task_list'] = $view;

  return $export;
}
