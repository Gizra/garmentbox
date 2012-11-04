<?php

/**
 * Plugin definition.
 */
$plugin = array(
  'title' => t('Item variants links'),
  'description' => t('Display links to item\'s variants.'),
  'required context' => new ctools_context_required(t('Node'), 'node'),
  'category' => t('Garmentbox Item'),
);

/**
 * Render callback.
 */
function garmentbox_item_item_variant_links_content_type_render($subtype, $conf, $args, $context) {
  if (empty($context->data)) {
    return FALSE;
  }

  $block = new stdClass();
  $block->module = 'garmentbox_item';
  $block->title = '';
  $block->css_class = 'tabs';

  $node = $context->data;
  // If the given node is a variant, load its main item.
  if ($node->type == 'item_variant') {
    $wrapper = entity_metadata_wrapper('node', $node);
    $node = $wrapper->field_item->value();
  }

  $items = array();
  if ($node->type == 'item') {
    $items[] = l(t('Main'), 'node/' . $node->nid);

    // Get all the item instances referencing the item.
    $query = new EntityFieldQuery();
    $result = $query
      ->entityCondition('entity_type', 'node')
      ->propertyCondition('type', 'item_variant')
      ->propertyCondition('status', NODE_PUBLISHED)
      ->fieldCondition('field_item', 'target_id', $node->nid)
      ->propertyOrderBy('nid')
      ->execute();

    if (!empty($result['node'])) {
      $nodes = node_load_multiple(array_keys($result['node']));
      foreach ($nodes as $node) {
        $items[] = l($node->title, 'node/' . $node->nid);
      }
    }
  }

  $block->content = theme('item_list', array('items' => $items));
  return $block;
}

/**
 * Edit form.
 */
function garmentbox_item_item_variant_links_content_type_edit_form($form, &$form_state) {
  return $form;
}
