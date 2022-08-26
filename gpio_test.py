import Adafruit_BBIO.GPIO as GPIO
import time
from threading import Thread
from datetime import datetime

GPIO.setup("P8_10", GPIO.OUT)
GPIO.setup("P8_8", GPIO.IN)

is_sending = False
should_end = False

flick_state = False
def flick():
  global flick_state, should_end
  while True:
    if should_end:
      break
    output = GPIO.HIGH if flick_state else GPIO.LOW
    GPIO.output("P8_10", output)
    time.sleep(1)
    flick_state = not flick_state

read_counter = 0
old_state = 0
def reader():
  global should_end, old_state, read_counter
  while True:
    if should_end:
      break
    read_data = GPIO.input("P8_8")
    if read_data != old_state:
      print("edge")
      old_state = read_data
    read_counter = read_counter + 1


flick_thread = Thread(target=flick)
flick_thread.start()

read_thread = Thread(target=reader)
read_thread.start()

time.sleep(10)
should_end = True
flick_thread.join()
read_thread.join()

print(read_counter)
GPIO.cleanup()
