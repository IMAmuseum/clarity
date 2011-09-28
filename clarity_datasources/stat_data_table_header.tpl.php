<colgroup span='4'></colgroup>
<colgroup span='<?=count($ds_header_labels);?>'></colgroup>
<tr class='header-top'>
<th colspan='4'>Assignment</th>
<?php foreach($ds_header_labels as $labels):?>
<th colspan='<?php count($labels['sublabels'])?>'><?=$labels['label']?></th>
<?php endforeach; ?>
<th colspan='2'></th>
</tr>
<tr class='header-bottom'>
<th class='assignment'>User</th>
<th class='assignment'>Date</th>
<th class='assignment'>Date Modified</th>
<th class='assignment'>&nbsp;</th>
<?php foreach($ds_header_labels as $labels):?>
<?php foreach($labels['sublabels'] as $label): ?>
<th><?=$label?></th>
<?php endforeach; ?>
<?php endforeach; ?>
<th>&nbsp;</th>
<th>&nbsp;</th>
</tr>