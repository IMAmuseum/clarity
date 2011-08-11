<?php

class ClarityTextDatasource implements DatasourceIfc, DatasourceStatIfc {


  public static function getDataFormFields($stat, $index, $assignment_id = null) {

    $delta = _clarity_datasources_delta_for_index($stat, $index);

    $label = t('Text');
    if ($stat->field_datasources['und'][$delta]['label']) {
      $label = $stat->field_datasources['und'][$delta]['label'];
    }

    $result = db_select('clarity_value_text', 'f')
              ->fields('f')
              ->condition('assignment_id', $assignment_id, '=')
              ->condition('field_index', $index, '=')
              ->execute();

    $default = null;
    if ($record = $result->fetchAssoc()) {
      $default = $record['value'];
    }

    $fields['text-value'] = array(
      '#type' => 'textfield',
      '#title' => $label,
      '#description' => $stat->field_datasources['und'][$delta]['config']['description'],
      '#required' => true,
      '#default_value' => $default
    );

    return $fields;

  }


  public static function validateDataFormFields($field_id_prefix, $field_values, $index) { }


  public static function submitDataFormFields($field_values, $assignment_id, $index) {

    db_query('REPLACE INTO {clarity_value_text} (assignment_id, value, field_index) VALUES (:aid, :val, :index)',
             array(':aid' => $assignment_id,
                   ':val' => $field_values['text-value'],
                   ':index' => $index));

  }


  public static function getStatConfigFormFields($stat) {

    $fields['description'] = array(
      '#type'     => 'textfield',
      '#title'    => 'Description',
      '#description'  => 'Enter the description for the field',
      '#required'   => TRUE
    );

    return $fields;

  }


  public static function validateStatConfigForm($stat) { }


  public static function getDataType() {
    return 'text';
  }


  public static function getData($stat_nid, $options = array()) {

    $q = 'SELECT * FROM {clarity_value_text} f
          INNER JOIN {assignment} as a ON f.assignment_id = a.aid
          WHERE a.sid = :stat';
    $args = array(':stat' => $stat_nid);

    if (isset($options['index'])) {
      $q .=  ' AND f.field_index = :index';
      $args[':index'] = $options['index'];
    }

    if (isset($options['uid'])) {
      $q .= ' AND a.uid = :uid';
      $args[':uid'] = $options['uid'];
    }

    $result = db_query($q, $args);
    $data = array();
    foreach($result as $record) {
      $data[$record->assignment_id] = $record->value;
    }

    return $data;

  }


  public static function getLatestValueContent($stat_nid, $index) {

    $q = 'SELECT * FROM {clarity_value_text} f
          INNER JOIN {assignment} as a ON f.assignment_id = a.aid
          WHERE a.sid = :stat AND f.field_index = :index ORDER BY expire_date DESC LIMIT 1';
    $args = array(':stat' => $stat_nid, ':index' => $index);
    $record =  db_query($q, $args)->fetchAssoc();

    $stat = node_load($stat_nid);
    $delta = _clarity_datasource_delta_for_index($stat, $index);
    $ds = $stat->field_datasources['und'][$delta];
    $content = "<div class='latest-value'>";
    $content .= "<span class='label'>{$ds['label']}:</span> ";
    $content .= "<span class='value'>{$record['value']}</span></div>";
    return $content;

  }


  public static function getDataTableHeaderInfo($stat_nid, $index) {

    $stat = node_load($stat_nid);
    $delta = _clarity_datasources_delta_for_index($stat, $index);
    return array('(' . $stat->field_datasources['und'][$delta]['label'] . ')');

  }


  public static function getDataTableColumnContent($stat_nid, $index, $options = array()) {

    $query = db_select('clarity_value_text', 'v');
    $query->join('assignment', 'a', 'v.assignment_id = a.aid');

    $results = $query->fields('v')
                     ->condition('sid', $stat_nid, '=')
                     ->condition('field_index', $index)
                     ->execute();

    $content = array();
    while($result = $results->fetchAssoc()) {
      $content[$result['assignment_id']] = $result['value'];
    }

    return $content;

  }


}