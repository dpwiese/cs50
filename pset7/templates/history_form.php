<table class="table table-striped">
    <tr>
        <td> <b> Tranaction Type </b> </td>
        <td> <b> Date/Time </b> </td>
        <td> <b> Symbol </b> </td>
        <td> <b> Shares </b> </td>
        <td> <b> Price </b> </td>
    </tr>

    <?php

        foreach ($positions as $position)
        {
            print("<tr>");
            print("<td>" . $position["type"] . "</td>");
            print("<td>" . $position["timestamp"] . "</td>");
            print("<td>" . $position["symbol"] . "</td>");
            print("<td>" . $position["shares"] . "</td>");
            print("<td>$" . number_format($position["price"], 2, '.', ',') . "</td>");
            print("</tr>");
        }

    ?>
</table>
