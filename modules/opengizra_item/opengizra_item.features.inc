<?php
/**
 * @file
 * opengizra_item.features.inc
 */

/**
 * Implementation of hook_ctools_plugin_api().
 */
function opengizra_item_ctools_plugin_api() {
  list($module, $api) = func_get_args();
  if ($module == "strongarm" && $api == "strongarm") {
    return array("version" => "1");
  }
}

/**
 * Implementation of hook_node_info().
 */
function opengizra_item_node_info() {
  $items = array(
    'item' => array(
      'name' => t('Item'),
      'base' => 'node_content',
      'description' => '',
      'has_title' => '1',
      'title_label' => t('Title'),
      'help' => '',
    ),
  );
  return $items;
}
