#!/bin/env python3
import requests
import json

print("==================================================");
print("[Poster Oriented Programming - GKRELLM] API Tester");
print("==================================================");

# Get configuration
is_ok = False
while not is_ok:
    IP = input("Hostname: ")
    PORT = ":" + input("Port: ")
    url = "http://" + IP + PORT + "/"
    print("--> %s" % (url))
    conf = input("OK ? [y/n]")
    if conf == "y":
        is_ok = True

# Test API
while True:
    route = input("Route: ")
    response = requests.get(url + route)
    if response.ok:
        elem = json.loads(response.content.decode())
        print(json.dumps(elem, indent=4, sort_keys=True))
    else:
        print("Error: %s" % (response.status_code))
