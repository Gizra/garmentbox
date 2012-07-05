<?php
/**
 * Plugin definition
 */
$plugin = array(
  'title' => t('OG Group message'),
  'description' => t("Show a link to a group, and recent messages."),
  'required context' => new ctools_context_required(t('User'), 'user'),
  'category' => t('Opengizra OG'),
);

/**
 * Render callback.
 */
function opengizra_og_og_message_content_type_render($subtype, $conf, $args, $context) {
  if (empty($context) || empty($context->data)) {
    return FALSE;
  }
  
  $module = 'opengizra_og';
  $wrapper = entity_metadata_wrapper('user', $context->data->uid);
  if (!$wrapper->og_membership->value()) {
    return;
  }

  // TODO: Make it a settings.
  $count = $wrapper->og_membership->count();
  $max = $count < 5 ? $count : 5;

  $items = array();
  $delta = 0;
  $node = menu_get_object('node');
  while ($delta < $max) {
    $group = $wrapper->og_membership->get($delta)->group;
    $count = opengizra_og_get_unviewed_message_count($group->gid->value());
    $text = $group->label->value() . ' (' . $count . ')';
    $options = array();
    if ($node && $node->nid == $group->entity->value(array('identifier' => TRUE))) {
      $options['attributes']['class'][] = 'active';
    }
    $items[] = array('data' => l($text, $group->url->value(), $options));
    $delta++;
  }

  $element[$subtype] = array(
    '#theme' => 'item_list',
    '#items' => $items,
  );

  $block = new stdClass();
  $block->module = $module;
  $block->title = '';
  $block->content = $element;

  return $block;
}

/**
 * Form callback.
 */
function opengizra_og_og_message_content_type_edit_form($form, &$form_state) {
  // Provide a blank form so we have a place to have context setting.
  return $form;
}
