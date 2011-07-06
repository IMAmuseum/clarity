<?php

interface DataCategoryIfc {

  /**
   * Clear the categories associated with the given id.
   */
  public static function clearCategories($id);

  /**
   * Associate the given categories with the id.
   */
  public static function saveCategories($id, $categories);

  /**
   * Load the categories associated with a given id.
   */
  public static function loadCategories($id);

}
