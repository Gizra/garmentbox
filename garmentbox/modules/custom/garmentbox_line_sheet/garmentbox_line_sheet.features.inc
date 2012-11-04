<?php
/**
 * @file
 * garmentbox_line_sheet.features.inc
 */

/**
 * Implements hook_ctools_plugin_api().
 */
function garmentbox_line_sheet_ctools_plugin_api() {
  list($module, $api) = func_get_args();
  if ($module == "page_manager" && $api == "pages_default") {
    return array("version" => "1");
  }
}

/**
 * Implements hook_flag_default_flags().
 */
function garmentbox_line_sheet_flag_default_flags() {
  $flags = array();
  // Exported flag: "Line Sheet".
  $flags['line_sheet'] = array(
    'content_type' => 'node',
    'title' => 'Line Sheet',
    'global' => '1',
    'types' => array(
      0 => 'item_variant',
    ),
    'flag_short' => 'Add to line Sheet',
    'flag_long' => '',
    'flag_message' => '',
    'unflag_short' => 'Remove from line Sheet',
    'unflag_long' => '',
    'unflag_message' => '',
    'unflag_denied_text' => '',
    'link_type' => 'toggle',
    'roles' => array(
      'flag' => array(
        0 => '2',
      ),
      'unflag' => array(
        0 => '2',
      ),
    ),
    'weight' => 0,
    'show_on_form' => 0,
    'access_author' => '',
    'show_on_page' => 0,
    'show_on_teaser' => 0,
    'show_contextual_link' => 0,
    'i18n' => 0,
    'module' => 'garmentbox_line_sheet',
    'locked' => array(
      0 => 'name',
    ),
    'api_version' => 2,
  );
  return $flags;
}
