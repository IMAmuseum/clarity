<?php
/**
 * @file
 * statistic_management_ui.views_default.inc
 */

/**
 * Implementation of hook_views_default_views().
 */
function statistic_management_ui_views_default_views() {
  $export = array();

$view = new view;
$view->name = 'Assignments';
$view->description = 'Display a list of assignments for a specific statistic.';
$view->tag = 'default';
$view->base_table = 'assignment';
$view->human_name = 'Assignments';
$view->core = 7;
$view->api_version = '3.0-alpha1';
$view->disabled = FALSE; /* Edit this to true to make a default view disabled initially */

/* Display: Master */
$handler = $view->new_display('default', 'Master', 'default');
$handler->display->display_options['title'] = 'Assignments';
$handler->display->display_options['access']['type'] = 'none';
$handler->display->display_options['cache']['type'] = 'none';
$handler->display->display_options['query']['type'] = 'views_query';
$handler->display->display_options['exposed_form']['type'] = 'basic';
$handler->display->display_options['pager']['type'] = 'full';
$handler->display->display_options['pager']['options']['items_per_page'] = '20';
$handler->display->display_options['style_plugin'] = 'table';
$handler->display->display_options['style_options']['columns'] = array(
  'expire_date' => 'expire_date',
  'complete' => 'complete',
  'modified' => 'modified',
  'name' => 'name',
);
$handler->display->display_options['style_options']['default'] = 'expire_date';
$handler->display->display_options['style_options']['info'] = array(
  'expire_date' => array(
    'sortable' => 1,
    'default_sort_order' => 'asc',
    'align' => '',
    'separator' => '',
  ),
  'complete' => array(
    'sortable' => 1,
    'default_sort_order' => 'asc',
    'align' => '',
    'separator' => '',
  ),
  'modified' => array(
    'sortable' => 1,
    'default_sort_order' => 'asc',
    'align' => '',
    'separator' => '',
  ),
  'name' => array(
    'sortable' => 1,
    'default_sort_order' => 'asc',
    'align' => '',
    'separator' => '',
  ),
);
$handler->display->display_options['style_options']['override'] = 1;
$handler->display->display_options['style_options']['sticky'] = 0;
$handler->display->display_options['style_options']['empty_table'] = 0;
/* Header: Global: Text area */
$handler->display->display_options['header']['area']['id'] = 'area';
$handler->display->display_options['header']['area']['table'] = 'views';
$handler->display->display_options['header']['area']['field'] = 'area';
$handler->display->display_options['header']['area']['label'] = 'View Assignments Header';
$handler->display->display_options['header']['area']['empty'] = TRUE;
$handler->display->display_options['header']['area']['content'] = '<?php
     if (arg(0) == \'node\' && is_numeric(arg(1))) {
          $node = node_load(arg(1));
          drupal_set_title($node->title . \' Assignments\');
          echo l(\'Create Assignment\', \'node/\' . $node->nid . \'/assignments/create\');
     }
?>';
$handler->display->display_options['header']['area']['format'] = 'php_code';
/* Relationship: Assignment: Statistic */
$handler->display->display_options['relationships']['sid']['id'] = 'sid';
$handler->display->display_options['relationships']['sid']['table'] = 'assignment';
$handler->display->display_options['relationships']['sid']['field'] = 'sid';
$handler->display->display_options['relationships']['sid']['required'] = 1;
/* Relationship: Assignment: User */
$handler->display->display_options['relationships']['uid']['id'] = 'uid';
$handler->display->display_options['relationships']['uid']['table'] = 'assignment';
$handler->display->display_options['relationships']['uid']['field'] = 'uid';
$handler->display->display_options['relationships']['uid']['required'] = 1;
/* Field: User: Name */
$handler->display->display_options['fields']['name']['id'] = 'name';
$handler->display->display_options['fields']['name']['table'] = 'users';
$handler->display->display_options['fields']['name']['field'] = 'name';
$handler->display->display_options['fields']['name']['relationship'] = 'uid';
$handler->display->display_options['fields']['name']['alter']['alter_text'] = 0;
$handler->display->display_options['fields']['name']['alter']['make_link'] = 0;
$handler->display->display_options['fields']['name']['alter']['absolute'] = 0;
$handler->display->display_options['fields']['name']['alter']['external'] = 0;
$handler->display->display_options['fields']['name']['alter']['replace_spaces'] = 0;
$handler->display->display_options['fields']['name']['alter']['trim'] = 0;
$handler->display->display_options['fields']['name']['alter']['nl2br'] = 0;
$handler->display->display_options['fields']['name']['alter']['word_boundary'] = 1;
$handler->display->display_options['fields']['name']['alter']['ellipsis'] = 1;
$handler->display->display_options['fields']['name']['alter']['strip_tags'] = 0;
$handler->display->display_options['fields']['name']['alter']['html'] = 0;
$handler->display->display_options['fields']['name']['element_label_colon'] = 1;
$handler->display->display_options['fields']['name']['element_default_classes'] = 1;
$handler->display->display_options['fields']['name']['hide_empty'] = 0;
$handler->display->display_options['fields']['name']['empty_zero'] = 0;
$handler->display->display_options['fields']['name']['link_to_user'] = 1;
$handler->display->display_options['fields']['name']['overwrite_anonymous'] = 0;
/* Field: Assignment: Date Created */
$handler->display->display_options['fields']['created']['id'] = 'created';
$handler->display->display_options['fields']['created']['table'] = 'assignment';
$handler->display->display_options['fields']['created']['field'] = 'created';
$handler->display->display_options['fields']['created']['alter']['alter_text'] = 0;
$handler->display->display_options['fields']['created']['alter']['make_link'] = 0;
$handler->display->display_options['fields']['created']['alter']['absolute'] = 0;
$handler->display->display_options['fields']['created']['alter']['external'] = 0;
$handler->display->display_options['fields']['created']['alter']['replace_spaces'] = 0;
$handler->display->display_options['fields']['created']['alter']['trim'] = 0;
$handler->display->display_options['fields']['created']['alter']['nl2br'] = 0;
$handler->display->display_options['fields']['created']['alter']['word_boundary'] = 1;
$handler->display->display_options['fields']['created']['alter']['ellipsis'] = 1;
$handler->display->display_options['fields']['created']['alter']['strip_tags'] = 0;
$handler->display->display_options['fields']['created']['alter']['html'] = 0;
$handler->display->display_options['fields']['created']['element_label_colon'] = 1;
$handler->display->display_options['fields']['created']['element_default_classes'] = 1;
$handler->display->display_options['fields']['created']['hide_empty'] = 0;
$handler->display->display_options['fields']['created']['empty_zero'] = 0;
$handler->display->display_options['fields']['created']['date_format'] = 'custom';
$handler->display->display_options['fields']['created']['custom_date_format'] = 'm/d/Y';
/* Field: Assignment: Date Modified */
$handler->display->display_options['fields']['modified_date']['id'] = 'modified_date';
$handler->display->display_options['fields']['modified_date']['table'] = 'assignment';
$handler->display->display_options['fields']['modified_date']['field'] = 'modified_date';
$handler->display->display_options['fields']['modified_date']['label'] = 'Date modified';
$handler->display->display_options['fields']['modified_date']['alter']['alter_text'] = 0;
$handler->display->display_options['fields']['modified_date']['alter']['make_link'] = 0;
$handler->display->display_options['fields']['modified_date']['alter']['absolute'] = 0;
$handler->display->display_options['fields']['modified_date']['alter']['external'] = 0;
$handler->display->display_options['fields']['modified_date']['alter']['replace_spaces'] = 0;
$handler->display->display_options['fields']['modified_date']['alter']['trim'] = 0;
$handler->display->display_options['fields']['modified_date']['alter']['nl2br'] = 0;
$handler->display->display_options['fields']['modified_date']['alter']['word_boundary'] = 1;
$handler->display->display_options['fields']['modified_date']['alter']['ellipsis'] = 1;
$handler->display->display_options['fields']['modified_date']['alter']['strip_tags'] = 0;
$handler->display->display_options['fields']['modified_date']['alter']['html'] = 0;
$handler->display->display_options['fields']['modified_date']['element_label_colon'] = 1;
$handler->display->display_options['fields']['modified_date']['element_default_classes'] = 1;
$handler->display->display_options['fields']['modified_date']['hide_empty'] = 0;
$handler->display->display_options['fields']['modified_date']['empty_zero'] = 0;
$handler->display->display_options['fields']['modified_date']['date_format'] = 'custom';
$handler->display->display_options['fields']['modified_date']['custom_date_format'] = 'm/d/Y';
/* Field: Assignment: Expiration Date */
$handler->display->display_options['fields']['expire_date']['id'] = 'expire_date';
$handler->display->display_options['fields']['expire_date']['table'] = 'assignment';
$handler->display->display_options['fields']['expire_date']['field'] = 'expire_date';
$handler->display->display_options['fields']['expire_date']['alter']['alter_text'] = 0;
$handler->display->display_options['fields']['expire_date']['alter']['make_link'] = 0;
$handler->display->display_options['fields']['expire_date']['alter']['absolute'] = 0;
$handler->display->display_options['fields']['expire_date']['alter']['external'] = 0;
$handler->display->display_options['fields']['expire_date']['alter']['replace_spaces'] = 0;
$handler->display->display_options['fields']['expire_date']['alter']['trim'] = 0;
$handler->display->display_options['fields']['expire_date']['alter']['nl2br'] = 0;
$handler->display->display_options['fields']['expire_date']['alter']['word_boundary'] = 1;
$handler->display->display_options['fields']['expire_date']['alter']['ellipsis'] = 1;
$handler->display->display_options['fields']['expire_date']['alter']['strip_tags'] = 0;
$handler->display->display_options['fields']['expire_date']['alter']['html'] = 0;
$handler->display->display_options['fields']['expire_date']['element_label_colon'] = 1;
$handler->display->display_options['fields']['expire_date']['element_default_classes'] = 1;
$handler->display->display_options['fields']['expire_date']['hide_empty'] = 0;
$handler->display->display_options['fields']['expire_date']['empty_zero'] = 0;
$handler->display->display_options['fields']['expire_date']['date_format'] = 'custom';
$handler->display->display_options['fields']['expire_date']['custom_date_format'] = 'm/d/Y';
/* Field: Assignment: Assignment Complete */
$handler->display->display_options['fields']['complete']['id'] = 'complete';
$handler->display->display_options['fields']['complete']['table'] = 'assignment';
$handler->display->display_options['fields']['complete']['field'] = 'complete';
$handler->display->display_options['fields']['complete']['alter']['alter_text'] = 0;
$handler->display->display_options['fields']['complete']['alter']['make_link'] = 0;
$handler->display->display_options['fields']['complete']['alter']['absolute'] = 0;
$handler->display->display_options['fields']['complete']['alter']['external'] = 0;
$handler->display->display_options['fields']['complete']['alter']['replace_spaces'] = 0;
$handler->display->display_options['fields']['complete']['alter']['trim'] = 0;
$handler->display->display_options['fields']['complete']['alter']['nl2br'] = 0;
$handler->display->display_options['fields']['complete']['alter']['word_boundary'] = 1;
$handler->display->display_options['fields']['complete']['alter']['ellipsis'] = 1;
$handler->display->display_options['fields']['complete']['alter']['strip_tags'] = 0;
$handler->display->display_options['fields']['complete']['alter']['html'] = 0;
$handler->display->display_options['fields']['complete']['element_label_colon'] = 1;
$handler->display->display_options['fields']['complete']['element_default_classes'] = 1;
$handler->display->display_options['fields']['complete']['hide_empty'] = 0;
$handler->display->display_options['fields']['complete']['empty_zero'] = 0;
$handler->display->display_options['fields']['complete']['not'] = 0;
/* Field: Assignment: Assignment Number */
$handler->display->display_options['fields']['aid']['id'] = 'aid';
$handler->display->display_options['fields']['aid']['table'] = 'assignment';
$handler->display->display_options['fields']['aid']['field'] = 'aid';
$handler->display->display_options['fields']['aid']['label'] = 'Modify';
$handler->display->display_options['fields']['aid']['alter']['alter_text'] = 1;
$handler->display->display_options['fields']['aid']['alter']['text'] = 'Edit';
$handler->display->display_options['fields']['aid']['alter']['make_link'] = 1;
$handler->display->display_options['fields']['aid']['alter']['path'] = 'node/!1/assignments/[aid]/edit';
$handler->display->display_options['fields']['aid']['alter']['absolute'] = 0;
$handler->display->display_options['fields']['aid']['alter']['external'] = 0;
$handler->display->display_options['fields']['aid']['alter']['replace_spaces'] = 0;
$handler->display->display_options['fields']['aid']['alter']['trim'] = 0;
$handler->display->display_options['fields']['aid']['alter']['nl2br'] = 0;
$handler->display->display_options['fields']['aid']['alter']['word_boundary'] = 1;
$handler->display->display_options['fields']['aid']['alter']['ellipsis'] = 1;
$handler->display->display_options['fields']['aid']['alter']['strip_tags'] = 0;
$handler->display->display_options['fields']['aid']['alter']['html'] = 0;
$handler->display->display_options['fields']['aid']['element_label_colon'] = 1;
$handler->display->display_options['fields']['aid']['element_default_classes'] = 1;
$handler->display->display_options['fields']['aid']['hide_empty'] = 0;
$handler->display->display_options['fields']['aid']['empty_zero'] = 0;
$handler->display->display_options['fields']['aid']['display_as_link'] = 1;
/* Contextual filter: Content: Nid */
$handler->display->display_options['arguments']['nid']['id'] = 'nid';
$handler->display->display_options['arguments']['nid']['table'] = 'node';
$handler->display->display_options['arguments']['nid']['field'] = 'nid';
$handler->display->display_options['arguments']['nid']['relationship'] = 'sid';
$handler->display->display_options['arguments']['nid']['default_action'] = 'empty';
$handler->display->display_options['arguments']['nid']['default_argument_type'] = 'fixed';
$handler->display->display_options['arguments']['nid']['default_argument_skip_url'] = 0;
$handler->display->display_options['arguments']['nid']['summary']['number_of_records'] = '0';
$handler->display->display_options['arguments']['nid']['summary']['format'] = 'default_summary';
$handler->display->display_options['arguments']['nid']['summary_options']['items_per_page'] = '25';
$handler->display->display_options['arguments']['nid']['break_phrase'] = 0;
$handler->display->display_options['arguments']['nid']['not'] = 0;
/* Filter criterion: Assignment: Assignment Complete */
$handler->display->display_options['filters']['complete']['id'] = 'complete';
$handler->display->display_options['filters']['complete']['table'] = 'assignment';
$handler->display->display_options['filters']['complete']['field'] = 'complete';
$handler->display->display_options['filters']['complete']['value'] = 'All';
$handler->display->display_options['filters']['complete']['exposed'] = TRUE;
$handler->display->display_options['filters']['complete']['expose']['operator_id'] = '';
$handler->display->display_options['filters']['complete']['expose']['label'] = 'Completed';
$handler->display->display_options['filters']['complete']['expose']['use_operator'] = FALSE;
$handler->display->display_options['filters']['complete']['expose']['operator'] = 'complete_op';
$handler->display->display_options['filters']['complete']['expose']['identifier'] = 'complete';
$handler->display->display_options['filters']['complete']['expose']['remember'] = 1;
$handler->display->display_options['filters']['complete']['expose']['multiple'] = FALSE;

/* Display: Page */
$handler = $view->new_display('page', 'Page', 'page');
$handler->display->display_options['path'] = 'node/%/assignments';
$handler->display->display_options['menu']['type'] = 'tab';
$handler->display->display_options['menu']['title'] = 'Assignments';
$handler->display->display_options['menu']['description'] = 'Statistic assignments';
$handler->display->display_options['menu']['weight'] = '1';
$handler->display->display_options['tab_options']['weight'] = '0';
$translatables['Assignments'] = array(
  t('Master'),
  t('Assignments'),
  t('more'),
  t('Apply'),
  t('Reset'),
  t('Sort by'),
  t('Asc'),
  t('Desc'),
  t('Items per page'),
  t('- All -'),
  t('Offset'),
  t('View Assignments Header'),
  t('<?php
     if (arg(0) == \'node\' && is_numeric(arg(1))) {
          $node = node_load(arg(1));
          drupal_set_title($node->title . \' Assignments\');
          echo l(\'Create Assignment\', \'node/\' . $node->nid . \'/assignments/create\');
     }
?>'),
  t('Statistic'),
  t('User'),
  t('Name'),
  t('Date Created'),
  t('Date modified'),
  t('Expiration Date'),
  t('Assignment Complete'),
  t('Modify'),
  t('Edit'),
  t('node/!1/assignments/[aid]/edit'),
  t('All'),
  t('Completed'),
  t('Page'),
);
  
  $export['Assignments'] = $view;

  $view = new view;
  $view->name = 'user_assignments';
  $view->description = 'Display a list of assignments assigned to a user.';
  $view->tag = 'default';
  $view->base_table = 'assignment';
  $view->human_name = 'User Assignments';
  $view->core = 7;
  $view->api_version = '3.0-alpha1';
  $view->disabled = FALSE; /* Edit this to true to make a default view disabled initially */

  /* Display: Master */
  $handler = $view->new_display('default', 'Master', 'default');
  $handler->display->display_options['title'] = 'Assignments';
  $handler->display->display_options['access']['type'] = 'none';
  $handler->display->display_options['cache']['type'] = 'none';
  $handler->display->display_options['query']['type'] = 'views_query';
  $handler->display->display_options['exposed_form']['type'] = 'basic';
  $handler->display->display_options['pager']['type'] = 'full';
  $handler->display->display_options['pager']['options']['items_per_page'] = '20';
  $handler->display->display_options['style_plugin'] = 'table';
  $handler->display->display_options['style_options']['columns'] = array(
    'expire_date' => 'expire_date',
    'complete' => 'complete',
    'modified' => 'modified',
    'name' => 'name',
  );
  $handler->display->display_options['style_options']['default'] = 'expire_date';
  $handler->display->display_options['style_options']['info'] = array(
    'expire_date' => array(
      'sortable' => 1,
      'default_sort_order' => 'asc',
      'align' => '',
      'separator' => '',
    ),
    'complete' => array(
      'sortable' => 1,
      'default_sort_order' => 'asc',
      'align' => '',
      'separator' => '',
    ),
    'modified' => array(
      'sortable' => 1,
      'default_sort_order' => 'asc',
      'align' => '',
      'separator' => '',
    ),
    'name' => array(
      'sortable' => 1,
      'default_sort_order' => 'asc',
      'align' => '',
      'separator' => '',
    ),
  );
  $handler->display->display_options['style_options']['override'] = 1;
  $handler->display->display_options['style_options']['sticky'] = 0;
  $handler->display->display_options['style_options']['empty_table'] = 0;
  /* Relationship: Assignment: Statistic */
  $handler->display->display_options['relationships']['sid']['id'] = 'sid';
  $handler->display->display_options['relationships']['sid']['table'] = 'assignment';
  $handler->display->display_options['relationships']['sid']['field'] = 'sid';
  $handler->display->display_options['relationships']['sid']['required'] = 1;
  /* Relationship: Assignment: User */
  $handler->display->display_options['relationships']['uid']['id'] = 'uid';
  $handler->display->display_options['relationships']['uid']['table'] = 'assignment';
  $handler->display->display_options['relationships']['uid']['field'] = 'uid';
  $handler->display->display_options['relationships']['uid']['required'] = 1;
  /* Field: Content: Title */
  $handler->display->display_options['fields']['title']['id'] = 'title';
  $handler->display->display_options['fields']['title']['table'] = 'node';
  $handler->display->display_options['fields']['title']['field'] = 'title';
  $handler->display->display_options['fields']['title']['relationship'] = 'sid';
  $handler->display->display_options['fields']['title']['alter']['alter_text'] = 0;
  $handler->display->display_options['fields']['title']['alter']['make_link'] = 0;
  $handler->display->display_options['fields']['title']['alter']['absolute'] = 0;
  $handler->display->display_options['fields']['title']['alter']['external'] = 0;
  $handler->display->display_options['fields']['title']['alter']['replace_spaces'] = 0;
  $handler->display->display_options['fields']['title']['alter']['trim'] = 0;
  $handler->display->display_options['fields']['title']['alter']['nl2br'] = 0;
  $handler->display->display_options['fields']['title']['alter']['word_boundary'] = 1;
  $handler->display->display_options['fields']['title']['alter']['ellipsis'] = 1;
  $handler->display->display_options['fields']['title']['alter']['strip_tags'] = 0;
  $handler->display->display_options['fields']['title']['alter']['html'] = 0;
  $handler->display->display_options['fields']['title']['element_label_colon'] = 1;
  $handler->display->display_options['fields']['title']['element_default_classes'] = 1;
  $handler->display->display_options['fields']['title']['hide_empty'] = 0;
  $handler->display->display_options['fields']['title']['empty_zero'] = 0;
  $handler->display->display_options['fields']['title']['link_to_node'] = 1;
  /* Field: Assignment: Date Created */
  $handler->display->display_options['fields']['created']['id'] = 'created';
  $handler->display->display_options['fields']['created']['table'] = 'assignment';
  $handler->display->display_options['fields']['created']['field'] = 'created';
  $handler->display->display_options['fields']['created']['alter']['alter_text'] = 0;
  $handler->display->display_options['fields']['created']['alter']['make_link'] = 0;
  $handler->display->display_options['fields']['created']['alter']['absolute'] = 0;
  $handler->display->display_options['fields']['created']['alter']['external'] = 0;
  $handler->display->display_options['fields']['created']['alter']['replace_spaces'] = 0;
  $handler->display->display_options['fields']['created']['alter']['trim'] = 0;
  $handler->display->display_options['fields']['created']['alter']['nl2br'] = 0;
  $handler->display->display_options['fields']['created']['alter']['word_boundary'] = 1;
  $handler->display->display_options['fields']['created']['alter']['ellipsis'] = 1;
  $handler->display->display_options['fields']['created']['alter']['strip_tags'] = 0;
  $handler->display->display_options['fields']['created']['alter']['html'] = 0;
  $handler->display->display_options['fields']['created']['element_label_colon'] = 1;
  $handler->display->display_options['fields']['created']['element_default_classes'] = 1;
  $handler->display->display_options['fields']['created']['hide_empty'] = 0;
  $handler->display->display_options['fields']['created']['empty_zero'] = 0;
  $handler->display->display_options['fields']['created']['date_format'] = 'custom';
  $handler->display->display_options['fields']['created']['custom_date_format'] = 'm/d/Y';
  /* Field: Assignment: Date Modified */
  $handler->display->display_options['fields']['modified_date']['id'] = 'modified_date';
  $handler->display->display_options['fields']['modified_date']['table'] = 'assignment';
  $handler->display->display_options['fields']['modified_date']['field'] = 'modified_date';
  $handler->display->display_options['fields']['modified_date']['label'] = 'Date modified';
  $handler->display->display_options['fields']['modified_date']['alter']['alter_text'] = 0;
  $handler->display->display_options['fields']['modified_date']['alter']['make_link'] = 0;
  $handler->display->display_options['fields']['modified_date']['alter']['absolute'] = 0;
  $handler->display->display_options['fields']['modified_date']['alter']['external'] = 0;
  $handler->display->display_options['fields']['modified_date']['alter']['replace_spaces'] = 0;
  $handler->display->display_options['fields']['modified_date']['alter']['trim'] = 0;
  $handler->display->display_options['fields']['modified_date']['alter']['nl2br'] = 0;
  $handler->display->display_options['fields']['modified_date']['alter']['word_boundary'] = 1;
  $handler->display->display_options['fields']['modified_date']['alter']['ellipsis'] = 1;
  $handler->display->display_options['fields']['modified_date']['alter']['strip_tags'] = 0;
  $handler->display->display_options['fields']['modified_date']['alter']['html'] = 0;
  $handler->display->display_options['fields']['modified_date']['element_label_colon'] = 1;
  $handler->display->display_options['fields']['modified_date']['element_default_classes'] = 1;
  $handler->display->display_options['fields']['modified_date']['hide_empty'] = 0;
  $handler->display->display_options['fields']['modified_date']['empty_zero'] = 0;
  $handler->display->display_options['fields']['modified_date']['date_format'] = 'short';
  /* Field: Assignment: Expiration Date */
  $handler->display->display_options['fields']['expire_date']['id'] = 'expire_date';
  $handler->display->display_options['fields']['expire_date']['table'] = 'assignment';
  $handler->display->display_options['fields']['expire_date']['field'] = 'expire_date';
  $handler->display->display_options['fields']['expire_date']['alter']['alter_text'] = 0;
  $handler->display->display_options['fields']['expire_date']['alter']['make_link'] = 0;
  $handler->display->display_options['fields']['expire_date']['alter']['absolute'] = 0;
  $handler->display->display_options['fields']['expire_date']['alter']['external'] = 0;
  $handler->display->display_options['fields']['expire_date']['alter']['replace_spaces'] = 0;
  $handler->display->display_options['fields']['expire_date']['alter']['trim'] = 0;
  $handler->display->display_options['fields']['expire_date']['alter']['nl2br'] = 0;
  $handler->display->display_options['fields']['expire_date']['alter']['word_boundary'] = 1;
  $handler->display->display_options['fields']['expire_date']['alter']['ellipsis'] = 1;
  $handler->display->display_options['fields']['expire_date']['alter']['strip_tags'] = 0;
  $handler->display->display_options['fields']['expire_date']['alter']['html'] = 0;
  $handler->display->display_options['fields']['expire_date']['element_label_colon'] = 1;
  $handler->display->display_options['fields']['expire_date']['element_default_classes'] = 1;
  $handler->display->display_options['fields']['expire_date']['hide_empty'] = 0;
  $handler->display->display_options['fields']['expire_date']['empty_zero'] = 0;
  $handler->display->display_options['fields']['expire_date']['date_format'] = 'custom';
  $handler->display->display_options['fields']['expire_date']['custom_date_format'] = 'm/d/Y';
  /* Field: Assignment: Assignment Complete */
  $handler->display->display_options['fields']['complete']['id'] = 'complete';
  $handler->display->display_options['fields']['complete']['table'] = 'assignment';
  $handler->display->display_options['fields']['complete']['field'] = 'complete';
  $handler->display->display_options['fields']['complete']['alter']['alter_text'] = 0;
  $handler->display->display_options['fields']['complete']['alter']['make_link'] = 0;
  $handler->display->display_options['fields']['complete']['alter']['absolute'] = 0;
  $handler->display->display_options['fields']['complete']['alter']['external'] = 0;
  $handler->display->display_options['fields']['complete']['alter']['replace_spaces'] = 0;
  $handler->display->display_options['fields']['complete']['alter']['trim'] = 0;
  $handler->display->display_options['fields']['complete']['alter']['nl2br'] = 0;
  $handler->display->display_options['fields']['complete']['alter']['word_boundary'] = 1;
  $handler->display->display_options['fields']['complete']['alter']['ellipsis'] = 1;
  $handler->display->display_options['fields']['complete']['alter']['strip_tags'] = 0;
  $handler->display->display_options['fields']['complete']['alter']['html'] = 0;
  $handler->display->display_options['fields']['complete']['element_label_colon'] = 1;
  $handler->display->display_options['fields']['complete']['element_default_classes'] = 1;
  $handler->display->display_options['fields']['complete']['hide_empty'] = 0;
  $handler->display->display_options['fields']['complete']['empty_zero'] = 0;
  $handler->display->display_options['fields']['complete']['not'] = 0;
  /* Field: Assignment: Assignment Number */
  $handler->display->display_options['fields']['aid']['id'] = 'aid';
  $handler->display->display_options['fields']['aid']['table'] = 'assignment';
  $handler->display->display_options['fields']['aid']['field'] = 'aid';
  $handler->display->display_options['fields']['aid']['label'] = 'Modify';
  $handler->display->display_options['fields']['aid']['alter']['alter_text'] = 1;
  $handler->display->display_options['fields']['aid']['alter']['text'] = 'Record Data';
  $handler->display->display_options['fields']['aid']['alter']['make_link'] = 1;
  $handler->display->display_options['fields']['aid']['alter']['path'] = 'assignment/[aid]/record?uid=%1';
  $handler->display->display_options['fields']['aid']['alter']['absolute'] = 0;
  $handler->display->display_options['fields']['aid']['alter']['external'] = 0;
  $handler->display->display_options['fields']['aid']['alter']['replace_spaces'] = 0;
  $handler->display->display_options['fields']['aid']['alter']['trim'] = 0;
  $handler->display->display_options['fields']['aid']['alter']['nl2br'] = 0;
  $handler->display->display_options['fields']['aid']['alter']['word_boundary'] = 1;
  $handler->display->display_options['fields']['aid']['alter']['ellipsis'] = 1;
  $handler->display->display_options['fields']['aid']['alter']['strip_tags'] = 0;
  $handler->display->display_options['fields']['aid']['alter']['html'] = 0;
  $handler->display->display_options['fields']['aid']['element_label_colon'] = 1;
  $handler->display->display_options['fields']['aid']['element_default_classes'] = 1;
  $handler->display->display_options['fields']['aid']['hide_empty'] = 0;
  $handler->display->display_options['fields']['aid']['empty_zero'] = 0;
  $handler->display->display_options['fields']['aid']['display_as_link'] = 1;
  /* Contextual filter: User: Uid */
  $handler->display->display_options['arguments']['uid']['id'] = 'uid';
  $handler->display->display_options['arguments']['uid']['table'] = 'users';
  $handler->display->display_options['arguments']['uid']['field'] = 'uid';
  $handler->display->display_options['arguments']['uid']['relationship'] = 'uid';
  $handler->display->display_options['arguments']['uid']['default_argument_type'] = 'fixed';
  $handler->display->display_options['arguments']['uid']['default_argument_skip_url'] = 0;
  $handler->display->display_options['arguments']['uid']['summary']['number_of_records'] = '0';
  $handler->display->display_options['arguments']['uid']['summary']['format'] = 'default_summary';
  $handler->display->display_options['arguments']['uid']['summary_options']['items_per_page'] = '25';
  $handler->display->display_options['arguments']['uid']['break_phrase'] = 0;
  $handler->display->display_options['arguments']['uid']['not'] = 0;
  /* Filter criterion: Assignment: Assignment Complete */
  $handler->display->display_options['filters']['complete']['id'] = 'complete';
  $handler->display->display_options['filters']['complete']['table'] = 'assignment';
  $handler->display->display_options['filters']['complete']['field'] = 'complete';
  $handler->display->display_options['filters']['complete']['value'] = 'All';
  $handler->display->display_options['filters']['complete']['exposed'] = TRUE;
  $handler->display->display_options['filters']['complete']['expose']['operator_id'] = '';
  $handler->display->display_options['filters']['complete']['expose']['label'] = 'Completed';
  $handler->display->display_options['filters']['complete']['expose']['use_operator'] = FALSE;
  $handler->display->display_options['filters']['complete']['expose']['operator'] = 'complete_op';
  $handler->display->display_options['filters']['complete']['expose']['identifier'] = 'complete';
  $handler->display->display_options['filters']['complete']['expose']['remember'] = 1;
  $handler->display->display_options['filters']['complete']['expose']['multiple'] = FALSE;

  /* Display: Page */
  $handler = $view->new_display('page', 'Page', 'page');
  $handler->display->display_options['path'] = 'user/%/assignments';
  $handler->display->display_options['menu']['type'] = 'tab';
  $handler->display->display_options['menu']['title'] = 'Assignments';
  $handler->display->display_options['menu']['description'] = 'Statistic assignments';
  $handler->display->display_options['menu']['weight'] = '0';
  $translatables['user_assignments'] = array(
    t('Master'),
    t('Assignments'),
    t('more'),
    t('Apply'),
    t('Reset'),
    t('Sort by'),
    t('Asc'),
    t('Desc'),
    t('Items per page'),
    t('- All -'),
    t('Offset'),
    t('Statistic'),
    t('User'),
    t('Title'),
    t('Date Created'),
    t('Date modified'),
    t('Expiration Date'),
    t('Assignment Complete'),
    t('Modify'),
    t('Record Data'),
    t('assignment/[aid]/record?uid=%1'),
    t('All'),
    t('Completed'),
    t('Page'),
  );
  $export['user_assignments'] = $view;

  return $export;
}
