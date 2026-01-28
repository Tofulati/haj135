<?php
header("Content-Type: application/json");

echo json_encode([
    "team" => "HAJ135",
    "message" => "Welcome to the 'Hello JSON PHP' page - Albert, Hajin, Joey",
    "language" => date("m-d-Y H:i:s"),
    "ip" => $_SERVER['REMOTE_ADDR'],
]);