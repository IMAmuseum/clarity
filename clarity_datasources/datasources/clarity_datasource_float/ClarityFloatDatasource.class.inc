<?php

class ClarityFloatDatasource implements DatasourceIfc, DatasourceStatIfc {


  public static function getDataFormFields($stat, $delta) {

    $fields['single-value'] = array(
      '#type' => 'textfield',
      '#title' => t('Value'),
      '#description' => $stat->field_datasources['und'][$delta]['config']['unit'],
      '#required' => true
    );

    return $fields;

  }

  // DEPRECATED
  public static function validateDataForm($form, $form_state) {

    foreach($form_state['values']['datasources'] as $delta => $ds_fieldset) {

      if (!is_numeric($ds_fieldset['data_fields']['single-value'])) {
        form_set_error("datasources][$delta][data_fields][single-value", t('Please enter a numeric value'));
      }

    }

  }


  public static function validateDataFormFields($field_id_prefix, $field_values, $delta) {

    if (!is_numeric($field_values['single-value'])) {
        form_set_error($field_id_prefix . 'single-value', t('Please enter a numeric value'));
    }

  }


  public static function submitDataFormFields($field_values, $assignment_id, $delta) {

    global $user;

    try {

      $result = db_insert('clarity_value_float')->fields(array(
        'assignment_id' => $assignment_id,
        'value'         => $field_values['single-value'],
        'delta'         => $delta
      ))->execute();

    } catch (PDOException $e) {

      watchdog_exception('data_submission', $e);
      if (($e->errorInfo[0] == 23000) && $e->errorInfo[1] == 1062) {
        drupal_set_message(t('An entry for this assignment already exists'), 'warning');
      } else {
        drupal_set_message(t('The system was unable to record this value'), 'warning');
      }

    }

  }


  public static function getStatConfigFormFields($stat) {

    $fields['unit'] = array(
      '#type' => 'textfield',
      '#title' => t('Unit'),
      '#description' => 'The unit of measure for this value',
      '#required' => true
    );

    return $fields;

  }

  public static function validateStatConfigForm($stat) {

  }

  public static function getData($stat_nid, $options = array()) {

    $q = 'SELECT * FROM {clarity_value_float} f
          INNER JOIN {assignment} as a ON f.assignment_id = a.aid
          WHERE a.sid = :stat';
    $args = array(':stat' => $stat_nid);

    if (isset($options['uid'])) {
      $q .= ' AND a.uid = :uid';
      $args[':uid'] = $options['uid'];
    }

    $result = db_query($q, $args);
    $data = array();
    foreach($result as $record) {
      $d = new Data($record->uid, $record->expire_date, $record->value);
      $d->modified_time = $record->modified_time;
      $data[] = $d;
    }

    return $data;

  }


  public static function createDataTable($stat_nid) {

    $data = ClarityFloatDatasource::getData($stat_nid);

    return theme('clarity_float_table', array('data' => $data));


  }


  public static function getDataTableHeaderInfo($stat_nid, $delta) {

    $stat = node_load($stat_nid);
    return array('(' . $stat->field_datasources['und'][$delta]['config']['unit'] . ')');

  }


  public static function getDataTableColumnContent($stat_nid, $delta, $options = array()) {

    $query = db_select('clarity_value_float', 'v');
    $query->join('assignment', 'a', 'v.assignment_id = a.aid');

    $results = $query->fields('v')
                     ->condition('sid', $stat_nid, '=')
                     ->condition('delta', $delta)
                     ->execute();

    $content = array();
    while($result = $results->fetchAssoc()) {
      $content[$result['assignment_id']] = $result['value'];
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