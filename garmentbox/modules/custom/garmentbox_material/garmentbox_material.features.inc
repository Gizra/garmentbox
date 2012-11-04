<?php
/**
 * @file
 * garmentbox_material.features.inc
 */

/**
 * Implements hook_ctools_plugin_api().
 */
function garmentbox_material_ctools_plugin_api() {
  list($module, $api) = func_get_args();
  if ($module == "page_manager" && $api == "pages_default") {
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
function garmentbox_material_views_api() {
  return array("version" => "3.0");
}

/**
 * Implements hook_node_info().
 */
function garmentbox_material_node_info() {
  $items = array(
    'material' => array(
      'name' => t('Material'),
      'base' => 'node_content',
      'description' => '',
      'has_title' => '1',
      'title_label' => t('Title'),
      'help' => '',
    ),
  );
  return $items;
}
