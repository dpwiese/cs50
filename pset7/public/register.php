<?php

    // configuration
    require("../includes/config.php");

    // if user reached page via GET (as by clicking a link or via redirect) then render register form
    if ($_SERVER["REQUEST_METHOD"] == "GET")
    {
        render("register_form.php", ["title" => "Register"]);
    }

    // else if user reached page via POST then we need to process their registration information and log them in if valid
    else if ($_SERVER["REQUEST_METHOD"] == "POST")
    {
        // validate submission
        if (empty($_POST["username"]))
        {
            apologize("You must provide your username.");
        }
        else if (empty($_POST["password"]))
        {
            apologize("You must provide your password.");
        }
        else if (empty($_POST["confirmation"]))
        {
            apologize("You must confirm your password.");
        }
        else if ($_POST["password"] != $_POST["confirmation"])
        {
            apologize("Passwords do not match");
        }

        // query database for user to see if user is there already
        $result = query("SELECT * FROM users WHERE username = ?", $_POST["username"]);

        // if user name already exists in database, then apologize
        if ($result == true)
        {
            apologize("Username is already taken.");
        }

        // else, if username is not there, then add the username
        else
        {
            // insert user into database with encrypted password, and starting with zero dollars
            query("INSERT INTO users (username, hash, cash) VALUES(?,?,0)", $_POST["username"], crypt($_POST["password"]));
            $rows = query("SELECT LAST_INSERT_ID() AS id");

            // first (and only) row
            $row = $rows[0];

            // remember that user's now logged in by storing user's ID in session
            $_SESSION["id"] = $row["id"];

            // redirect to portfolio
            redirect("/");
        }
    }

?>
