<?php

/**
 * Plugin definition.
 */
$plugin = array(
  'title' => t('Prepopulate link'),
  'description' => t('Display node prepopulate link.'),
  'required context' => new ctools_context_required(t('Node'), 'node'),
  'category' => t('Garmentbox'),
);

/**
 * Render callback.
 */
function garmentbox_general_prepopulate_link_content_type_render($subtype, $conf, $args, $context) {
  if (empty($context->data)) {
    return FALSE;
  }

  $node = $context->data;
  // If the node is an item variant, load the related item.
  if ($node->type == 'item_variant') {
    $wrapper = entity_metadata_wrapper('node', $node);
    $node = $wrapper->field_item->value();
  }

  $block = new stdClass();
  $block->module = 'garmentbox_general';
  $block->title = '';

  switch ($conf['type']) {
    case 'task':
      $field_name = 'field_entity_reference';
      $link_text = t('Add new task');
      break;

    case 'item_variant':
      $field_name = 'field_item';
      $link_text = t('Add new variation');
      break;

    case 'order':
      $field_name = 'field_season';
      $link_text = t('Add new order');
      break;

    case 'item':
      $field_name = 'field_season';
      $link_text = t('Add new item');
      break;

    default:
      return;
  }

  $options = array(
    'query' => array($field_name => $node->nid) + drupal_get_destination(),
  );
  $block->content = l($link_text, 'node/add/' . str_replace('_', '-', $conf['type']), $options);
  return $block;
}

/**
 * Edit form.
 */
function garmentbox_general_prepopulate_link_content_type_edit_form($form, &$form_state) {
  $conf = $form_state['conf'];

  $options = array();
  foreach (node_type_get_types() as $type) {
    $options[$type->type] = check_plain($type->name);
  }

  $form['type'] = array(
    '#title' => t('Create content of type'),
    '#type' => 'select',
    '#options' => $options,
    '#default_value' => $conf['type'],
  );

  return $form;
}

/**
 * Edit form submit callback.
 */
function garmentbox_general_prepopulate_link_content_type_edit_form_submit($form, &$form_state) {
  $form_state['conf']['type'] = $form_state['values']['type'];
}

