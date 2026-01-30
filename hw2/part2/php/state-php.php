<?php
$contentType = $_SERVER["CONTENT_TYPE"] ?? '';
$name = "";
$message = "";

if (stripos($contentType, 'application/json') !== false) {
    // Handle JSON: Read raw input stream
    $input = file_get_contents('php://input');
    $data = json_decode($input, true);
    $name = $data['name'] ?? '';
    $message = $data['message'] ?? '';
} else {
    // Handle Form Data: PHP does this automatically in $_POST
    $name = $_POST['name'] ?? '';
    $message = $_POST['message'] ?? '';
}

// 2. Set Cookies
// setcookie() sends headers, so this must happen before any HTML output
setcookie('username', $name, 0, "/");
setcookie('message', $message, 0, "/");
?>
