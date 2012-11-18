<?php

/**
 * Plugin definition.
 */
$plugin = array(
  'title' => t('Material links'),
  'description' => t('Display material links.'),
  'required context' => new ctools_context_required(t('Node'), 'node'),
  'category' => t('Garmentbox'),
);

/**
 * Render callback.
 */
function garmentbox_material_material_links_content_type_render($subtype, $conf, $args, $context) {
  if (empty($context->data)) {
    return;
  }
  $nid = $context->data->nid;

  $block = new stdClass();
  $block->module = 'garmentbox_material';
  $block->title = '';

  $query = new EntityFieldQuery();
  $result = $query
    ->entityCondition('entity_type', 'node', '=')
    ->entityCondition('bundle', 'material')
    ->execute();

  if (empty($result['node'])) {
    return;
  }

  $items = array();
  $nodes = node_load_multiple(array_keys($result['node']));
  foreach ($nodes as $node) {
    $wrapper = entity_metadata_wrapper('node', $node);
    $title = $wrapper->field_nick_name->value() ? $wrapper->field_nick_name->value() : $node->title ;
    // Mark current node's tab.
    $options = $node->nid == $nid ? array('attributes' => array('class' => 'active')) : array();
    $items[] = l($title, "material/" . $node->nid, $options);
  }

  $block->content = theme('item_list', array('items' => $items));
  return $block;
}

/**
 * Edit form.
 */
function garmentbox_material_material_links_content_type_edit_form($form, &$form_state) {
  return $form;
}
