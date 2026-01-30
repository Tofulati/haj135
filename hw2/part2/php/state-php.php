<?php
$query_string = $_SERVER['QUERY_STRING'] ?? '';
parse_str($query_string, $parsed_query);
setcookie("username", $parsed_query['username']);
setcookie("message", $parsed_query['message']);
?>
