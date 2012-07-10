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

/**
 * Implements hook_default_message_type().
 */
function opengizra_og_default_message_type() {
  $items = array();
  $items['create_content'] = entity_import('message_type', '{
    "name" : "create_content",
    "description" : "Create content",
    "argument_keys" : [],
    "argument" : [],
    "category" : "message_type",
    "data" : { "purge" : { "override" : 0, "enabled" : 0, "quota" : "", "days" : "" } },
    "language" : "",
    "arguments" : null,
    "message_text" : { "und" : [
        {
          "value" : "\\u003Ca href=\\u0022[message:user:uid]\\u0022\\u003E[message:user:name]\\u003C\\/a\\u003E created \\u003Ca href=\\u0022[message:field-groups:0:url]\\u0022\\u003E[message:field-groups:0:title]\\u003C\\/a\\u003E",
          "format" : "full_html",
          "safe_value" : "\\u003Cp\\u003E\\u003Ca href=\\u0022[message:user:uid]\\u0022\\u003E[message:user:name]\\u003C\\/a\\u003E created \\u003Ca href=\\u0022[message:field-groups:0:url]\\u0022\\u003E[message:field-groups:0:title]\\u003C\\/a\\u003E\\u003C\\/p\\u003E\\n"
        }
      ]
    },
    "rdf_mapping" : []
  }');
  return $items;
}
