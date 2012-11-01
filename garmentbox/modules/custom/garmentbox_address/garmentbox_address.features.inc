<?php
/**
 * @file
 * garmentbox_address.features.inc
 */

/**
 * Implements hook_ctools_plugin_api().
 */
function garmentbox_address_ctools_plugin_api() {
  list($module, $api) = func_get_args();
  if ($module == "strongarm" && $api == "strongarm") {
    return array("version" => "1");
  }
}

/**
 * Implements hook_node_info().
 */
function garmentbox_address_node_info() {
  $items = array(
    'address' => array(
      'name' => t('Address'),
      'base' => 'node_content',
      'description' => '',
      'has_title' => '1',
      'title_label' => t('Title'),
      'help' => '',
    ),
  );
  return $items;
}
