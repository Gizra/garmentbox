<?php

/**
 * @file
 * Template overrides as well as (pre-)process and alter hooks for the
 * Default Omega Starterkit theme.
 */

/**
 * Page preprocess.
 */
function opengizra_omega_preprocess_page(&$variables) {
  $node = menu_get_object();
  // When the node wasn't loaded, try fetching it from the menu item.
  if (!$node) {
    $item = menu_get_item();
    if (substr($item['path'], 0, 8) == 'season/%') {
      $node = $item['map'][1]->data;
    }
  }

  if ($node) {
    $variables['page']['title'] = node_view($node, 'opengizra_header');
  }
}

/**
 * Node preprocess.
 */
function opengizra_omega_preprocess_node(&$variables) {
  if ($variables['view_mode'] == 'opengizra_header') {
    $variables['display_submitted'] = FALSE;
  }
}
