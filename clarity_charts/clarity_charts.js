
var clarity_charts = [];

function ClarityChart(element_id, chart_type) {		
	
  var self = this;
  this.element_id = element_id;
  this.chart_type = chart_type;
  this.chart = null;
  
  this.init = function() {
	
    switch (this.chart_type) {
      case 'line':
  	    this.chart = new google.visualization.LineChart(document.getElementById(element_id));
  	    break;
      case 'bar':
    	this.chart = new google.visualization.BarChart(document.getElementById(element_id));
    	break;
    }
  
  }	
	
  this.draw = function(data) {
	  
    if (this.chart != null) {
      this.chart.draw(data, {width: 400, height: 240});
    }
				
  }	
	
}


(function($) {

  google.load('visualization', '1', {'packages':['corechart']});	
  
  google.setOnLoadCallback(loadData);    

  function loadData() {
	  
	  // TODO: determine this in a better way
	  var stat_nid = document.URL.split('/').pop();
	  
	  var query = new google.visualization.Query(Drupal.settings.basePath + 'datasource/wire/' + stat_nid);
	  query.send(handleWireResponse);
      for (i in clarity_charts) {
    	  clarity_charts[i].init();
      }
	  
  }
  
  function handleWireResponse(response) {

    if (response.isError()) {
      alert('Error in query: ' + response.getMessage() + ' ' + response.getDetailedMessage());
      return;
    }

    var data = response.getDataTable();
  
    for (i in clarity_charts) {	       
	  clarity_charts[i].draw(data);
    }  
	  
  }

}(jQuery));


