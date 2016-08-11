<?php

function form_type_radiosCredit_value(&$element, $input = FALSE) {
  if ($input !== FALSE) {
    if (!isset($input) && !empty($element['#default_value'])) {
      $element['#needs_validation'] = TRUE;
    }
    return $input;
  }
  else {
    $value = isset($element['#default_value']) ? $element['#default_value'] : NULL;
    if (!isset($value)) {
      $element['#has_garbage_value'] = TRUE;
    }
    return $value;
  }
}

function theme_radiosCredit($variables) {
  $element = $variables['element'];
  $attributes = array();
  if (isset($element['#id'])) {
    $attributes['id'] = $element['#id'];
  }
  $attributes['class'] = 'form-radios';
  if (!empty($element['#attributes']['class'])) {
    $attributes['class'] .= ' ' . implode(' ', $element['#attributes']['class']);
  }
  if (isset($element['#attributes']['title'])) {
    $attributes['title'] = $element['#attributes']['title'];
  }
  //return '<div' . drupal_attributes($attributes) . '>' . (!empty($element['#children']) ? $element['#children'] : '') . '</div>';
  return  !empty($element['#children']) ? $element['#children'] : '';
}

function form_process_radiosCredit($element) {
  if (count($element['#options']) > 0) {
    $weight = 0;
    foreach ($element['#options'] as $key => $choice) {
      $weight += 0.001;

      $element += array($key => array());
      $parents_for_id = array_merge($element['#parents'], array($key));
      //$choice = explode('</>',$choice);
      //print_r($choice);
      if($key != 'Вручную'){
        $element[$key] += array(
          '#type' => 'radioCredit',
          '#title' => $choice,//$choice
          '#prefix' => '
          <h3>'.$key.'</h3>
          <div class="input-group">
            <span class="input-group-addon">',//$choice[0],
          '#suffix' => '
            </span>
            <input readonly="" placeholder="'.$choice.' руб." id="readonly" class="form-control">
          </div>',//$choice[1],
          '#return_value' => $key,
          '#default_value' => isset($element['#default_value']) ? $element['#default_value'] : FALSE,
          //'#attributes' => array('class' => array('checkbox'),),//$element['#attributes'],
          '#parents' => $element['#parents'],
          '#id' => drupal_html_id('edit-' . implode('-', $parents_for_id)),//$key,//
          '#ajax' => isset($element['#ajax']) ? $element['#ajax'] : NULL,
          '#weight' => $weight,
        );
      }else{
        $element[$key] += array(
          '#type' => 'radioCredit',
          '#title' => $choice,//$choice
          '#prefix' => '
          <h3>'.$key.'</h3>
          <div class="input-group">
            <span class="input-group-addon">',//$choice[0],
          '#suffix' => '
            </span>',//$choice[1],
          '#return_value' => $key,
          '#default_value' => isset($element['#default_value']) ? $element['#default_value'] : FALSE,
          //'#attributes' => array('class' => array('checkbox'),),//$element['#attributes'],
          '#parents' => $element['#parents'],
          '#id' => drupal_html_id('edit-' . implode('-', $parents_for_id)),//$key,//
          '#ajax' => isset($element['#ajax']) ? $element['#ajax'] : NULL,
          '#weight' => $weight,
        );
      }
    }
  }
  return $element;
}
