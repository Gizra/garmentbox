<?php


/**
 * @file
 * Definition of the 'Tabs' panel style.
 */

// Plugin definition
$plugin = array(
  'title' => t('Odd & even'),
  'description' => t('Add odd and even classes to panes in a region.'),
  'render region' => 'opengizra_main_odd_even_style_render_region',
);

/**
 * Render callback.
 *
 * @ingroup themeable
 */
function theme_opengizra_main_odd_even_style_render_region($vars) {
  $display = $vars['display'];
  $region_id = $vars['region_id'];
  $panes = $vars['panes'];

  // Unique ID of this region.
  $id = $display->did . ':' . $region_id;
  static $even = array();

  $element = array();
  foreach ($panes as $pane_id => $pane) {
    $class = !empty($even[$id]) ? 'even' : 'odd';
    $even[$id] = empty($even[$id]);

    $element[$pane_id] = array(
      '#prefix' => '<div class="row-' . $class . '">',
      '#suffix' => '</div>',
      '#markup' => $pane,
    );
  }

  return drupal_render($element);
}
