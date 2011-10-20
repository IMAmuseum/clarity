<?php

function clarity_datasources_preprocess_stat_data_table(&$vars) {

  $results = db_select('assignment', 'a')
             ->fields('a')
             ->condition('sid', $vars['stat_nid'], '=')
             ->execute();

  $assignments = array();
  $vars['rows'] = array();

  $datasources = _clarity_datasources_get_datasources_for_stat($vars['stat_nid']);
  $stat = node_load($vars['stat_nid']);

  // Assemble the header content
  $ds_header_info = array();
  $ds_col_content = array();
  foreach ($datasources as $index => $datasource) {

    $sublabels = call_user_func_array($datasource->class . '::getDataTableHeaderInfo',
                                      array($vars['stat_nid'], $index));
    foreach($sublabels as &$label) {
      if (!isset($label)) $label = '&nbsp;';
    }

    $delta = _clarity_datasources_delta_for_index($stat, $index);
    $ds_header_info[$index] = array('label' => $stat->field_datasources['und'][$delta]['label'],
                                    'sublabels' => $sublabels);
    $ds_col_content[$index] = call_user_func_array($datasource->class . '::getDataTableColumnContent',
                                                   array($vars['stat_nid'], $index));
  }

  $assignment_header_labels = array(t('User'), t('Date'), t('Date Modified'));
  if (property_exists($stat, 'field_assignment_properties')) {
    $items = $stat->field_assignment_properties['und'];
    foreach($items as $item) {
      $assignment_header_labels[] = $item['label'];
    }
  }
  $assignment_header_labels[] = '&nbsp';

  $vars['header_content'] = theme('stat_data_table_header',
                                  array('assignment_header_labels' => $assignment_header_labels, 'ds_header_labels' => $ds_header_info));

  // Assemble the content for each row
  while($result = $results->fetchAssoc()) {

    $assignment = assignment_load($result['aid']);

    if ($assignment != null) {

      $ds_content = array();

      foreach($ds_col_content as $index => $content) {
        $ds_content[$index][] = isset($content[$result['aid']]) ? $content[$result['aid']] : null;
      }

      $vars['rows'][] = theme('stat_data_table_row', array('assignment' => $assignment,
                                                           'ds_column_content' => $ds_content));

    }
  }

}


function clarity_datasources_preprocess_stat_data_table_row(&$vars) {

  $vars['columns'] = array();

  $vars['columns']['assignment_user'] = array(
    'classes' => '',
    'content' => l(user_load($vars['assignment']->uid)->name, 'user/'. $vars['assignment']->uid)
  );

  $vars['columns']['assignment_date'] = array(
    'classes' => '',
    'content' => date('m/d/Y', $vars['assignment']->expire_date),
  );

  $vars['columns']['assignment_modified'] = array(
    'classes' => '',
    'content' => isset($vars['assignment']->modified_date) ? date('m/d/Y', $vars['assignment']->modified_date) : '&nbsp;',
  );

  $stat = node_load($vars['assignment']->sid);
  if (property_exists($stat, 'field_assignment_properties')) {
    $items = $stat->field_assignment_properties['und'];
    foreach($items as $item) {
      $result = db_query('SELECT * FROM assignment_properties WHERE `assignment_id` = :a AND `key` = :k',
                         array(':a' => $vars['assignment']->aid, ':k' => $item['key']))->fetchAssoc();
      $vars['columns'][$item['key']] = array(
        'classes' => '',
        'content' => isset($result) ? $result['value'] : '&nbsp;'
      );
    }
  }

  $vars['columns']['assignment_edit'] = array(
    'classes' => '',
    'content' => l(t('Edit'),
                   "node/{$vars['assignment']->sid}/assignments/{$vars['assignment']->aid}/edit",
                   array('attributes' => array('title' => t('Edit assignment')))
                   )
  );

  foreach ($vars['ds_column_content'] as $index => $column) {
    foreach($column as $subcolumn) {
      $vars['columns']['ds-' . $index] = array(
        'classes' => '',
        'content' => isset($subcolumn) ? $subcolumn : '&nbsp;'
      );
    }
  }

  $vars['columns']['fields_edit'] = array(
    'classes' => '',
    'content' => l(t('Edit'),
                   'submit-data/' . $vars['assignment']->aid,
                   array('attributes' => array('title' => t('Edit data')))
                   )
  );

  $flag = assignment_get_flag($vars['assignment']->aid);
  $flag_content = (isset($flag)) ? "<span class='flag' title='{$flag['comment']}'>*</span>" : '&nbsp;';
  $vars['columns']['flag'] = array(
    'classes' => '',
    'content' => $flag_content
  );

}