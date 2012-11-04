<?php
/**
 * @file
 * garmentbox_vendor.strongarm.inc
 */

/**
 * Implements hook_strongarm().
 */
function garmentbox_vendor_strongarm() {
  $export = array();

  $strongarm = new stdClass();
  $strongarm->disabled = FALSE; /* Edit this to true to make a default strongarm disabled initially */
  $strongarm->api_version = 1;
  $strongarm->name = 'comment_anonymous_vendor';
  $strongarm->value = 0;
  $export['comment_anonymous_vendor'] = $strongarm;

  $strongarm = new stdClass();
  $strongarm->disabled = FALSE; /* Edit this to true to make a default strongarm disabled initially */
  $strongarm->api_version = 1;
  $strongarm->name = 'comment_default_mode_vendor';
  $strongarm->value = 1;
  $export['comment_default_mode_vendor'] = $strongarm;

  $strongarm = new stdClass();
  $strongarm->disabled = FALSE; /* Edit this to true to make a default strongarm disabled initially */
  $strongarm->api_version = 1;
  $strongarm->name = 'comment_default_per_page_vendor';
  $strongarm->value = '50';
  $export['comment_default_per_page_vendor'] = $strongarm;

  $strongarm = new stdClass();
  $strongarm->disabled = FALSE; /* Edit this to true to make a default strongarm disabled initially */
  $strongarm->api_version = 1;
  $strongarm->name = 'comment_form_location_vendor';
  $strongarm->value = 1;
  $export['comment_form_location_vendor'] = $strongarm;

  $strongarm = new stdClass();
  $strongarm->disabled = FALSE; /* Edit this to true to make a default strongarm disabled initially */
  $strongarm->api_version = 1;
  $strongarm->name = 'comment_preview_vendor';
  $strongarm->value = '1';
  $export['comment_preview_vendor'] = $strongarm;

  $strongarm = new stdClass();
  $strongarm->disabled = FALSE; /* Edit this to true to make a default strongarm disabled initially */
  $strongarm->api_version = 1;
  $strongarm->name = 'comment_subject_field_vendor';
  $strongarm->value = 1;
  $export['comment_subject_field_vendor'] = $strongarm;

  $strongarm = new stdClass();
  $strongarm->disabled = FALSE; /* Edit this to true to make a default strongarm disabled initially */
  $strongarm->api_version = 1;
  $strongarm->name = 'comment_vendor';
  $strongarm->value = '1';
  $export['comment_vendor'] = $strongarm;

  $strongarm = new stdClass();
  $strongarm->disabled = FALSE; /* Edit this to true to make a default strongarm disabled initially */
  $strongarm->api_version = 1;
  $strongarm->name = 'menu_options_vendor';
  $strongarm->value = array(
    0 => 'main-menu',
  );
  $export['menu_options_vendor'] = $strongarm;

  $strongarm = new stdClass();
  $strongarm->disabled = FALSE; /* Edit this to true to make a default strongarm disabled initially */
  $strongarm->api_version = 1;
  $strongarm->name = 'menu_parent_vendor';
  $strongarm->value = 'main-menu:0';
  $export['menu_parent_vendor'] = $strongarm;

  $strongarm = new stdClass();
  $strongarm->disabled = FALSE; /* Edit this to true to make a default strongarm disabled initially */
  $strongarm->api_version = 1;
  $strongarm->name = 'node_options_vendor';
  $strongarm->value = array(
    0 => 'status',
    1 => 'promote',
  );
  $export['node_options_vendor'] = $strongarm;

  $strongarm = new stdClass();
  $strongarm->disabled = FALSE; /* Edit this to true to make a default strongarm disabled initially */
  $strongarm->api_version = 1;
  $strongarm->name = 'node_preview_vendor';
  $strongarm->value = '1';
  $export['node_preview_vendor'] = $strongarm;

  $strongarm = new stdClass();
  $strongarm->disabled = FALSE; /* Edit this to true to make a default strongarm disabled initially */
  $strongarm->api_version = 1;
  $strongarm->name = 'node_submitted_vendor';
  $strongarm->value = 1;
  $export['node_submitted_vendor'] = $strongarm;

  return $export;
}
