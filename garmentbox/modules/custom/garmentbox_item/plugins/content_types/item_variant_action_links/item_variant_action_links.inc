<?php

/**
 * Plugin definition.
 */
$plugin = array(
  'title' => t('Item variant action links'),
  'description' => t('Display item variant action links.'),
  'required context' => new ctools_context_required(t('Node'), 'node'),
  'category' => t('Garmentbox Item'),
);

/**
 * Render callback.
 */
function garmentbox_item_item_variant_action_links_content_type_render($subtype, $conf, $args, $context) {
  if (empty($context->data)) {
    return FALSE;
  }

  $block = new stdClass();
  $block->module = 'garmentbox_item';
  $block->title = t('More actions');

  $items = array();
  $items[] = l(t('Download pattern file'), '', array('attributes' => array('class' => array('icon pattern'))));
  $items[] = l(t("Print cutter's must"), '', array('attributes' => array('class' => array('icon cutter-must'))));
  $items[] = l(t('See pattern history...'), '', array('attributes' => array('class' => array('pattern-history'))));

  $block->content = theme('item_list', array('items' => $items));
  return $block;
}

/**
 * Edit form.
 */
function garmentbox_item_item_variant_action_links_content_type_edit_form($form, &$form_state) {
  return $form;
}
