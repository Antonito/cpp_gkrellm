#!/bin/env python3

import requests
import progressbar
import colorama
from colorama import Fore, Back, Style
import sys
from time import sleep

IP = "127.0.0.1"
PORT = ":12345"

def up():
    sys.stdout.write('\x1b[1A')
    sys.stdout.flush()

def down():
    sys.stdout.write('\n')
    sys.stdout.flush()


colorama.init()
url = "http://" + IP + PORT

print("==================================================");
print("[Poster Oriented Programming - GKRELLM] API Demo  ");
print("==================================================\n\n");

# Brightness
response = requests.get(url + "/misc")
json = response.json()
max_brightness = json["brightness_max"]
brightness = progressbar.ProgressBar(maxval=max_brightness, \
            widgets=[progressbar.Bar('=', Style.BRIGHT + Fore.YELLOW + 'Brightness'+ Style.RESET_ALL +' [', ']'), ' ', progressbar.Percentage()])

# RAM
response = requests.get(url + "/memory")
json = response.json()
max_ram = json["ram"]["mem_total"]
ram = progressbar.ProgressBar(maxval=max_ram, \
        widgets=[progressbar.Bar('=', Style.BRIGHT + Fore.YELLOW + 'RAM       ' + Style.RESET_ALL + ' [', ']'), ' ', progressbar.Percentage()])

# CPU
response = requests.get(url + "/cpu")
json = response.json()
nb_core = json["nb_core"] - 1
cpu = []
for i in range(nb_core):
    cpu += [progressbar.ProgressBar(maxval=100, \
        widgets=[progressbar.Bar('=', Style.BRIGHT + Fore.YELLOW + 'CORE{}     '.format(i) + Style.RESET_ALL + ' [', ']'), ' ', progressbar.Percentage()])]

while True:
    up()
    response = requests.get(url + "/misc")
    json = response.json()
    brightness.update(json["brightness"])
    down()

    response = requests.get(url + "/memory")
    json = response.json()
    ram.update(max_ram - json["ram"]["mem_available"])
    sleep(0.1)

    response = requests.get(url + "/cpu")
    json = response.json()
    total_jiffies1 = []
    work_jiffies1 = []
    for i in range(nb_core):
        total_jiffies1 += [json["core"][i]["user"] + json["core"][i]["nice"] + json["core"][i]["system"] + json["core"][i]["idle"] + json["core"][i]["iowait"] + json["core"][i]["irq"] + json["core"][i]["softirq"]]
        work_jiffies1 += [json["core"][i]["user"] + json["core"][i]["nice"] + json["core"][i]["system"]]

    sleep(0.1);
    response = requests.get(url + "/cpu")
    json = response.json()
    total_jiffies2 = []
    work_jiffies2 = []
    for i in range(nb_core):
        total_jiffies2 += [json["core"][i]["user"] + json["core"][i]["nice"] + json["core"][i]["system"] + json["core"][i]["idle"] + json["core"][i]["iowait"] + json["core"][i]["irq"] + json["core"][i]["softirq"]]
        work_jiffies2 += [json["core"][i]["user"] + json["core"][i]["nice"] + json["core"][i]["system"]]

    for i in range(nb_core):
        down()
        work_over_period = work_jiffies2[i] - work_jiffies1[i];
        total_over_period = total_jiffies2[i] - total_jiffies1[i];
        if total_over_period != 0:
            load = work_over_period / total_over_period * 100
        else:
            load = 0
        cpu[i].update(load)

    for i in range(nb_core):
        up()


brightness.finish()
