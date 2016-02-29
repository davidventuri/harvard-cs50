<?php

    // configuration
    require("../includes/config.php");
    
    // if user reached page via GET (as by clicking a link or via redirect)
    if ($_SERVER["REQUEST_METHOD"] == "GET")
    {
        // query database for user's holdings
        $rows = CS50::query("SELECT * FROM portfolios WHERE user_id = ?", $_SESSION["id"]);
        
        // if user has no holdings
        if (count($rows) == 0)
        {
            apologize("Nothing to sell.");
        }
        else
        {
            // render sell form
            render("sell_form.php", ["rows" => $rows, "title" => "Sell"]);
        }
    }
    // else if user reached page via POST (as by submitting a form via POST)
    else if ($_SERVER["REQUEST_METHOD"] == "POST")
    {
        // calculate current value of holdings for stock submitted via sell form
        $shares = CS50::query("SELECT shares FROM portfolios WHERE user_id = ? AND symbol = ?", $_SESSION["id"], $_POST["symbol"]);
        $stock = lookup($_POST["symbol"]);
        $total = $stock["price"] * $shares[0]["shares"];
        
        // update user's cash balance with proceeds from sale of stock
        CS50::query("UPDATE users SET cash = cash + ? WHERE id = ?", $total, $_SESSION["id"]);
        
        // delete total position in stock submitted via sell form
        CS50::query("DELETE FROM portfolios WHERE user_id = ? AND symbol = ?", $_SESSION["id"], $stock["symbol"]);
        
        // insert row into transaction history table
        CS50::query("INSERT INTO history (user_id, transaction, symbol, shares, price) VALUES (?, ?, ?, ?, ?)", $_SESSION["id"], "SELL", $stock["symbol"], $shares[0]["shares"], $stock["price"]);
        
        // redirect to portfolio
        redirect("/");
    }
    
?>
