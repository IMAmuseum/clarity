<?php

class ClarityMultiTermDatasource implements DatasourceIfc, DatasourceAssignmentIfc {


  public static function getDataFormFields($stat) {
  	
  	$taxonomy = taxonomy_vocabulary_load($stat->field_categories['und'][0]['value']);
  	$terms = taxonomy_get_tree($stat->field_categories['und'][0]['value'], $parent = 0, $max_depth = 1);
  	$options = array();
  	foreach($terms as $term) {
  		$options[$term->tid] = $term->name;
  	}
  	
  	$fields['terms'] = array(
			'#type' => 'checkboxes',
  		'#title' => t($taxonomy->name),
  		'#options' => $options,
  		'#description' => $stat->field_unit['und'][0]['value'],
  		'#required' => true
  	);

    return $fields;

  }

  public static function getStatConfigFormFields($stat) {

  
  }

  public static function validateStatConfigForm($form, $form_state) {
  	
  }
  
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

  }


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


  public static function createDataTable($stat_nid) {

    $data = ClarityMultiTermDatasource::getData($stat_nid);

    return theme('clarity_multi_term_table', array('data' => $data));


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