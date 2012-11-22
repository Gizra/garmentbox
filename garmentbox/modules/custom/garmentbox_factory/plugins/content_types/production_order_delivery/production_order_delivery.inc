<?php

/**
 * Plugin definition.
 */
$plugin = array(
  'title' => t('Production order delivery'),
  'description' => t('Display production order delivery details.'),
  'required context' => new ctools_context_required(t('Node'), 'node'),
  'category' => t('Garmentbox'),
);

/**
 * Render callback.
 */
function garmentbox_factory_production_order_delivery_content_type_render($subtype, $conf, $args, $context) {
  if (empty($context->data)) {
    return;
  }
  $node = $context->data;

  $block = new stdClass();
  $block->module = 'garmentbox_factory';
  $block->title = t('Production Delivery');
  $form = drupal_get_form('garmentbox_factory_production_order_delivery_form', $node);
  $block->content = drupal_render($form);
  return $block;
}

/**
 * Edit form.
 */
function garmentbox_factory_production_order_delivery_content_type_edit_form($form, &$form_state) {
  return $form;
}

/**
 * Theme the production order delivery form.
 */
function theme_garmentbox_factory_production_order_delivery_form($variables) {
  $vocabulary = taxonomy_vocabulary_machine_name_load('size');
  $size_tree = taxonomy_get_tree($vocabulary->vid);

  $form = $variables['form'];
  $rows = array();
  foreach ($form['variants'] as $nid => $variant) {
    // Ignore FAPI settings.
    if (!is_numeric($nid)) {
      continue;
    }

    $row = _garmentbox_factory_production_order_delivery_form_row($nid, 'received', t('Received'), NULL, $variant['received']);
    // Override the first row's settings.
    $row['id'] = "variant-$nid";
    $row['class'] = array('received');
    unset($row['ref']);
    // Override the first cells.
    $row['data'][0] = array(
      'data' => render($variant["received_variant_$nid"]),
      'class' => array('received'),
    );
    $row['data'][1] = render($variant['title']);
    $rows[] = $row;

    $row = _garmentbox_factory_production_order_delivery_form_row($nid, 'original', t('Original'), 'subrow', $variant['original']);
    $row['data'][1] = render($variant['lines_expander']);
    $rows[] = $row;
    foreach ($variant['lines'] as $inventory_line_nid => $line) {
      // Ignore FAPI settings.
      if (!is_numeric($inventory_line_nid)) {
        continue;
      }
      $wrapper = entity_metadata_wrapper('node', $inventory_line_nid);
      $label = render($line["line_{$inventory_line_nid}_title_variant_{$nid}"]);

      $rows[] = _garmentbox_factory_production_order_delivery_form_row($nid, 'line', $label, NULL, $line);
      // Add the "Create missing IL" checkbox.
      $row = _garmentbox_factory_production_order_delivery_form_row($nid, 'missing', t('Missing'), NULL);
      $row['data-il-ref'] = $inventory_line_nid;
      $row['data'][1] = render($variant['missing'][$inventory_line_nid]["create_missing_variant_{$nid}_il_{$inventory_line_nid}"]);
      $rows[] = $row;
    }

    $rows[] = _garmentbox_factory_production_order_delivery_form_row($nid, 'defective', t('Defective'), 'subrow', $variant['defective']);
    $rows[] = _garmentbox_factory_production_order_delivery_form_row($nid, 'extras', t('Extras'), 'subrow');

  }

  $header = array(t('Received'), t('Item Variation'), t('Type'));
  $vocabulary = taxonomy_vocabulary_machine_name_load('size');
  foreach (taxonomy_get_tree($vocabulary->vid) as $term) {
    $header[] = $term->name;
  }
  $header[] = t('Production price');

  $variables = array(
    'header' => $header,
    'rows' => $rows,
    'attributes' => array('id' => 'delivery-details'),
  );
  hide($form['actions']);
  hide($form['variants']);
  hide($form['totals']);

  $output = drupal_render_children($form);
  $output .= theme('table', $variables);
  $output .= render($form['totals']);
  $output .= render($form['actions']);

  return $output;
}

/**
 * Build a row for the delivery form.
 *
 * @param $nid
 *   Item variant node ID.
 * @param $type
 *   The row type.
 * @param $label
 *   The row label.
 * @param $exrta_class
 *   Extra class for the row.
 * @param $quantity_info
 *   The row's quantity information.
 *
 * @return
 *   Table row.
 */
function _garmentbox_factory_production_order_delivery_form_row($nid, $type, $label, $extra_class, $quantity_info = NULL) {
  $row = array(
    'data' => array('', ''),
    'class' => array('hidden', $type, $extra_class),
    'ref' => "variant-$nid",
    'data-variant-nid' => $nid,
  );

  $row['data'][] = $label;

  $vocabulary = taxonomy_vocabulary_machine_name_load('size');
  $size_tree = taxonomy_get_tree($vocabulary->vid);

  foreach ($size_tree as $term) {
    $row['data'][] = array(
      'data' => empty($quantity_info[$term->tid]) ? '' : render($quantity_info[$term->tid]),
      'data-tid' => $term->tid,
      'class' => array('size-quantity', 'hidden-label'),
    );
  }
  $row['data'][] = array(
    'data' => '-',
    'class' => array('price'),
  );

  return $row;
}

/**
 * Create the production order delivery update form.
 *
 * @param $node
 *   The production order node.
 */
function garmentbox_factory_production_order_delivery_form($form, &$form_state, $node) {
  $wrapper = entity_metadata_wrapper('node', $node);
  $form['factory_details'] = array(
    '#markup' => t('Factory: @factory', array('@factory' => $wrapper->field_factory->label())),
  );

  // Create the delivery details table.
  $data = garmentbox_factory_production_order_delivery_get_data($node);
  $vocabulary = taxonomy_vocabulary_machine_name_load('size');
  $size_tree = taxonomy_get_tree($vocabulary->vid);

  $types = array(
    'received',
    'original',
    'defective',
  );
  foreach ($data as $nid => $item_variant) {
    $available_sizes = garmentbox_item_get_available_sizes($nid);

    $form['variants'][$nid]["received_variant_{$nid}"] = array(
      '#type' => 'checkbox',
    );

    $form['variants'][$nid]['title'] = array(
      '#markup' => check_plain($item_variant['title']),
    );

    // Add the lines expander link.
    $form['variants'][$nid]['lines_expander'] = array(
      '#markup' => l('', '', array('attributes' => array('class' => array('expander', 'collapsed')))),
    );

    foreach ($types as $type) {
      foreach ($size_tree as $term) {
        // Ignore the term if it's not available to the item variant.
        if (empty($available_sizes[$term->tid])) {
          continue;
        }

        $markup = '';
        switch ($type) {
          case 'original':
            $form['variants'][$nid][$type][$term->tid] = array(
              '#prefix' => '<span>',
              '#suffix' => '</span>',
              '#markup' => $item_variant['sizes'][$term->tid],
            );
            break;

          case 'received':
          case 'defective':
            $form['variants'][$nid][$type][$term->tid]["{$type}_quantity_variant_{$nid}_tid_{$term->tid}"] = array(
              '#type' => 'textfield',
              '#title' => check_plain($term->name),
              '#element_validate' => array('garmentbox_factory_element_validate_not_negative_integer'),
              '#default_value' => $type == 'defective' ? '' : $item_variant['sizes'][$term->tid],
              '#size' => 4,
            );
            break;
        }
      }
    }

    // Add the inventory line rows and "missing" rows.
    foreach ($data[$nid]['lines'] as $inventory_line_nid => $line) {
      // Add a "Create new IL for missing quantities" checkbox.
      $form['variants'][$nid]['missing'][$inventory_line_nid]["create_missing_variant_{$nid}_il_{$inventory_line_nid}"] = array(
        '#type' => 'checkbox',
        '#attributes' => array(
          'title' => t('Create this inventory line'),
        ),
        '#default_value' => TRUE,
      );

      // Set the inventory line label.
      $customer = empty($line['customer']) ? t('N/A') : $line['customer'];
      $form['variants'][$nid]['lines'][$inventory_line_nid]["line_{$inventory_line_nid}_title_variant_{$nid}"] = array(
        '#markup' => t('Customer: !customer', array('!customer' => $customer)),
      );

      foreach ($size_tree as $term) {
        // Ignore the term if it's not available to the item variant.
        if (empty($line['quantity'][$term->tid])) {
          continue;
        }

        $form['variants'][$nid]['lines'][$inventory_line_nid][$term->tid]["line_{$inventory_line_nid}_quantity_variant_{$nid}_tid_{$term->tid}"] = array(
          '#type' => 'textfield',
          '#title' => check_plain($term->name),
          '#element_validate' => array('garmentbox_factory_element_validate_not_negative_integer'),
          '#default_value' => $line['quantity'][$term->tid],
          '#attributes' => array('data-il-nid' => $inventory_line_nid),
          '#size' => 4,
        );
      }
    }
  }

  $totals = array(
    'total_items_new' => t('Total items new'),
    'production_cost_new' => t('Production cost new'),
  );
  foreach ($totals as $name => $title) {
    $form['totals'][$name] = array(
      '#title' => $title,
      '#type' => 'textfield',
      '#disabled' => TRUE,
      '#size' => 10,
    );
  }

  $form['actions'] = array(
    '#type' => 'submit',
    '#value' => t('Save'),
  );

  $form['#attached']['js'] = array(
    drupal_get_path('module', 'garmentbox_factory') . '/plugins/content_types/production_order_delivery/production_order_delivery.js',
    array('data' => array(
      'garmentbox_factory' => array('delivery_data' => $data)),
      'type' => 'setting',
    ),
    drupal_get_path('module', 'format_number') . '/format_number.js',
    array(
      'data' => array('format_number' => format_number_get_options()),
      'type' => 'setting',
    ),
  );

  $form_state['original_data'] = $data;

  return $form;
}

/**
 * Validate handler for the delivery form.
 *
 * When the received amount is less than expected, make sure the inventory lines
 * quantities reflect the change.
 */
function garmentbox_factory_production_order_delivery_form_validate($form, &$form_state) {
  $original_data = $form_state['original_data'];

  // Validate the data on variants that are marked as receiced.
  foreach ($original_data as $variant_nid => $variant) {
    // Ignore variants that aren't marked as received.
    if (!$form_state['values']["received_variant_$variant_nid"]) {
      continue;
    }

    foreach ($variant['sizes'] as $tid => $quantity) {
      if (!$quantity) {
        continue;
      }

      // Ignore quantities which are as expected.
      $received = $form_state['values']["received_quantity_variant_{$variant_nid}_tid_{$tid}"];
      if ($received == $quantity) {
        continue;
      }
      // When the received quantity differ, the sum of IL quantities must match
      // the received quantity.
      $ils_sum = 0;
      foreach ($variant['lines'] as $il_nid => $il) {
        $key = "line_{$il_nid}_quantity_variant_{$variant_nid}_tid_{$tid}";
        if (!array_key_exists($key, $form_state['values'])) {
          continue;
        }

        $ils_sum += ($form_state['values'][$key]);
      }
      if ($ils_sum != $received) {
        form_set_error($key, t('The sum of the inventory lines quantities should be the same as the received quantity.'));
      }
    }
  }
}

/**
 * Submit handler for the delivery form.
 */
function garmentbox_factory_production_order_delivery_form_submit($form, &$form_state) {
  $vocabulary = taxonomy_vocabulary_machine_name_load('size');
  $size_tree = taxonomy_get_tree($vocabulary->vid);

  $original_data = $form_state['original_data'];

  $current_prooduction_tid = key(taxonomy_get_term_by_name(INVENTORY_TYPE_CURRENT_PRODUCTION, 'inventory_type'));
  $regular_stock_tid = key(taxonomy_get_term_by_name(INVENTORY_TYPE_REGULAR_STOCK, 'inventory_type'));

  // This data is used to compare the deltas between the amounts received and
  // the expected amounts.
  $data = garmentbox_factory_production_order_delivery_get_data($production_order_node);

  // Set inventory lines as received if their variant was checked as received.
  foreach (array_keys($form['variants']) as $item_variant_nid) {
    // Ignore irrelevant values added by FAPI.
    if (!is_numeric($item_variant_nid)) {
      continue;
    }

    // Ignore variants that are not marked as "Received".
    if (!$form_state['values']["received_variant_$item_variant_nid"]) {
      continue;
    }

    $inventory_line_nids = garmentbox_factory_get_production_order_inventory_lines($production_order_node->nid, $item_variant_nid);
    foreach (node_load_multiple($inventory_line_nids) as $inventory_line_node) {
      $wrapper = entity_metadata_wrapper('node', $inventory_line_node);

      // Set the "Current production" inventory lines type to "Regular stock".
      if ($wrapper->field_inventory_type->getIdentifier() == $current_prooduction_tid) {
        $wrapper->field_inventory_type->set($regular_stock_tid);
        $wrapper->save();
      }
      else {
        // If the current variant is already received continue to the next one.
        continue 2;
      }
    }

    // Check if new inventory lines should be created for the received items.
    $extra_quantity_info = array();
    $missing_quantity_info = array();
    foreach ($size_tree as $term) {
      $received = $form_state['values']["received_quantity_variant_{$item_variant_nid}_tid_{$term->tid}"];
      $original = $data[$item_variant_nid]['sizes'][$term->tid];
      if ($received > $original) {
        $extra_quantity_info[$term->tid] = $received - $original;
      }
      if ($original > $received) {
        $missing_quantity_info[$term->tid] = $original - $received;
      }
    }
    // Create "Regular stock" inventory for extra items.
    if ($extra_quantity_info) {
      garmentbox_factory_create_inventory_line(NULL, $production_order_node->nid, $item_variant_nid, $extra_quantity_info, INVENTORY_TYPE_REGULAR_STOCK);
    }
    // Create "Future production" inventory for missing items. (Attached to the
    // current production order).
    if ($missing_quantity_info) {
      garmentbox_factory_create_inventory_line($production_order_node->nid, $production_order_node->nid, $item_variant_nid, $extra_quantity_info, INVENTORY_TYPE_FUTURE_PRODUCTION);
    }

    // Create an inventory for the defective items.
    $create_inventory_line = FALSE;
    $quantity_info = array();
    foreach ($size_tree as $term) {
      $quantity = $form_state['values']["defective_quantity_variant_{$item_variant_nid}_tid_{$term->tid}"];
      if ($quantity) {
        $create_inventory_line = TRUE;
      }
      $quantity_info[$term->tid] = $quantity;
    }
    if ($create_inventory_line) {
      garmentbox_factory_create_inventory_line(NULL, $production_order_node->nid, $item_variant_nid, $quantity_info, INVENTORY_TYPE_DEFECTIVE);
    }
  }
}

/**
 * Prepare the raw data for the delivery form.
 *
 * @param $node
 *   The production order node.
 *
 * @return
 *   Array of data.
 */
function garmentbox_factory_production_order_delivery_get_data($node) {
  $data = array();

  $vocabulary = taxonomy_vocabulary_machine_name_load('size');
  $size_tree = taxonomy_get_tree($vocabulary->vid);

  // TODO: Will this work when viewing the page translated?
  $current_prooduction_tid = key(taxonomy_get_term_by_name(INVENTORY_TYPE_CURRENT_PRODUCTION, 'inventory_type'));
  $inventory_line_nids = garmentbox_factory_get_production_order_inventory_lines($node->nid);
  foreach($inventory_line_nids as $nid) {
    $wrapper = entity_metadata_wrapper('node', $nid);
    $line_nid = $wrapper->getIdentifier();
    $variant_nid = $wrapper->field_item_variant->getIdentifier();

    $received = $wrapper->field_inventory_type->getIdentifier() != $current_prooduction_tid;

    if (empty($data[$variant_nid])) {
      $data[$variant_nid] = array(
        'sizes' => array(),
        'item_price' => garmentbox_item_get_variant_price($variant_nid),
        'title' => $wrapper->field_item_variant->label(),
        'checked' => $received,
        'lines' => array(),
        'items_count' => array(
          'original' => 0,
          'received' => 0,
          'defective' => 0,
          'extras' => 0,
          'missing' => 0,
        ),
      );
      // Create a placeholder for all sizes on the variant.
      foreach ($size_tree as $term) {
        $data[$variant_nid]['sizes'][$term->tid] = '';
      }
    }

    foreach ($wrapper->field_quantity_info as $quantity_wrapper) {
      $tid = $quantity_wrapper->field_size->getIdentifier();

      if (empty($data[$variant_nid]['sizes'][$tid])) {
        // Initialize the quantity counter.
        $data[$variant_nid]['sizes'][$tid] = 0;
      }

      if (empty($data[$variant_nid]['lines'][$line_nid]['quantity'][$tid])) {
        // Initialize the line specific quantity counter.
        $data[$variant_nid]['lines'][$line_nid]['quantity'][$tid] = 0;
      }

      $quantity = $quantity_wrapper->field_quantity_integer->value();
      $data[$variant_nid]['lines'][$line_nid]['quantity'][$tid] += $quantity;
      $data[$variant_nid]['sizes'][$tid] += $quantity;
      $data[$variant_nid]['items_count']['original'] += $quantity;
    }
  }

  $order_nids = garmentbox_factory_get_inventory_orders($inventory_line_nids);
  if (empty($order_nids)) {
    return $data;
  }

  foreach (node_load_multiple($order_nids) as $order_node) {
    $wrapper = entity_metadata_wrapper('node', $order_node);
    $order_link = l($wrapper->field_customer->label(), 'node/' . $order_node->nid);

    foreach ($wrapper->field_inventory_line_inline as $inventory_line_wrapper) {
      $variant_nid = $inventory_line_wrapper->field_item_variant->getIdentifier();
      $inventory_line_nid = $inventory_line_wrapper->getIdentifier();

      if (!empty($data[$variant_nid]['lines'][$inventory_line_nid])) {
        $data[$variant_nid]['lines'][$inventory_line_nid]['customer'] = $order_link;
      }
    }
  }

  return $data;
}
