<?php

function clarity_datasources_wire($stat) {

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
  $ds_info = _clarity_datasources_get_datasource_for_stat($stat->nid);
  if ($ds_info) {
    $data = call_user_func($ds_info->class . '::getData', $stat->nid);
  } else {
    $data = array();
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

  $table['rows'] = array();
  foreach ($data as $data_row) {
      $table_row = array('c' => array());
      $table_row['c'][] = array('v' => date('M j', $data_row->timestamp));
      $table_row['c'][] = array('v' => intval($data_row->value));
      $table['rows'][] = $table_row;
  }

  $result['table'] = $table;
  $json = json_encode($table);
  $result['sig'] = md5($json);

  // TODO: write cache?

  print $handler . '(' . json_encode($result) . ')';
  exit();


}