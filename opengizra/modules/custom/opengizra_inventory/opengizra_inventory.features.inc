<?php
/**
 * @file
 * opengizra_inventory.features.inc
 */

/**
 * Implements hook_ctools_plugin_api().
 */
function opengizra_inventory_ctools_plugin_api() {
  list($module, $api) = func_get_args();
  if ($module == "strongarm" && $api == "strongarm") {
    return array("version" => "1");
  }
}

/**
 * Implements hook_views_api().
 */
function opengizra_inventory_views_api() {
  return array("version" => "3.0");
}

/**
 * Implements hook_node_info().
 */
function opengizra_inventory_node_info() {
  $items = array(
    'inventory_line' => array(
      'name' => t('Inventory line'),
      'base' => 'node_content',
      'description' => '',
      'has_title' => '1',
      'title_label' => t('Title'),
      'help' => '',
    ),
  );
  return $items;
}
