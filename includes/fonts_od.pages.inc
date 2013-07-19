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
      switch ($i['module']) {
        case 'fonts_od':
          $info_link = 'admin/appearance/fonts/' . $i['name'];
          break;
        case 'fontyourface':
          $info_link = 'admin/appearance/fontyourface/edit/' . $i['file path'];
          break;
      }

      $row = array(
        'data' => array(
          ($i['download url'] ? l($i['title'], $i['download url']) : $i['title']),
          $i['family'],
          $i['font-family'],
          l('Edit', $info_link, array(
            'query' => drupal_get_destination(),
          )),
          //'<div style="font-family: ' . $i['font-family'] . '">' . $example . '</div>',
        ),
      );
      $rows[$i['title']] = $row;
    }
    ksort($rows);
    $build[] = array(
      '#theme' => 'table',
      '#rows' => $rows,
      '#header' => array(t('Font Name'), t('Family'), t('Fallback Fonts'), t('Operations')/*, t('Example')*/),
    );
  }
  return $build;
}

/**
 * Return font details page
 *
 * @param string $name
 *   Font machine name
 *
 * @return array
 */
function fonts_od_font_detail_page($name) {
  if (!$font = fonts_od_get_font($name)) {
    return MENU_NOT_FOUND;
  }
  $build = array();
  $build['export']['sass'] = array(
    '#type' => 'textarea',
    '#title' => t('Sass Snippet'),
    '#value' => fonts_od_get_sass($font),
    '#required' => TRUE,
    '#rows' => 10,
    '#resizable' => TRUE,
  );
  return $build;
}

/** @} */ //end of group: fonts_od
