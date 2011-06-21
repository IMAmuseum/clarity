<?php

abstract class Datasource {

  abstract public static function getDataFormFields($stat);
  abstract public static function validateDataForm($form, $form_state);
  abstract public static function submitDataForm($form, $form_state);

}