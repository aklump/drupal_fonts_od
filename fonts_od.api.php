<?php
/**
 * @file
 * API documentation for fonts_od module.
 *
 * @addtogroup hooks
 * @{
 */

/**
 * Implements hook_fonts_od_defaults_alter().
 *
 * @param array &$defaults
 */
function hook_fonts_od_defaults_alter(&$defaults) {
  $defaults['fallback']['sans-serif'] = array('Arial', 'Georgia', 'san-serif');
}

/**
 * Implements hook_fonts_od_info().
 *
 * Provide font information directly
 *
 * @return array
 *   Keys are the basename! This should be unique from all fonts.
 *   - download url: where the font was sourced from
 *   - name: the machine name
 *   - title: the human title, also becomes the font family
 *   - family: FONTS_OD_SANS_SERIF, FONTS_OD_SERIF, FONTS_OD_MONOSPACE
 *   - fallback: an array of fonts to use for css fallbacks
 *   - basename: the basename of the font without extension; this must be the
 *   same as the key of the array element
 *   - file path: (Optional) This defaults to a folder called 'fonts' inside the
 *   active theme. Use this if you need to specific a different location for your
 *   font.
 */
function hook_fonts_od_info() {
  return array(
    'fontin_sans_sc_45b-webfont' => array(
      'download url' => 'http://www.fontsquirrel.com/fonts/Fontin-Sans',
      'name' => 'fontin_sans_small_caps',
      'title' => 'Fontin Sans Small Caps',
      'family' => FONTS_OD_SANS_SERIF,
      'fallback' => array(),
      'basename' => 'fontin_sans_sc_45b-webfont',
      'file path' => drupal_get_path('theme', 'gop3_theme') . '/fonts/fontin-sans',
    ),
  );
}

/**
 * Implements hook_fonts_od_info_alter(&$info).
 *
 * Set the correct font family of auto-detected fonts. Alter the information
 * provided by modules about available fonts.
 *
 * @param array &$info
 */
function hook_fonts_od_info_alter(&$info) {
  
  // Give the font family a new name (from it's auto-detected one) to use in
  // your css declarations.
  $info['OpenSans-CondLight-webfont']['title'] = 'Open Sans Narrow';

  // Set the font family type on an auto-detected font
  $info['Enriqueta-Bold-webfont']['family'] = FONTS_OD_SERIF;
}

/**
 * Implements hook_fonts_od_name_alter(&$name).
 *
 * Influence the automatic naming of fonts
 *
 * @param string &$name
 *   An all lowercase string generated from the filename
 */
function hook_fonts_od_name_alter(&$name) {
  $name = trim(str_replace('45b', '', $name));
  switch ($name) {
    case 'fontin sans bi':
      $name = 'fontin sans bold italic';
      break;
    case 'fontin sans i':
      $name = 'fontin sans italic';
      break;
    case 'fontin sans b':
      $name = 'fontin sans bold';
      break;
    case 'fontin sans r':
      $name = 'fontin sans';
      break;
    case 'fontin sans sc':
      $name = 'fontin sans small caps';
      break;
    default:
      $name = str_replace('opensans', 'open sans', $name);
      break;
  }
}

/**
 * Implements hook_fonts_od_fonts_alter(&$fonts).
 *
 * Alter the final font information before it gets cached such as 'download url'
 *
 * @param array &$fonts
 */
function hook_fonts_od_fonts_alter(&$fonts) {

}

/**
 * Implements hook_fonts_od_include_font().
 *
 * @param array $font
 *
 * @see fonts_od_get_font()
 */
function hook_fonts_od_include_font($font) {
  // Act on the adding of a font to the page
}

/** @} */ //end of group hooks
