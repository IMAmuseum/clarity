<?php

function clarity_datasources_wire($stat, $delta = null) {

  $result = array('version' => '0.6');

  if (!isset($_REQUEST['tqx'])) die();

  $params = array();

  foreach (explode(';', $_GET['tqx']) as $param) {
      preg_match('/(?P<key>\w+):(?P<val>\w+)/', $param, $matches);
      if (isset($matches['key'])) {
        $params[$matches['key']] = $matches['val'];
      }
  }

  if (!array_key_exists('reqId', $params)) {
      print 'Missing parameter reqId'; die();
  }

  $handler = 'google.visualization.Query.setResponse';
  if (array_key_exists('responseHandler', $params)) {
      $handler = $params['responseHandler'];
  }

  $result['status'] = 'ok';
  $result['reqId'] = $params['reqId'];

  // TODO: read cache?

  if (is_numeric($stat)) {
    $stat = node_load($stat);
  }
  if (!isset($stat) || ($stat->type != 'statistic')) {
    // TODO: return as an error
    print "Node {$params['reqId']} is not a statistic";
    exit();
  }
  $ds_info = _clarity_datasources_get_datasources_for_stat($stat->nid);
  if (isset($delta)) $ds_info = $ds_info[$delta];

  if (isset($ds_info)) {
    $ds_data = call_user_func($ds_info->class . '::getData', $stat->nid, array('delta' => $delta));
  } else {
    $ds_data = array();
  }

  $table = array(
      'cols' => array(
          array('id' => 'col-1',
                'label' => 'Date',
                'type' => 'string'),
          array('id' => 'col-2',
                'label' => 'Value',
                'type' => 'number')
      )
  );

  $q = 'SELECT * FROM {assignment} a WHERE a.sid = :stat';
  $args = array(':stat' => $stat->nid);

  if (isset($uid)) {
    $q .= ' AND a.uid = :uid';
    $args[':uid'] = $uid;
  }

  $assignments = db_query($q, $args);

  $table['rows'] = array();
  foreach ($assignments as $assignment) {
    $table_row = array('c' => array());
    $table_row['c'][] = array('v' => date('M j', $assignment->expire_date));
    // TODO: why intval?
    if (isset($ds_data[$assignment->aid])) {
      $table_row['c'][] = array('v' => intval($ds_data[$assignment->aid]));
    } else {
      $table_row['c'][] = array('v' => null);
    }
    $table['rows'][] = $table_row;
  }

  $result['table'] = $table;
  $json = json_encode($table);
  $result['sig'] = md5($json);

  // TODO: write cache?

  print $handler . '(' . json_encode($result) . ')';
  exit();


}