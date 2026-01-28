#!/usr/bin/env python3

import os
import sys
import json
from urllib.parse import parse_qs

method = os.environ.get("REQUEST_METHOD", "GET").upper()
content_type = os.environ.get("CONTENT_TYPE", "")

length = int(os.environ.get("CONTENT_LENGTH", 0))
input_data = sys.stdin.read(length) if length > 0 else ""

data = {}

if method == "GET":
    query = os.environ.get("QUERY_STRING", "")
    data = parse_qs(query)
    data = {k: v[0] if len(v) == 1 else v for k, v in data.items()}
else:
    if "application/json" in content_type:
        try:
            data = json.loads(input_data) if input_data else {}
        except json.JSONDecodeError:
            data = {"error": "Invalid JSON"}
    else:
        data = parse_qs(input_data)
        data = {k: v[0] if len(v) == 1 else v for k, v in data.items()}

response = {
    "method": method,
    "user_ip": os.environ.get("REMOTE_ADDR", "Unknown"),
    "user_agent": os.environ.get("HTTP_USER_AGENT", "Unknown"),
    "data": data
}

print("Content-Type: application/json\n")
print(json.dumps(response, indent=2))
