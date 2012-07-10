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
    return;
  }

  $module = 'opengizra_og';
  $wrapper = entity_metadata_wrapper('user', $context->data->uid);
  if (!$wrapper->og_membership->value()) {
    // User has no groups.
    return;
  }

  // TODO: Make it a settings.
  $membership_count = $wrapper->og_membership->count();

  $max = $membership_count < 5 ? $membership_count : 5;

  $items = array();
  $delta = 0;
  $node = menu_get_object('node');
  while ($delta < $max) {
    $group_node = $wrapper->og_membership->get($delta)->group->value();
    $count = opengizra_og_get_unviewed_message_count($group_node->nid);
    $text = $group_node->title . ' (' . $count . ')';
    $options = array();
    if ($node && $node->nid == $group_node->nid) {
      $options['attributes']['class'][] = 'active';
    }
    $items[] = array('data' => l($text, 'node/' . $group_node->nid, $options));
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
