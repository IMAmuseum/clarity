<colgroup span='<?=count($assignment_header_labels);?>'></colgroup>
<colgroup span='<?=count($ds_header_labels);?>'></colgroup>
<tr class='header-top'>
<th colspan='<?=count($assignment_header_labels);?>'>Assignment</th>
<?php foreach($ds_header_labels as $labels):?>
<th colspan='<?php count($labels['sublabels'])?>'><?=$labels['label']?></th>
<?php endforeach; ?>
<th colspan='2'></th>
</tr>
<tr class='header-bottom'>
<?php foreach($assignment_header_labels as $label):?>
<th class='assignment'><?=$label;?></th>
<?php endforeach;?>
<?php foreach($ds_header_labels as $labels):?>
<?php foreach($labels['sublabels'] as $label): ?>
<th><?=$label?></th>
<?php endforeach; ?>
<?php endforeach; ?>
<th>&nbsp;</th>
<th>&nbsp;</th>
</tr>