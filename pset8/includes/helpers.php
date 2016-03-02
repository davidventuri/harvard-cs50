<?php

    /**
     * Looks up news articles for specified geography. Retuns an array of
     * associative arrays, each of which has two keys: link and title.
     */
    function lookup($geo)
    {
        // enable $_SESSION
        @session_start();

        // if this geo was cached
        if (isset($_SESSION["cache"], $_SESSION["cache"][$geo]))
        {
            // within the past hour
            if (time() < $_SESSION["cache"][$geo]["timestamp"] + 60 * 60)
            {
                // return cached articles
                return $_SESSION["cache"][$geo]["articles"];
            }
        }

        // (soon-to-be numerically indexed) array of articles
        $articles = [];
        
        // headers for proxy servers
        $headers = [
            "Accept" => "*/*",
            "Connection" => "Keep-Alive",
            "User-Agent" => sprintf("curl/%s", curl_version()["version"])
        ];
        $context = stream_context_create([
            "http" => [
                "header" => implode(array_map(function($value, $key) { return sprintf("%s: %s\r\n", $key, $value); }, $headers, array_keys($headers))),
                "method" => "GET"
            ]
        ]);

        // download RSS from Google News if possible
        $contents = @file_get_contents("http://news.google.com/news?geo=" . urlencode($geo) . "&output=rss", false, $context);
        if ($contents !== false)
        {
            // parse RSS
            $rss = @simplexml_load_string($contents);
            if ($rss !== false)
            {
                // iterate over items in channel
                foreach ($rss->channel->item as $item)
                {
                    // add article to array
                    $articles[] = [
                        "link" => (string) $item->link,
                        "title" => (string) $item->title
                    ];
                }

                // cache articles
                if (!isset($_SESSION["cache"]))
                {
                    $_SESSION["cache"] = [];
                }
                $_SESSION["cache"][$_GET["geo"]] = [
                    "articles" => $articles,
                    "timestamp" => time()
                ];
            }
        }

        // else from the Onion
        else
        {
            $contents = @file_get_contents("http://www.theonion.com/feeds/rss", false, $context);
            if ($contents !== false)
            {
                // parse RSS
                $rss = @simplexml_load_string($contents);
                if ($rss !== false)
                {
                    // iterate over items in channel
                    foreach ($rss->channel->item as $item)
                    {
                        // add article to array
                        $articles[] = [
                            "link" => (string) $item->link,
                            "title" => (string) $item->title
                        ];
                    }
                }
            }
        }

        return $articles;
    }

?>
