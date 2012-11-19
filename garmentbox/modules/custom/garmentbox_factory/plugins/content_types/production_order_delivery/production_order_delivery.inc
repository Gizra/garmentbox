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
    if (!is_numeric($nid)) {
      continue;
    }
    $row = array(
      'data' => array(),
      'id' => "variant-$nid",
      'class' => array('original'),
    );
    $row['data'][] = array(
      'data' => render($variant["received_variant_$nid"]),
      'class' => array('received'),
    );
    $row['data'][] = render($variant['title']);
    $row['data'][] = t('Original');
    foreach ($size_tree as $term) {
      $row['data'][] = array(
        'data' => render($variant['original'][$term->tid]),
        'class' => array('size-quantity'),
        'data-tid' => $term->tid,
      );
    }
    $row['data'][] = array(
      'data' => '-',
      'class' => array('price'),
    );
    $rows[] = $row;

    $types = array(
      'received' => t('Received'),
      'defective' => t('Defective'),
      'extras' => t('Extras'),
      'missing' => t('Missing'),
    );
    foreach ($types as $type => $label) {
      $row = array(
        'data' => array('', ''),
        'class' => array('hidden', $type),
        'ref' => "variant-$nid",
      );

      $row['data'][] = $label;

      $vocabulary = taxonomy_vocabulary_machine_name_load('size');
      $size_tree = taxonomy_get_tree($vocabulary->vid);

      foreach ($size_tree as $term) {
        $row['data'][] = array(
          'data' => render($variant[$type][$term->tid]),
          'data-tid' => $term->tid,
          'class' => array('size-quantity'),
        );
      }
      $row['data'][] = array(
        'data' => '-',
        'class' => array('price'),
      );

      $rows[] = $row;
    }
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

  $types = array(
    'original',
    'received',
    'defective',
    'extras',
    'missing',
  );
  foreach ($data as $nid => $item_variant) {
    $form['variants'][$nid]["received_variant_{$nid}"] = array(
      '#type' => 'checkbox',
    );

    $form['variants'][$nid]['title'] = array(
      '#markup' => check_plain($item_variant['title']),
    );
    foreach ($types as $type) {
      foreach (taxonomy_get_tree($vocabulary->vid) as $term) {
        $markup = '';
        switch ($type) {
          case 'original':
            $form['variants'][$nid][$type][$term->tid] = array(
              '#markup' => $item_variant['sizes'][$term->tid],
            );
            break;

          case 'received':
          case 'defective':
            $form['variants'][$nid][$type][$term->tid]["{$type}_quantity_variant_{$nid}_tid_{$term->tid}"] = array(
              '#type' => 'textfield',
              '#title' => check_plain($term->name),
              '#element_validate' => array('element_validate_integer_positive'),
              '#default_value' => $type == 'defective' ? '' : $item_variant['sizes'][$term->tid],
              '#size' => 4,
            );
            break;
        }
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

  $form_state['node'] = $node;

  return $form;
}

/**
 * Submit handler for the delivery form.
 */
function garmentbox_factory_production_order_delivery_form_submit($form, &$form_state) {
  $vocabulary = taxonomy_vocabulary_machine_name_load('size');
  $size_tree = taxonomy_get_tree($vocabulary->vid);

  $production_order_node = $form_state['node'];

  $current_prooduction_tid = key(taxonomy_get_term_by_name(INVENTORY_TYPE_CURRENT_PRODUCTION, 'inventory_type'));
  $regular_stock_tid = key(taxonomy_get_term_by_name(INVENTORY_TYPE_REGULAR_STOCK, 'inventory_type'));

  $data = garmentbox_factory_production_order_delivery_get_data($production_order_node);

  // Set inventory lines as received if their variant was checked as received.
  foreach (array_keys($form['variants']) as $item_variant_nid) {
    if (!is_numeric($item_variant_nid)) {
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
      garmentbox_factory_create_inventory_line(NULL, $item_variant_nid, $extra_quantity_info, INVENTORY_TYPE_REGULAR_STOCK);
    }
    // Create "Future production" inventory for missing items. (Attached to the
    // current production order).
    if ($missing_quantity_info) {
      garmentbox_factory_create_inventory_line($production_order_node->nid, $item_variant_nid, $extra_quantity_info, INVENTORY_TYPE_FUTURE_PRODUCTION);
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
      garmentbox_factory_create_inventory_line(NULL, $item_variant_nid, $quantity_info, INVENTORY_TYPE_DEFECTIVE);
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

  foreach(garmentbox_factory_get_production_order_inventory_lines($node->nid) as $nid) {
    $wrapper = entity_metadata_wrapper('node', $nid);
    $variant_nid = $wrapper->field_item_variant->getIdentifier();

    $received = $wrapper->field_inventory_type->getIdentifier() != $current_prooduction_tid;

    if (empty($data[$variant_nid])) {
      $data[$variant_nid] = array(
        'sizes' => array(),
        'item_price' => garmentbox_item_get_variant_price($variant_nid),
        'title' => $wrapper->field_item_variant->label(),
        'checked' => $received,
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
      $quantity = $quantity_wrapper->field_quantity_integer->value();
      $data[$variant_nid]['sizes'][$tid] += $quantity;
      $data[$variant_nid]['items_count']['original'] += $quantity;
    }
  }

  return $data;
}
