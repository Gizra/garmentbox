<?php
/**
 * @file
 * opengizra_season.features.inc
 */

/**
 * Implements hook_ctools_plugin_api().
 */
function opengizra_season_ctools_plugin_api() {
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
function opengizra_season_flag_default_flags() {
  $flags = array();
  // Exported flag: "Active Season".
  $flags['active_season'] = array(
    'content_type' => 'node',
    'title' => 'Active Season',
    'global' => '1',
    'types' => array(
      0 => 'season',
    ),
    'flag_short' => 'Active season',
    'flag_long' => '',
    'flag_message' => 'Season is marked as active',
    'unflag_short' => 'Unactive season',
    'unflag_long' => 'Season is not marked as active',
    'unflag_message' => '',
    'unflag_denied_text' => 'Set another season as active to make this season non-active',
    'link_type' => 'confirm',
    'roles' => array(
      'flag' => array(
        0 => '2',
      ),
      'unflag' => array(),
    ),
    'weight' => 0,
    'show_on_page' => 1,
    'show_on_teaser' => 0,
    'show_on_form' => 0,
    'show_contextual_link' => 0,
    'access_author' => '',
    'i18n' => 0,
    'flag_confirmation' => 'Mark this season as active?',
    'unflag_confirmation' => 'Mark this season as non-active?',
    'module' => 'opengizra_season',
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
function opengizra_season_node_info() {
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
