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
    $delta = _clarity_datasources_delta_for_index($stat, $index);
    $ds_header_info[$index] = array('label' => $stat->field_datasources['und'][$delta]['label'],
                                    'sublabels' => call_user_func_array($datasource->class . '::getDataTableHeaderInfo',
                                                                        array($vars['stat_nid'], $index)));
    $ds_col_content[$index] = call_user_func_array($datasource->class . '::getDataTableColumnContent',
                                                   array($vars['stat_nid'], $index));
  }

  $vars['header_content'] = theme('stat_data_table_header', array('ds_header_labels' => $ds_header_info));

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


function clarity_datasources_preprocess_stat_data_table_header(&$vars) {

}


function clarity_datasources_preprocess_stat_data_table_row(&$vars) {

  $vars['columns'] = array();

  $vars['columns']['assignment_user'] = array(
    'classes' => 'w1',
    'content' => l(user_load($vars['assignment']->uid)->name, 'user/'. $vars['assignment']->uid)
  );

  $vars['columns']['assignment_date'] = array(
    'classes' => 'w2',
    'content' => date('m/d/Y', $vars['assignment']->expire_date),
  );

  $vars['columns']['assignment_modified'] = array(
    'classes' => 'w2',
    'content' => isset($vars['assignment']->modified_date) ? date('m/d/Y', $vars['assignment']->modified_date) : '&nbsp;',
  );

  $vars['columns']['assignment_edit'] = array(
    'classes' => 'w1',
    'content' => l(t('Edit'), "node/{$vars['assignment']->sid}/assignments/{$vars['assignment']->aid}/edit")
  );

  foreach ($vars['ds_column_content'] as $index => $column) {
    foreach($column as $subcolumn) {
      $vars['columns']['ds-' . $index] = array(
        'classes' => 'w2',
        'content' => isset($subcolumn) ? $subcolumn : '&nbsp;'
      );
    }
  }

  $vars['columns']['fields_edit'] = array(
    'classes' => 'w1',
    'content' => l(t('Edit'), 'submit-data/' . $vars['assignment']->aid)
  );

}