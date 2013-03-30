<?php
/**
 * @file
 * Generate pages for fonts_od module
 *
 * @ingroup fonts_od
 * @{
 */

/**
 * Generate a page showing a list of all font information
 */
function fonts_od_fonts_page() {
  $build = array();
  if (!($fonts = fonts_od_fonts())) {
    $build[] = array('#markup' => t('There are no fonts registered'));
  }
  else {
    $rows = array();
    $example = 'The quick brown fox';
    foreach ($fonts as $i) {
      //fonts_od_add_font($i['name']);
      $row = array(
        'data' => array(
          ($i['download url'] ? l($i['title'], $i['download url']) : $i['title']),
          $i['family'],
          $i['font-family'],
          //'<div style="font-family: ' . $i['font-family'] . '">' . $example . '</div>',
        ),
      );
      $rows[$i['title']] = $row;
    }
    ksort($rows);
    $build[] = array(
      '#theme' => 'table',
      '#rows' => $rows,
      '#header' => array(t('Font Name'), t('Family'), t('font-family')/*, t('Example')*/),
    );
  }
  return $build;
}



/** @} */ //end of group: fonts_od
