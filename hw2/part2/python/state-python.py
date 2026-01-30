#!/usr/bin/env python3
import os
import sys
import json
from urllib.parse import parse_qs
import http.cookies

# 1. Read POST Body
try:
    content_length = int(os.environ.get("CONTENT_LENGTH", 0))
except ValueError:
    content_length = 0

body = sys.stdin.read(content_length)

# 2. Parse Data based on Content-Type
content_type = os.environ.get("CONTENT_TYPE", "")
name = ""
message = ""

if "application/json" in content_type:
    try:
        data = json.loads(body)
        name = data.get("name", "")
        message = data.get("message", "")
    except json.JSONDecodeError:
        pass
else:
    # parse_qs returns a dictionary of lists: {'name': ['value']}
    parsed = parse_qs(body)
    name = parsed.get("name", [""])[0]
    message = parsed.get("message", [""])[0]

# 3. Create Cookie Object
cookie = http.cookies.SimpleCookie()
cookie["username"] = name
cookie["username"]["path"] = "/"
cookie["message"] = message
cookie["message"]["path"] = "/"

# 4. Output Headers
print(cookie.output()) 
print("Content-Type: text/plain\r\n")