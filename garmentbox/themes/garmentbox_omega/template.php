<?php

/**
 * @file
 * Template overrides as well as (pre-)process and alter hooks for the
 * Default Omega Starterkit theme.
 */

/**
 * Page preprocess.
 */
function garmentbox_omega_preprocess_page(&$variables) {
  if (overlay_get_mode() == 'child') {
    $variables['theme_hook_suggestions'][] = 'page__overlay';
  }
  elseif ($node = garmentbox_general_get_node()) {
    // Node context.
    $variables['page']['title'] = node_view($node, 'garmentbox_header');
    $variables['page']['breadcrumbs'] = garmentbox_general_get_node_breadcrumbs($node);
    $variables['page']['tabs'] = garmentbox_general_get_node_tabs($node);
    $variables['page']['primary_button'] = garmentbox_general_get_node_primary_button($node);
  }
}

/**
 * Node preprocess.
 */
function garmentbox_omega_preprocess_node(&$variables) {
  $node = $variables['node'];

  $view_mode = $variables['view_mode'] == 'full' ? '' : '_' . $variables['view_mode'];
  if ($view_mode == '_garmentbox_header') {
    $variables['display_submitted'] = FALSE;
  }
  // Preprocess nodes by generic function names. 'Full' display node as the
  // default.
  $preprocess_function = "garmentbox_omega_preprocess_{$node->type}_node{$view_mode}";
  if (function_exists($preprocess_function)) {
    $preprocess_function($variables);
  }
}

/**
 * Material node page header preprocess.
 *
 * @see garmentbox_omega_preprocess_node().
 */
function garmentbox_omega_preprocess_material_node(&$variables) {
  $wrapper = entity_metadata_wrapper('node', $variables['nid']);

  // Hide the measurements that are not enabled for this material type.
  $disabled_measurements = array_diff(array('width', 'length', 'radius') , $wrapper->field_material_type->field_measurement_types->value());
  foreach ($disabled_measurements as $measurement) {
    $variables['content']['field_' . $measurement]['#access'] = FALSE;
  }
}

/**
 * Returns HTML for a textfield form element.
 *
 * @param $variables
 *   An associative array containing:
 *   - element: An associative array containing the properties of the element.
 *     Properties used: #title, #value, #description, #size, #maxlength,
 *     #required, #attributes, #autocomplete_path.
 *
 * @ingroup themeable
 */
function garmentbox_omega_textfield($variables) {
  $element = $variables['element'];

  if (empty($element['#attributes']['type'])) {
    $element['#attributes']['type'] = 'text';
  }

  element_set_attributes($element, array('id', 'name', 'value', 'size', 'maxlength'));
  _form_set_class($element, array('form-text'));

  $extra = '';
  if ($element['#autocomplete_path'] && drupal_valid_path($element['#autocomplete_path'])) {
    drupal_add_library('system', 'drupal.autocomplete');
    $element['#attributes']['class'][] = 'form-autocomplete';

    $attributes = array();
    $attributes['type'] = 'hidden';
    $attributes['id'] = $element['#attributes']['id'] . '-autocomplete';
    $attributes['value'] = url($element['#autocomplete_path'], array('absolute' => TRUE));
    $attributes['disabled'] = 'disabled';
    $attributes['class'][] = 'autocomplete';
    $extra = '<input' . drupal_attributes($attributes) . ' />';
  }

  $output = '<input' . drupal_attributes($element['#attributes']) . ' />';

  return $output . $extra;
}