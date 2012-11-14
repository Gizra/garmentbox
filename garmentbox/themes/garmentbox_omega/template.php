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
    if (substr($item['path'], 0, 8) == 'season/%' && !empty($item['map'][1]->data)) {
      $node = $item['map'][1]->data;
    }
  }

  if ($node) {
    $variables['page']['title'] = node_view($node, 'garmentbox_header');
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
function garmentbox_omega_preprocess_material_node_garmentbox_header(&$variables) {
  // Add variables to create the "Add material" button.
  $variables['theme_hook_suggestions'][] = 'node__header';

  $content = &$variables['content'];
  $content['add_material_link'] = l('Add new material', 'node/add/material');
}

/**
 * Material node preprocess.
 *
 * @see garmentbox_omega_preprocess_node()
 */
function garmentbox_omega_preprocess_material_node(&$variables) {
  $variables['theme_hook_suggestions'][] = 'node__material_page';
  $content = &$variables['content'];

  $hidden_fields = array('og_group_ref', 'body', 'field_images', 'field_nick_name', 'field_source_info');
  $wrapper = entity_metadata_wrapper('node', $variables['nid']);
  foreach(array('length', 'width', 'radius') as $measurement) {
    // Hide disabled measurements by material type.
    if (!$wrapper->field_material_type->{'field_has_' . $measurement}->value()) {
      $hidden_fields[] = "field_$measurement";
    }
  }

  foreach($hidden_fields as $field_name) {
    unset($content[$field_name]);
  }
}
