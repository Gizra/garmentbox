<?php

/**
 * Plugin definition.
 */
$plugin = array(
  'title' => t('Breadcrumbs'),
  'description' => t('Display node breadcrumbs.'),
  'required context' => new ctools_context_required(t('Node'), 'node'),
  'category' => t('Opengizra'),
);

/**
 * Render callback.
 */
function opengizra_general_breadcrumbs_content_type_render($subtype, $conf, $args, $context) {
  if (empty($context->data)) {
    return FALSE;
  }

  $wrapper = entity_metadata_wrapper('node', $context->data);

  $block = new stdClass();
  $block->module = 'opengizra_general';
  $block->title = '';

  $links = array();
  $links[] = l(t('home'), '');

  if (!empty($wrapper->field_reference_hierarchy)) {
    $count = count($wrapper->field_reference_hierarchy->value());
    for ($delta = 0; $delta < $count; $delta++) {
      $node = $wrapper->field_reference_hierarchy->get($delta)->value();
      $links[] = l($node->title, 'node/' . $node->nid);
    }
  }


  $links[] = '<span>' . $wrapper->label() . '</span>';

  $block->content = implode('<span>&gt;</span>', $links);
  return $block;
}

/**
 * Edit form.
 */
function opengizra_general_breadcrumbs_content_type_edit_form($form, &$form_state) {
  return $form;
}
