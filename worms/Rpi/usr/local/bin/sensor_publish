#!/usr/bin/env python

import serial
import json
import logging
import sys
import paho.mqtt.publish as publish

logging.basicConfig(level=logging.DEBUG)
LOGGER = logging.getLogger('sensor_publish')

def main():
    try:
        with serial.Serial('/dev/ttyACM0') as f:
            while True:
                sensor_json = f.readline()
                try:
                    sensor_data = json.loads(sensor_json)
                    LOGGER.info("Sensor data is %s", sensor_data)
                except Exception as e:
                    LOGGER.info('no valid json that time: %s - %s', sensor_json, e)
                else:
                    publish.single('/sensors/wormbin', payload=json.dumps(sensor_data), hostname='ice-station-zebra.local')
    except Exception as e:
        LOGGER.exception("Bad news: %s", e)
        sys.exit()

if __name__ == '__main__':
    main()
