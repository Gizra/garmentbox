<?php

/**
 * Plugin definition.
 */
$plugin = array(
  'title' => t('Inventory summary'),
  'description' => t('Show inventory summary per Item/ Season'),
  'required context' => new ctools_context_required(t('Node'), 'node'),
  'category' => t('Opengizra Inventory'),
);

/**
 * Render callback.
 */
function opengizra_inventory_summary_content_type_render($subtype, $conf, $args, $context) {
  if (empty($context->data)) {
    return FALSE;
  }

  $node = $context->data;
  if (!in_array($node->type, array('item', 'season'))) {
    throw new Exception('Wrong node type passed to Inventory summary');
  }

  $module = 'opengizra_inventory';

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

  $vocab = taxonomy_vocabulary_machine_name_load('inventory_type');
  foreach (taxonomy_get_tree($vocab->vid) as $value) {
    $tids[] = $value->tid;
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

  // Build inventory data info, keyed by the inventory item type TID.
  $inventory = array();
  $inventory_nodes = node_load_multiple(array_keys($result['node']));
  foreach($inventory_nodes as $inventory_node) {
    $wrapper = entity_metadata_wrapper('node', $inventory_node);
    $tid = $wrapper->field_inventory_type->getIdentifier();
    $nid = $wrapper->field_item_variant->getIdentifier();

    $inventory[$nid]['label'] = $wrapper->field_item_variant->label();
    $inventory[$nid]['types'][$tid]['type_label'] = $wrapper->field_inventory_type->label();

    $inventory[$nid]['types'][$tid]['availablity'] = !empty($inventory[$nid]['availablity']) ? $inventory[$nid]['availablity'] : 0;
    $inventory[$nid]['types'][$tid]['quantity'] = !empty($inventory[$nid]['quantity']) ? $inventory[$nid]['quantity'] : 0;

    $is_ordered = opengizra_inventory_is_inventory_item_ordered($inventory_node->nid);

    foreach ($wrapper->field_quantity_info as $quantity_wrapper) {
      $size_tid = $quantity_wrapper->field_size->getIdentifier();
      $info = !empty($inventory[$nid]['types'][$tid]['data'][$size_tid]) ? $inventory[$nid]['types'][$tid]['data'][$size_tid] : array();
      $info['availability'] = !empty($info['availability']) ? $info['availability'] : 0;
      $info['quantity'] = !empty($info['quantity']) ? $info['quantity'] : 0;
      // Determine if we need to add or subtract the quantity from the
      // total calcualtion.
      $status = $wrapper->field_inventory_status->value();
      $quantity = $quantity_wrapper->field_quantity->value();

      // Inventory line with Order ref are always sold (or ordered) stock and
      // need to be deducted from total and availability if marked as OUT, and
      // from availability only if marked as IN .
      if ($is_ordered) {
        if (!$status) {
          $info['availability'] -= $quantity;
          $inventory[$nid]['types'][$tid]['availablity'] -= $quantity;
        }
      }
      else {
        $operation = $status ? 1 : -1;
        $info['availability'] += $quantity * $operation;
        $inventory[$nid]['types'][$tid]['availablity'] += $quantity * $operation;
        if ($status) {
          $info['quantity'] += $quantity;
          $inventory[$nid]['types'][$tid]['quantity'] += $quantity;
        }
      }

      $inventory[$nid]['types'][$tid]['data'][$size_tid] = $info;
    }
  }

  // Build the output based on the inventory data info.
  foreach ($inventory as $nid => $variant_data) {

    $items = array();
    $variant_label = $variant_data['label'];

    // Variant total row.
    $row = array(t('@variant - Total', array('@variant' => $variant_label)));
    // TODO: Fix the total row.
    // foreach($size_tree as $term) {
      // $row[] = opengizra_inventory_summary_quantity_cell($variant_data['types'][$term->tid]['quantity'], $variant_data['types'][$term->tid]['availablity']);
    // }

    $rows[] = $row;

    foreach ($variant_data['types'] as $inventory_tid => $variant_inventory_data) {
      if (empty($variant_inventory_data['data'])) {
        // There are no values for this inventory type.
        continue;
      }
      $row = array();

      $row[] = $variant_label;

      foreach($size_tree as $term) {
        if (empty($variant_inventory_data['data'][$term->tid])) {
          $row[] = '-';
          continue;
        }

        $row[] = opengizra_inventory_summary_quantity_cell($variant_inventory_data['data'][$term->tid]['quantity'], $variant_inventory_data['data'][$term->tid]['availability']);
      }
      $row[] = $variant_inventory_data['type_label'];
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
function opengizra_inventory_summary_content_type_edit_form($form, &$form_state) {
  return $form;
}

/**
 * TODO: Add tpl for the mess.
 */
function opengizra_inventory_summary_quantity_cell($quantity, $availability) {
  $cell = '<div class="quantity">' . $quantity . '</div>';

  if ($availability) {
    if ($availability > 0) {
      $class = 'available';
      $label = t('Available');
    }
    else {
      $class = 'backorder';
      $label = t('Backorder');
      // Display the absolute value.
      $availability *= -1;
    }

    $cell .= "<div class=\"availability $class\"><span class=\"amount\">$availability</span><span class=\"label\">$label</span></div>";
  }

  return $cell;
}
