<?php

function form_type_tableradios_value($element, $input = FALSE) {
  if (isset($element['#multiple']) && $element['#multiple']) {
    if ($input === FALSE) {
      $value = array();
      $element += array('#default_value' => array());
      foreach ($element['#default_value'] as $key => $flag) {
        if ($flag) {
          $value[$key] = $key;
        }
      }
      return $value;
    }
    else {
      return is_array($input) ? drupal_map_assoc($input) : array();
    }
  }
}

function theme_tableradios($variables)
{
  /*foreach($variables['element']['#parents'] as $item){
    $table_id = $item ;
  }*/
  unset($item);
  //print_r($variables);
  $element = $variables['element'];
  $rows = array();
  $header = $element['#header'];
  //print_r($element['#options']);
  if (!empty($element['#options'])) {
    $last_element = count($element['#header']);
    $count = 1;
    foreach ($element['#header'] as $key => $item) {
      if ($count == $last_element) {
        $last_element = $key;
      }
      $count++;
    }
    unset($key);
    unset($item);
    foreach (element_children($element) as $key) {
      $row = array();
      $row['data'] = array();
      if (isset($element['#options'][$key]['#attributes'])) {
        $row += $element['#options'][$key]['#attributes'];
      }
      $first_element = TRUE;
      $colspan = FALSE;
      foreach ($element['#header'] as $fieldname => $title) {
        if ($colspan) {
          $row['data'][] = array(
            'colspan' => count($element['#header']) + 1,
            'data' => $element['#options'][$key][$fieldname],
          );
          $colspan = FALSE;
        }
        else {
          if ($element['#options'][$key][$fieldname] == 'colspan') {
            $colspan = TRUE;
          }	elseif ($element['#options'][$key][$fieldname] != 'empty') {
            if ($first_element) {// Render the checkbox / radio element.
              $row['data'][] = array(
                'class' => 'tariff-change-row-first',
                'data' => drupal_render($element[$key]),
              );
              $row['data'][] = $element['#options'][$key][$fieldname];
              $first_element = FALSE;
            }elseif ($last_element == $fieldname) {
              $row['data'][] = array(
                'class' => 'tariff-change-row-last',
                'data' => $element['#options'][$key][$fieldname],
              );
            }	else {
              $row['data'][] = $element['#options'][$key][$fieldname];
            }
          }
        }
      }
      //print_r($row);
      $rows[] = $row;
    }
    array_unshift($header, '');
  }
  //return '<div id="'. $table_id .'" class="form-item form-type-item">'.theme('table', array('header' => $header, 'rows' => $rows, 'empty' => $element['#empty'], 'attributes' => $element['#attributes'])).'</div>';
  return '<div class="form-item form-type-item">'.theme('table', array('header' => $header, 'rows' => $rows, 'empty' => $element['#empty'], 'attributes' => $element['#attributes'])).'</div>';
}

function form_process_tableradios($element) {

  $value = is_array($element['#value']) ? $element['#value'] : array();

  $element['#tree'] = TRUE;

  if (count($element['#options']) > 0) {
    if (!isset($element['#default_value']) || $element['#default_value'] === 0) {
      $element['#default_value'] = array();
    }
    foreach ($element['#options'] as $key => $choice) {
      if (!isset($element[$key])) {
        if ($element['#multiple']) {
          $title = '';
          if (!empty($element['#options'][$key]['title']['data']['#title'])) {
            $title = t('Update @title', array(
              '@title' => $element['#options'][$key]['title']['data']['#title'],
            ));
          }
          /*$element[$key] = array(
            '#type' => 'radio',
            '#title' => $title,
            '#description' => '&nbsp',
            '#title_display' => 'invisible',
            '#return_value' => $key,
            '#default_value' => isset($value[$key]) ? $key : NULL,
            '#attributes' => $element['#attributes'],
            '#ajax' => isset($element['#ajax']) ? $element['#ajax'] : NULL,
          );*/
          $element[$key] = array(
            '#type' => 'checkbox',
            '#title' => $title,
            '#description' => '&nbsp',
            '#title_display' => 'invisible',
            '#return_value' => $key,
            '#id' => 'edit-' . $key,
            '#default_value' => isset($value[$key]) ? $key : NULL,
            '#attributes' => $element['#attributes'],
            '#ajax' => isset($element['#ajax']) ? $element['#ajax'] : NULL,
          );
        }
        else {
          $parents_for_id = array_merge($element['#parents'], array($key));
          $element[$key] = array(
            '#type' => 'radio',
            '#description' => '&nbsp',
            '#title' => '',
            '#return_value' => $key,
            '#default_value' => ($element['#default_value'] == $key) ? $key : NULL,
            '#attributes' => $element['#attributes'],
            '#parents' => $element['#parents'],
            '#id' => 'edit-' . $key,
            '#ajax' => isset($element['#ajax']) ? $element['#ajax'] : NULL,
          );
        }
        if (isset($element['#options'][$key]['#weight'])) {
          $element[$key]['#weight'] = $element['#options'][$key]['#weight'];
        }
      }
    }
  }
  else {
    $element['#value'] = array();
  }
  return $element;
}
