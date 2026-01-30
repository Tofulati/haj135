<?php
$query_string = $_SERVER['QUERY_STRING'] ?? '';
parse_str($query_string, $parsed_query);

$name = $parsed_query['name'];
$message = $parsed_query['message'];
$expire = 0;
$path = "/";

setcookie('username', $name, $expire, $path);
setcookie('message', $message, $expire, $path);
?>
