<?php

class ClarityMultiTermDatasource implements DatasourceIfc, DatasourceStatIfc {


  public static function getStatConfigFormFields($stat) {

    $vocabs = taxonomy_get_vocabularies();
    foreach($vocabs as $vocab) {
      $vocab_options[$vocab->vid] = $vocab->name;
    }

    $fields['vocabulary'] = array(
      '#type' => 'select',
      '#options' => $vocab_options,
      '#description' => 'The set of options for this stat',
      '#required' => true
    );

    $fields['minimum'] = array(
      '#type' => 'textfield',
      '#default_value' => 1,
      '#description' => t('The minimum number of options to allow'),
      '#required' => false
    );

    $fields['maximum'] = array(
      '#type' => 'textfield',
      '#default_value' => 1,
      '#description' => t('The maximum number of options to allow'),
      '#required' => false
    );

    return $fields;

  }


  public static function validateStatConfigForm($values) {

    if (!empty($values['minimum']) && (!is_numeric($values['minimum']) || ($values['minimum'] < 0))) {
      form_set_error('minimum', t('Minimum must be a non-negative number'));
    }

    if (!empty($values['maximum']) && (!is_numeric($values['maximum']) || ($values['maximum'] < 0))) {
      form_set_error('maximum', t('Maximum must be a non-negative number'));
    }

    if (!empty($values['maximum']) && ($values['minimum'] > $values['maximum'])) {
      form_set_error('maximum', t('Maximum is less than minimum'));
    }

  }


  public static function getDataFormFields($stat, $index, $assignment_id = null) {

    $delta = _clarity_datasources_delta_for_index($stat, $index);

    $vid = $stat->field_datasources['und'][$delta]['config']['vocabulary'];
    $taxonomy = taxonomy_vocabulary_load($vid);
    $terms = taxonomy_get_tree($vid, $parent = 0, $max_depth = 1);
    $min = $stat->field_datasources['und'][$delta]['config']['minimum'];
    $max = $stat->field_datasources['und'][$delta]['config']['maximum'];

    $type = ($max == 1) ? 'radios' : 'checkboxes';
    $required = !($min == 0);

    $options = array();
    if (($type == 'radios') && !$required) $options[null] = t('None');

    // Figure out how to express the requirements
    if ($max == 1) {
      $description = t("Please select one item.");
    } else {
      if ($min == $max) {
        if (empty($min)) {
          $description = t("Please select any items that apply.");
        } else {
          $description = t("Please select @n items.", array('@n' => $min));
        }
      } else {
        if (empty($min)) {
          $description = t("Please select up to @max items.", array('@max' => $max));
        } else if (empty($max)) {
          $description = t("Please select @min or more items.", array('@min' => $min));
        } else {
          $description = t("Please select @min to @max items.", array('@min' => $min, '@max' => $max));
        }
      }
    }

    foreach($terms as $term) {
      $options[$term->tid] = $term->name;
    }

    // Define default value(s)
    $result = db_select('clarity_value_term', 't')
              ->fields('t')
              ->condition('assignment_id', $assignment_id, '=')
              ->condition('field_index', $index, '=')
              ->execute();
    $default = array();
    while ($record = $result->fetchAssoc()) {
      $default[] = $record['term_id'];
    }
    if ($type == 'radios') {
      $default = isset($default[0]) ? $default[0] : null;
    }

    $fields['terms'] = array(
      '#type' => $type,
      //'#title' => t($taxonomy->name),
      '#options' => $options,
      '#default_value' => $default,
      '#description' => $description,
      '#required' => $required
    );

    $fields['config'] = array(
      '#type' => 'value',
      '#value' => $stat->field_datasources['und'][$delta]['config']
    );

    return $fields;

  }


  public static function validateDataFormFields($field_id_prefix, $field_values, $index) {

    if (is_array($field_values['terms'])) {

      $count = 0;
      foreach($field_values['terms'] as $value) {
        if ($value) $count++;
      }

      $min = $field_values['config']['minimum'];
      $max = $field_values['config']['maximum'];

      if (($min == $max) && ($count != $min)) {
        if (empty($min)) return; // No requirements
        form_set_error('terms', t('Please select @n items.', array('@n' => $min)));
      } else if ($count < $min) {
        form_set_error('terms', t('Please select more items.'));
      } else if ($count > $max) {
        form_set_error('terms', t('Please select fewer items.'));
      }

    }

  }


  /**
   * Helper function to add values to the database
   */
  private static function submitDataFormValue($aid, $index, $tid) {

    db_query('REPLACE INTO {clarity_value_term} (assignment_id, term_id, field_index) VALUES (:aid, :term, :index)',
             array(':aid' => $aid, ':term' => $tid, ':index' => $index));

  }


  public static function submitDataFormFields($field_values, $assignment_id, $index) {

    // Clear out previous values
    db_delete('clarity_value_term')
      ->condition('assignment_id', $assignment_id)
      ->condition('field_index', $index)
      ->execute();

    if (is_numeric($field_values['terms'])) {
      self::submitDataFormValue($assignment_id, $index, $field_values['terms']);
      return;
    }

    if (is_array($field_values['terms'])) {
      foreach ($field_values['terms'] as $tid) {
        if ($tid) {
          self::submitDataFormValue($assignment_id, $index, $tid);
        }
      }
    }

  }

  public static function getDataType() {
    return 'term';
  }


  /**
   * @todo Figure out how this should work for term data
   */
  public static function getData($stat_nid, $options = array()) { return array(); }


  /**
   * @todo Figure out how this should work for term data
   */
  public static function getLatestValueContent($stat_nid, $index) { return 0; }


  public static function getDataTableHeaderInfo($stat_nid, $index) {

    return array(null);

  }


  public static function getDataTableColumnContent($stat_nid, $index, $options = array()) {

    $result = db_select('clarity_value_term', 't')
              ->fields('t')
              ->condition('field_index', $index, '=')
              ->execute();

    $results = array();
    while ($record = $result->fetchAssoc()) {
      $term = taxonomy_term_load($record['term_id']);
      $results[$record['assignment_id']][] = $term->name;
    }

    foreach($results as $aid => &$result) {
      $result = implode(', ', $result);
    }

    return $results;

  }


  /*
  public static function assignmentFormFields(&$form, &$form_state, $form_id) {

    $node = node_load($form['sid']['#value']);
    $items = field_get_items('node', $node, 'field_categories');
    $vid = $items[0]['value'];
    $term_options = AssignmentTaxonomyCategory::getTermsForVocabulary($vid);

    if(!empty($term_options)) {
      $vocab = taxonomy_vocabulary_load($vid);
      $form['terms'] = array(
        '#type'         => 'select',
        '#title'        => t($vocab->name),
        '#options'      => $term_options,
        '#multiple'     => TRUE,
        '#required'      => TRUE
      );
    } else {

      return;

    }

    if ($form_id == 'assignment_form_edit')  {
      $assignment = assignment_load($form['aid']['#value']);
      if(!empty($term_options)) {
        $form['terms']['#default_value'] = $assignment->terms;
      }
    }

  }


  public static function onAssignmentLoad($assignments) {

    foreach ($assignments as $assignment) {
      $assignment->terms = AssignmentTaxonomyCategory::loadCategories($assignment->aid);
    }

  }


  public static function onAssignmentPresave($assignment) {

    AssignmentTaxonomyCategory::clearCategories($assignment->aid);

  }


  public static function onAssignmentUpdate($assignment) {

    if(isset($assignment->terms)) {
      AssignmentTaxonomyCategory::saveCategories($assignment->aid, $assignment->terms);
    }

  }


  public static function onAssignmentInsert($assignment) {

    if(isset($assignment->terms)) {
      AssignmentTaxonomyCategory::saveCategories($assignment->aid, $assignment->terms);
    }

  }
  */

}