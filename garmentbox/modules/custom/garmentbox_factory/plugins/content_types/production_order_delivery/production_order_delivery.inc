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
  $block->content = drupal_get_form('garmentbox_factory_production_order_delivery', $node);
  return $block;
}

/**
 * Edit form.
 */
function garmentbox_factory_production_order_delivery_content_type_edit_form($form, &$form_state) {
  return $form;
}

/**
 * Create the production order delivery update form.
 *
 * @param $node
 *   The production order node.
 */
function garmentbox_factory_production_order_delivery($form, &$form_state, $node) {
  $wrapper = entity_metadata_wrapper('node', $node);
  $form['factory_details'] = array(
    '#markup' => t('Factory: @factory', array('@factory' => $wrapper->field_factory->label())),
  );

  // Create the delivery details table.
  $data = garmentbox_factory_production_order_delivery_get_data($node);
  $vocabulary = taxonomy_vocabulary_machine_name_load('size');
  $header = array(t('Received'), t('Item Variation'), t('Type'));
  foreach (taxonomy_get_tree($vocabulary->vid) as $term) {
    $header[] = $term->name;
  }
  $header[] = t('Production price');
  $form['delivery_details'] = array(
    '#theme' => 'table',
    '#rows' => garmentbox_factory_production_order_delivery_rows($data),
    '#header' => $header,
    '#attributes' => array('id' => 'delivery-details'),
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

  return $form;
}

/**
 * Build the rows for the order delivery table.
 *
 * @param $data
 *   The delivery raw data.
 *
 * @return
 *   Themed table.
 */
function garmentbox_factory_production_order_delivery_rows($data) {
  $rows = array();
  foreach ($data as $variant_nid => $variant_data) {
    // Create the 'Original' row.
    $row = array('data' => array());
    $variables = array(
      'element' => array(
        '#attributes' => array(
          'name' => "inventory_line_received[$variant_nid]",
          'value' => $variant_nid,
        ),
      ),
    );
    // Determine whether the checkbox is checked.
    // if ($inventory_line['checked']) {
    $variables['element']['#attributes']['checked'] = 'checked';
    // }

    $row = garmentbox_factory_production_order_delivery_row($variant_nid, NULL, t('Original'), $variant_data);
    // Rewrite row settings.
    $row['class'] = array('expandable');
    $row['id'] = $row['ref'];
    unset($row['ref']);
    // Rewrite the first and second cells.
    $row['data'][0] = array(
      'data' => theme('checkbox', $variables),
      'class' => array('received'),
    );
    $row['data'][1] = $variant_data['title'];
    $row['data'][6] = commerce_currency_format($variant_data['item_price'] * $variant_data['items_count'], commerce_default_currency());
    $rows[] = $row;

    $rows[] = garmentbox_factory_production_order_delivery_row($variant_nid, 'received', t('Received'), $variant_data, 'received_inventory');
    $rows[] = garmentbox_factory_production_order_delivery_row($variant_nid, 'defective', t('Defective'), NULL, 'defective_inventory');
    $rows[] = garmentbox_factory_production_order_delivery_row($variant_nid, 'extras', t('Extras'));
    $rows[] = garmentbox_factory_production_order_delivery_row($variant_nid, 'missing', t('Missing'));
  }
  return $rows;
}

/**
 * Build a delivery table row.
 *
 * @param $nid
 *   The production order node ID.
 * @param $row_class
 *   Class to add to the row.
 * @param $row_title
 *   The value of the "Type" column.
 * @param $variant_data
 *   The raw item variant data.
 * @param $input_name
 *   When not null, determines the name of the quantity inputs.
 *
 * @return
 *   The table row.
 */
function garmentbox_factory_production_order_delivery_row($nid, $row_class, $row_title, $variant_data = NULL, $input_name = NULL) {
  $row = array(
    'data' => array('', ''),
    'class' => array('hidden', $row_class),
    'ref' => "variant-$nid",
  );

  $row['data'][] = $row_title;

  $vocabulary = taxonomy_vocabulary_machine_name_load('size');
  $size_tree = taxonomy_get_tree($vocabulary->vid);
  foreach ($size_tree as $term) {
    $quantity = empty($variant_data['sizes'][$term->tid]) ? '' : $variant_data['sizes'][$term->tid];
    if ($input_name) {
      $variables = array(
        'element' => array(
          '#attributes' => array(
            'name' => $input_name . "[$nid][$term->tid]",
            'size' => 4,
            'title' => $term->name,
            'value' => $quantity,
          ),
          '#autocomplete_path' => '',
        ),
      );
      $quantity = theme('textfield', $variables);
    }
    $row['data'][] = array(
      'data' => $quantity,
      'data-tid' => $term->tid,
      'class' => array('size-quantity'),
    );
  }
  $row['data'][] = array(
    'data' => '-',
    'class' => array('price'),
  );

  return $row;
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

  foreach(garmentbox_factory_get_production_order_inventory_lines($node->nid) as $nid) {
    $wrapper = entity_metadata_wrapper('node', $nid);
    $variant_nid = $wrapper->field_item_variant->getIdentifier();

    if (empty($data[$variant_nid])) {
      $data[$variant_nid] = array(
        'sizes' => array(),
        'item_price' => garmentbox_item_get_variant_price($variant_nid),
        'title' => $wrapper->field_item_variant->label(),
        'items_count' => 0,
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
      $data[$variant_nid]['items_count'] += $quantity;
    }
  }

  return $data;
}
