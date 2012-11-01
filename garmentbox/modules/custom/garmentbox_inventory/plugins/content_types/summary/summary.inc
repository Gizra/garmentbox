<?php

/**
 * Plugin definition.
 */
$plugin = array(
  'title' => t('Inventory summary'),
  'description' => t('Show inventory summary per Item/ Season'),
  'required context' => new ctools_context_required(t('Node'), 'node'),
  'category' => t('Garmentbox Inventory'),
  'hook theme' => 'garmentbox_inventory_summary_content_type_theme',
);

/**
 * Render callback.
 */
function garmentbox_inventory_summary_content_type_render($subtype, $conf, $args, $context) {
  if (empty($context->data)) {
    return FALSE;
  }

  $node = $context->data;
  if (!in_array($node->type, array('item', 'season'))) {
    throw new Exception('Wrong node type passed to Inventory summary');
  }

  $module = 'garmentbox_inventory';

  $block = new stdClass();
  $block->module = $module;
  $block->title = t('Inventory summary');
  $block->content = t('No inventory created yet.');

  $item_nids = array();
  if ($node->type == 'item') {
    $item_nids = array($node->nid);
  }
  else {
    // Get all the items that belong to the season.
    $query = new EntityFieldQuery();
    $result = $query->entityCondition('entity_type', 'node')
      ->propertyCondition('type', 'item')
      ->propertyCondition('status', NODE_PUBLISHED)
      ->fieldCondition('field_season', 'target_id', $node->nid)
      ->execute();

    if (empty($result['node'])) {
      return $block;
    }

    $item_nids = array_keys($result['node']);
  }

  // Build an array of inventory types, keyed by TID. Specifying whether the
  // type should be included in "totals".
  $excluded_inventory_types = array();
  $vocab = taxonomy_vocabulary_machine_name_load('inventory_type');
  foreach (taxonomy_get_tree($vocab->vid, 0, NULL, TRUE) as $term) {
    $wrapper = entity_metadata_wrapper('taxonomy_term', $term);
    $inventory_types[$term->tid] = array(
      'include_in_total' => $wrapper->field_include_in_total->value(),
    );
    if (!$wrapper->field_include_in_total->value()) {
      $excluded_inventory_types[] = $wrapper->label();
    }
  }

  $total_type_label = t('All types');
  if ($excluded_inventory_types) {
    $total_type_label .= t('<span class="minor">Except of @types.</span>', array('@types' => implode(', ', $excluded_inventory_types)));
  }

  $header = $rows = array();
  $header['item variant'] = t('Variation');

  $vocab = taxonomy_vocabulary_machine_name_load('size');
  $size_tree = taxonomy_get_tree($vocab->vid);
  foreach ($size_tree as $term) {
    $header[$term->tid] = $term->name;
  }

  $header['type'] = t('Type');

  // Get all the item variants that belong to the items.
  $query = new EntityFieldQuery();
  $result = $query->entityCondition('entity_type', 'node')
    ->propertyCondition('type', 'item_variant')
    ->propertyCondition('status', NODE_PUBLISHED)
    ->fieldCondition('field_item', 'target_id', $item_nids, 'IN')
    ->execute();

  if (empty($result['node'])) {
    return $block;
  }

  // Get all the inventory lines that belong to the item variants.
  $query = new EntityFieldQuery();
  $result = $query->entityCondition('entity_type', 'node')
    ->propertyCondition('type', 'inventory_line')
    ->propertyCondition('status', NODE_PUBLISHED)
    ->fieldCondition('field_item_variant', 'target_id', array_keys($result['node']), 'IN')
    ->fieldOrderBy('field_item_variant', 'target_id')
    ->execute();

  if (empty($result['node'])) {
    return $block;
  }

  drupal_add_js(drupal_get_path('module', $module) . '/plugins/content_types/' . $subtype . '/' . $subtype . '.js');

  // Build inventory data info, keyed by the inventory item type TID.
  $inventory = array();
  $inventory_nodes = node_load_multiple(array_keys($result['node']));
  foreach($inventory_nodes as $inventory_node) {
    $wrapper = entity_metadata_wrapper('node', $inventory_node);
    $tid = $wrapper->field_inventory_type->getIdentifier();

    // Determine if we need to add or subtract the quantity from the total
    // calcualtion.
    $in_warehouse = $wrapper->field_inventory_type->field_in_warehouse->value();

    $nid = $wrapper->field_item_variant->getIdentifier();

    // Don't affect the total with excluded inventory types.
    $include_in_total = $inventory_types[$tid]['include_in_total'];

    $inventory[$nid]['label'] = $wrapper->field_item_variant->label();
    $inventory[$nid]['types'][$tid]['type_label'] = $wrapper->field_inventory_type->label();
    $inventory[$nid]['types'][$tid]['in_total'] = $include_in_total;

    foreach ($size_tree as $term) {
      $inventory[$nid]['total'][$term->tid]['available'] = !empty($inventory[$nid]['total'][$term->tid]['available']) ? $inventory[$nid]['total'][$term->tid]['available'] : 0;
      $inventory[$nid]['total'][$term->tid]['ordered'] = !empty($inventory[$nid]['total'][$term->tid]['ordered']) ? $inventory[$nid]['total'][$term->tid]['ordered'] : 0;
      $inventory[$nid]['total'][$term->tid]['future_stock'] = !empty($inventory[$nid]['total'][$term->tid]['future_stock']) ? $inventory[$nid]['total'][$term->tid]['future_stock'] : 0;
      $inventory[$nid]['total'][$term->tid]['quantity'] = !empty($inventory[$nid]['total'][$term->tid]['quantity']) ? $inventory[$nid]['total'][$term->tid]['quantity'] : 0;
    }

    $is_ordered = garmentbox_inventory_is_inventory_item_ordered($inventory_node->nid);

    foreach ($wrapper->field_quantity_info as $quantity_wrapper) {
      $size_tid = $quantity_wrapper->field_size->getIdentifier();
      $info = !empty($inventory[$nid]['types'][$tid]['data'][$size_tid]) ? $inventory[$nid]['types'][$tid]['data'][$size_tid] : array();
      $info['quantity'] = !empty($info['quantity']) ? $info['quantity'] : 0;
      $info['ordered'] = !empty($info['ordered']) ? $info['ordered'] : 0;

      $quantity = $quantity_wrapper->field_quantity->value();

      $info['quantity'] += $quantity;
      if ($is_ordered) {
        $info['ordered'] += $quantity;
      }
      $inventory[$nid]['types'][$tid]['data'][$size_tid] = $info;

      // Quantity - Inventory line with stock type marked as “in warehouse” and
      // both ordered and not ordered (also could be Available + ordered).
      // Available (green) - This is stock NOT ordered marked as in warehouse.
      // Ordered (blue)(used to available) - This is ordered stock in status
      // marked as in warehouse. + Ordered-future.
      // Ordered-future (red)- This is a sum of ordered inventory lines in
      // status marked as NOT in warehouse deducted from sum of all inventory
      // line with not in warehouse and no order.
      // Future stock - Sum not in warehouse and No order.
      if ($in_warehouse) {
        $inventory[$nid]['total'][$size_tid]['quantity'] += $include_in_total ? $quantity : 0;

        if ($is_ordered) {
          $inventory[$nid]['total'][$size_tid]['ordered'] += $include_in_total ? $quantity : 0;
        }
        else {
          $inventory[$nid]['total'][$size_tid]['available'] += $include_in_total ? $quantity : 0;
        }
      }
      else {
        if ($is_ordered) {
          $inventory[$nid]['total'][$size_tid]['ordered'] += $include_in_total ? $quantity : 0;
        }
        else {
          $inventory[$nid]['total'][$size_tid]['future_stock'] += $include_in_total ? $quantity : 0;
        }
      }
    }
  }

  // Build the output based on the inventory data info.
  foreach ($inventory as $nid => $variant_data) {

    $items = array();
    $variant_label = $variant_data['label'];

    // Variant total row.
    $row = array(
      'data' => array(),
      'class' => array('expandable'),
      'variant-nid' => $nid,
    );
    $params = array(
      'attributes' => array(
        'class' => array('expander', 'collapsed'),
      )
    );
    $expand_link = l('', url(''), $params);
    $row['data'][] = $expand_link . t('@variant - Total', array('@variant' => $variant_label));
    foreach($size_tree as $term) {
      $row['data'][] = theme('garmentbox_inventory_cell', $variant_data['total'][$term->tid] + array('quantity_title' => t('Stock')));
    }

    // Total row description.
    $row['data'][] = $total_type_label;

    $rows[] = $row;

    foreach ($variant_data['types'] as $inventory_tid => $variant_inventory_data) {
      if (empty($variant_inventory_data['data'])) {
        // There are no values for this inventory type.
        continue;
      }
      $row = array(
        'data' => array(),
        'class' => array('type', 'hidden', 'variant-nid-' . $nid),
      );

      // Add a class specifying that the row is included in the total, to enable
      // highlighting it when the total is hovered.
      if ($variant_inventory_data['in_total']) {
        $row['class'][] = 'in-total';
      }

      $row['data'][] = $variant_label;

      foreach($size_tree as $term) {
        if (empty($variant_inventory_data['data'][$term->tid])) {
          $row['data'][] = theme('garmentbox_inventory_cell', array('quantity' => 0));
          continue;
        }

        $row['data'][] = theme('garmentbox_inventory_cell', $variant_inventory_data['data'][$term->tid]);
      }
      $row['data'][] = $variant_inventory_data['type_label'];
      $rows[] = $row;
    }
  }

  $block->content = array(
    '#theme' => 'table',
    '#header' => $header,
    '#rows' => $rows,
  );
  return $block;
}

/**
 * Edit form.
 */
function garmentbox_inventory_summary_content_type_edit_form($form, &$form_state) {
  return $form;
}

/**
 * Delegated hook_theme().
 */
function garmentbox_inventory_summary_content_type_theme(&$theme, $plugin) {
  $theme['garmentbox_inventory_cell'] = array(
    'variables' => array(
      'quantity' => NULL,
      'available' => NULL,
      'ordered' => NULL,
      'future_stock' => NULL,
      'label' => NULL,
      'class' => NULL,
      'quantity_title' => NULL,
      'subfigure_types' => array(
        'available' => t('Available'),
        'ordered' => t('Ordered'),
        'future_stock' => t('Future stock'),
      ),
    ),
    'path' => $plugin['path'],
    'template' => 'inventory-cell',
  );
}
