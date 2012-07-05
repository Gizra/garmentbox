<?php
/**
 * Plugin definition
 */
$plugin = array(
  'title' => t('Picture and name'),
  'description' => t("Show the user's picture and name."),
  'required context' => new ctools_context_required(t('User'), 'user'),
  'category' => t('User'),
);

/**
 * Render callback.
 */
function opengizra_user_picture_name_content_type_render($subtype, $conf, $args, $context) {
  if (empty($context) || empty($context->data)) {
    return;
  }

  $module = 'opengizra_user';
  $account = clone $context->data;

  $element['plugin_content'] = array(
    '#prefix' => '<div class="clearfix">',
    '#suffix' => '</div>',
    'picture' => array('#theme' => 'user_picture', '#account' => $account),
    'name' => array('#theme' => 'username', '#account' => $account),
  );

  $element['#attached']['css'][] = drupal_get_path('module', $module) . '/plugins/content_types/' . $subtype . '/' . $subtype . '.css.less';

  $block = new stdClass();
  $block->module = $module;
  $block->delta = $account->uid;
  $block->title = '';
  $block->content = $element;

  return $block;
}

/**
 * Form callback.
 */
function opengizra_user_picture_name_content_type_edit_form($form, &$form_state) {
  // Provide a blank form so we have a place to have context setting.
  return $form;
}
