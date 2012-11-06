<?php

/**
 * Plugin definition.
 */
$plugin = array(
  'title' => t('Production order items'),
  'description' => t("Display a form for selecting the production order's items."),
  'required context' => new ctools_context_optional(t('Node'), 'node'),
  'category' => t('Garmentbox Factory'),
);

/**
 * Render callback.
 */
function garmentbox_factory_production_order_items_content_type_render($subtype, $conf, $args, $context) {
  $block = new stdClass();
  $block->module = 'garmentbox_factory';
  $block->title = '';

  $node = $context->data;

  $block->content = 'asfd';
  return $block;
}

/**
 * Edit form.
 */
function garmentbox_factory_production_order_items_content_type_edit_form($form, &$form_state) {
  return $form;
}
