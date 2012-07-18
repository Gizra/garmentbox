<?php

/**
 * Preprocessor for page.tpl.php template file.
 */
function ninesixty_preprocess_page(&$vars) {

  // For easy printing of variables.
  // Branding
  $vars['logo_img'] = '';
  if (!empty($vars['logo'])) {
    $vars['logo_img'] = theme('image__logo', array(
      'path'  => $vars['logo'],
      'alt'   => t('Site Logo'),
    ));
  }
  $vars['linked_logo_img']  = '';
  if (!empty($vars['logo_img'])) {
    $vars['linked_logo_img'] = l($vars['logo_img'], '<front>', array(
      'html' => TRUE,
      'attributes' => array(
        'rel'   => 'home',
        'title' => t('Home'),
      ),
    ));
  }
  $vars['linked_site_name'] = '';
  if (!empty($vars['site_name'])) {
    $vars['linked_site_name'] = l($vars['site_name'], '<front>', array(
      'attributes' => array(
        'rel'   => 'home',
        'title' => t('Home'),
      ),
    ));
  }
  // Site navigation links.
  $vars['main_menu_links'] = theme('links__system_main_menu', array(
    'links' => $vars['main_menu'],
    'attributes' => array(
      'id'    => 'main-menu',
      'class' => array('main-menu', 'inline'),
    ),
    'heading' => array(
      'text'  => t('Main menu'),
      'level' => 'h2',
      'class' => array('element-invisible'),
    ),
  ));
  $vars['secondary_menu_links'] = theme('links__system_secondary_menu', array(
    'links' => $vars['secondary_menu'],
    'attributes' => array(
      'id'    => 'secondary-menu',
      'class' => array('secondary-menu', 'inline'),
    ),
    'heading' => array(
      'text'  => t('Secondary menu'),
      'level' => 'h2',
      'class' => array('element-invisible'),
    ),
  ));

}

/**
 * Contextually adds 960 Grid System classes.
 *
 * The first parameter passed is the *default class*. All other parameters must
 * be set in pairs like so: "$variable, 3". The variable can be anything available
 * within a template file and the integer is the width set for the adjacent box
 * containing that variable.
 *
 *  class="<?php print ns('grid-16', $var_a, 6); ?>"
 *
 * If $var_a contains data, the next parameter (integer) will be subtracted from
 * the default class. See the README.txt file.
 */
function ns() {
  $args = func_get_args();
  $default = array_shift($args);
  // Get the type of class, i.e., 'grid', 'pull', 'push', etc.
  // Also get the default unit for the type to be procesed and returned.
  list($type, $return_unit) = explode('-', $default);

  // Process the conditions.
  $flip_states = array('var' => 'int', 'int' => 'var');
  $state = 'var';
  foreach ($args as $arg) {
    if ($state == 'var') {
      $var_state = !empty($arg);
    }
    elseif ($var_state) {
      $return_unit = $return_unit - $arg;
    }
    $state = $flip_states[$state];
  }

  $output = '';
  // Anything below a value of 1 is not needed.
  if ($return_unit > 0) {
    $output = $type . '-' . $return_unit;
  }
  return $output;
}

/**
 * Implements hook_css_alter.
 *
 * Alters the css based on the theme settings.
 */
function ninesixty_css_alter(&$css) {
  global $language;

  // Get .info defined settings.
  $settings = array();
  foreach (ns_active_themes() as $active_theme) {
    $settings += ns_theme_info('settings', array(), $active_theme);
  }

  // Get floats.
  $css_float = array();
  if (isset($settings['css_float'])) {
    $css_float = array_flip($settings['css_float']);
  }

  // Setup to replace when alternate grid columns are defined.
  $grid_replace = array();
  $ns_target  = isset($settings['ns_columns_target']) ? $settings['ns_columns_target'] : '';
  $ns_options = isset($settings['ns_columns_option']) ? $settings['ns_columns_option'] : array();
  $ns_select  = isset($settings['ns_columns_select']) ? $settings['ns_columns_select'] : '';
  if ($ns_target && isset($ns_options[$ns_select])) {
    $grid_replace[$ns_target] = $ns_options[$ns_select];
  }

  $ns_css = array();
  foreach ($css as $css_key => &$css_data) {
    // Skip if it's not a local file or not part of the theme.
    if ($css_data['type'] != 'file' || $css_data['group'] != CSS_THEME) {
      continue;
    }

    $css_path = $css_data['data'];
    $css_name = basename($css_path);

    // Process floats.
    if (isset($css_float[$css_name])) {
      // Add it to the system css group instead of creating a new one to
      // prevent an extra linked group when the styles are aggregated.
      $css_data['group']   = CSS_SYSTEM;
      $css_data['weight'] -= 0.01;
    }

    // Process known grid styles.
    if (in_array($css_name, $ns_options)) {
      // Prevent multiple 960 styles by setting a common key. Multiple inclusions
      // can happen if a subtheme includes one manually. Since there are multiple
      // iterations with different names, overriding won't be predictable. This
      // will only work for all the known names set from settings[ns_columns_option].
      $ns_css['ninesixty_grids'] = $css_data;

      // Make it lighter since grid styles are generic.
      $ns_css['ninesixty_grids']['weight'] -= 0.1;

      // Process grid replacement.
      if (isset($grid_replace[$css_name])) {
        $target_grid = str_replace($css_name, $grid_replace[$css_name], $css_path);
        if ($target_grid != $css_path && file_exists($target_grid)) {
          $ns_css['ninesixty_grids']['data']    = $target_grid;
        }
      }

      // Process grid debugging style.
      if ((bool) $settings['ns_columns_debug']) {
        $ns_debug_style = str_replace($css_name, $settings['ns_columns_debug_css'], $css_path);
        if (file_exists($ns_debug_style)) {
          $css_new               = $css_data;
          $css_new['weight']    += 0.1;
          $css_new['data']       = $ns_debug_style;
          $css_new['every_page'] = FALSE;
          $ns_css['ninesixty_debug'] = $css_new;
        }
      }

      // Key was renamed to 'ninesixty_grids' so remove it.
      unset($css[$css_key]);
    }

    // Apply RTL styles to our custom set.
    if ($language->direction == LANGUAGE_RTL
      && strpos($css_name, '-rtl.css')
      && in_array(str_replace('-rtl.css', '.css', $css_name), $ns_options)) {

      foreach (array('ninesixty_grids', 'ninesixty_debug') as $ns_key) {
        // Add.
        if (isset($ns_css[$ns_key])) {
          $rtl_path = str_replace('.css', '-rtl.css', $ns_css[$ns_key]['data']);
          if (file_exists($rtl_path)) {
            // Same weight used by locale_css_alter().
            $rtl_data                 = $ns_css[$ns_key];
            $rtl_data['data']         = $rtl_path;
            $rtl_data['weight']      += 0.01;
            $ns_css[$ns_key . '_rtl'] = $rtl_data;
          }
        }
      }
      // Get rid of stray RTL styles added by core.
      if (isset($css[$css_path])) {
        unset($css[$css_key]);
      }
    }
  }
  $css += $ns_css;

}

/**
 * Returns the current active theme. Use this instead of the global variable.
 */
function ns_active_theme() {
  global $theme_key;
  return $theme_key;
}

/**
 * List the active sub-theme and their connected parents.
 */
function ns_active_themes() {

  $themes        = list_themes();
  $active_theme  = ns_active_theme();
  $active_themes = array($active_theme => $active_theme);
  $parent_key    = $active_theme;

  while ($parent_key && isset($themes[$parent_key]->base_theme)) {
    $parent_key                 = $themes[$themes[$parent_key]->name]->base_theme;
    $active_themes[$parent_key] = $parent_key;
  }

  return $active_themes;
}

/**
 * Get the values defined within the .info file.
 * 
 * @param $info_key
 *  (required) The key to retrieve.
 * @param $default
 *  Fall back value if nothing is found.
 * @param $theme
 *  Theme specific value. If not set, it will return the value for the active
 *  theme.
 */
function ns_theme_info($info_key, $default = NULL, $theme_key = NULL) {

  if (!isset($theme_key)) {
    $theme_key = ns_active_theme();
  }
  $list_themes = list_themes();

  return isset($list_themes[$theme_key]->info[$info_key]) ? $list_themes[$theme_key]->info[$info_key] : $default;
}
