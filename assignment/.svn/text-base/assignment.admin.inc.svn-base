<?php

	/**
	 * @file 
	 * Assignment entity admin settings
	 */ 

	function assignment_admin() {
	    $form = array();
	
	    $form['assignment_notification_reminder_frequency'] = array(
	        '#type' => 'textfield',
	    	'#title' => t('Default Notification Reminder Frequency'),
	    	'#default_value' => variable_get('assignment_notification_reminder_frequency', 1),
	    	'#description' => t("The default interval for which reminder notifications are sent."),
	    	'#required' => TRUE,
	    );
	
	    return system_settings_form($form);
	}