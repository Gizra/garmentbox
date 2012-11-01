<?php
/**
 * @file
 * garmentbox_pattern_task.features.inc
 */

/**
 * Implements hook_ctools_plugin_api().
 */
function garmentbox_pattern_task_ctools_plugin_api() {
  list($module, $api) = func_get_args();
  if ($module == "strongarm" && $api == "strongarm") {
    return array("version" => "1");
  }
}

/**
 * Implements hook_views_api().
 */
function garmentbox_pattern_task_views_api() {
  return array("version" => "3.0");
}

/**
 * Implements hook_node_info().
 */
function garmentbox_pattern_task_node_info() {
  $items = array(
    'pattern_task' => array(
      'name' => t('Pattern Task'),
      'base' => 'node_content',
      'description' => '',
      'has_title' => '1',
      'title_label' => t('Title'),
      'help' => '',
    ),
  );
  return $items;
}
