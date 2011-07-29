
var clarity_charts = [];

function ClarityChart(element_id, chart_type, stat_nid, delta) {		
	
  var self = this;
  this.element_id = element_id;
  this.chart_type = chart_type;
  this.chart = null;
  this.stat_nid = stat_nid;
  this.delta = delta;
  
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
	
  this.fetchData = function() {
	  
	var query = new google.visualization.Query(Drupal.settings.basePath + 'datasource/wire/' + self.stat_nid + '/' + self.delta);
	query.send(self.handleWireResponse);	  
	  
  }
  
  this.handleWireResponse = function(response) {
	  
   if (response.isError()) {
	 alert('Error in query: ' + response.getMessage() + ' ' + response.getDetailedMessage());
	 return;
   }

   self.draw(response.getDataTable());
	  
  }
  
  this.draw = function(data) {
	  
    if (this.chart != null) {
      this.chart.draw(data, {width: 400, height: 240});
    }
				
  }	
	
}


(function($) {

  google.load('visualization', '1', {'packages':['corechart']});	
  
  google.setOnLoadCallback(startCharting);    

  function startCharting() {
	  
    for (i in clarity_charts) {
	  clarity_charts[i].init();
	  clarity_charts[i].fetchData();
    }
	  
  }

}(jQuery));


