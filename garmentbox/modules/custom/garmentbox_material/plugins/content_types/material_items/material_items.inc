<?php

/**
 * Plugin definition.
 *
 * Find item variants that use a material, regardless of vendor, and display
 * them using a view.
 */
$plugin = array(
  'title' => t('Material items'),
  'description' => t('Display item variants that use a certain material.'),
  'required context' => new ctools_context_required(t('Node'), 'node'),
  'category' => t('Garmentbox Item'),
);

/**
 * Render callback.
 */
function garmentbox_material_material_items_content_type_render($subtype, $conf, $args, $context) {
  if (empty($context->data)) {
    return;
  }
  $node = $context->data;

  $block = new stdClass();
  $block->module = 'garmentbox_material';
  $block->title = '';

  $wrapper = entity_metadata_wrapper('node', $node->nid);
  if (empty($wrapper->field_source_info)) {
    // No sources are available.
    return;
  }

  // Find item variants that use the material.
  $source_ids = array();
  foreach($wrapper->field_source_info as $source_info) {
    // Get material's source IDs.
    $source_ids[] = $source_info->value()->item_id;
  }

  // Find BOM field collections point to those sources.
  $query = new EntityFieldQuery();
  $result = $query
    ->entityCondition('entity_type', 'field_collection_item', '=')
    ->entityCondition('bundle', 'field_bom_info', '=')
    ->fieldCondition('field_source_info_ref', 'target_id', $source_ids, 'IN')
    ->execute();

  if (empty($result['field_collection_item'])) {
    // None of the BOM field collections point to the material.
    return;
  }
  $bom_collection_ids = array_keys($result['field_collection_item']);

  // Display a view.
  $view = views_get_view('material');
  $view->set_arguments(array(implode(',', $bom_collection_ids)));

  $block->content = $view->preview('material_item_variants');
  return $block;
}

/**
 * Edit form.
 */
function garmentbox_material_material_items_content_type_edit_form($form, &$form_state) {
  return $form;
}
