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
 */
function hook_fonts_od_defaults_alter(&$defaults) {
  $defaults['fallbacks']['sans-serif'] = array('Arial', 'Georgia', 'san-serif');
}

/**
 * Implements hook_fonts_od_fonts().
 *
 * @return array
 *   - download url: where the font was sourced from
 *   - name: the machine name
 *   - title: the human title, also becomes the font family
 *   - family: FONTS_OD_SANS_SERIF, FONTS_OD_SERIF, FONTS_OD_MONOSPACE
 *   - basename: the basename of the font without extension
 *   - file path: (Optional) This defaults to a folder called 'fonts' inside the
     active theme. Use this if you need to specific a different location for your
     font.
 */
function hook_fonts_od_fonts() {
  return array(
    array(
      'download url' => 'http://www.fontsquirrel.com/fonts/Fontin-Sans',
      'name' => 'fontin_sans_small_caps',
      'title' => 'Fontin Sans Small Caps',
      'family' => FONTS_OD_SANS_SERIF,
      'basename' => 'fontin_sans_sc_45b-webfont',
      'file path' => drupal_get_path('theme', 'gop3_theme') . '/fonts/fontin-sans',
    ),
  );
}

/** @} */ //end of group hooks
