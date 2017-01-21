#!/bin/env python3

import requests
import time
import matplotlib.pyplot as plt
import matplotlib.animation as animation
import numpy as np

IP = "127.0.0.1"
PORT = ":12345"

url = "http://" + IP + PORT + "/cpu"
response = requests.get(url)
if response.ok:
    print ("%s" % (response.content))
else:
    response.raise_for_status()
json = response.json()

fig = plt.figure()
ax = plt.axes(xlim=(0, 1), ylim=(0, 3500))
line, = ax.plot([], [], lw=2)

def init():
    line.set_data([], [])
    return line,

def animate(i):
    response = requests.get(url)
    json = response.json()
    x = np.linspace(0, 2, 1000)
    y = json["core"][0]["freq_mhz"]
    line.set_data(x, y)
    return line,

anim = animation.FuncAnimation(fig, animate, init_func=init,
                               frames=2, interval=20, blit=True)
plt.show()
