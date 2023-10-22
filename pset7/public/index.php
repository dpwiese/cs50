<?php

    // configuration
    require("../includes/config.php");

    $prows = query("SELECT symbol, shares FROM portfolio WHERE id = ?", $_SESSION["id"]);
    $urows = query("SELECT cash FROM users WHERE id = ?", $_SESSION["id"]);

    $urow = $urows[0];

    $positions = [];
    foreach ($prows as $prow)
    {
        $stock = lookup($prow["symbol"]);
        if ($stock !== false)
        {
            $positions[] = [
                "name" => $stock["name"],
                "price" => $stock["price"],
                "shares" => $prow["shares"],
                "symbol" => $prow["symbol"]
            ];
        }
    }

    // render portfolio
    render("portfolio.php", ["positions" => $positions, "title" => "Portfolio", "cash" => $urow["cash"]]);

?>
