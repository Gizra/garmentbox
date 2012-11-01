<?php
/**
 * @file
 * garmentbox_task.features.inc
 */

/**
 * Implements hook_ctools_plugin_api().
 */
function garmentbox_task_ctools_plugin_api() {
  list($module, $api) = func_get_args();
  if ($module == "field_group" && $api == "field_group") {
    return array("version" => "1");
  }
  list($module, $api) = func_get_args();
  if ($module == "strongarm" && $api == "strongarm") {
    return array("version" => "1");
  }
}

/**
 * Implements hook_views_api().
 */
function garmentbox_task_views_api() {
  return array("version" => "3.0");
}

/**
 * Implements hook_node_info().
 */
function garmentbox_task_node_info() {
  $items = array(
    'task' => array(
      'name' => t('Task'),
      'base' => 'node_content',
      'description' => '',
      'has_title' => '1',
      'title_label' => t('Title'),
      'help' => '',
    ),
  );
  return $items;
}
