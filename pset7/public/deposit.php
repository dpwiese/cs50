<?php

    // configuration (MIGHT HAVE TO INCLUDE FUNCTIONS HERE)
    require("../includes/config.php");

    if ($_SERVER["REQUEST_METHOD"] == "POST")
    {
        // validate submission
        if (empty($_POST["deposit"]))
        {
            apologize("You must provide an amount to deposit.");
        }

        // need to figure out how much money the user currently has
        $urows = query("SELECT * FROM users WHERE id = ?", $_SESSION["id"]);
        $urow = $urows[0];

        // give the user the money
        query("UPDATE users SET cash = ? WHERE id = ?", $urow["cash"] + $_POST["deposit"], $_SESSION["id"]);

        // log the transaction in the history
        query(
            "INSERT INTO history (id, type, symbol, shares, price) VALUES(?,?,?,?,?)",
            $_SESSION["id"],
            "DEPOSIT",
            '-',
            '0',
            $_POST["deposit"]);

        redirect("/");

    }

    render("deposit_form.php", ["title" => "Deposit"]);

?>
