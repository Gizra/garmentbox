<?php

/**
 * Plugin definition.
 */
$plugin = array(
  'title' => t('Main material'),
  'description' => t('Display the main material of an item variant.'),
  'required context' => new ctools_context_required(t('Node'), 'node'),
  'category' => t('Opengizra Item'),
);

/**
 * Render callback.
 */
function opengizra_item_main_material_content_type_render($subtype, $conf, $args, $context) {
  if (empty($context->data)) {
    return FALSE;
  }

  $block = new stdClass();
  $block->module = 'opengizra_item';
  $block->title = '';

  $node = $context->data;
  $block->content = opengizra_item_get_main_material_icon($node);
  return $block;
}

/**
 * Edit form.
 */
function opengizra_item_main_material_content_type_edit_form($form, &$form_state) {
  return $form;
}
