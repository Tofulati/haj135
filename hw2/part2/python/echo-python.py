#!/usr/bin/env python3

import os
import sys
import json
from urllib.parse import parse_qs
from datetime import datetime
import socket

method = os.environ.get("REQUEST_METHOD", "GET").upper()
protocol = os.environ.get("SERVER_PROTOCOL", "unknown")
query_string = os.environ.get("QUERY_STRING", "")
content_type = os.environ.get("CONTENT_TYPE", "")

length = int(os.environ.get("CONTENT_LENGTH", 0)) if os.environ.get("CONTENT_LENGTH") else 0
raw_body = sys.stdin.read(length) if length > 0 else ""

parsed_query = parse_qs(query_string)
parsed_query = {k: v[0] if len(v) == 1 else v for k, v in parsed_query.items()}

parsed_body = {}
if method in ["POST", "PUT", "DELETE"]:
    if "application/json" in content_type:
        try:
            parsed_body = json.loads(raw_body) if raw_body else {}
        except json.JSONDecodeError:
            parsed_body = {"error": "Invalid JSON"}
    else:
        parsed_body = parse_qs(raw_body)
        parsed_body = {k: v[0] if len(v) == 1 else v for k, v in parsed_body.items()}

hostname = socket.gethostname()
timestamp = datetime.now().strftime("%Y-%m-%d %H:%M:%S")
user_ip = os.environ.get("REMOTE_ADDR", "Unknown")
user_agent = os.environ.get("HTTP_USER_AGENT", "Unknown")

print("Content-Type: text/plain\n")
print(f"Server Protocol: {protocol}")
print(f"HTTP Method: {method}")
print(f"Raw Query: {query_string}")
print(f"Parsed Query: {json.dumps(parsed_query)}")
print(f"Raw Message Body: {raw_body}")
print(f"Parsed Message Body: {json.dumps(parsed_body)}")
print(f"Hostname: {hostname}")
print(f"Timestamp: {timestamp}")
print(f"IP Address: {user_ip}")
print(f"User-Agent: {user_agent}")
