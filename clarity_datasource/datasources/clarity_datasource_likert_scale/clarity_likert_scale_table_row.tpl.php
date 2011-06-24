<tr>
    <td class='user'><?=$data->uid?></td>
    <td class='timestamp'><?=$data->timestamp?></td>
    <td class='value' ><?php print $data->extra['string_value'] . ' (' . $data->value . ')'; ?></td>
    <td class='modified'><?=$data->modified_time?></td>
    <td class='actions'><a class='edit' href='#'>edit</a></td>
</tr>
