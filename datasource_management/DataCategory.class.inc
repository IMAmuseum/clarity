<?php

abstract class DataCategory {

  abstract public static function assignmentFormFields(&$form, &$form_state, $form_id);

  abstract public static function onAssignmentInsert($assignment);
  abstract public static function onAssignmentLoad($assignment);
  abstract public static function onAssignmentPresave($assignment);
  abstract public static function onAssignmentUpdate($assignment);


}