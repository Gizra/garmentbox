<?php

/**
 * Plugin definition.
 */
$plugin = array(
  'title' => t('Production order links'),
  'description' => t('Display production order links.'),
  'required context' => new ctools_context_required(t('Node'), 'node'),
  'category' => t('Garmentbox'),
);

/**
 * Render callback.
 */
function garmentbox_factory_production_order_links_content_type_render($subtype, $conf, $args, $context) {
  if (empty($context->data)) {
    return;
  }
  $nid = $context->data->nid;

  $block = new stdClass();
  $block->module = 'garmentbox_factory';
  $block->title = '';

  $items = array();
  $items[] = l(t('Main'), "node/$nid");
  $items[] = l(t('Production delivery'), "production-order/$nid/delivery");

  $block->content = theme('item_list', array('items' => $items));
  return $block;
}

/**
 * Edit form.
 */
function garmentbox_factory_production_order_links_content_type_edit_form($form, &$form_state) {
  return $form;
}
