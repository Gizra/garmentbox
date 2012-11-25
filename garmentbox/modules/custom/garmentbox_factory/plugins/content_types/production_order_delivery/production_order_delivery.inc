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
      if (!is_numeric($inventory_line_nid)) {
        // Ignore FAPI settings.
        continue;
      }

      $wrapper = entity_metadata_wrapper('node', $inventory_line_nid);
      $label = render($line["line_{$inventory_line_nid}_title_variant_{$nid}"]);

      // Add an editable hidden missing row.
      $rows[] = _garmentbox_factory_production_order_delivery_form_row($nid, 'line', $label, NULL, $line);
      // Add the "Create missing IL" checkbox.
      $row = _garmentbox_factory_production_order_delivery_form_row($nid, 'missing', t('Missing'), NULL);
      $row['data-il-ref'] = $inventory_line_nid;
      $row['data'][1] = render($variant['missing']['lines'][$inventory_line_nid]["create_missing_variant_{$nid}_il_{$inventory_line_nid}"]);
      $rows[] = $row;
    }

    // Display former missing rows.
    foreach ($variant['missing'] as $inventory_line_nid => $line) {
      if (!is_numeric($inventory_line_nid)) {
        // Ignore FAPI settings.
        continue;
      }

      $row = _garmentbox_factory_production_order_delivery_form_row($nid, 'missing', t('Missing'), NULL, $line);
      $row['class'] = array('missing-created');
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

  foreach ($data as $nid => $variant_data) {
    $available_sizes = garmentbox_item_get_available_sizes($nid);

    $form['variants'][$nid]["received_variant_{$nid}"] = array(
      '#type' => 'checkbox',
      '#default_value' => $variant_data['in_warehouse'],
      // Once a variant is checked, it stays checked.
      //'#disabled' => $variant_data['received'],
    );

    $form['variants'][$nid]['title'] = array(
      '#markup' => check_plain($variant_data['title']),
    );

    // Add the lines expander link.
    $form['variants'][$nid]['lines_expander'] = array(
      '#markup' => l('', '', array('attributes' => array('class' => array('expander', 'collapsed')))),
    );

    foreach (array('received', 'original', 'defective') as $type) {
      foreach ($size_tree as $term) {
        // Ignore the term if it's not available to the item variant.
        if (empty($available_sizes[$term->tid])) {
          continue;
        }

        $markup = '';
        switch ($type) {
          case 'original':
            $form['variants'][$nid][$type][$term->tid] = array(
              '#markup' => $variant_data[$type]['sizes'][$term->tid],
            );
            break;

          case 'received':
          case 'defective':
            $form['variants'][$nid][$type][$term->tid]["{$type}_quantity_variant_{$nid}_tid_{$term->tid}"] = array(
              '#type' => 'textfield',
              '#title' => check_plain($term->name),
              '#element_validate' => array('garmentbox_factory_element_validate_not_negative_integer'),
              '#default_value' => $type == 'defective' ? '' : $variant_data[$type]['sizes'][$term->tid],
              '#size' => 4,
            );
            break;
        }
      }
    }

    // Add the inventory line rows and empty "missing" rows.
    foreach ($data[$nid]['original']['lines'] as $inventory_line_nid => $line) {
      // Add a "Create new IL for missing quantities" checkbox.
      $form['variants'][$nid]['missing']['lines'][$inventory_line_nid]["create_missing_variant_{$nid}_il_{$inventory_line_nid}"] = array(
        '#type' => 'checkbox',
        '#attributes' => array(
          'title' => t('Create this inventory line'),
        ),
        '#default_value' => TRUE,
      );

      // Set the inventory line label.
      $customer = empty($line['order']) ? t('N/A') : $line['order']['link'];
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

    // Add "missing" lines that were already created.
    foreach ($data[$nid]['missing']['lines'] as $inventory_line_nid => $line) {
      foreach ($size_tree as $term) {
        // Ignore the term if it's not available to the item variant.
        if (empty($line['quantity'][$term->tid])) {
          continue;
        }

        $form['variants'][$nid]['missing'][$inventory_line_nid][$term->tid] = array(
          '#markup' => $line['quantity'][$term->tid],
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

  // Instead of re-calculating the data on validate and submit, re-use the data
  // used here.
  $form_state['original_data'] = $data;
  // Use the production order node for setting the "origin" field on new
  // inventory lines.
  $form_state['node'] = $node;

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
  foreach ($original_data as $variant_nid => $variant_data) {
    // Ignore variants that aren't marked as received.
    if (!$form_state['values']["received_variant_$variant_nid"]) {
      continue;
    }

    foreach ($variant_data['original']['sizes'] as $tid => $quantity) {
      if (!$quantity) {
        // This size is not available to the current variant.
        continue;
      }

      // Ignore quantities which are as expected, or that are larger than
      // expected.
      $received = $form_state['values']["received_quantity_variant_{$variant_nid}_tid_{$tid}"];
      if ($received >= $quantity) {
        continue;
      }
      // When the received quantity differ, the sum of IL quantities must match
      // the received quantity.
      $ils_sum = 0;
      foreach ($variant_data['original']['lines'] as $il_nid => $il) {
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
  // This data is used to compare the deltas between the amounts received and
  // the expected amounts.
  $original_data = $form_state['original_data'];
  $production_order_nid = $form_state['node']->nid;

  $current_prooduction_tid = key(taxonomy_get_term_by_name(INVENTORY_TYPE_CURRENT_PRODUCTION, 'inventory_type'));
  $regular_stock_tid = key(taxonomy_get_term_by_name(INVENTORY_TYPE_REGULAR_STOCK, 'inventory_type'));

  // Set inventory lines as received if their variant was checked as received.
  foreach ($original_data as $variant_nid => $variant_data) {
    // Ignore variants that are not marked as "Received".
    if (!$form_state['values']["received_variant_$variant_nid"]) {
      continue;
    }

    // Specifying on which term IDs the iLines quantites should be reduced.
    $update_quantity_for_size = array();

    foreach ($variant_data['original']['sizes'] as $tid => $quantity) {
      if (!$quantity) {
        // This size is not available to the current variant.
        continue;
      }

      $received = $form_state['values']["received_quantity_variant_{$variant_nid}_tid_{$tid}"];
      if ($received < $quantity) {
        $missing_iline = TRUE;
        $update_quantity_for_size[$tid] = TRUE;
      }
    }

    $il_nids = array_keys($variant_data['original']['lines']);
    foreach (node_load_multiple($il_nids) as $node) {
      // The revision must be enabled before the quantity items are re-saved.
      $node->revision = TRUE;
      $original_revision = $node->vid;
      $missing_size_data = array();
      // Flag specifying whether the currrent IL has missing quantity.
      $il_missing_data = FALSE;

      $wrapper = entity_metadata_wrapper('node', $node);

      // Reduce quantities of iLines where the received quantity was lower than
      // expected.
      foreach ($wrapper->field_quantity_info as $item_wrapper) {
        $tid = $item_wrapper->field_size->getIdentifier();
        if (empty($update_quantity_for_size[$tid])) {
          // This size doesn't require reducing quantities.
          continue;
        }

        // Amend the IL quantity for current size.
        $quantity = $form_state['values']["line_{$node->nid}_quantity_variant_{$variant_nid}_tid_{$tid}"];
        $item_wrapper->field_quantity_integer->set($quantity);
        $item_wrapper->save();

        // Store the delta for creating the missing iLine.
        $original_quantity = $variant_data['original']['lines'][$node->nid]['quantity'][$tid];
        $missing_quantity = $original_quantity - $quantity;
        $missing_size_data[$tid] = $missing_quantity;
        if ($missing_quantity) {
          $il_missing_data = TRUE;
        }
      }

      // Set the "Current production" inventory lines type to "Regular stock".
      if ($wrapper->field_inventory_type->getIdentifier() == $current_prooduction_tid) {
        $wrapper->field_inventory_type->set($regular_stock_tid);
        // Save the iLine revision when the when it was received.
        $wrapper->field_original_revision->set($original_revision);
        $wrapper->save();
      }

      // Check if the missing IL checkbox is checked.
      if ($il_missing_data && $form_state['values']["create_missing_variant_{$variant_nid}_il_{$node->nid}"]) {
        $i_line = garmentbox_factory_create_inventory_line(NULL, $production_order_nid, $variant_nid, $missing_size_data, INVENTORY_TYPE_FUTURE_PRODUCTION);

        // Attach the inventory line to the original order.
        if (!empty($variant_data['lines'][$node->nid]['order']['nid'])) {
          $order_wrapper = entity_metadata_wrapper('node', $variant_data['lines'][$node->nid]['order']['nid']);
          $i_lines = $order_wrapper->field_inventory_line_inline->value();
          $i_lines[] = $i_line;
          $order_wrapper->field_inventory_line_inline->set($i_lines);
          $order_wrapper->save();
        }
      }
    }

    // Check if new inventory lines should be created for the received items.
    $quantity_info = array();
    foreach ($variant_data['original']['sizes'] as $tid => $original) {
      $key = "received_quantity_variant_{$variant_nid}_tid_{$tid}";
      if (!array_key_exists($key, $form_state['values'])) {
        continue;
      }

      $received = $form_state['values'][$key];
      if ($received > $original) {
        $quantity_info[$tid] = $received - $original;
      }
    }

    // Create "Regular stock" inventory for extra items.
    if ($quantity_info) {
      garmentbox_factory_create_inventory_line(NULL, $production_order_nid, $variant_nid, $quantity_info, INVENTORY_TYPE_REGULAR_STOCK);
    }

    // Create an inventory for the defective items.
    $create_inventory_line = FALSE;
    $quantity_info = array();
    foreach (array_keys($variant_data['original']['sizes']) as $tid) {
      $key = "defective_quantity_variant_{$variant_nid}_tid_{$tid}";
      if (!array_key_exists($key, $form_state['values'])) {
        continue;
      }

      $quantity = $form_state['values'][$key];
      if ($quantity) {
        $create_inventory_line = TRUE;
      }
      $quantity_info[$tid] = $quantity;
    }
    if ($create_inventory_line) {
      garmentbox_factory_create_inventory_line(NULL, $production_ordernid, $variant_nid, $quantity_info, INVENTORY_TYPE_DEFECTIVE);
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

  $il_nids = garmentbox_factory_get_production_order_inventory_lines($node->nid);
  foreach(node_load_multiple($il_nids) as $il_node) {
    $wrapper = entity_metadata_wrapper('node', $il_node);

    $variant_nid = $wrapper->field_item_variant->getIdentifier();

    if (empty($data[$variant_nid])) {
      $data[$variant_nid] = array(
        'in_warehouse' => $wrapper->field_inventory_type->field_in_warehouse->value(),
        'item_price' => garmentbox_item_get_variant_price($variant_nid),
        'title' => $wrapper->field_item_variant->label(),
      );
      foreach (array('received', 'original', 'defective', 'missing', 'extras') as $type) {
        $data[$variant_nid][$type] = array(
          'sizes' => array(),
          'lines' => array(),
          'items_count' => 0,
        );

        // Create a placeholder for all sizes on the variant.
        foreach ($size_tree as $term) {
          $data[$variant_nid][$type]['sizes'][$term->tid] = '';
        }
      }
    }

    foreach ($wrapper->field_quantity_info as $quantity_wrapper) {
      _garmentbox_factory_production_order_delivery_get_quantity_data($data, 'received', $quantity_wrapper, $variant_nid, $il_node->nid);
    }

    // Load the "Original revision" of the ILs.
    $original_vid = $wrapper->field_original_revision->value();
    if ($original_vid) {
      $il_node = node_load(NULL, $original_vid);
      $wrapper = entity_metadata_wrapper('node', $il_node);
    }
    // The wrapper ignores the field collection item revision. In the mean time,
    // load the item manually.
    foreach ($il_node->field_quantity_info[LANGUAGE_NONE] as $quantity_item) {
      $quantity_item = field_collection_item_revision_load($quantity_item['revision_id']);
      $quantity_wrapper = entity_metadata_wrapper('field_collection_item', $quantity_item);
      _garmentbox_factory_production_order_delivery_get_quantity_data($data, 'original', $quantity_wrapper, $variant_nid, $il_node->nid);
    }
  }

  // Retrieve "missing" lines.
  $missing_il_nids = garmentbox_factory_get_production_order_missing_inventory_lines($node->nid);
  foreach (node_load_multiple($missing_il_nids) as $il_node) {
    $wrapper = entity_metadata_wrapper('node', $il_node);
    foreach ($wrapper->field_quantity_info as $quantity_wrapper) {
      _garmentbox_factory_production_order_delivery_get_quantity_data($data, 'missing', $quantity_wrapper, $variant_nid, $il_node->nid);
    }
  }

  $order_nids = garmentbox_factory_get_inventory_orders($il_nids);
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
        $data[$variant_nid]['lines'][$inventory_line_nid]['order'] = array(
          'link' => $order_link,
          'nid' => $order_node->nid,
        );
      }
    }
  }

  return $data;
}

/**
 * Sum the quantities of a specific type.
 *
 * @param $data
 *   The delivery data.
 * @param $type
 *   The data type. I.e. 'original', 'received'.
 * @param $quantity_wrapper
 *   The quantity field collection item wrapper.
 * @param $variant_nid
 *   Item variant node ID.
 * @param $il_nid
 *   Inventory line node ID.
 */
function _garmentbox_factory_production_order_delivery_get_quantity_data(&$data, $type, $quantity_wrapper, $variant_nid, $il_nid) {
  $tid = $quantity_wrapper->field_size->getIdentifier();

  if (empty($data[$variant_nid][$type]['sizes'][$tid])) {
    // Initialize the quantity counter.
    $data[$variant_nid][$type]['sizes'][$tid] = 0;
  }

  if (empty($data[$variant_nid][$type]['lines'][$il_nid]['quantity'][$tid])) {
    // Initialize the line specific quantity counter.
    $data[$variant_nid][$type]['lines'][$il_nid]['quantity'][$tid] = 0;
  }

  $quantity = $quantity_wrapper->field_quantity_integer->value();
  $data[$variant_nid][$type]['lines'][$il_nid]['quantity'][$tid] += $quantity;
  $data[$variant_nid][$type]['sizes'][$tid] += $quantity;
  $data[$variant_nid][$type]['items_count'] += $quantity;
}
