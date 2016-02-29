<?php

    // configuration
    require("../includes/config.php");
    
    // if user reached page via GET (as by clicking a link or via redirect)
    if ($_SERVER["REQUEST_METHOD"] == "GET")
    {
        // render buy form
        render("buy_form.php", ["title" => "Buy"]);
    }
    
    // else if user reached page via POST (as by submitting a form via POST)
    else if ($_SERVER["REQUEST_METHOD"] == "POST")
    {
        // lookup stock requested in buy form
        $stock = lookup($_POST["symbol"]);
        
        // if stock requested in buy form does not exist
        if ($stock == false)
        {
            apologize("The requested stock does not exist.");
        }
        
        // if user did not submit a non-negative integer in buy form's shares field
        else if (preg_match("/^\d+$/", $_POST["shares"]) != true)
        {
            apologize("You can only buy whole shares of stocks, not fractions thereof.");
        }
        else
        {
            // determine total cost of requested stock purchase
            $total = $stock["price"] * $_POST["shares"];
            
            // query database for user's cash balance
            $cash = CS50::query("SELECT cash FROM users WHERE id = ?", $_SESSION["id"]);
            
            // if user doesn't have enough cash to buy requested stock position
            if ($cash[0]["cash"] < $total)
            {
                apologize("You don't have enough cash to buy the requested amount of stock.");
            }
            else
            {
                // insert a new row into portfolios table unless the specified
                // id/symbol pair already exists in some row, in which case that 
                // row’s number of shares will simply be increased
                // also, recall that lookup() returns symbol in uppercase
                CS50::query("INSERT INTO portfolios (user_id, symbol, shares) VALUES(?, ?, ?) ON DUPLICATE KEY UPDATE shares = shares + VALUES(shares)", $_SESSION["id"], $stock["symbol"], $_POST["shares"]);
                
                // update user's cash balance following purchase of stock
                CS50::query("UPDATE users SET cash = cash - ? WHERE id = ?", $total, $_SESSION["id"]);
                
                // insert row into transaction history table
                CS50::query("INSERT INTO history (user_id, transaction, symbol, shares, price) VALUES (?, ?, ?, ?, ?)", $_SESSION["id"], "BUY", $stock["symbol"], $_POST["shares"], $stock["price"]);
                
                // redirect to portfolio
                redirect("/");
            }
        }
    }
?>