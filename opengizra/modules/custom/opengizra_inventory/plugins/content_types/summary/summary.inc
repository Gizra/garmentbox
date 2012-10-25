<?php

/**
 * Plugin definition.
 */
$plugin = array(
  'title' => t('Inventory summary'),
  'description' => t('Show inventory summary per Item/ Season'),
  'required context' => new ctools_context_required(t('Node'), 'node'),
  'category' => t('Opengizra Inventory'),
  'hook theme' => 'opengizra_inventory_summary_content_type_theme',
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
      $inventory[$nid]['total'][$term->tid]['availablity'] = !empty($inventory[$nid]['total'][$term->tid]['availablity']) ? $inventory[$nid]['total'][$term->tid]['availablity'] : 0;
      $inventory[$nid]['total'][$term->tid]['quantity'] = !empty($inventory[$nid]['total'][$term->tid]['quantity']) ? $inventory[$nid]['total'][$term->tid]['quantity'] : 0;
    }

    $is_ordered = opengizra_inventory_is_inventory_item_ordered($inventory_node->nid);

    foreach ($wrapper->field_quantity_info as $quantity_wrapper) {
      $size_tid = $quantity_wrapper->field_size->getIdentifier();
      $info = !empty($inventory[$nid]['types'][$tid]['data'][$size_tid]) ? $inventory[$nid]['types'][$tid]['data'][$size_tid] : array();
      $info['availability'] = !empty($info['availability']) ? $info['availability'] : 0;
      $info['quantity'] = !empty($info['quantity']) ? $info['quantity'] : 0;

      $quantity = $quantity_wrapper->field_quantity->value();

      // Inventory line with Order ref are always sold (or ordered) stock and
      // need to be deducted from total and availability if marked as OUT, and
      // from availability only if marked as IN. IN = 0, OUT = 1.
      if ($is_ordered) {
        if (!$in_warehouse) {
          $info['availability'] -= $quantity;
          $inventory[$nid]['total'][$size_tid]['availablity'] -= $include_in_total ? $quantity : 0;
        }
      }
      else {
        $operation = $in_warehouse ? -1 : 1;
        $info['availability'] += $quantity * $operation;
        $inventory[$nid]['total'][$size_tid]['availablity'] += $include_in_total ? ($quantity * $operation) : 0;
        if ($in_warehouse) {
          $info['quantity'] += $quantity;
          $inventory[$nid]['total'][$size_tid]['quantity'] += $include_in_total ? $quantity : 0;
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
      $row['data'][] = opengizra_inventory_summary_quantity_cell($variant_data['total'][$term->tid]['quantity'], $variant_data['total'][$term->tid]['availablity']);
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
          $row['data'][] = 0;
          continue;
        }

        $quantity = $variant_inventory_data['data'][$term->tid]['quantity'] + abs($variant_inventory_data['data'][$term->tid]['availability']);
        $row['data'][] = $quantity;
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
function opengizra_inventory_summary_content_type_edit_form($form, &$form_state) {
  return $form;
}

/**
 * Render a quantity / availablity cell.
 *
 * @param $quantity
 *   The quantity.
 * @param $availablity
 *   How much is actualy available out of the quantity.
 *
 * @return
 *   Rendered "inventory cell".
 */
function opengizra_inventory_summary_quantity_cell($quantity, $availability) {
  $params = array(
    'quantity' => $quantity,
    'availability' => $availability,
    'label' => NULL,
    'class' => NULL,
  );

  if ($availability) {
    if ($availability > 0) {
      $params['class'] = 'available';
      $params['label'] = t('Available');
    }
    else {
      $params['class'] = 'backorder';
      $params['label'] = t('Backorder');
      // Display the absolute value.
      $params['availability'] *= -1;
    }
  }

  return theme('opengizra_inventory_cell', $params);
}

/**
 * Delegated hook_theme().
 */
function opengizra_inventory_summary_content_type_theme(&$theme, $plugin) {
  $theme['opengizra_inventory_cell'] = array(
    'variables' => array(
      'quantity' => NULL,
      'availability' => NULL,
      'label' => NULL,
      'class' => NULL,
    ),
    'path' => $plugin['path'],
    'template' => 'inventory-cell',
  );
}
