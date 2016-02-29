<?php

    // configuration
    require("../includes/config.php"); 

    // query database for user's information
    $user = CS50::query("SELECT * FROM users WHERE id = ?", $_SESSION["id"]);
    $user[0]["cash"] = desired_decimal_format($user[0]["cash"]);
    
    // query database for user's holdings
    $rows = CS50::query("SELECT * FROM portfolios WHERE user_id = ?", $_SESSION["id"]);
    
    $positions = [];
    foreach ($rows as $row)
    {
        $stock = lookup($row["symbol"]);
        if ($stock !== false)
        {
            // calculate current value of holdings for each stock
            $total = $stock["price"] * $row["shares"];
            
            // format price and total to at least two decimal places but no more than four
            $stock["price"] = desired_decimal_format($stock["price"]);
            $total = desired_decimal_format($total);
            
            $positions[] = [
                "name" => $stock["name"],
                "price" => $stock["price"],
                "shares" => $row["shares"],
                "symbol" => $row["symbol"],
                "total" => $total
            ];
        }
    }
    
    render("portfolio.php", ["positions" => $positions, "user" => $user, "title" => "Portfolio"]);
    
?>
