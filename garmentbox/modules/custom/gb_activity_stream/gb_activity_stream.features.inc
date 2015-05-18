<?php
/**
 * @file
 * gb_activity_stream.features.inc
 */

/**
 * Implements hook_ctools_plugin_api().
 */
function gb_activity_stream_ctools_plugin_api($module = NULL, $api = NULL) {
  if ($module == "strongarm" && $api == "strongarm") {
    return array("version" => "1");
  }
}

/**
 * Implements hook_default_message_type().
 */
function gb_activity_stream_default_message_type() {
  $items = array();
  $items['content_updated'] = entity_import('message_type', '{
    "name" : "content_updated",
    "description" : "Content updated",
    "argument_keys" : [],
    "argument" : [],
    "category" : "message_type",
    "data" : {
      "token options" : { "clear" : 0 },
      "purge" : { "override" : 0, "enabled" : 0, "quota" : "", "days" : "" }
    },
    "language" : "",
    "arguments" : null,
    "message_text" : { "und" : [
        {
          "value" : "\\u003Ca href=\\u0022[message:field-node-ref:url:absolute]\\u0022\\u003Enode [message:field-node-ref:title] is updated now.",
          "format" : "filtered_html",
          "safe_value" : "\\u003Cp\\u003E\\u003Ca href=\\u0022absolute]\\u0022\\u003Enode [message:field-node-ref:title] is updated now.\\u003C\\/a\\u003E\\u003C\\/p\\u003E\\n"
        }
      ]
    }
  }');
  return $items;
}
