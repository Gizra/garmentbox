<?php

/**
 * @file
 * The theme system, which controls the output of the messages.
 */

function mimemail_theme_theme() {
  $path = drupal_get_path('module', 'mimemail') . '/theme';

  return array(
    'mimemail_message' => array(
      'variables' => array('key' => NULL, 'recipient' => NULL, 'subject' => NULL, 'body' => NULL),
      'template' => 'mimemail-message',
      'pattern' => 'mimemail_message__',
      'file' => 'mimemail.theme.inc',
      'path' => $path,
    )
  );
}

/**
 * Implements hook_theme_registry_alter().
 */
function mimemail_theme_theme_registry_alter(&$theme_registry) {
  global $theme_key;
  static $executed = array();

  // Preventing double execution.
  if (isset($executed[$theme_key])) {
    return;
  }

  $executed[$theme_key] = TRUE;
  foreach ($theme_registry as $name => $hook) {
    if ($name == 'mimemail_message') {
      $mimemail_theme = _mimemail_get_theme();

      // We don't have to change anything in case the render theme is the current theme.
      if ($mimemail_theme != $theme_key) {
        $themes = list_themes();
        // Getting the render theme.
        $theme = isset($themes[$mimemail_theme]) ? clone $themes[$mimemail_theme] : NULL;
        if ($theme != NULL) {
          // Stablishing variables for further process.
          $base_theme = array();
          if (isset($theme->base_themes)) {
            foreach (array_keys($theme->base_themes) as $base) {
              $base_theme[$base] = clone $themes[$base];
            }
          }
          if (isset($theme->base_theme) && !isset($base_theme[$theme->base_theme])) {
            $base_theme[$theme->base_theme] = clone $themes[$theme->base_theme];
          }
          $theme_engine = isset($theme->engine) ? $theme->engine : NULL;

          // Include template files to let _theme_load_registry add preprocess functions.
          include_once(drupal_get_path('theme', $theme->name) . '/template.php');
          foreach ($base_theme as $base) {
            include_once(drupal_get_path('theme', $base->name) . '/template.php');
          }

          // Get the theme_registry cache.
          $cache = _theme_load_registry($theme, $base_theme, $theme_engine);
          if (isset($cache[$name])) {
            $cache[$name]['includes'][] = drupal_get_path('theme', $theme->name) . '/template.php';
            foreach ($base_theme as $base) {
              $cache[$name]['includes'][] = drupal_get_path('theme', $base->name) . '/template.php';
            }
            // Changing current registry for the new record.
            $theme_registry[$name] = $cache[$name];
          }
        }
      }
    }
  }
}

/**
 * A preprocess function for theme('mimemail_message').
 *
 * The $variables array initially contains the following arguments:
 * - $recipient: The recipient of the message
 * - $key:  The mailkey associated with the message
 * - $subject: The message subject
 * - $body:  The message body
 *
 * @see theme/mimemail-message.tpl.php for additional variables.
 */
function template_preprocess_mimemail_message(&$variables) {
  $theme = _mimemail_get_theme();
  $themepath = drupal_get_path('theme', $theme);

  $sitestyle = variable_get('mimemail_sitestyle', 1);
  $mailstyles = file_scan_directory($themepath, '#^mail\.css*$#');

  // Check recursively for the existence of a mail.css file in the theme folder.
  if (!empty($mailstyles)) {
    foreach ($mailstyles as $mailstyle) {
      $styles = $mailstyle->uri;
    }
  }
  // If no mail.css was found and the site style sheets including is enabled,
  // gather all style sheets and embed a version of all style definitions.
  elseif ($sitestyle) {
    $css_all = drupal_add_css();
    $css_files = array();
    foreach ($css_all as $key => $options) {
      if ($options['group'] == CSS_THEME && $options['type'] == 'file' &&
         ($options['media'] == 'all' || $options['media'] == 'screen')) {
        $css_files[$key] = $options;
      }
    }
    // Grab local.css if it exists (support for Fusion based themes).
    $local = $themepath . '/css/local.css';
    if (@file_exists($local)) {
      $css_files['all']['theme'][$local] = TRUE;
    }
    if (variable_get('preprocess_css', FALSE)) {
      $pattern = '|<link.*href="' . $GLOBALS['base_url'] . '/([^"?]*)[?"].*|';
      $replacement = '\1';
    }
    else {
      $pattern = array(
        '/<([^<>]*)>/', // Remove the style tag.
        '/@import\s+url\("([^"]+)"\);+/', // Remove the import directive.
        '|' . $GLOBALS['base_url'] . '/([^"?]*)[?"].*|' // Remove the base URL.
      );
      $replacement = array('', '\1', '\1');
    }
    $styles = preg_replace($pattern, $replacement, drupal_get_css($css_files));
  }

  $css = '';
  if (isset($styles)) {
    // Process each style sheet.
    foreach (explode("\n", $styles) as $style) {
      if (!empty($style) && @file_exists($style)) {
        $css .= @file_get_contents($style);
      }
    }

    // Regexp to match comment blocks.
    $comment = '/\*[^*]*\*+(?:[^/*][^*]*\*+)*/';
    // Regexp to match double quoted strings.
    $double_quot = '"[^"\\\\]*(?:\\\\.[^"\\\\]*)*"';
    // Regexp to match single quoted strings.
    $single_quot = "'[^'\\\\]*(?:\\\\.[^'\\\\]*)*'";

    // Perform some safe CSS optimizations (derived from core CSS aggregation).
    $css = preg_replace_callback(
      "<$double_quot|$single_quot|$comment>Sus",  // Match all comment blocks along
      "_mimemail_process_comment",                // with double/single quoted strings
      $css);                                      // and feed them to _mimemail_process_comment().
    $css = preg_replace(
      '<\s*([@{}:;,]|\)\s|\s\()\s*[^\n\S]>S',  // Remove whitespace around separators,
      '\1',                                    // but keep space around parentheses
      $css);                                   // and new lines between definitions.

    // End the file with a new line.
    $css .= "\n";

    // Wordwrap to adhere to RFC821
    $css = wordwrap($css, 700);
  }

  // Set styles for the message.
  $variables['css'] = $css;

   // Process key to be a proper CSS class.
  $variables['key'] = str_replace('_', '-', $variables['key']);
}

/**
 * Process comment blocks. (derived from core CSS aggregation)
 *
 * This is the callback function for the preg_replace_callback()
 * used in drupal_load_stylesheet_content(). Support for comment
 * hacks is implemented here.
 */
function _mimemail_process_comment($matches) {
  static $keep_nextone = FALSE;
  // Quoted string, keep it.
  if ($matches[0][0] == "'" || $matches[0][0] == '"') {
    return $matches[0];
  }
  // End of IE-Mac hack, keep it.
  if ($keep_nextone) {
    $keep_nextone = FALSE;
    return $matches[0];
  }
  switch (strrpos($matches[0], '\\')) {
    case FALSE :
      // No backslash, strip it.
      return '';
    case drupal_strlen($matches[0])-3 :
      // Ends with \*/ so is a multi line IE-Mac hack, keep the next one also.
      $keep_nextone = TRUE;
      return '/*_\*/';
    default :
      // Single line IE-Mac hack.
      return '/*\_*/';
  }
}

/**
 * Helper function to retrieve the key of the theme to render the emails.
 *
 * @todo Add some kind of hook to let other modules alter this behavior.
 */
function _mimemail_get_theme() {
  global $theme_key;

  $theme = variable_get('mimemail_theme', 'current');
  switch ($theme) {
    case 'default':
      $theme = variable_get('theme_default', NULL);
      break;
    case 'current':
      $theme = $theme_key;
      break;
    case 'domain_theme':
      // Fetch the theme for the current domain.
      if (module_exists('domain_theme')) {
        // Assign the selected theme, based on the active domain.
        global $_domain;
        $domain_theme = domain_theme_lookup($_domain['domain_id']);
        // The above returns -1 on failure.
        $theme = ($domain_theme != -1) ? $domain_theme['theme'] : $theme_key;
      }
      break;
  }

  return $theme;
}
