import Adafruit_BBIO.GPIO as GPIO
import Adafruit_BBIO.PWM as PWM
import time

brightness = [25,50,75]
i_brightness = 0
 
#PWM.start(channel, duty, freq=2000, polarity=0)
PWM.start("P9_14", 50)

# Will cycle through three level of brightness
while True:
	if(i_brightness == 3)
		i_brightness = 0
    PWM.set_duty_cycle("P9_14", brightness[i_brightness++])
    time.sleep(0.5)