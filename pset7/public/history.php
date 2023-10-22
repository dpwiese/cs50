<?php

    // configuration (MIGHT HAVE TO INCLUDE FUNCTIONS HERE)
    require("../includes/config.php");

    $hrows = query("SELECT * FROM history WHERE id = ?", $_SESSION["id"]);

    $positions = [];
    foreach ($hrows as $hrow)
    {
        // $stock = lookup($prow["symbol"]);
        // if ($stock !== false)
        // {
            $positions[] = [
                "type" => $hrow["type"],
                "timestamp" => $hrow["timestamp"],
                "symbol" => $hrow["symbol"],
                "shares" => $hrow["shares"],
                "price" => $hrow["price"]
            ];
        // }
    }

    render("history_form.php", ["positions" => $positions, "title" => "Price"]);

?>
