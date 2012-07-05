<?php
/**
 * Plugin definition
 */
$plugin = array(
  'title' => t('Group link'),
  'description' => t("Show a link to group link, for authorized users."),
  'required context' => array(
    new ctools_context_required(t('User'), 'user'),
    new ctools_context_required(t('Group'), 'entity:group'),
   ),
  'category' => t('Opengizra OG'),
);

/**
 * Render callback.
 */
function opengizra_og_group_link_content_type_render($subtype, $conf, $args, $context) {
  list($user_context, $group_context) = $context;

  if (empty($group_context) || empty($group_context->data)) {
    return FALSE;
  }

  if (empty($user_context) || empty($user_context->data)) {
    return FALSE;
  }

  $module = 'opengizra_og';
  $account = clone $user_context->data;
  $group = clone $group_context->data;

  // Check user has permissions.
  if (!og_user_access($group->gid, 'administer group', $account)) {
    return;
  }

  $node = $group->getEntity();
  if (!$node) {
    return;
  }

  $element['group_link'] = array(
    '#type' => 'link',
    '#title' => t('Group settings'),
    '#href' => 'node/' . $node->nid . '/group',
  );

  $block = new stdClass();
  $block->module = $module;
  $block->delta = $group->gid;
  $block->title = '';
  $block->content = $element;

  return $block;
}

/**
 * Form callback.
 */
function opengizra_og_group_link_content_type_edit_form($form, &$form_state) {
  // Provide a blank form so we have a place to have context setting.
  return $form;
}
