<?php

/**
 * This interface must be defined by a Datasource.
 */
interface DatasourceIfc {


  /**
   * A function to get fields for the data entry form.
   * @return An array of fields
   */
  static function getDataFormFields($stat, $index, $assignment_id = null);

  /**
   * A function to validate data entry form fields.
   */
  static function validateDataFormFields($fieldset_id_prefix, $field_values, $index);

  /**
   * A function to submit data entry form field values.
   */
  static function submitDataFormFields($field_values, $assignment_id, $index);



  /**
   * A function to fetch all data for a stat
   * Returns an array of Data objects
   */
  static function getData($stat_id, $options = array());


  /**
   *
   * A function to get the content to display for the latest value
   * @param $stat_id
   */
  static function getLatestValueContent($stat_id, $index);



  /**
   * A function to fetch info for the data table header
   * @return An array of header sub-labels
   */
  static function getDataTableHeaderInfo($stat_id, $index);

  /**
   * A function to fetch data table content
   * @param array $options (TBD)
   * @return An array of the form: array(assignment_id => content)
   */
  static function getDataTableColumnContent($stat_nid, $index, $options = array());

}


/**
 * Datasources which allow configuration for individual stats should implement this interface
 */
interface DatasourceStatIfc {

  /**
   * A function to get fields for the datasource config form for a stat
   * @return An array of fields
   */
  public static function getStatConfigFormFields($stat);

  public static function validateStatConfigForm($stat);

}


/**
 * Datasources which add configuration options for assignments should implement this interface
 */
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


