<?php
/**
 * @file
 * garment_box_bubble.features.inc
 */

/**
 * Implements hook_ctools_plugin_api().
 */
function garment_box_bubble_ctools_plugin_api() {
  list($module, $api) = func_get_args();
  if ($module == "strongarm" && $api == "strongarm") {
    return array("version" => "1");
  }
}

/**
 * Implements hook_node_info().
 */
function garment_box_bubble_node_info() {
  $items = array(
    'bubble' => array(
      'name' => t('Bubble'),
      'base' => 'node_content',
      'description' => t('Help bubbles.'),
      'has_title' => '1',
      'title_label' => t('Title'),
      'help' => '',
    ),
  );
  return $items;
}
