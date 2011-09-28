<tr class='row <?=$zebra?>'>
<?php foreach ($columns as $col_id => $column): ?>
<td class="<?= $col_id . ' ' . $column['classes']?>"><?= $column['content']; ?></td>
<?php endforeach; ?>
</tr>
