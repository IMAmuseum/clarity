<?php

interface iDataCategory {

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

/**
 * DataCategory is a class that manages the associaton of data with categories. Subclasses
 * can support this by leveraging taxonomy terms, users, or other types of categorizations.
 */
abstract class DataCategory implements iDataCategory {

}