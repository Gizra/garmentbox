<?php

/**
 * Implementation of hook_default_message_type().
 */
function opengizra_og_default_message_type() {
  $items = array();
  $items['create_content'] = entity_import('message_type', '{
  "name" : "create_content",
  "description" : "Create content",
  "argument_keys" : [ "@user-url", "@name", "@url", "@title" ],
  "category" : "message_type",
  "message_text" : { "und" : [
      {
        "value" : "\u003ca href=\"@user-url\"\u003e@name\u003c\/a\u003e created \u003ca href=\"@url\"\u003e@title\u003c\/a\u003e",
        "format" : "filtered_html",
        "safe_value" : "\u003cp\u003e\u003ca href=\"@user-url\"\u003e@name\u003c\/a\u003e created \u003ca href=\"@url\"\u003e@title\u003c\/a\u003e\u003c\/p\u003e\n"
      }
    ]
  },
  "rdf_mapping" : []
}');
  return $items;
}
