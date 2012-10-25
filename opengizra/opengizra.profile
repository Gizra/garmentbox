<?php
/**
 * @file
 * Opengizra profile.
 */

/**
 * Implements hook_form_FORM_ID_alter().
 *
 * Allows the profile to alter the site configuration form.
 */
function opengizra_form_install_configure_form_alter(&$form, $form_state) {
  // Pre-populate the site name with the server name.
  $form['site_information']['site_name']['#default_value'] = $_SERVER['SERVER_NAME'];
}

/**
 * Implements hook_install_tasks().
 */
function opengizra_install_tasks() {
  $tasks = array();

  $tasks['opengizra_import_data'] = array(
    'display_name' => st('Import content'),
    'display' => TRUE,
    'type' => 'batch',
    'run' => INSTALL_TASK_RUN_IF_NOT_COMPLETED,
  );
  return $tasks;
}

/**
 * Task callback: return a batch API array, for importing content and creating
 * menues.
 */
function opengizra_import_data() {
  drupal_set_title(st('Import content'));

  // Fixes problems when the CSV files used for importing have been created
  // on a Mac, by forcing PHP to detect the appropriate line endings.
  ini_set('auto_detect_line_endings', TRUE);

  $migrations = migrate_migrations();
  foreach ($migrations as $machine_name => $migration) {
    $operations[] =  array('_opengizra_import_data', array($machine_name, t('Importing content.')));
  }
  // Perform post-import tasks.
  $operations[] = array('_opengizra_setup_blocks', array(t('Setup blocks.')));

  $batch = array(
    'title' => t('Importing content'),
    'operations' => $operations,
  );

  return $batch;
}

/**
 * BatchAPI callback.
 *
 * @see opengizra_profile_import_data()
 */
function _opengizra_import_data($operation, $type, &$context) {
  $context['message'] = t('@operation', array('@operation' => $type));
  $migration =  Migration::getInstance($operation);
  $migration->processImport();
}

/**
 * BatchAPI callback.
 *
 * @see opengizra_profile_import_data()
 */
function _opengizra_setup_blocks($operation, $type, &$context) {
  $default_theme = variable_get('theme_default', 'opengizra_omega');

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
