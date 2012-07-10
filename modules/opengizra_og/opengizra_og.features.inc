<?php
/**
 * @file
 * opengizra_og.features.inc
 */

/**
 * Implements hook_ctools_plugin_api().
 */
function opengizra_og_ctools_plugin_api() {
  list($module, $api) = func_get_args();
  if ($module == "page_manager" && $api == "pages_default") {
    return array("version" => "1");
  }
  list($module, $api) = func_get_args();
  if ($module == "panels_mini" && $api == "panels_default") {
    return array("version" => "1");
  }
}

/**
 * Implements hook_views_api().
 */
function opengizra_og_views_api() {
  return array("version" => "3.0");
}
