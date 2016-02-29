<?php

    // configuration
    require("../includes/config.php");
    
    // if user reached page via GET (as by clicking a link or via redirect)
    if ($_SERVER["REQUEST_METHOD"] == "GET")
    {
        // else render form
        render("change_password_form.php", ["title" => "Change Password"]);
    }
    
     // else if user reached page via POST (as by submitting a form via POST)
    else if ($_SERVER["REQUEST_METHOD"] == "POST")
    {
        // query database for user's hashed password
        $hash = CS50::query("SELECT hash FROM users WHERE id = ?", $_SESSION["id"]);
        $old_password_hash = $hash[0]["hash"];
        
        // confirm old password submitted via post matches password in database
        if (password_verify($_POST["old-password"], $old_password_hash) != true)
        {
            apologize("Old password submitted is incorrect.");
        }
        // confirm new password matches new password confirmation
        else if ($_POST["new-password"] != $_POST["new-password-confirmation"])
        {
            apologize("New password does not match its confirmation.");
        }
        // change password hash in database
        else
        {
            CS50::query("UPDATE users SET hash = ? WHERE id = ?", password_hash($_POST["new-password"], PASSWORD_DEFAULT), $_SESSION["id"]);
            render("change_password_success.php", ["title" => "Password Change Success"]);
        }
    }
?>