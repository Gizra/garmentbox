  <?php
/**
 * @file
 * Garmentbox profile.
 */

/**
 * Implements hook_form_FORM_ID_alter().
 *
 * Allows the profile to alter the site configuration form.
 */
function garmentbox_form_install_configure_form_alter(&$form, $form_state) {
  // Pre-populate the site name with the server name.
  $form['site_information']['site_name']['#default_value'] = $_SERVER['SERVER_NAME'];
}

/**
 * Implements hook_install_tasks().
 */
function garmentbox_install_tasks() {
  $tasks = array();

  $tasks['garmentbox_setup_blocks'] = array(
    'display_name' => st('Setup Blocks'),
    'display' => FALSE,
  );

  $tasks['garmentbox_setup_og_permissions'] = array(
    'display_name' => st('Setup Blocks'),
    'display' => FALSE,
  );
  return $tasks;
}

/**
 * Task callback; Setup blocks.
 */
function garmentbox_setup_blocks() {
  $default_theme = variable_get('theme_default', 'garmentbox_omega');

  $blocks = array(
    array(
      'module' => 'system',
      'delta' => 'user-menu',
      'theme' => $default_theme,
      'status' => 1,
      'weight' => 0,
      'region' => 'header',
      'pages' => '',
      'title' => '<none>',
      'cache' => DRUPAL_NO_CACHE,
    ),
  );

  drupal_static_reset();
  _block_rehash($default_theme);
  foreach ($blocks as $record) {
    $module = array_shift($record);
    $delta = array_shift($record);
    $theme = array_shift($record);
    db_update('block')
      ->fields($record)
      ->condition('module', $module)
      ->condition('delta', $delta)
      ->condition('theme', $theme)
      ->execute();
  }
}

/**
 * Task callback; Setup OG permissions.
 *
 * We do this here, late enough to make sure all group-content were
 * created.
 */
function garmentbox_setup_og_permissions() {
  $og_roles = og_roles('node', 'company');
  $rid = array_search(OG_AUTHENTICATED_ROLE, $og_roles);

  $permissions = array();
  $types = array(
    'customer',
    'department',
    'event',
    'inventory_line',
    'item',
    'item_variant',
    'material',
    'order',
    'pattern_task',
    'factory',
    'production_order',
    'season',
    'task',
    'vendor',
  );
  foreach ($types as $type) {
    $permissions["create $type content"] = TRUE;
    $permissions["update own $type content"] = TRUE;
    $permissions["update any $type content"] = TRUE;
  }
  og_role_change_permissions($rid, $permissions);
}
