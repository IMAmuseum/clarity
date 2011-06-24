<?php

class ClarityDatasourceComment implements DatasourceIfc {


  public static function getDataFormFields($stat) {

    $fields['value'] = array(
      '#type' => 'textfield',
      '#title' => t('Comment'),
      '#description' => $stat->field_unit['und'][0]['value'],
      '#required' => true
    );

    return $fields;

  }


  public static function validateDataForm($form, $form_state) {

    /*
  	if (!is_numeric($form_state['values']['value'])) {
      form_set_error('single-value', t('Please enter a numeric value'));
    }
    */

  }


  public static function submitDataForm($form, $form_state) {

    global $user;

    try {

      $result = db_insert('clarity_datasource_comment')->fields(array(
        'stat_nid'      => $form_state['values']['assignment']->sid,
        'uid'           => $user->uid,
        'timestamp'     => $form_state['values']['assignment']->expire_date,
        'value'         => $form_state['values']['value'],
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


  public static function getData($stat_nid, $options = array()) {

    $q = 'SELECT * FROM {clarity_datasource_comment} WHERE stat_nid = :stat';
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
      $data[] = $d;
    }

    return $data;

  }


  public static function createDataTable($stat_nid) {

    $data = ClarityDatasourceComment::getData($stat_nid);

    return theme('clarity_single_value_table', array('data' => $data));


  }


 }