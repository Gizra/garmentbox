<?php

/**
 * Plugin definition.
 */
$plugin = array(
  'title' => t('Production price'),
  'description' => t('Display the production price of an item variant.'),
  'required context' => new ctools_context_required(t('Node'), 'node'),
  'category' => t('Opengizra Item'),
  'hook theme' => 'opengizra_item_production_price_content_type_theme',
);

/**
 * Render callback.
 */
function opengizra_item_production_price_content_type_render($subtype, $conf, $args, $context) {
  if (empty($context->data)) {
    return FALSE;
  }

  $block = new stdClass();
  $block->module = 'opengizra_item';
  $block->title = '';

  $node = $context->data;

  // Sum the total BOM and BOL prices.
  $raw_price = opengizra_bom_get_variant_bom_price($node) + opengizra_bol_get_variant_bol_price($node);

  $variables = array(
    'price' => commerce_currency_format($raw_price, commerce_default_currency()),
  );

  $block->content = theme('opengizra_item_production_price', $variables);
  return $block;
}

/**
 * Edit form.
 */
function opengizra_item_production_price_content_type_edit_form($form, &$form_state) {
  return $form;
}

/**
 * Delegated hook_theme().
 */
function opengizra_item_production_price_content_type_theme(&$theme, $plugin) {
  $theme['opengizra_item_production_price'] = array(
    'variables' => array('price' => NULL),
    'path' => $plugin['path'],
    'template' => 'production-price',
  );
}
