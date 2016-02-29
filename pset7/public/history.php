<?php

    // configuration
    require("../includes/config.php");
    
    // query database for user's transaction history
    $transactions = CS50::query("SELECT * FROM history WHERE user_id = ?", $_SESSION["id"]);
    
    if (count($transactions) == 0)
        {
            apologize("No transactions to display.");
        }
    else
    {
        // format price to at least two decimal places but no more than four
        $num_transactions = count($transactions);
        for ($i = 0; $i < $num_transactions; $i++)
        {
            $transactions[$i]["price"] = desired_decimal_format($transactions[$i]["price"]);
        }
        
        render("history.php", ["transactions" => $transactions, "title" => "History"]);
    }
    
?>