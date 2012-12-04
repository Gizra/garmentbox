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
  $node = menu_get_object();
  // When the node wasn't loaded, try fetching it from the menu item.
  if (!$node) {
    $item = menu_get_item();
    if (strpos($item['path'], 'season/%') === 0) {
      // When on a panels page, ['map'][1] has the node itself.
      if (!empty($item['map'][1]->data)) {
        $node = $item['map'][1]->data;
      }
      // When on a views page, ['map'][1] has the node ID.
      elseif (!empty($item['map']) && is_numeric($item['map'][1])) {
        $node = node_load($item['map'][1]);
      }
    }
  }

  if ($node) {
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
