<?php

/**
 * Plugin definition.
 */
$plugin = array(
  'title' => t('Item variants tabs'),
  'description' => t('Show item instances as tabs'),
  'required context' => new ctools_context_required(t('Node'), 'node'),
  'category' => t('Opengizra Item'),
);

/**
 * Render callback.
 */
function opengizra_item_item_variant_tabs_content_type_render($subtype, $conf, $args, $context) {
  if (empty($context->data)) {
    return FALSE;
  }

  $node = $context->data;
  if ($node->type != 'item') {
    throw new Exception('Item variants tabs expects passed node to be of type Instance');
  }

  $module = 'opengizra_item';
  $block = new stdClass();
  $block->module = $module;
  $block->title = '';

  // Get all the item instances referencing the item.
  $query = new EntityFieldQuery();
  $result = $query
    ->entityCondition('entity_type', 'node')
    ->propertyCondition('type', 'item_variant')
    ->propertyCondition('status', NODE_PUBLISHED)
    ->fieldCondition('field_item', 'target_id', $node->nid)
    ->propertyOrderBy('nid')
    ->execute();

  if (empty($result['node'])) {
    $block->content = t('@title has no Item Variations', array('@title' => $node->title));
    return $block;
  }

  // Render each node through a mini-panel.
  $nodes = node_load_multiple(array_keys($result['node']));

  $form = array();
  $form['tabs_wrapper'] = array(
    '#prefix' => '<div id="tabs">',
    '#suffix' => '</div>',
  );


  $items = array();
  foreach ($nodes as $node) {
    $items[] = '<a href="#item-variant-' . $node->nid . '">' . check_plain($node->title) . '</a>';


    $output = '<div id="item-variant-' . $node->nid . '">' . opengizra_general_render_node_as_mini_panel($node, 'item_variant') . '</div>';
    // Add the tab itself.
    $form['tabs_wrapper']['item_variant_' . $node->nid] = array('#markup' => $output);
  }

  $form['tabs_wrapper']['tabs_header'] = array(
    '#theme' => 'item_list',
    '#items' => $items,
    '#weight' => -5,
  );

  $form['#attached']['library'][] = array('system', 'ui.tabs');
  $form['#attached']['js'][] = drupal_get_path('module', 'opengizra_item') . "/plugins/content_types/$subtype/$subtype.js";

  $block->content = $form;
  return $block;
}

/**
 * Edit form.
 */
function opengizra_item_item_variant_tabs_content_type_edit_form($form, &$form_state) {
  return $form;
}
