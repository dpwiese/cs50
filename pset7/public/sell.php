<?php

    // configuration
    require("../includes/config.php");

    // if the user arrived via POST, then process the input
    if ($_SERVER["REQUEST_METHOD"] == "POST")
    {
        // validate submission
        if (empty($_POST["symbol"]))
        {
            apologize("You must provide a stock symbol.");
        }

        // look up the info (symbol, name, price) of tock user wants to sell
        $stock = lookup($_POST["symbol"]);

        // check that the stock the user wants to sell is an actual stock
        if ($stock === false)
        {
            apologize("Symbol not found.");
        }

        // retreive the user data (cash) and portfolio data (shares)
        $urows = query("SELECT * FROM users WHERE id = ?", $_SESSION["id"]);
        $prows = query("SELECT * FROM portfolio WHERE id = ? AND symbol = ?", $_SESSION["id"], $_POST["symbol"]);

        // if the user has the requested stock to sell
        if (count($prows) == 1)
        {
            // first (and only) row
            $urow = $urows[0];
            $prow = $prows[0];

            // delete the stock from the users portfolio
            query("DELETE FROM portfolio WHERE id = ? AND symbol = ?", $_SESSION["id"],  $_POST["symbol"]);

            // give the user the money
            query("UPDATE users SET cash = ? WHERE id = ?", $urow["cash"] + $prow["shares"] * $stock["price"], $_SESSION["id"]);

            // log the transaction in the history
            query(
                "INSERT INTO history (id, type, symbol, shares, price) VALUES(?,?,?,?,?)",
                $_SESSION["id"],
                "SELL",
                $_POST["symbol"],
                $prow["shares"],
                $stock["price"]);

            redirect("/");
        }

        // otherwise, if user does not have the stock to sell: apologize
        else
        {
            apologize("You don't have any of this stock to sell");
        }
    }

    // else, if the user didnt arrive via POST, ie the user arrived via GET
    else
    {
        render("sell_form.php", ["title" => "Sell"]);
    }

?>
