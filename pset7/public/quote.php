<?php

    // configuration (MIGHT HAVE TO INCLUDE FUNCTIONS HERE)
    require("../includes/config.php");

    if ($_SERVER["REQUEST_METHOD"] == "POST")
    {
        // if result of lookup is not false
        $stock = lookup($_POST["symbol"]);

        if ($stock == false)
        {
            apologize("Symbol not found.");
        }
        else
        {
            render("quote.php", ["title" => "Quote", "stock" => $stock]);
        }
    }
    else
    {
        render("quote_form.php", ["title" => "Quote"]);
    }

?>
