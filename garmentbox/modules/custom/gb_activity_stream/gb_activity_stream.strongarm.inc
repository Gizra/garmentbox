<?php
/**
 * @file
 * gb_activity_stream.strongarm.inc
 */

/**
 * Implements hook_strongarm().
 */
function gb_activity_stream_strongarm() {
  $export = array();

  $strongarm = new stdClass();
  $strongarm->disabled = FALSE; /* Edit this to true to make a default strongarm disabled initially */
  $strongarm->api_version = 1;
  $strongarm->name = 'field_bundle_settings_message__content_updated';
  $strongarm->value = array(
    'view_modes' => array(),
    'extra_fields' => array(
      'form' => array(),
      'display' => array(),
    ),
  );
  $export['field_bundle_settings_message__content_updated'] = $strongarm;

  return $export;
}
