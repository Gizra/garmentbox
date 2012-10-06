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
  if ($node = menu_get_object()) {
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
