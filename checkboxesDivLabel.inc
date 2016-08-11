<?php

function form_type_checkboxesDivLabel_value($element, $input = FALSE) {
  if ($input === FALSE) {
    $value = array();
    $element += array('#default_value' => array());
    foreach ($element['#default_value'] as $key) {
      $value[$key] = $key;
    }
    return $value;
  }
  elseif (is_array($input)) {
    foreach ($input as $key => $value) {
      if (!isset($value)) {
        unset($input[$key]);
      }
    }
    return drupal_map_assoc($input);
  }
  else {
    return array();
  }
}

function theme_checkboxesDivLabel($variables) {
  $element = $variables['element'];
  $attributes = array();
  if (isset($element['#id'])) {
    $attributes['id'] = $element['#id'];
  }
  $attributes['class'][] = 'form-checkboxes';
  if (!empty($element['#attributes']['class'])) {
    $attributes['class'] = array_merge($attributes['class'], $element['#attributes']['class']);
  }
  if (isset($element['#attributes']['title'])) {
    $attributes['title'] = $element['#attributes']['title'];
  }
  return '<div' . drupal_attributes($attributes) . '>' . (!empty($element['#children']) ? $element['#children'] : '') . '</div>';
}

function form_process_checkboxesDivLabel($element) {
  $value = is_array($element['#value']) ? $element['#value'] : array();
  $element['#tree'] = TRUE;
  if (count($element['#options']) > 0) {
    if (!isset($element['#default_value']) || $element['#default_value'] == 0) {
      $element['#default_value'] = array();
    }
    $weight = 0;
    foreach ($element['#options'] as $key => $choice) {
      if ($key === 0) {
        $key = '0';
      }
      $weight += 0.001;

      $element += array($key => array());
      $choice = explode('</>',$choice);
      $element[$key] += array(
        '#type' => 'checkbox',
        '#title' => 'Выбрать',
        //'#id' => $key,
        '#prefix' => $choice[0],
        '#suffix' => $choice[1],
        '#return_value' => $key,
        '#default_value' => isset($value[$key]) ? $key : NULL,
        '#attributes' => array('class' => array('checkbox'),),//$element['#attributes'],
        '#ajax' => isset($element['#ajax']) ? $element['#ajax'] : NULL,
        '#weight' => $weight,
      );
    }
  }
  return $element;
}