<?php 

	/**
	 * @file 
	 */ 

	/**
	 * Implements hook_views_data 
	 */	 
	function assignment_views_data() {
		$data = array();
		$data['assignment']['table'] = array(
			'group' => t("Assignment")
		);
		
		$data['assignment']['table']['base'] = array(
			'field' 	=> 'aid',
			'title'		=> t('Assignment'),
			'help'		=> t('User/group assigned statistics.'),
			'weight'	=> 1
		);
		
		$data['assignment']['table']['join'] = array(
			'node' => array(
				'left_field' 	=> 'nid',
				'field'			=> 'sid'
			),
			'users' => array(
				'left_field'	=> 'uid',
				'field'			=> 'uid'
			)
		);	
	
		$data['assignment']['uid'] = array(
		    'title' 		=> t('User'),
		    'help' 			=> t('References a username.'),
		    'relationship' 	=> array(
		    	'base' 		=> 'users',
		    	'field' 	=> 'name',
		    	'handler' 	=> 'views_handler_relationship',
		    	'label' 	=> t('User')
		    )			
		);
		
		$data['assignment']['sid'] = array(
		    'title' 		=> t('Statistic'),
		    'help' 			=> t('Statistic Title.'),
		    'relationship' 	=> array(
		    	'base' 		=> 'node',
		    	'field' 	=> 'title',
		    	'handler' 	=> 'views_handler_relationship',
		    	'label' 	=> t('Statistic')
		    )				
		);		
				
		$data['assignment']['expire_date'] = array(
			'title' 	=> t('Expiration Date'),
    		'help' 		=> t('Date assignment expires.'),
    		'field' 	=> array(
      			'handler' 			=> 'views_handler_field_date',
      			'click sortable' 	=> TRUE,
    		),
    		'sort' 		=> array('handler' => 'views_handler_sort_date'),
    		'filter' 	=> array('handler' => 'views_handler_filter_date')
		);
		
		$data['assignment']['modified_date'] = array(
			'title' 	=> t('Date Modified'),
    		'help' 		=> t('Date last modified.'),
    		'field' 	=> array(
      			'handler' 			=> 'views_handler_field_date',
      			'click sortable' 	=> TRUE,
    		),
    		'sort' 		=> array('handler' => 'views_handler_sort_date'),
    		'filter' 	=> array('handler' => 'views_handler_filter_date')
		);
		
		$data['assignment']['created'] = array(
			'title' 	=> t('Date Created'),
    		'help' 		=> t('Date assignment created.'),
    		'field' 	=> array(
      			'handler' 			=> 'views_handler_field_date',
      			'click sortable' 	=> TRUE,
    		),
    		'sort' 		=> array('handler' => 'views_handler_sort_date'),
    		'filter' 	=> array('handler' => 'views_handler_filter_date')
		);
		
		$data['assignment']['complete'] = array(
    		'title' 	=> t('Assignment Complete'),
    		'help' 		=> t('Whether or not the assignment is complete.'),
    		'field' 	=> array(
      			'handler' 			=> 'views_handler_field_boolean',
      			'click sortable' 	=> TRUE,
    		),
    		'filter' 	=> array(
      			'handler' 	=> 'views_handler_filter_boolean_operator',
      			'label' 	=> t('Completed'),
      			'type' 		=> 'yes-no',
      			'use equal' => TRUE,
    		),
    		'sort' 		=> array('handler' 	=> 'views_handler_sort')
  		);
  		
		$data['assignment']['aid'] = array(
    		'title' 	=> t('Assignment Number'),
    		'help' 		=> t('Assignment link placeholder'),
    		'field' 	=> array('handler' => 'views_handler_field_url')  		
  		);  		
  		return $data;
	}