<?php
/**
 * @file
 * statistic_management.features.inc
 */

/**
 * Implements hook_node_info().
 */
function statistic_management_node_info() {
  $items = array(
    'statistic' => array(
      'name' => t('Statistic'),
      'base' => 'node_content',
      'description' => t('Use statistics for creating a unique statistic type.'),
      'has_title' => '1',
      'title_label' => t('Title'),
      'help' => '',
    ),
  );
  return $items;
}
