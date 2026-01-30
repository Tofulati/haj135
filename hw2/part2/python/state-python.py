#!/usr/bin/env python3

import os
import sys
import json
from urllib.parse import parse_qs, quote
from http import cookies
import cgitb

# Enable debug mode: prints errors to browser if script crashes
cgitb.enable()

def main():
    try:
        content_length = int(os.environ.get("CONTENT_LENGTH", 0))
    except (ValueError, TypeError):
        content_length = 0

    # Read binary and decode (safest for CGI)
    if content_length > 0:
        body = sys.stdin.buffer.read(content_length).decode('utf-8', 'ignore')
    else:
        body = ""

    # 2. PARSE DATA (Handle JSON vs Form)
    content_type = os.environ.get("CONTENT_TYPE", "")
    name = ""
    message = ""

    if "application/json" in content_type:
        try:
            data = json.loads(body)
            name = data.get("name", "")
            message = data.get("message", "")
        except json.JSONDecodeError:
            pass # Name/Message remain empty
    else:
        # Handle x-www-form-urlencoded
        parsed = parse_qs(body)
        # parse_qs returns lists, use .get(key, [default])[0]
        name = parsed.get("name", [""])[0]
        message = parsed.get("message", [""])[0]

    # 3. SET COOKIES
    # Use SimpleCookie to handle formatting
    cookie = cookies.SimpleCookie()
    
    # Only set if values exist
    if name:
        # Explicitly quote/encode if necessary, though SimpleCookie handles basic quotes
        cookie["username"] = name
        cookie["username"]["path"] = "/"
    
    if message:
        cookie["message"] = message
        cookie["message"]["path"] = "/"

    # Check if we actually have cookies to print
    cookie_string = cookie.output()
    if cookie_string:
        print(cookie_string)
    
    print("Content-Type: text/plain\r\n")

if __name__ == "__main__":
    main()