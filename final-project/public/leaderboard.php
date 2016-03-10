<?php

    // configuration
    require("../includes/config.php");
    
    $user = CS50::query("SELECT username, score FROM users WHERE id = ?", $_SESSION["id"]);
    $rankings = CS50::query("SELECT username, score FROM users ORDER BY score DESC LIMIT 9");
    
    render("leaderboard.php", ["user" => $user, "rankings" => $rankings]);
    
?>