<?php

    // configuration
    require("../includes/config.php");

    // if user reached page via GET (as by clicking a link or via redirect)
    if ($_SERVER["REQUEST_METHOD"] == "GET")
    {
        // else render form
        render("register_form.php", ["title" => "Register"]);
    }

    // else if user reached page via POST (as by submitting a form via POST)
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
            apologize("You must provide your password confirmation.");
        }
        else if ($_POST["password"] != $_POST["confirmation"])
        {
            apologize("Password and password confirmation must be the same.");
        }
        
        // query returns 0 on insert failure caused by non-unique username
        $insert_success = CS50::query("INSERT IGNORE INTO users (username, hash) VALUES(?, ?)", $_POST["username"], password_hash($_POST["password"], PASSWORD_DEFAULT));
        
        if($insert_success != 0)
        {
            // find user id
            $rows = CS50::query("SELECT LAST_INSERT_ID() AS id");
            $id = $rows[0]["id"];
            
            // remember that user's now logged in by storing user's ID in session
            $_SESSION["id"] = $id;

            // redirect to portfolio
            redirect("/");
        }
        
        // else apologize
        apologize("Username has already been taken.");
    }

?>