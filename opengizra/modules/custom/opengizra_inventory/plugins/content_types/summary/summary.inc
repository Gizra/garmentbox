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

  $terms = taxonomy_term_load_multiple($tids);


  $header = $rows = array();
  $header['item variant'] = t('Item Variant');
  // Determine which inventory type should be calcualted in the total.
  $include_total = array();
  $not_include_total = array();
  foreach ($terms as $term) {
    $wrapper = entity_metadata_wrapper('taxonomy_term', $term);
    $header[$term->tid] = $term->name;
    $value = $wrapper->field_include_in_total->value();

    $include_total[$term->tid] = $value;
    if (!$value) {
      $not_include_total[$term->tid] = $term->name;
    }
  }

  $header['total'] = $not_include_total ? t('Total (not including @types)', array('@types' => implode(', ', $not_include_total))) : t('Total');

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
    ->execute();

  if (empty($result['node'])) {
    return $block;
  }

  // Build inventory data info, keyed by the item variant node ID.
  $inventory = array();
  $inventory_nodes = node_load_multiple(array_keys($result['node']));
  foreach($inventory_nodes as $inventory_node) {
    $wrapper = entity_metadata_wrapper('node', $inventory_node);
    $nid = $wrapper->field_item_variant->getIdentifier();
    $tid = $wrapper->field_inventory_type->getIdentifier();

    $inventory[$nid]['label'] = $wrapper->field_item_variant->label();

    foreach ($wrapper->field_quantity_info as $quantity_wrapper) {
      $size_tid = $quantity_wrapper->field_size->getIdentifier();
      $info = !empty($inventory[$nid]['data'][$tid][$size_tid]) ? $inventory[$nid]['data'][$tid][$size_tid] : array();

      $info['label'] = $quantity_wrapper->field_size->label();
      $info['quantity'] = !empty($info['quantity']) ? $info['quantity'] : 0;
      // Determine if we need to add or subtract the quantity from the
      // total calcualtion.
      $operation = $wrapper->field_inventory_status->value() ? 1 : -1;
      $info['quantity'] += $quantity_wrapper->field_quantity->value() * $operation;

      $inventory[$nid]['data'][$tid][$size_tid] = $info;
    }
  }

  // Add empty data for non-exsiting inventory types.
  foreach ($terms as $term) {
    foreach ($inventory as $nid => $data) {
      if (empty($inventory[$nid]['data'][$term->tid])) {
        $inventory[$nid]['data'][$term->tid] = array();
      }
    }
  }

  // Calcualte total.
  foreach ($inventory as $nid => $node_data) {
    foreach ($node_data['data'] as $tid => $term_data) {
      if (!$term_data) {
        continue;
      }
      foreach ($term_data as $size_tid => $data) {
        $inventory[$nid]['total'][$size_tid]['label'] = $data['label'];
        $inventory[$nid]['total'][$size_tid]['quantity'] = !empty($inventory[$nid]['total'][$size_tid]['quantity']) ? $inventory[$nid]['total'][$size_tid]['quantity'] : 0;

        // Check if the term should be included in the total calculation.
        $wrapper = entity_metadata_wrapper('taxonomy_term', $tid);
        if ($wrapper->field_include_in_total->value()) {
          $inventory[$nid]['total'][$size_tid]['quantity'] += $data['quantity'];
        }
      }
    }
    $inventory[$nid]['total'] = !empty($inventory[$nid]['total']) ? $inventory[$nid]['total'] : array();
  }

  // Build the output based on the inventory data info.
  foreach ($inventory as $nid => $data) {
    $row = array();
    if ($node->type == 'season') {
      $wrapper = entity_metadata_wrapper('node', $nid);
      $row[] = l($data['label'], 'node/' . $wrapper->field_item->getIdentifier());
    }
    else {
      $row[] = $data['label'];
    }


    $items = array();
    foreach ($header as $inventory_tid => $header_value) {
      if (!is_numeric($inventory_tid)) {
        continue;
      }

      $inventory_data = $data['data'][$inventory_tid];
      if (!$inventory_data) {
        // There are no values for this inventory type.
        $row[] = '-';
        continue;
      }

      $items = array();
      foreach ($inventory_data as $value) {
        $params = array(
          '@size' => $value['label'],
          '@quantity' => $value['quantity'],
        );
        $items[] =  format_string('@size: @quantity', $params);
      }
      $row[] = theme('item_list', array('items' => $items));
    }

    $items = array();
    if ($data['total']) {
      foreach ($data['total'] as $value) {
        $params = array(
          '@size' => $value['label'],
          '@quantity' => $value['quantity'],
        );
        $items[] =  format_string('@size: @quantity', $params);
      }

      $row[] = theme('item_list', array('items' => $items));
    }
    else {
      $row[] = '-';
    }

    $rows[] = $row;
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
