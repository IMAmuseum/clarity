<?php

abstract class TaxonomyCategory extends DataCategory {


  private function getTermsForVocabulary($vid) {
    $result = db_query("SELECT tid, name
                        FROM {taxonomy_term_data}
                        WHERE vid = :vid", array(':vid' => $vid));

    $terms = array();
    foreach($result as $row) {
      $terms[$row->tid] = $row->name;
    }

    return $terms;

  }


  public static function assignmentFormFields(&$form, &$form_state, $form_id) {

    switch($form_id) {

    case 'assignment_form_create':

      // Find terms from the vocabulary assigned to the stat
      // TODO: This is assuming that stats are assigned vocabularies
      $node = node_load($form['sid']['#value']);
      $items = field_get_items('node', $node, 'field_categories');

      $term_options = getTermsForVocabulary($items[0]['value']);

      if(!empty($term_options)) {
        $vocab = taxonomy_vocabulary_load($items[0]['value']);
        $form['terms'] = array(
          '#type'         => 'select',
          '#title'        => t($vocab->name),
          '#options'      => $term_options,
          '#multiple'     => TRUE,
          '#required'      => TRUE
        );
      }

      //$form['#submit'][] = 'clarity_datasource_assignment_form_create_submit';

      break;

    case 'assignment_form_edit':

      $assignment = assignment_load($form['aid']['#value']);
      $node = node_load($form['sid']['#value']);
      $items = field_get_items('node', $node, 'field_categories');
      $result = db_query("SELECT tid, name
                          FROM {taxonomy_term_data}
                          WHERE vid = :vid", array(':vid' => $items[0]['value']));
      $term_options = array();
      foreach($result as $row) {
          $term_options[$row->tid] = $row->name;
      }

      if(!empty($term_options)) {
          $vocab = taxonomy_vocabulary_load($items[0]['value']);
          $form['terms'] = array(
              '#type'             => 'select',
              '#title'            => t($vocab->name),
              '#options'          => $term_options,
              '#default_value'    => $assignment->terms,
              '#multiple'         => TRUE,
              '#required'          => TRUE
          );
      }

      break;

  }



  }


}
