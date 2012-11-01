<?php

/**
 * Plugin definition.
 */
$plugin = array(
  'title' => t('Main material'),
  'description' => t('Display the main material of an item variant.'),
  'required context' => new ctools_context_required(t('Node'), 'node'),
  'category' => t('Garmentbox Item'),
);

/**
 * Render callback.
 */
function garmentbox_item_main_material_content_type_render($subtype, $conf, $args, $context) {
  if (empty($context->data)) {
    return FALSE;
  }

  $block = new stdClass();
  $block->module = 'garmentbox_item';
  $block->title = '';

  $node = $context->data;
  $block->content = garmentbox_item_get_main_material_icon($node);
  return $block;
}

/**
 * Edit form.
 */
function garmentbox_item_main_material_content_type_edit_form($form, &$form_state) {
  return $form;
}
