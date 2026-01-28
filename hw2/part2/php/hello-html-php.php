<?php
    $team = "HAJ135";
    $lang = "PHP";
    $datetime = date("m-d-Y H:i:s");
    $ip = $_SERVER['REMOTE_ADDR'];
?>

<!DOCTYPE html>
<html>
    <head>
        <title>Hello HTML PHP</title>
    </head>
    <body>
        <h1>Hello from <? echo $team ?></h1>
        <p>Welcome to the "Hello HTML PHP" page - Albert, Hajin, Joey</p>
        <p>Coding language: <? echo $lang ?></p>
        <p>Generated at: <? echo $datetime ?></p>
        <p>Your IP address: <? echo $ip ?></p>
    </body>
</html>