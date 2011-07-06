<?php

class ClarityLikertScaleDatasource implements DatasourceIfc {
    
    public static $scale = array(
        1 => 'strongly disagree',
        2 => 'disagree',
        3 => 'neutral',
        4 => 'agree',
        5 => 'strongly agree'
    );
    
    /**
    * A function to get fields for the data entry form.
    */
    static function getDataFormFields($stat)
    {
        $fields['likert-scale'] = array(
            '#title'   => '',
            '#type'    => 'radios',
            '#options' => self::$scale
        );
        
        return $fields;
    }
    
    /**
    * A function to validate the data entry form.
    */
    static function validateDataForm($form, $form_state)
    {
        if (!is_numeric($form_state['values']['likert-scale']) && array_key_exists($form_state['values']['likert-scale'], self::$scale)) {
            form_set_error('likert-scale', t('Please select a value'));
        }
    }
    
    /**
    * A function to submit data from the data entry form.
    */
    static function submitDataForm($form, $form_state)
    {
        global $user;

        try {
              $result = db_insert('clarity_datasource_likert_scale')->fields(array(
          	  	'stat_nid'      => $form_state['values']['assignment']->sid,
        	  	'uid'           => $user->uid,
        	  	'timestamp'     => $form_state['values']['assignment']->expire_date,
        	  	'value'         => $form_state['values']['likert-scale'],
        	  	'modified_time' => time()
            ))->execute();

        } catch (PDOException $e) {
            watchdog_exception('data_submission', $e);
            if (($e->errorInfo[0] == 23000) && $e->errorInfo[1] == 1062) {
                drupal_set_message(t('An entry for this assignment already exists'), 'warning');
            } else {
                drupal_set_message(t('The system was unable to record this value'), 'warning');
            }
        }
    }
    
    /**
    * A function to fetch all data for a stat
    * Returns an array of Data objects
    */
    static function getData($stat_id, $options = array())
    {
        $q = 'SELECT * FROM {clarity_datasource_likert_scale} WHERE stat_nid = :stat';
        $args = array(':stat' => $stat_id);

        if (isset($options['uid'])) {
            $q .= ' AND uid = :uid';
            $args[':uid'] = $options['uid'];
        }

        $result = db_query($q, $args);
        $data = array();
        foreach($result as $record) {
            $d = new Data($record->uid, $record->timestamp, $record->value);
            $d->modified_time = $record->modified_time;
            $d->extra['string_value'] = self::$scale[$record->value];
            $data[] = $d;
        }

        return $data;
    }
    
    /**
    * A function to create the data table for a stat
    * Returns the content for the data table
    */
    static function createDataTable($stat_id)
    {
        $data = self::getData($stat_id);

        return theme('clarity_likert_scale_table', array('data' => $data));
    }
  
}