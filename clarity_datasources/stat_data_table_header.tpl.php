<div class='header'>
<div class='assignment column w5'>
<div class='w5'>Assignment</div>
<div class='clear'></div>
<div class='assignment column w2'>Date</div>
<div class='assignment column w2'>Date Modified</div>
</div>
<?php foreach($ds_header_labels as $labels): ?>
<div class='column w<?=count($labels['sublabels'])*2?>'>
<div class='w<?=count($labels['sublabels'])*2?>'><?=$labels['label']?></div>
<div class='clear'></div>
<?php foreach($labels['sublabels'] as $label): ?>
<div class='column w2'><?=$label?></div>
<?php endforeach; ?>
</div>
<?php endforeach; ?>
</div>