#!/usr/bin/env python3

import os
from datetime import datetime

print("Content-Type: text/html\n")

ip = os.environ.get("REMOTE_ADDR", "Unknown")

html = f"""<!DOCTYPE html>
    <html lang="en">
    <head>
        <meta charset="UTF-8">
        <title>Hello HTML Python</title>
    </head>
    <body>
        <h1>Hello from HAJ135</h1>
        <p>Welcome to Python HTML - Albert, Hajin, Joey</p>
        <p>Language: Python</p>
        <p>Generated at: {datetime.now()}</p>
        <p>Your IP Address: {ip}</p>
    </body>
    </html>
"""

print(html)