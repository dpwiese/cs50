<table class="table table-striped">
    <tr>
        <td> <b> Symbol </b> </td>
        <td> <b> Number of Shares </b> </td>
        <td> <b> Price per Share </b> </td>
    </tr>

    <?php

        foreach ($positions as $position)
        {
            print("<tr>");
            print("<td>" . $position["symbol"] . "</td>");
            print("<td>" . $position["shares"] . "</td>");
            print("<td>$" . number_format($position["price"], 2, '.', ',') . "</td>");
            print("</tr>");
        }

    ?>
</table>

<div>
    <h3>
        <?php
            print("Your account balance is: $" . number_format($cash, 2, '.', ','));
        ?>
    </h3>
</div>
