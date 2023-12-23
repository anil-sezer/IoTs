# Deployment Command:
# sudo systemctl stop degreeCheckForBeer.service
# scp degreeCheck.py pi@raspberrypi.local:
# sudo systemctl daemon-reload
# sudo systemctl start degreeCheckForBeer.service

# Check status
# sudo systemctl status degreeCheckForBeer.service


# journalctl -u degreeCheckForBeer.service
# sudo journalctl -u degreeCheckForBeer.service --since 09:00 --until "now"


import os
import glob
import time
from datetime import datetime
# set up logging #####################################
import logging
import sys

logger = logging.getLogger(__name__)
logger.setLevel(logging.INFO)

# this is just to make the output look nice
formatter = logging.Formatter(fmt="%(asctime)s %(name)s.%(levelname)s: %(message)s", datefmt="%Y.%m.%d %H:%M:%S")

# this logs to stdout and I think it is flushed immediately
handler = logging.StreamHandler(stream=sys.stdout)
handler.setFormatter(formatter)
logger.addHandler(handler)

logger.info('Heyya! Service Begun. Working Directory: ' + os.getcwd())
os. chdir("/home/pi")
logger.info('Heyya! Working Directory Is now: ' + os.getcwd())
temperatureFile = open("temperatureFile.txt", "a")
logger.info("Tried to open: " + temperatureFile.name)

temperatureFile.write("Started Service At: " + datetime.now().strftime("%d/%m - %H:%M") + " \n")

#import psycopg2

#con = psycopg2.connect(database="db", user="postgres", password="uwHVFhZUyiJ43g", host="127.0.0.1", port="5432")

#print("Database opened successfully")

os.system('modprobe w1-gpio')
os.system('modprobe w1-therm')

base_dir = '/sys/bus/w1/devices/'
device_folder = glob.glob(base_dir + '28*')[0]
device_file = device_folder + '/w1_slave'


def read_temp_raw():
    f = open(device_file, 'r')
    lines = f.readlines()
    f.close()
    return lines


def read_temp():
    lines = read_temp_raw()
    while lines[0].strip()[-3:] != 'YES':
        time.sleep(0.2)
        lines = read_temp_raw()
    equals_pos = lines[1].find('t=')
    if equals_pos != -1:
        temp_string = lines[1][equals_pos + 2:]
        temp_c = float(temp_string) / 1000.0
        return temp_c


while True:
    temp = read_temp()
    currentTime = datetime.now().strftime("%d/%m - %H:%M")
    text = currentTime + " - " + str(temp) + "\n"
    temperatureFile.write(text)
    temperatureFile.flush()
    logger.info(text)
    time.sleep(10)

