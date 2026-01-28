<?php
header("Content-Type: text/plain");

$protocol = $_SERVER['SERVER_PROTOCOL'] ?? 'unknown';
$method = $_SERVER['REQUEST_METHOD'] ?? 'unknown';
$query_string = $_SERVER['QUERY_STRING'] ?? '';
$content_type = $_SERVER['CONTENT_TYPE'] ?? '';
$raw_body = file_get_contents('php://input');

parse_str($query_string, $parsed_query);

$parsed_body = [];
if (in_array($method, ['POST','PUT','DELETE'])) {
    if (strpos($content_type, 'application/json') !== false) {
        $parsed_body = json_decode($raw_body, true) ?: [];
    } else {
        parse_str($raw_body, $parsed_body);
    }
}

$hostname = gethostname();
$timestamp = date("Y-m-d H:i:s");
$user_ip = $_SERVER['REMOTE_ADDR'] ?? 'Unknown';
$user_agent = $_SERVER['HTTP_USER_AGENT'] ?? 'Unknown';

function to_json($arr) {
    return json_encode($arr, JSON_UNESCAPED_SLASHES);
}

echo "Server Protocol: $protocol\n";
echo "HTTP Method: $method\n";
echo "Raw Query: $query_string\n";
echo "Parsed Query: " . to_json($parsed_query) . "\n";
echo "Raw Message Body: $raw_body\n";
echo "Parsed Message Body: " . to_json($parsed_body) . "\n";
echo "Hostname: $hostname\n";
echo "Timestamp: $timestamp\n";
echo "IP Address: $user_ip\n";
echo "User-Agent: $user_agent\n";
?>
