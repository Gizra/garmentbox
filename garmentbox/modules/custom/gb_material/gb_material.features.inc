<?php
/**
 * @file
 * gb_material.features.inc
 */

/**
 * Implements hook_ctools_plugin_api().
 */
function gb_material_ctools_plugin_api($module = NULL, $api = NULL) {
  if ($module == "strongarm" && $api == "strongarm") {
    return array("version" => "1");
  }
}

/**
 * Implements hook_node_info().
 */
function gb_material_node_info() {
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
