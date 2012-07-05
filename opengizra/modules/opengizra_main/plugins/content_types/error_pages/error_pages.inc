<?php
/**
 * Plugin definition
 */
$plugin = array(
  'title' => t('Error pages'),
  'description' => t("Showe page 403 or 404."),
  'category' => t('Opengizra'),
  'defaults' => array('error_number' => 403),
);

/**
 * Render callback.
 */
function opengizra_main_error_pages_content_type_render($subtype, $conf, $args, $context) {
  $module = 'opengizra_main';
  $image = theme('image', array('path' => drupal_get_path('module', $module) . '/plugins/content_types/' . $subtype . '/'. $conf['error_number'] . '.png'));

  $block = new stdClass();
  $block->module = $module;
  $block->title = '';
  $block->content = l($image, '', array('html' => TRUE));

  return $block;
}

/**
 * Form callback.
 */
function opengizra_main_error_pages_content_type_edit_form($form, &$form_state) {
  $conf = $form_state['conf'];

  $form['error_number'] = array(
    '#type' => 'select',
    '#title' => t('Error number'),
    '#default_value' => $conf['error_number'],
    '#options' => array(
      403 => t('Access denied - 403'),
      404 => t('Page not found- 404'),
    ),
    '#required' => TRUE,
  );
  return $form;
}

/**
 * Form submit.
 */
function opengizra_main_error_pages_content_type_edit_form_submit($form, &$form_state) {
  // Copy everything from our defaults.
  foreach (array_keys($form_state['plugin']['defaults']) as $key) {
    $form_state['conf'][$key] = $form_state['values'][$key];
  }
}
