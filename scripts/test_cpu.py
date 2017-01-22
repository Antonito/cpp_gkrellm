#!/bin/env python3

import threading

#
# Starts several threads
#

def bench():
    while True:
        pass

for i in range(12):
    threading.Thread(target=bench).start()
