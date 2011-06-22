<?php

/**
 * This interface must be defined by a Datasource.
 */
interface iDatasource {

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

}


abstract class Datasource implements iDatasource {

  // These methods do not have to be overridden (e.g. the datasource does not have categories)
  public static function assignmentFormFields(&$form, &$form_state, $form_id) {}
  public static function onAssignmentInsert($assignment) {}
  public static function onAssignmentLoad($assignment) {}
  public static function onAssignmentPresave($assignment) {}
  public static function onAssignmentUpdate($assignment) {}

}