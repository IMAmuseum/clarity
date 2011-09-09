(function($) {

$(document).ready(function() {
	
	$('#edit-flag-assignment').click(function() {
		
		var data = {};
		var re = /([0-9]+)(\?.*)?$/;		
		data['assignment_id'] = window.location.href.match(re)[1];
		
		var flag = $('#edit-assignment-flag .flag');
		if (flag.length) {
			flag = flag[0].textContent;
		} else {
			flag = null;
		}
		
		data['comment'] = prompt('Set a comment for this flag', flag);
		
		if ((data['comment'] == null) || (data['comment'] == '')) {
			data['comment'] = null;
		} 

		$.post(Drupal.settings.basePath + '/ajax/flag-assignment', data, function(result) {
			window.location.reload();
		},'json');
		
		return false;
		
	});
	
});

}(jQuery));