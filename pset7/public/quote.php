<?php

    // configuration
    require("../includes/config.php");
    
    // if user reached page via GET (as by clicking a link or via redirect)
    if ($_SERVER["REQUEST_METHOD"] == "GET")
    {
        // else render form
        render("quote_form.php", ["title" => "Get Quote"]);
    }
    
    // else if user reached page via POST (as by submitting a form via POST)
    else if ($_SERVER["REQUEST_METHOD"] == "POST")
    {
         // lookup stock symbol
        $stock = lookup($_POST["symbol"]);
        
        // ensure stock exists
        if ($stock != false)
        {
            // format price to at least two decimal places but no more than four
            $stock["price"] = desired_decimal_format($stock["price"]);
            render("quote.php", ["title" => "Quote", "stock" => $stock]);
        }
        // if stock doesn't exist
        else
        {
            apologize("Stock does not exist.");
        }
    }

?>