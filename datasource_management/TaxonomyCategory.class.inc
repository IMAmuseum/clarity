<?php

/**
 * TaxonomyCategory provides helper functions to assist with managing categories based on taxonomies.
 */
abstract class TaxonomyCategory extends DataCategory {


  /**
   * Helper function to get terms for a vocabulary.
   */
  public static function getTermsForVocabulary($vid) {
    $result = db_query("SELECT tid, name
                        FROM {taxonomy_term_data}
                        WHERE vid = :vid", array(':vid' => $vid));

    $terms = array();
    foreach($result as $row) {
      $terms[$row->tid] = $row->name;
    }

    return $terms;

  }


}
