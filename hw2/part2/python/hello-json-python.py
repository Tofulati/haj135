#!/usr/bin/env python3

import os
import json
from datetime import datetime

print("Content-type: application/json\n")

response = {
    "greeting": "Hello from HAJ135",
    "message": "Welcome to Python JSON - Albert, Hajin, Joey",
    "language": "Python",
    "generated_at": str(datetime.now()),
    "ip": os.environ.get("REMOTE_ADDR", "Unknown")
}

print(json.dumps(response))