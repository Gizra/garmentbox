<?php
/**
 * @file
 * gb_season.features.inc
 */

/**
 * Implements hook_ctools_plugin_api().
 */
function gb_season_ctools_plugin_api($module = NULL, $api = NULL) {
  if ($module == "strongarm" && $api == "strongarm") {
    return array("version" => "1");
  }
}

/**
 * Implements hook_node_info().
 */
function gb_season_node_info() {
  $items = array(
    'season' => array(
      'name' => t('Season'),
      'base' => 'node_content',
      'description' => '',
      'has_title' => '1',
      'title_label' => t('Title'),
      'help' => '',
    ),
  );
  return $items;
}
