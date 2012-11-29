<?php
/**
 * @file
 * garmentbox_production.features.inc
 */

/**
 * Implements hook_ctools_plugin_api().
 */
function garmentbox_production_ctools_plugin_api() {
  list($module, $api) = func_get_args();
  if ($module == "field_group" && $api == "field_group") {
    return array("version" => "1");
  }
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
function garmentbox_production_views_api() {
  return array("version" => "3.0");
}

/**
 * Implements hook_node_info().
 */
function garmentbox_production_node_info() {
  $items = array(
    'factory' => array(
      'name' => t('Factory'),
      'base' => 'node_content',
      'description' => '',
      'has_title' => '1',
      'title_label' => t('Title'),
      'help' => '',
    ),
    'production_order' => array(
      'name' => t('Production order'),
      'base' => 'node_content',
      'description' => '',
      'has_title' => '1',
      'title_label' => t('Title'),
      'help' => '',
    ),
  );
  return $items;
}
