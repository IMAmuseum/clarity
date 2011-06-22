<?php

/**
 * The AssignmentTaxonomyCategory class manages the data associated with taxonomy terms assigned to assignments.
 */
class AssignmentTaxonomyCategory extends TaxonomyCategory {


  public static function clearCategories($assignment_id) {

    // remove all previously selected terms
    $result = db_query("DELETE FROM {assignment_terms}
                        WHERE aid = :aid", array(':aid' => $assignment_id));

  }


  public static function loadCategories($assignment_id) {

    $result = db_query("SELECT tid
                        FROM {assignment_terms}
                        WHERE aid = :aid", array(':aid' => $assignment_id));
    $terms = array();
    foreach($result as $row) {
        array_push($terms, $row->tid);
    }
    return $terms;

  }


  public static function saveCategories($assignment_id, $term_ids) {

    foreach($term_ids as $term_id) {
      $assignment_terms = new stdClass();
      $assignment_terms->aid = $assignment_id;
      $assignment_terms->tid = $term_id;
      drupal_write_record('assignment_terms', $assignment_terms);
   }

  }


}