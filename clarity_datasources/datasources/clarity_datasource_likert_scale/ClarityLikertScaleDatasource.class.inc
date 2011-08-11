<?php

class ClarityLikertScaleDatasource implements DatasourceIfc {

  public static $scale = array(
      1 => 'strongly disagree',
      2 => 'disagree',
      3 => 'neutral',
      4 => 'agree',
      5 => 'strongly agree'
  );

  /**
  * A function to get fields for the data entry form.
  */
  public static function getDataFormFields($stat, $index, $assignment_id = null)
  {

    $result = db_select('clarity_value_likert_scale', 'f')
              ->fields('f')
              ->condition('assignment_id', $assignment_id, '=')
              ->condition('field_index', $index, '=')
              ->execute();

    $default = null;
    if ($record = $result->fetchAssoc()) {
      $default = $record['value'];
    }

    $fields['likert-scale'] = array(
      '#title'   => '',
      '#type'    => 'radios',
      '#options' => self::$scale,
      '#default_value' => $default
    );

    return $fields;

  }

  /**
  * A function to validate the data entry form.
  */
  public static function validateDataFormFields($field_id_prefix, $field_values, $index)
  {

      if (!is_numeric($field_values['likert-scale']) && array_key_exists($field_values['likert-scale'], self::$scale)) {
          form_set_error('likert-scale', t('Please select a value'));
      }
  }

  /**
  * A function to submit data from the data entry form.
  */
  public static function submitDataFormFields($field_values, $assignment_id, $index)
  {

      db_query('REPLACE INTO {clarity_value_likert_scale} (assignment_id, value, field_index) VALUES (:aid, :val, :index)',
               array(':aid' => $assignment_id,
                     ':val' => $field_values['likert-scale'],
                     ':index' => $index));

  }


  public static function getDataType() {
    return 'enum';
  }


  /**
   * @param Int   $stat_nid
   * @param Array $options
   *              Set string_value = true to get the string value
   */
  public static function getData($stat_nid, $options = array()) {

    $q = 'SELECT * FROM {clarity_value_likert_scale} f
          INNER JOIN {assignment} as a ON f.assignment_id = a.aid
          WHERE a.sid = :stat';
    $args = array(':stat' => $stat_nid);

    if (isset($options['index'])) {
      $q .=  ' AND f.field_index = :index';
      $args[':index'] = $options['index'];
    }

    if (isset($options['uid'])) {
      $q .= ' AND a.uid = :uid';
      $args[':uid'] = $options['uid'];
    }

    $result = db_query($q, $args);
    $data = array();
    foreach($result as $record) {
      if (isset($options['string_value']) && $options['string_value']) {
        $data[$record->assignment_id] = self::$scale[$record->value];
      } else {
        $data[$record->assignment_id] = $record->value;
      }
    }

    return $data;

  }


  public static function getLatestValueContent($stat_nid, $index) {

    $q = 'SELECT * FROM {clarity_value_likert_scale} f
          INNER JOIN {assignment} as a ON f.assignment_id = a.aid
          WHERE a.sid = :stat AND f.field_index = :index ORDER BY expire_date DESC LIMIT 1';
    $args = array(':stat' => $stat_nid, ':index' => $index);
    $record =  db_query($q, $args)->fetchAssoc();

    $stat = node_load($stat_nid);
    $delta = _clarity_datasource_delta_for_index($stat, $index);
    $ds = $stat->field_datasources['und'][$delta];
    $content  = "<div class='latest-value'>";
    $content .= "<span class='label'>{$ds['label']}:</span> ";
    $content .= "<span class='value'>" . self::$scale[$record['value']] . "</span></div>";
    return $content;

  }


  public static function getDataTableHeaderInfo($stat_nid, $index) {

    return array(null);

  }


  public static function getDataTableColumnContent($stat_nid, $index, $options = array()) {

    $query = db_select('clarity_value_likert_scale', 'v');
    $query->join('assignment', 'a', 'v.assignment_id = a.aid');

    $results = $query->fields('v')
                     ->condition('sid', $stat_nid, '=')
                     ->condition('field_index', $index)
                     ->execute();

    $content = array();
    while($result = $results->fetchAssoc()) {
      $content[$result['assignment_id']] = self::$scale[$result['value']];
    }

    return $content;

  }

}