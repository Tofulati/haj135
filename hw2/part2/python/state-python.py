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