<?php
header("Content-Type: application/json");

$contentType = $_SERVER['CONTENT_TYPE'] ?? '';
$rawBody = file_get_contents("php://input");

if (strpos($contentType, "application/json") !== false) {
    $data = json_decode($rawBody, true);
} else {
    $data = $_REQUEST;
}

$response = [
    "hostname" => gethostname(),
    "time" => date("m-d-Y H:i:s"),
    "ip" => $_SERVER['REMOTE_ADDR'] ?? "unknown",
    "user_agent" => $_SERVER['HTTP_USER_AGENT'] ?? "unknown",
    "method" => $_SERVER['REQUEST_METHOD'],
    "content_type" => $contentType,
    "data_recieved" => $data
];

echo json_encode($response, JSON_PRETTY_PRINT);