<?php

/**
 * Plugin definition.
 */
$plugin = array(
  'title' => t('Line Sheet'),
  'description' => t('Show a line sheet of a season.'),
  'category' => t('Garmentbox - Line Sheet'),
  'required context' => new ctools_context_required(t('Node'), 'node'),
  'hook theme' => 'garmentbox_line_sheet_line_sheet_content_type_theme',
);

/**
 * Render callback.
 */
function garmentbox_line_sheet_line_sheet_content_type_render($subtype, $conf, $args, $context) {
  if (empty($context->data)) {
    return;
  }

  $node = $context->data;

  $module = 'garmentbox_line_sheet';
  $block = new stdClass();
  $block->module = $module;
  $block->title = t('Line Sheet @season', array('@season' => $node->title));

  if (!$nids = garmentbox_line_sheet_flag_get_flagged_content('line_sheet', $node)) {
    $block->content = t('No items added to the line sheet.');
    return $block;
  }

  $items = array();
  // Iterate over the item instances, but key them by the item node ID.
  foreach ($nids as $row) {
    $nid = $row->content_id;
    $sizes = array();
    $materials = array();
    $wrapper = entity_metadata_wrapper('node', $nid);
    $item_wrapper = $wrapper->field_item;

    $item_nid = $item_wrapper->getIdentifier();

    $items[$item_nid]['title'] = $item_wrapper->label();
    $items[$item_nid]['body'] = $item_wrapper->body->value() ? $item_wrapper->body->value->value() : '';
    if ($image = $wrapper->field_images->value()) {
      $items[$item_nid]['images'][] = theme('image_style', array('style_name' => 'thumbnail', 'path' => $image[0]['uri']));
    }
    foreach ($wrapper->field_size_info as $size_wrapper) {
      $sizes[] = $size_wrapper->field_size->label();
    }

    foreach ($wrapper->field_bom_info as $bom_wrapper) {
      if ($material = $bom_wrapper->field_source_info_ref->field_nick_name->value()) {
        $materials[] = $material;
      }
    }

    if (empty($items[$item_nid]['sizes'])) {
      $items[$item_nid]['sizes'] = implode(', ', $sizes);
    }

    if (empty($items[$item_nid]['materials'])) {
      $items[$item_nid]['materials'] = implode(', ', $materials);
    }

    $items[$item_nid]['links'][] = l(t('View'), 'node/' . $nid);
    $items[$item_nid]['links'][] = flag_create_link('line_sheet', $nid);
  }

  $output = '';
  foreach ($items as $nid => $variables) {
    $variables['images'] = theme('item_list', array('items' => $variables['images']));
    $variables['links'] = theme('item_list', array('items' => $variables['links']));
    $output .= theme('garmentbox_line_sheet', $variables);
  }

  $block->content = $output;
  return $block;
}

/**
 * Form settings.
 */
function garmentbox_line_sheet_line_sheet_content_type_edit_form($form, &$form_state) {
  return $form;
}

/**
 * Delegated hook_teheme().
 */
function garmentbox_line_sheet_line_sheet_content_type_theme(&$theme, $plugin) {
  $theme['garmentbox_line_sheet'] = array(
    'path' => $plugin['path'],
    'template' => 'line-sheet',
    'variables' => array(
      'body' => NULL,
      'images' => NULL,
      'links' => NULL,
      'materials' => NULL,
      'sizes' => NULL,
      'title' => NULL,
    ),
  );
}


