#!/usr/bin/env python3

import os
import sys
import json
from urllib.parse import parse_qs, quote

name = ""
message = ""

method = os.environ.get("REQUEST_METHOD", "GET").upper()
content_type = os.environ.get("CONTENT_TYPE", "")

length = int(os.environ.get("CONTENT_LENGTH", 0)) if os.environ.get("CONTENT_LENGTH") else 0
raw_body = sys.stdin.read(length) if length > 0 else ""

if method == "POST" and raw_body:
    if "application/json" in content_type:
        try:
            data = json.loads(raw_body)
            name = data.get("name", "")
            message = data.get("message", "")
        except json.JSONDecodeError:
            pass # Fail silently or handle error as needed
    elif "application/x-www-form-urlencoded" in content_type:
        # parse_qs returns a dictionary of lists (e.g., {'name': ['value']})
        data = parse_qs(raw_body)
        name = data.get("name", [""])[0]
        message = data.get("message", [""])[0]

print(f"Set-Cookie: username={quote(name)}; Path=/")
print(f"Set-Cookie: message={quote(message)}; Path=/")
print("Content-Type: text/plain\n")