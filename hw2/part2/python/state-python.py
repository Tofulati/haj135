#!/usr/bin/env python3

import os
from urllib.parse import parse_qs
import http.cookies

query_string = os.environ.get("QUERY_STRING", "")
parsed_query = parse_qs(query_string)
parsed_query = {k: v[0] if len(v) == 1 else v for k, v in parsed_query.items()}
cookie = http.cookies.SimpleCookie()
cookie["username"] = parsed_query["name"]
cookie["message"] = parsed_query["message"]

print(cookie.output())
