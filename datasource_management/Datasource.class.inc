<?php

/**
 * This interface must be defined by a Datasource.
 */
interface DatasourceIfc {

  /**
   * A function to get fields for the data entry form.
   */
  static function getDataFormFields($stat);

  /**
   * A function to validate the data entry form.
   */
  static function validateDataForm($form, $form_state);

  /**
   * A function to submit data from the data entry form.
   */
  static function submitDataForm($form, $form_state);

  /**
   * A function to fetch all data for a stat
   * Returns an array of Data objects
   */
  static function getData($stat_id, $options);

  /**
   * A function to create the data table for a stat
   * Returns the content for the data table
   */
  static function createDataTable($stat_id);

}

interface DatasourceStatIfc {

  public static function getStatConfigFormFields($stat);
  public static function validateStatConfigData($stat);

}


interface DatasourceAssignmentIfc {

  public static function assignmentFormFields(&$form, &$form_state, $form_id);
  public static function onAssignmentInsert($assignment);
  public static function onAssignmentLoad($assignment);
  public static function onAssignmentPresave($assignment);
  public static function onAssignmentUpdate($assignment);

}


class Data {

    public $uid;
    public $timestamp;
    public $value;
    public $annotation = null;
    public $modified_time = 0;
    public $category = null;
    public $extra = array();

    public function Data($uid = null, $timestamp = 0, $value = null) {
      $this->uid = $uid;
      $this->timestamp = $timestamp;
      $this->value = $value;
    }

}


