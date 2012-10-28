<?php

/**
 * Plugin definition.
 */
$plugin = array(
  'title' => t('Orders'),
  'description' => t('Displau orders per Item/ Season'),
  'required context' => new ctools_context_required(t('Node'), 'node'),
  'category' => t('Opengizra Order'),
);

/**
 * Render callback.
 */
function opengizra_order_orders_content_type_render($subtype, $conf, $args, $context) {
  if (empty($context->data)) {
    return FALSE;
  }

  $node = $context->data;

  $module = 'opengizra_order';

  $block = new stdClass();
  $block->module = $module;
  $block->title = t('Orders');
  $block->content = t('No orders created yet.');

  $query = db_select('node', 'n');
  $query->innerJoin('field_data_field_item_variant', 'fiv', 'n.nid = fiv.entity_id');
  $query->innerJoin('field_data_field_item', 'fi', 'fiv.field_item_variant_target_id = fi.entity_id');
  if ($node->type == 'season') {
    $query->innerJoin('field_data_field_season', 'fs', 'fi.field_item_target_id = fs.entity_id');
  }
  $query->innerJoin('field_data_field_inventory_line_inline', 'fili', 'fili.field_inventory_line_inline_target_id = n.nid');
  $query->innerJoin('node', 'n_order', 'fili.entity_id = n_order.nid');
  $query->innerJoin('field_data_field_customer', 'fc', 'fc.entity_id = n_order.nid');
  $query->innerJoin('node', 'n_customer', 'n_customer.nid = fc.field_customer_target_id');
  $query->innerJoin('node', 'n_variant', 'n_variant.nid = fiv.field_item_variant_target_id');
  $query->innerJoin('field_data_field_inventory_type', 'fit', 'fit.entity_id = n.nid');
  $query->innerJoin('taxonomy_term_data', 'td', 'td.tid = fit.field_inventory_type_target_id');
  $query->leftJoin('field_data_field_quantity_info', 'fqi', 'fqi.entity_id = n.nid');
  $query->innerJoin('field_data_field_quantity', 'fq', 'fq.entity_id = fqi.field_quantity_info_value');
  $query->innerJoin('field_data_field_size', 'fsz', 'fsz.entity_id = fqi.field_quantity_info_value');
  $query->leftJoin('field_data_field_delivery_date', 'fdd', 'fdd.entity_id = n.nid');
  $query->innerJoin('field_data_field_order_status', 'fos', 'fos.entity_id = n_order.nid');
  $query->innerJoin('taxonomy_term_data', 'tdfos', 'tdfos.tid = fos.field_order_status_target_id');

  $query->addField('n', 'nid');
  $query->addField('n_order', 'nid', 'order_nid');
  $query->addField('n_order', 'title', 'order_title');
  $query->addField('tdfos', 'name', 'order_status');
  $query->addField('n_customer', 'nid', 'customer_nid');
  $query->addField('n_customer', 'title', 'customer');
  $query->addField('n_variant', 'nid', 'variant_nid');
  $query->addField('n_variant', 'title', 'variant');
  $query->addField('td', 'name', 'type');
  $query->addField('fsz', 'field_size_target_id', 'size_tid');
  $query->addField('fq', 'field_quantity_value', 'quantity');
  $query->addExpression('UNIX_TIMESTAMP(fdd.field_delivery_date_value)', 'delivery_date');

  $query
    ->condition('n.type', 'inventory_line')
    ->condition('n.status', NODE_PUBLISHED)
    ->condition('n_customer.status', NODE_PUBLISHED)
    ->condition('n_variant.status', NODE_PUBLISHED)
    ->condition('n_order.status', NODE_PUBLISHED)
    ->condition('fiv.entity_type', 'node')
    ->condition('fi.entity_type', 'node')
    ->condition('fili.entity_type', 'node')
    ->condition('fc.entity_type', 'node')
    ->condition('fit.entity_type', 'node')
    ->condition('fqi.entity_type', 'node')
    ->condition('fdd.entity_type', 'node')
    ->condition('fos.entity_type', 'node')
    ->condition('fq.entity_type', 'field_collection_item')
    ->condition('fsz.entity_type', 'field_collection_item');

  if ($node->type == 'season') {
    $query->condition('fs.field_season_target_id', $node->nid);
  }

  $query->orderBy('n_order.nid');

  $result = $query->execute();

  $vocabulary = taxonomy_vocabulary_machine_name_load('size');
  $size_tree = taxonomy_get_tree($vocabulary->vid);

  $now = time();

  $rows = array();
  $orders = array();
  // group the rows by inventory line node.
  foreach ($result as $row) {
    if (empty($orders[$row->order_nid])) {
      $orders[$row->order_nid] = array(
        'title' => $row->order_title,
        'total_items' => 0,
        'last_delivery_date' => 0,
        'next_delivery_date' => 0,
        'order_status' => $row->order_status,
      );
    }

    if (empty($orders[$row->order_nid]['lines'][$row->nid])) {
      $orders[$row->order_nid]['lines'][$row->nid] = array(
        'customer' => $row->customer,
        'customer_nid' => $row->customer_nid,
        'variant' => $row->variant,
        'variant_nid' => $row->variant_nid,
        'type' => $row->type,
      );

      foreach($size_tree as $term) {
        $orders[$row->order_nid]['lines'][$row->nid][$term->tid] = 0;
      }

      // Update last and next delivery dates.
      if ($row->delivery_date) {
        // Delivery date in the future - Update next_delivery_date.
        if ($row->delivery_date - $now >= 0) {
          $next_delivery_delta = abs($orders[$row->order_nid]['next_delivery_date'] - $now);
          // If this row's "next delivery date" is closer to now than the
          // currently order's "next delivery date", update the order.
          if (($row->delivery_date - $now) < $next_delivery_delta) {
            $orders[$row->order_nid]['next_delivery_date'] = $row->delivery_date;
          }
        }
        // Delivery date in the past - Update last_delivery_date.
        else {
          $last_delivery_delta = abs($orders[$row->order_nid]['last_delivery_date'] - $now);

          if (abs($row->delivery_date - $now) < $next_delivery_delta) {
            $orders[$row->order_nid]['last_delivery_date'] = $row->delivery_date;
          }
        }
      }
    }
    $orders[$row->order_nid]['lines'][$row->nid][$row->size_tid] += $row->quantity;
    $orders[$row->order_nid]['total_items'] += $row->quantity;
  }
  if (!$orders) {
    return $block;
  }

  drupal_add_js(drupal_get_path('module', $module) . '/plugins/content_types/' . $subtype . '/' . $subtype . '.js');

  $header = array(
    t('Order'),
    t('Total price'),
    t('Total items'),
    t('Last delivery date'),
    t('Next delivery date'),
    t('Status'),
  );

  $inventory_header = array();
  $inventory_header[] = t('Customer');
  $inventory_header[] = t('Variation');
  foreach ($size_tree as $term) {
    $inventory_header[] = $term->name;
  }
  $inventory_header[] = t('Total');
  $inventory_header[] = t('Status');

  $order_table = array();
  foreach ($orders as $order_nid => $order) {
    $order_row = array(
      'data' => array(),
      'class' => array('expandable'),
      'ref' => 'order-inventory-' . $order_nid,
    );
    $params = array(
      'attributes' => array(
        'class' => array('expander', 'collapsed'),
      )
    );
    $expand_link = l('', url(''), $params);
    $order_row['data'][] = $expand_link . l($order['title'], 'node/' . $order_nid);
    $order_row['data'][] = t('N/A');
    $order_row['data'][] = $order['total_items'];
    $order_row['data'][] = $order['last_delivery_date'] ? format_date($order['last_delivery_date']) : t('N/A');
    $order_row['data'][] = $order['next_delivery_date'] ? format_date($order['next_delivery_date']) : t('N/A');
    $order_row['data'][] = $order['order_status'];

    $order_table[] = $order_row;

    $inventory_table = array();
    foreach ($order['lines'] as $inventory_line) {
      $row = array();
      $row[] = l($inventory_line['customer'], 'node/' . $inventory_line['customer_nid']);
      $row[] = l($inventory_line['variant'], 'node/' . $inventory_line['variant_nid']);

      $total = 0;
      foreach($size_tree as $term) {
        $total += $inventory_line[$term->tid];
        $row[] = $inventory_line[$term->tid];
      }

      $row[] = array('data' => $total, 'class' => array('emphasized'));
      $row[] = $inventory_line['type'];

      $inventory_table[] = $row;
    }
    $variables = array(
      'header' => $inventory_header,
      'rows' => $inventory_table,
    );

    $order_table[] = array(
      'data' => array(
        array(
          'data' => theme('table', $variables),
          'colspan' => 6,
        ),
      ),
      'class' => array('hidden'),
      'id' => 'order-inventory-' . $order_nid,
    );
  }

  $block->content = array(
    '#theme' => 'table',
    '#header' => $header,
    '#rows' => $order_table,
  );
  return $block;
}

/**
 * Edit form.
 */
function opengizra_order_orders_content_type_edit_form($form, &$form_state) {
  return $form;
}
