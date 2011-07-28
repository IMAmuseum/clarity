<div class='row <?=$zebra?>'>
<?php foreach ($columns as $col_id => $column): ?>
<div class="column <?= $col_id . ' ' . $column['classes'] ?>"><?= $column['content']; ?></div>
<?php endforeach; ?>
</div>
<div class='clear'></div>
