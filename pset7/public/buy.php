<?php

    // configuration
    require("../includes/config.php");

    // if the user arrived via POST, then process the input
    if ($_SERVER["REQUEST_METHOD"] == "POST")
    {
        // validate submission
        if (empty($_POST["symbol"]))
        {
            apologize("You must specify a stock to buy.");
        }
        else if (empty($_POST["shares"]))
        {
            apologize("You must specify a number of shares.");
        }

        // make sure user can only buy whole stocks, not fractions
        else if (preg_match("/^\d+$/", $_POST["shares"]) == false)
        {
            apologize("Invalid number of shares.");
        }

        // look up the info (symbol, name, price) of tock user wants to buy
        $stock = lookup($_POST["symbol"]);

        // check that the stock the user wants to buy is an actual stock
        if ($stock === false)
        {
            apologize("Symbol not found.");
        }

        // retreive the user data (cash)
        $urows = query("SELECT * FROM users WHERE id = ?", $_SESSION["id"]);
        $urow = $urows[0];

        // check how much the cost of the stocks are
        $cost = $stock["price"] * $_POST["shares"];

        // check to see that the user has enough money to buy the stocks
        if ($urow["cash"] >= $cost)
        {
            // subtract the money from the users account: users["cash"]
            query("UPDATE users SET cash = ? WHERE id = ?", $urow["cash"] - $cost, $_SESSION["id"]);

            // check to see if stock is already in portfolio
            $prows = query("SELECT * FROM portfolio WHERE id = ? AND symbol = ?", $_SESSION["id"], $_POST["symbol"]);

            // if the user already has this stock in the portfolio, then we just update this entry with more stocks
            if (count($prows) == 1)
            {
                $prow = $prows[0];
                query("UPDATE portfolio SET shares = ? WHERE id = ? AND symbol = ?", $prow["shares"] + $_POST["shares"], $_SESSION["id"], strtoupper($_POST["symbol"]));
            }
            else
            {
                // if the user doesn't have this stock already, then it needs to be inserted into the table
                query("INSERT INTO portfolio (id, symbol, shares) VALUES(?,?,?)", $_SESSION["id"], strtoupper($_POST["symbol"]), $_POST["shares"]);
            }

            // log the transaction in the history
            query(
                "INSERT INTO history (id, type, symbol, shares, price) VALUES(?,?,?,?,?)",
                $_SESSION["id"],
                "BUY",
                strtoupper($_POST["symbol"]),
                $_POST["shares"],
                $stock["price"]);

            redirect("/");
        }

        // else if user does not have enough money to buy the stocks
        else
        {
            apologize("You can't afford that.");
        }
    }

    // else, if the user didnt arrive via POST, ie the user arrived via GET
    else
    {
        render("buy_form.php", ["title" => "Buy"]);
    }

?>
