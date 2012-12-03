<?php

/**
 * Plugin definition.
 */
$plugin = array(
  'title' => t('Inventory summary'),
  'description' => t('Show inventory summary per Item'),
  'required context' => new ctools_context_required(t('Node'), 'node'),
  'category' => t('Garmentbox Inventory'),
  'hook theme' => 'garmentbox_inventory_summary_content_type_theme',
);

/**
 * Render callback.
 */
function garmentbox_inventory_summary_content_type_render($subtype, $conf, $args, $context) {
  if (empty($context->data)) {
    return;
  }

  $node = $context->data;

  $module = 'garmentbox_inventory';

  $block = new stdClass();
  $block->module = $module;
  $block->title = t('Inventory summary');
  $block->content = garmentbox_inventory_get_summary($node);

  return $block;
}

/**
 * Edit form.
 */
function garmentbox_inventory_summary_content_type_edit_form($form, &$form_state) {
  return $form;
}
