<?php

    require(__DIR__ . "/../includes/config.php");

    // numerically indexed array of places
    $places = [];

    // TODO: search database for places matching $_GET["geo"]
    $location = $_GET["geo"];

    $sql = "SELECT country_code, postal_code, place_name, admin_name1, admin_code1, admin_name2, latitude, longitude
            FROM places
            WHERE(  country_code LIKE '$location'
                    OR postal_code LIKE '$location'
                    OR place_name LIKE '$location'
                    OR admin_name1 LIKE '$location'
                    OR admin_code1 LIKE '$location'
                    OR admin_name2 LIKE '$location')";

    $places = query($sql);

    // output places as JSON (pretty-printed for debugging convenience)
    header("Content-type: application/json");
    print(json_encode($places, JSON_PRETTY_PRINT));

?>
