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
  $wrapper = entity_metadata_wrapper('node', $node);
  if (empty($wrapper->field_bom_info)) {
    return;
  }

  // Get the first BOM collection item.
  if (!$entity = $wrapper->field_bom_info->get(0)->field_material_item->value()) {
    return;
  }

  // Wrap the host entity of the first item.
  $wrapper = entity_metadata_wrapper('node', $entity->hostEntity());
  if (!$wrapper->field_images->value()) {
    return;
  }
  // Display the first material image.
  $image = $wrapper->field_images->get(0)->value();
  $block->content = theme('image_style', array('style_name' => 'material_thumbnail', 'path' => $image['uri']));
  return $block;
}

/**
 * Edit form.
 */
function opengizra_item_main_material_content_type_edit_form($form, &$form_state) {
  return $form;
}
