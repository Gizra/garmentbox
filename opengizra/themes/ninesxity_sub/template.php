<?php

/**
 * @file
 * Contains theme override functions and preprocess functions for the theme.
 */

/**
 * Preprocess page.
 */
function ninesixty_sub_preprocess_page(&$vars, $hook) {
  global $user;
  if (overlay_get_mode() == 'child') {
    // Add our custom overlay.tpl
    $vars['theme_hook_suggestions'][] = 'page__overlay';
  }

  if (count(drupal_get_breadcrumb()) == 1) {
    // Don't show breadcrumb, if it's only "Home".
    drupal_set_breadcrumb(array());
  }

  // Invoke the og-message block. We do it late in the template, to allow the
  // viewed message to be registered.
  $vars['og_message'] = '';
}

/**
 * Comment preprocess.
 */
function ninesixty_sub_preprocess_comment(&$vars, $hook) {
  $vars['date'] = date('F Y', $vars['comment']->created);
  $params = array ('!author' => $vars['author']);
  $vars['author'] = t('!author wrote:' ,$params);
}

/**
 * Override theme_system_powered_by().
 */
function ninesixty_sub_system_powered_by() {
  return '<span>' . t('Powered by <a href="@poweredby">Drupal</a> (also <a href="@gizra">Gizra</a> kinda helped)', array('@poweredby' => 'http://drupal.org', '@gizra' => 'http://gizra.com')) . '</span>';
}

/**
 * Override theme_filter_tips().
 */
function ninesixty_sub_filter_tips() {
  return;
}

/**
 * Override theme_filter_tips_more_info().
 */
function ninesixty_sub_filter_tips_more_info() {
  return;
}
