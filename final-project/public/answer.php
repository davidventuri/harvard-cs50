<?php

    // configuration
    require("../includes/config.php");
    
    // if user reached page via GET (as by clicking a link or via redirect)
    if ($_SERVER["REQUEST_METHOD"] == "GET")
    {
        // redirect to game page
        redirect("/");
    }
    // else if user reached page via POST (as by submitting a form via POST)
    else if ($_SERVER["REQUEST_METHOD"] == "POST")
    {
        list($submitted_answer, $correct_answer, $url, $name) = explode("^", $_POST['answer'], 4);
        
        if ($submitted_answer == "rick" && $correct_answer == "r")
        {
            // update user's score
            CS50::query("UPDATE users SET score = score + 1 WHERE id = ?", $_SESSION["id"]);
            $user = CS50::query("SELECT username, score FROM users WHERE id = ?", $_SESSION["id"]);
            $background = "#00D200";
            $message = "Correct! This is " . $name . ".";
            render("answer.php", ["background" => $background, "user" => $user, "message" => $message, "url" => $url]);
        }
        else if ($submitted_answer == "stick" && $correct_answer == "s")
        {
            // update user's score
            CS50::query("UPDATE users SET score = score + 1 WHERE id = ?", $_SESSION["id"]);
            $user = CS50::query("SELECT username, score FROM users WHERE id = ?", $_SESSION["id"]);
            $background = "#00D200";
            $message = "Correct! This is a stick.";
            render("answer.php", ["background" => $background, "user" => $user, "message" => $message, "url" => $url]);
        }
        else if ($submitted_answer == "rick" && $correct_answer == "s")
        {
            $user = CS50::query("SELECT username, score FROM users WHERE id = ?", $_SESSION["id"]);
            $background = "#D20000";
            $message = "Sorry! This is a stick, not a Rick.";
            render("answer.php", ["background" => $background, "user" => $user, "message" => $message, "url" => $url]);
        }
        else if ($submitted_answer == "stick" && $correct_answer == "r")
        {
            $user = CS50::query("SELECT username, score FROM users WHERE id = ?", $_SESSION["id"]);
            $background = "#D20000";
            $message = "Sorry! This is " . $name . ", not a stick.";
            render("answer.php", ["background" => $background, "user" => $user, "message" => $message, "url" => $url]);
        }
    }
?>