<?php
/**
 * @file
 * gb_activity_stream.features.field_instance.inc
 */

/**
 * Implements hook_field_default_field_instances().
 */
function gb_activity_stream_field_default_field_instances() {
  $field_instances = array();

  // Exported field_instance: 'message-content_updated-field_node_ref'
  $field_instances['message-content_updated-field_node_ref'] = array(
    'bundle' => 'content_updated',
    'default_value' => NULL,
    'deleted' => 0,
    'description' => '',
    'display' => array(
      'default' => array(
        'label' => 'above',
        'module' => 'entityreference',
        'settings' => array(
          'link' => FALSE,
        ),
        'type' => 'entityreference_label',
        'weight' => 0,
      ),
    ),
    'entity_type' => 'message',
    'field_name' => 'field_node_ref',
    'label' => 'Node reference',
    'required' => 0,
    'settings' => array(
      'user_register_form' => FALSE,
    ),
    'widget' => array(
      'active' => 1,
      'module' => 'entityreference',
      'settings' => array(
        'match_operator' => 'CONTAINS',
        'path' => '',
        'size' => 60,
      ),
      'type' => 'entityreference_autocomplete',
      'weight' => 2,
    ),
  );

  // Translatables
  // Included for use with string extractors like potx.
  t('Node reference');

  return $field_instances;
}
