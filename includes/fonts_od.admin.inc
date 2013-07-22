<?php
/**
 * @file
 * Administration page callbacks for the fonts_od module.
 *
 * @ingroup fonts_od
 * @{
 */

/**
 * Form builder for the fonts_od_edit_form form.
 *
 * Define for editing user overrides by font
 *
 * @param array $form
 * @param array &$form_state
 * @param string $name
 *   The machine name of the font
 *
 * @see fonts_od_edit_form_validate()
 * @see fonts_od_edit_form_submit()
 * @ingroup forms
 */
function fonts_od_edit_form($form, &$form_state, $name) {
  if (!($info = fonts_od_get_font($name))) {
    return drupal_not_found();
  }

  // Code Export
  if ($sass = fonts_od_get_sass($info)) {
    $form['export'] = array(
      '#type' => 'fieldset',
      '#title' => t('CSS/SASS'),
      '#collapsible' => TRUE,
      '#collapsed' => TRUE,
    );

    $form['export']['sass'] = array(
      '#type' => 'textarea',
      '#title' => t('Sass Snippet'),
      '#value' => $sass,
      '#required' => TRUE,
      '#rows' => 5,
      '#resizable' => TRUE,
    );
  }

  $form['db'] = array(
    '#type' => 'container',
    '#tree' => TRUE,
  );

  $form['db']['name'] = array(
    '#type' => 'textfield',
    '#title' => t('Font ID'),
    '#default_value' => $info['name'],
    '#required' => TRUE,
    '#disabled' => TRUE,
  );
  $form['db']['title'] = array(
    '#type' => 'textfield',
    '#title' => t('Title'),
    '#default_value' => $info['title'],
    '#required' => TRUE,
  );

  $options = fonts_od_defaults();
  $options = array(
    '' => t('- Choose -'),
  ) + drupal_map_assoc(array_keys($options['fallback']));
  $form['db']['family'] = array(
    '#type' => 'select',
    '#title' => t('Generic Font Family'),
    '#default_value' => $info['family'],
    '#options' => $options,
    '#required' => TRUE,
  );

  //'disabled'=>array(
  //  ':input[name=device]' => $non_uuid_devices,
  //),

  $fallback = explode(',', $info['font-family']);
  foreach (array_keys($fallback) as $key) {
    $fallback[$key] = trim($fallback[$key]);
  }
  $form['db']['fallback'] = array(
    '#type' => 'textfield',
    '#description' => t('List out the <a href="@url">fallback fonts</a>, comma-separated for this font. <strong>Leave blank for defaults by Generic Font Family.</strong>', array(
      '@url' => url('http://www.w3schools.com/cssref/css_websafe_fonts.asp'),
    )),
    '#title' => t('Font-family Fallback List'),
    '#field_prefix' => array_shift($fallback) . ', ',
    '#default_value' => fonts_od_implode($fallback),
  );

  $form['actions']['submit'] = array(
    '#type' => 'submit',
    '#value' => t('Update'),
    '#name' => 'update',
  );

  if (fonts_od_load($info['name'])) {
    $form['actions']['revert'] = array(
      '#type' => 'submit',
      '#name' => 'revert',
      '#value' => t('Revert to Defaults'),
      '#limit_validation_erros' => array(),
    );
  }

  return $form;
}

/**
 * Form submission handler for fonts_od_edit_form().
 *
 * @see fonts_od_edit_form()
 * @see fonts_od_edit_form_validate()
 */
function fonts_od_edit_form_submit($form, &$form_state) {
  switch ($form_state['clicked_button']['#name']) {
    case 'revert':
      db_delete('fonts_od')
        ->condition('name', $form_state['values']['db']['name'])
        ->execute();
      drupal_set_message(t('The overridden values for %name have been removed.', array(
        '%name' => $form_state['values']['db']['title'],
      )));
      break;
    default:
      $form_state['values']['db']['fallback'] = array_filter(explode(',', $form_state['values']['db']['fallback']));
      fonts_od_save($form_state['values']['db']);
      drupal_set_message(t('The overridden values have been saved.'));
      break;
  }
}
