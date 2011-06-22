<?php

interface iDataCategory {

  public function assignmentFormFields(&$form, &$form_state, $form_id);

  public static function onAssignmentInsert($assignment);
  public static function onAssignmentLoad($assignment);
  public static function onAssignmentPresave($assignment);
  public static function onAssignmentUpdate($assignment);

}

abstract class DataCategory implements iDataCategory {

  /*
  abstract public function assignmentFormFields(&$form, &$form_state, $form_id);

  abstract public static function onAssignmentInsert($assignment);
  abstract public static function onAssignmentLoad($assignment);
  abstract public static function onAssignmentPresave($assignment);
  abstract public static function onAssignmentUpdate($assignment);
  */


}