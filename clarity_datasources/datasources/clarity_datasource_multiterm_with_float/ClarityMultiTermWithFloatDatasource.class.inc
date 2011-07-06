<?php
define('VID', 2);

class ClarityMultiTermWithFloatDatasource implements DatasourceIfc, DatasourceStatIfc {

    public static function getStatConfigFormFields($stat) {
        $options = array('' => 'Select a vocabulary');
        $vocabs = taxonomy_get_vocabularies();
        foreach($vocabs as $vid => $vocab) {
            $options[$vid] = $vocab->name;
        }

        $fields['clarity_multiterm_with_float'] = array(
            '#type'     => 'select',
            '#title'    => t('Vocabulary'),
            '#options'  => $options,
            '#required' => TRUE,
        );

        return $fields;
    }

    public static function validateStatConfigForm($form_state) {

    }

    public static function getDataFormFields($stat) {
        $form['multi_term_category'] = array(
            '#type'     => 'item',
            '#markup'   => $vocabulary,
        );

        $terms = taxonomy_get_tree(VID); // TODO find the vid after its implemented
        foreach($terms as $term) {
            $form['multi_term_with_float_' . $term->tid] = array(
                '#type'     => 'textfield',
                '#title'    => t($term->name),
                '#required' => TRUE,
            );
        }

        return $form;

    }

    public static function validateDataForm($form, $form_state) {
        $terms = taxonomy_get_tree(VID);
        foreach ($terms as $term) {
            if (!is_numeric($form_state['values']['multi_term_with_float_' . $term->tid])) {
                form_set_error('multi_term_with_float_' . $term->tid, t('Please enter a numeric value'));
            }
        }
    }

    public static function submitDataForm($form, $form_state) {
        $terms = taxonomy_get_tree(VID);
        foreach ($terms as $term) {
            try {
                $result = db_insert('clarity_value_multiterm_with_float')->fields(array(
                    'aid'       => $form_state['values']['assignment']->aid,
                    'value'     => $form_state['values']['multi_term_with_float_' . $term->tid],
                    'tid'       => $term->tid,
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
    }


    public static function getData($stat_nid, $options = array()) {
        $query = 'SELECT * FROM {clarity_value_multiterm_with_float} c INNER JOIN {assignment} a ON c.aid = a.aid WHERE a.sid = :stat';
        $args = array(':stat' => $stat_nid);
        $result = db_query($query, $args);
        $data = array();
        foreach($result as $record) {
            $data[] = $record;
        }

        return $data;
    }


    public static function createDataTable($stat_nid) {
        $data = ClarityMultiTermWithFloatDatasource::getData($stat_nid);
        return theme('clarity_multiterm_with_value_table', array('data' => $data));
    }

    public static function assignmentFormFields(&$form, &$form_state, $form_id) {
        //TODO

        /****
        $node = node_load($form['sid']['#value']);
        $items = field_get_items('node', $node, 'field_categories');
        $vid = $items[0]['value'];
        $term_options = AssignmentTaxonomyCategory::getTermsForVocabulary($vid);

        if(!empty($term_options)) {
            $vocab = taxonomy_vocabulary_load($vid);
            $form['terms'] = array(
                '#type'         => 'select',
                '#title'        => t($vocab->name),
                '#options'      => $term_options,
                '#multiple'     => TRUE,
                '#required'      => TRUE
            );
        } else {

            return;

        }

        if ($form_id == 'assignment_form_edit')  {
            $assignment = assignment_load($form['aid']['#value']);
            if(!empty($term_options)) {
                $form['terms']['#default_value'] = $assignment->terms;
            }
        }
        */
    }


/**
  public static function onAssignmentLoad($assignments) {

    foreach ($assignments as $assignment) {
      $assignment->terms = AssignmentTaxonomyCategory::loadCategories($assignment->aid);
    }

  }


  public static function onAssignmentPresave($assignment) {

    AssignmentTaxonomyCategory::clearCategories($assignment->aid);

  }


  public static function onAssignmentUpdate($assignment) {

    if(isset($assignment->terms)) {
      AssignmentTaxonomyCategory::saveCategories($assignment->aid, $assignment->terms);
    }

  }


  public static function onAssignmentInsert($assignment) {

    if(isset($assignment->terms)) {
      AssignmentTaxonomyCategory::saveCategories($assignment->aid, $assignment->terms);
    }

  }
*/
}
