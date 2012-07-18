<?php
/**
 * @file
 * opengizra_collection.features.inc
 */

/**
 * Implements hook_ctools_plugin_api().
 */
function opengizra_collection_ctools_plugin_api() {
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
 * Implements hook_flag_default_flags().
 */
function opengizra_collection_flag_default_flags() {
  $flags = array();
  // Exported flag: "Active Collection".
  $flags['active_collection'] = array(
    'content_type' => 'node',
    'title' => 'Active Collection',
    'global' => '1',
    'types' => array(
      0 => 'collection',
    ),
    'flag_short' => 'Active collection',
    'flag_long' => '',
    'flag_message' => 'Collection is marked as active',
    'unflag_short' => 'Unactive collection',
    'unflag_long' => 'Collection is not marked as active',
    'unflag_message' => '',
    'unflag_denied_text' => 'Set another collection as active to make this collection non-active',
    'link_type' => 'confirm',
    'roles' => array(
      'flag' => array(
        0 => '2',
      ),
      'unflag' => array(),
    ),
    'weight' => 0,
    'show_on_page' => 0,
    'show_on_teaser' => 0,
    'show_on_form' => 0,
    'show_contextual_link' => 0,
    'access_author' => '',
    'i18n' => 0,
    'flag_confirmation' => 'Mark this collection as active?',
    'unflag_confirmation' => 'Mark this collection as non-active?',
    'module' => 'opengizra_collection',
    'locked' => array(
      0 => 'name',
    ),
    'api_version' => 2,
  );
  return $flags;
}

/**
 * Implements hook_node_info().
 */
function opengizra_collection_node_info() {
  $items = array(
    'collection' => array(
      'name' => t('Collection'),
      'base' => 'node_content',
      'description' => '',
      'has_title' => '1',
      'title_label' => t('Title'),
      'help' => '',
    ),
  );
  return $items;
}
