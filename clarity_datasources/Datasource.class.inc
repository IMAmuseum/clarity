<?php

/**
 * This interface must be defined by a Datasource.
 */
interface DatasourceIfc {


  /**
   * A function to get fields for the data entry form.
   */
  static function getDataFormFields($stat, $delta);

  /**
   * A function to validate data entry form fields.
   */
  static function validateDataFormFields($fieldset_id_prefix, $field_values, $delta);

  /**
   * A function to submit data entry form field values.
   */
  static function submitDataFormFields($field_values, $assignment_id, $delta);



  /**
   * A function to fetch all data for a stat
   * Returns an array of Data objects
   */
  static function getData($stat_id, $options = array());

  /**
   * A function to create the data table for a stat
   * Returns the content for the data table
   */
  static function createDataTable($stat_id);

  /**
   * Returns an associative array of content for the data table
   * @param unknown_type $stat_nid
   * @param unknown_type $delta
   * @param unknown_type $options
   */
  static function getDataTableHeaderInfo($stat_id, $delta);


  static function getDataTableColumnContent($stat_nid, $delta, $options = array());

}


interface DatasourceStatIfc {

  public static function getStatConfigFormFields($stat);
  public static function validateStatConfigForm($stat);

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


