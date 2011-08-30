<?php

class ClarityMultiTermDatasource implements DatasourceIfc, DatasourceStatIfc {


  public static function getStatConfigFormFields($stat) {

    $vocabs = taxonomy_get_vocabularies();
    foreach($vocabs as $vocab) {
      $vocab_options[$vocab->vid] = $vocab->name;
    }

    $fields['vocabulary'] = array(
      '#type' => 'select',
      '#options' => $vocab_options,
      '#description' => 'The set of options for this stat',
      '#required' => true
    );

    $fields['minimum'] = array(
      '#type' => 'textfield',
      '#default_value' => 1,
      '#description' => t('The minimum number of options to allow'),
      '#required' => true
    );

    $fields['maximum'] = array(
      '#type' => 'textfield',
      '#default_value' => 1,
      '#description' => t('The maximum number of options to allow'),
      '#required' => true
    );

    return $fields;

  }


  public static function validateStatConfigForm($values) {

    if (!is_numeric($values['minimum']) || ($values['minimum'] < 0)) {
      form_set_error('minimum', t('Minimum must be a non-negative number'));
    }

    if (!is_numeric($values['maximum']) || ($values['maximum'] < 0)) {
      form_set_error('maximum', t('Maximum must be a non-negative number'));
    }

    if ($values['minimum'] > $values['maximum']) {
      form_set_error('maximum', t('Maximum is less than minimum'));
    }

  }


  public static function getDataFormFields($stat, $index, $assignment_id = null) {

    $delta = _clarity_datasources_delta_for_index($stat, $index);

    $vid = $stat->field_datasources['und'][$delta]['config']['vocabulary'];
    $taxonomy = taxonomy_vocabulary_load($vid);
    $terms = taxonomy_get_tree($vid, $parent = 0, $max_depth = 1);

    $type = ($stat->field_datasources['und'][$delta]['config']['maximum'] == 1) ? 'radios' : 'checkboxes';
    $required = !($stat->field_datasources['und'][$delta]['config']['minimum'] == 0);

    $options = array();
    if (($type == 'radios') && !$required) $options[null] = t('None');

    foreach($terms as $term) {
      $options[$term->tid] = $term->name;
    }

    $fields['terms'] = array(
      '#type' => $type,
      '#title' => t($taxonomy->name),
      '#options' => $options,
      '#description' => t('Select terms'),
      '#required' => $required
    );

    return $fields;

  }


  public static function validateDataFormFields($field_id_prefix, $field_values, $index) { }

  public static function submitDataFormFields($field_values, $assignment_id, $index) { }

  public static function getDataType() {
    return 'term';
  }


  public static function getData($stat_nid, $options = array()) { return array(); }


  public static function getLatestValueContent($stat_nid, $index) { return 0; }


  public static function getDataTableHeaderInfo($stat_nid, $index) {

    return array(null);

  }


  public static function getDataTableColumnContent($stat_nid, $index, $options = array()) { return null; }


  /*
  public static function validateDataForm($form, $form_state) {

    if (!isset($form_state['values']['terms'])) {
      form_set_error('terms', t('Please select a value'));
    }

  }


  public static function submitDataForm($form, $form_state) {

    try {
      $result = db_insert('clarity_multi_term')->fields(array(
        'aid'      => $form_state['values']['assignment']->aid,
        'value'         => $term,
      ))->execute();

    } catch (PDOException $e) {

      watchdog_exception('data_submission', $e);
      if (($e->errorInfo[0] == 23000) && $e->errorInfo[1] == 1062) {
        drupal_set_message(t('An entry for this assignment already exists'), 'warning');
      } else {
        drupal_set_message(t('The system was unable to record this value'), 'warning');
      }

    }

  }*/

/*
  public static function getData($stat_nid, $options = array()) {

    $q = 'SELECT * FROM {clarity_multi_term} WHERE stat_nid = :stat';
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
 */




  /*
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
  */

}