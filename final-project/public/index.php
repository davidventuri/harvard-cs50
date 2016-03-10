<?php

    // configuration
    require("../includes/config.php");
    
    // pick a random image's id from the database
    $min = 1;
    $max = 82;
    $random_id = mt_rand($min, $max);
    
    // query database for random image
    $image = CS50::query("SELECT * FROM images WHERE id = ?", $random_id);
    
    // query database for user's score
    $user = CS50::query("SELECT username, score FROM users WHERE id = ?", $_SESSION["id"]);
    
    // render image and buttons
    render("play.php", ["image" => $image, "user" => $user]);
    
?>
