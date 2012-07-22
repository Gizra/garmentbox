<?php
/**
 * @file
 * opengizra_pattern_task.rules_defaults.inc
 */

/**
 * Implements hook_default_rules_configuration().
 */
function opengizra_pattern_task_default_rules_configuration() {
  $items = array();
  $items['rules_create_pattern_tasks'] = entity_import('rules_config', '{ "rules_create_pattern_tasks" : {
      "LABEL" : "Create Pattern Tasks",
      "PLUGIN" : "reaction rule",
      "REQUIRES" : [ "rules" ],
      "ON" : [ "node_insert" ],
      "IF" : [ { "data_is" : { "data" : [ "node:type" ], "value" : "pattern" } } ],
      "DO" : [
        { "entity_create" : {
            "USING" : {
              "type" : "node",
              "param_type" : "pattern_task",
              "param_title" : "Create pattern for [node:title]",
              "param_author" : [ "node:author" ]
            },
            "PROVIDE" : { "entity_created" : { "pattern" : "Create pattern" } }
          }
        },
        { "data_set" : { "data" : [ "pattern:field-pattern" ], "value" : [ "node" ] } },
        { "entity_create" : {
            "USING" : {
              "type" : "node",
              "param_type" : "pattern_task",
              "param_title" : "Prepare fitting for [node:title]",
              "param_author" : [ "node:author" ]
            },
            "PROVIDE" : { "entity_created" : { "fitting" : "Create fitting" } }
          }
        },
        { "data_set" : { "data" : [ "fitting:field-pattern" ], "value" : [ "node" ] } }
      ]
    }
  }');
  return $items;
}
