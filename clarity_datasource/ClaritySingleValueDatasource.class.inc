<?php

class ClaritySingleValueDatasource extends Datasource {


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

      $result = db_insert('clarity_value_single_float')->fields(array(
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


  public static function assignmentFormFields(&$form, &$form_state, $form_id) {

    $data_cat = new TaxonomyCategory();
    $data_cat->assignmentFormFields($form, $form_state, $form_id);
    unset($data_cat);

  }


  public static function onAssignmentLoad($assignments) {

    foreach ($assignments as $assignment) {
      $result = db_query("SELECT tid
                          FROM {assignment_terms}
                          WHERE aid = :aid", array(':aid' => $assignment->aid));
      $terms = array();
      foreach($result as $row) {
          array_push($terms, $row->tid);
      }
      $assignment->terms = $terms;
    }

  }


  public static function onAssignmentPresave($assignment) {

    // remove all previously selected terms
    $result = db_query("DELETE FROM {assignment_terms}
                        WHERE aid = :aid", array(':aid' => $assignment->aid));

  }


  public static function onAssignmentUpdate($assignment) {

    if(isset($assignment->terms)) {
      foreach($assignment->terms as $term) {
          $assignment_terms = new stdClass();
          $assignment_terms->aid = $assignment->aid;
          $assignment_terms->tid = $term;
          drupal_write_record('assignment_terms', $assignment_terms);
      }
    }

  }


  public static function onAssignmentInsert($assignment) {

    if(isset($assignment->terms)) {
      foreach($assignment->terms as $term) {
        $assignment_terms = new stdClass();
        $assignment_terms->aid = $assignment->aid;
        $assignment_terms->tid = $term;
        drupal_write_record('assignment_terms', $assignment_terms);
      }
    }

  }

}