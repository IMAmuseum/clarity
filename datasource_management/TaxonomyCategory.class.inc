<?php

class TaxonomyCategory extends DataCategory {

  private $vocab_source = 'stat';
  private $term_source = 'assignment';

  private static function getTermsForVocabulary($vid) {
    $result = db_query("SELECT tid, name
                        FROM {taxonomy_term_data}
                        WHERE vid = :vid", array(':vid' => $vid));

    $terms = array();
    foreach($result as $row) {
      $terms[$row->tid] = $row->name;
    }

    return $terms;

  }

  private function getVocabularyFromEntity($id) {

    if ($this->vocab_source == 'stat') {
      $node = node_load($id);
      $items = field_get_items('node', $node, 'field_categories');
      return $items[0]['value'];
    } else {
      // TODO: support for vocabs defined on assignments
    }

  }

  public function assignmentFormFields(&$form, &$form_state, $form_id) {

    $vid = $this->getVocabularyFromEntity($form['sid']['#value']);
    $term_options = TaxonomyCategory::getTermsForVocabulary($vid);

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

  public static function onAssignmentInsert($assignment) {}
  public static function onAssignmentLoad($assignment) {}
  public static function onAssignmentPresave($assignment) {}
  public static function onAssignmentUpdate($assignment) {}

}
