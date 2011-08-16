<?php

class ClarityFloatDatasource implements DatasourceIfc, DatasourceStatIfc {


  /**
   * Applies formatting to a value
   */
  private static function formatValue($format, $value) {

    switch($format) {

      case 'money':
        return '$' . number_format($value, 2);
        break;

      default:
        return $value;

    }

  }


  public static function getDataFormFields($stat, $index, $assignment_id = null) {

    $delta = _clarity_datasources_delta_for_index($stat, $index);

    $result = db_select('clarity_value_float', 'f')
              ->fields('f')
              ->condition('assignment_id', $assignment_id, '=')
              ->condition('field_index', $index, '=')
              ->execute();

    $default = null;
    if ($record = $result->fetchAssoc()) {
      $default = $record['value'];
    }

    $fields['single-value'] = array(
      '#type' => 'textfield',
      '#title' => t('Value'),
      '#description' => $stat->field_datasources['und'][$delta]['config']['unit'],
      '#required' => true,
      '#default_value' => $default
    );

    return $fields;

  }


  public static function validateDataFormFields($field_id_prefix, $field_values, $index) {

    if (!is_numeric($field_values['single-value'])) {
        form_set_error($field_id_prefix . 'single-value', t('Please enter a numeric value'));
    }

  }


  public static function submitDataFormFields($field_values, $assignment_id, $index) {

    db_query('REPLACE INTO {clarity_value_float} (assignment_id, value, field_index) VALUES (:aid, :val, :index)',
             array(':aid' => $assignment_id,
                   ':val' => $field_values['single-value'],
                   ':index' => $index));

  }


  public static function getStatConfigFormFields($stat) {

    $fields['unit'] = array(
      '#type' => 'textfield',
      '#title' => t('Unit'),
      '#description' => 'The unit of measure for this value',
      '#required' => true
    );


    $format_options = array(
      null => 'None',
      'money' => '$1,000.00'
    );

    $fields['formatting'] = array(
      '#type' => 'select',
      '#options' => $format_options,
      '#description' => 'Special formatting for this value'
    );

    return $fields;

  }


  public static function validateStatConfigForm($stat) {

  }


  public static function getDataType() {
    return 'float';
  }


  public static function getData($stat_nid, $options = array()) {

    $q = 'SELECT * FROM {clarity_value_float} f
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

    $q = 'SELECT * FROM {clarity_value_float} f
          INNER JOIN {assignment} as a ON f.assignment_id = a.aid
          WHERE a.sid = :stat AND f.field_index = :index ORDER BY expire_date DESC LIMIT 1';
    $args = array(':stat' => $stat_nid, ':index' => $index);
    $record =  db_query($q, $args)->fetchAssoc();

    $stat = node_load($stat_nid);
    $delta = _clarity_datasource_delta_for_index($stat, $index);
    $ds = $stat->field_datasources['und'][$delta];
    $content  = "<div class='latest-value'>";
    $content .= "<span class='label'>{$ds['label']}:</span> ";
    $content .= "<span class='value'>{$record['value']}</span> ";
    $content .= "<span class='suffix'>{$ds['config']['unit']}</span></div>";
    return $content;

  }


  public static function getDataTableHeaderInfo($stat_nid, $index) {

    $stat = node_load($stat_nid);
    $delta = _clarity_datasources_delta_for_index($stat, $index);
    return array('(' . $stat->field_datasources['und'][$delta]['config']['unit'] . ')');

  }


  public static function getDataTableColumnContent($stat_nid, $index, $options = array()) {

    $stat = node_load($stat_nid);
    $delta = _clarity_datasources_delta_for_index($stat, $index);
    $format = $stat->field_datasources['und'][$delta]['config']['formatting'];

    $query = db_select('clarity_value_float', 'v');
    $query->join('assignment', 'a', 'v.assignment_id = a.aid');

    $results = $query->fields('v')
                     ->condition('sid', $stat_nid, '=')
                     ->condition('field_index', $index)
                     ->execute();

    $content = array();
    while($result = $results->fetchAssoc()) {
      $content[$result['assignment_id']] = self::formatValue($format, $result['value']);
    }

    return $content;

  }


  public static function assignmentFormFields(&$form, &$form_state, $form_id) {

    $node = node_load($form['sid']['#value']);
    $items = field_get_items('node', $node, 'field_categories');
    $vid = $items[0]['value'];
    $term_options = AssignmentTaxonomyCategory::getTermsForVocabulary($vid);

    if(!empty($term_options)) {
      $vocab = taxonomy_vocabulary_load($vid);
      $form['terms'] = array(
        '#type'         => 'select',
        '#title'        => t($vocab->name),
        '#options'      => $term_options,
        '#multiple'     => TRUE,
        '#required'      => TRUE
      );
    } else {

      return;

    }

    if ($form_id == 'assignment_form_edit')  {
      $assignment = assignment_load($form['aid']['#value']);
      if(!empty($term_options)) {
        $form['terms']['#default_value'] = $assignment->terms;
      }
    }

  }


  public static function onAssignmentLoad($assignments) {

    foreach ($assignments as $assignment) {
      $assignment->terms = AssignmentTaxonomyCategory::loadCategories($assignment->aid);
    }

  }


  public static function onAssignmentPresave($assignment) {

    AssignmentTaxonomyCategory::clearCategories($assignment->aid);

  }


  public static function onAssignmentUpdate($assignment) {

    if(isset($assignment->terms)) {
      AssignmentTaxonomyCategory::saveCategories($assignment->aid, $assignment->terms);
    }

  }


  public static function onAssignmentInsert($assignment) {

    if(isset($assignment->terms)) {
      AssignmentTaxonomyCategory::saveCategories($assignment->aid, $assignment->terms);
    }

  }

}