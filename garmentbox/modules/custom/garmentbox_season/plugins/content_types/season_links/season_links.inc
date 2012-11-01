<?php

/**
 * Plugin definition.
 */
$plugin = array(
  'title' => t('Season links'),
  'description' => t('Display season links.'),
  'required context' => new ctools_context_required(t('Node'), 'node'),
  'category' => t('Garmentbox'),
);

/**
 * Render callback.
 */
function garmentbox_season_season_links_content_type_render($subtype, $conf, $args, $context) {
  if (empty($context->data)) {
    return;
  }
  $nid = $context->data->nid;

  $block = new stdClass();
  $block->module = 'garmentbox_season';
  $block->title = '';

  $items = array();
  $items[] = l(t('Task List'), "node/$nid");
  $items[] = l(t('Items'), "season/$nid/items");
  $items[] = l(t('Inventory'), "season/$nid/inventory");
  $items[] = l(t('Orders'), "season/$nid/orders");

  $block->content = theme('item_list', array('items' => $items));
  return $block;
}

/**
 * Edit form.
 */
function garmentbox_season_season_links_content_type_edit_form($form, &$form_state) {
  return $form;
}
