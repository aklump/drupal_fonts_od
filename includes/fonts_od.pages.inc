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
  $build = array(
    '#id' => 'fonts_od_fonts_page',
  );

  if (!($fonts = fonts_od_fonts())) {
    $build[] = array('#markup' => t('There are no fonts registered'));
  }
  else {
    $rows = $font_info = array();
    $provider = '';
    foreach ($fonts as $i) {
      $ops = array();
      $ops[] = l(t('Edit'), 'admin/appearance/fonts-od/' . $i['name'], array(
        'query' => drupal_get_destination(),
      ));
      $row = array(
        'data' => array(
          'title' => ($i['download url'] ? l($i['title'], $i['download url']) : $i['title']),
          'family' => $i['family'],
          'fallback' => $i['font-family'],
          'provider' => '',
          'ops' => implode(' ', $ops),
        ),
      );
      $rows[$i['title']] = $row;
      $font_info[$i['title']] = $i;
    }
    ksort($rows);
    $build[] = array(
      '#theme' => 'table',
      '#rows' => $rows,
      '#header' => array(t('Font Name'), t('Family'), t('Fallback Fonts'), t('Provider'), t('Operations')),
      '#fonts' => $font_info,
    );
  }
  return $build;
}

/** @} */ //end of group: fonts_od
