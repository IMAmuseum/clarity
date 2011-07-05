<?php

class ClarityFloatDatasource implements DatasourceIfc, DatasourceAssignmentIfc, DatasourceStatIfc {


  public static function getDataFormFields($stat) {

    $fields['single-value'] = array(
      '#type' => 'textfield',
      '#title' => t('Value'),
      '#description' => $stat->field_unit['und'][0]['value'],
      '#required' => true
    );

    $fields['annotation'] = array(
      '#type' => 'textfield',
      '#title' => t('Annotation'),
      '#description' => t('An optional annotation for this entry')
    );

    return $fields;

  }


  public static function validateDataForm($form, $form_state) {

    if (!is_numeric($form_state['values']['single-value'])) {
      form_set_error('single-value', t('Please enter a numeric value'));
    }

  }


  public static function submitDataForm($form, $form_state) {

    global $user;

    try {

      $result = db_insert('clarity_value_float')->fields(array(
        'stat_nid'      => $form_state['values']['assignment']->sid,
        'uid'           => $user->uid,
        'timestamp'     => $form_state['values']['assignment']->expire_date,
        'value'         => $form_state['values']['single-value'],
        'annotation'    => $form_state['values']['annotation'],
        'modified_time' => time()
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

    $fields['single-value'] = array(
      '#type' => 'textfield',
      '#title' => t('test'),
      '#description' => 'foo',
      '#required' => true
    );

    return $fields;

  }

  public static function validateStatConfigForm($stat) {


  }

  public static function getData($stat_nid, $options = array()) {

    $q = 'SELECT * FROM {clarity_value_float} WHERE stat_nid = :stat';
    $args = array(':stat' => $stat_nid);

    if (isset($options['uid'])) {
      $q .= ' AND uid = :uid';
      $args[':uid'] = $options['uid'];
    }

    $result = db_query($q, $args);
    $data = array();
    foreach($result as $record) {
      $d = new Data($record->uid, $record->timestamp, $record->value);
      $d->modified_time = $record->modified_time;
      $d->category = $record->category;
      $d->annotation = $record->annotation;
      $data[] = $d;
    }

    return $data;

  }


  public static function createDataTable($stat_nid) {

    $data = ClarityFloatDatasource::getData($stat_nid);

    return theme('clarity_single_value_table', array('data' => $data));


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