from rp2 import PIO, StateMachine, asm_pio
from machine import Pin, PWM, time_pulse_us, Timer
import array, time
import gc

# This is a possible example of how to use a servo and an ultrasonic sensor
# Next step:
# - use the collected data to draw a map around the vehicle

# Ultrasonic sensor HC-SR04
# Pinout
# Vcc Trig Echo Gnd
# Vcc:  Power 5V
# Trig: 10us trigger signal from uController.
#    Accepts 3.3V
# Echo: Single pulse signal from sensor.
#    Pulse duration proportional with the distance to the obstacle.
#    5V signal !!!
#    Connect to uController input pin via voltage divider: 330 Ohm + 680 Ohm
# Gnd:  Power ground

TriggerPin = Pin(8,Pin.OUT)
EchoPin    = Pin(9,Pin.IN)
LEDPin     = Pin(25,Pin.OUT)
distance = 0

TIMEOUT_ECHO = const(2000)
V_SOUND_2    = const(17)
MAX_DISTANCE = const(40)

# Servo PWM: ORANGE
# SERVO Vcc: RED
# Servo GND: BROWN
Servo      = PWM(Pin(2))
Servo.freq(50)
Servo.duty_ns(1500000)
DutyValues = [ 480000, 536000, 592000, 648000, 704000, 760000,
               816000, 872000, 928000, 984000,1040000,1096000,
              1152000,1208000,1264000,1320000,1376000,1432000,
              1488000,1544000,1600000,1656000,1712000,1768000,
              1824000,1880000,1936000,1992000,2048000,2104000,
              2160000,2216000,2272000,2328000,2384000,2440000]
angleValues = [0,5,10,15,21,26,31,36,41,46,51,57,62,67,72,77,82,87,93,98,103,108,113,118,123,129,134,139,144,149,154,159,165,170,175,180]


ServoPosition = 0
ServoDirection = 1

@asm_pio(set_init=PIO.OUT_LOW)
def TriggerPulse():
    pull()                # wait for PIO buffer new value
    set(pins, 1) [9]      # set output pin to 1 for 10 steps = 10us
    set(pins, 0)          # reset output pin

# Statemachine number 1, running the TriggerPulse at 1MHz on TriggerPin output
sm = StateMachine(1, TriggerPulse, freq=1000000, set_base=TriggerPin)
# PIO buffer. Used for sending dummy data to PIO.
# The PIO program waits for the buffer to become non-empty
ar = array.array("I")

def SweepServo():
    global DutyValues
    global ServoPosition
    global ServoDirection
# The servo sweeps the area in front of the vehicle
    ServoPosition = ServoPosition + ServoDirection
    if ServoDirection == 1:
        if ServoPosition == 35:
            ServoDirection = -1
    else:
        if ServoPosition == 0:
            ServoDirection = 1
    Servo.duty_ns(DutyValues[ServoPosition])

def MeasureDistance():
    global TriggerPin
    global EchoPin
    global ar
    
    RetVal = 0 # used for result
# #     Generating a trigger pulse
# #     Method 1.: simple instruction delay
#     TriggerPin.value(1) # duration of one instruction is ~6us
#     TriggerPin.value(1) # duration of two instructions is ~12us
#     TriggerPin.value(0)

# #     Method 2.: PIO internal delay
    sm.put(ar)       # send the buffer to PIO
    # At this moment the PIO statemachine starts the output pulse of 10us
    
    # time_pulse_us measures an incoming pulse's duration in us
    # time_pulse_us returns -2 if timeout exceeded.
    # 5000 us in duration means 85cm to the obstacle
    # v_sound = 340 m/s
    # distance = v_sound * duration / 2
    # Note: if the obstacle's measured surface is not nearly perpendicular to the sensor's beam,
    # the measurement can be easily compromised
    RetVal = time_pulse_us(EchoPin, 1, TIMEOUT_ECHO)
    if RetVal > 0:
        RetVal = int(RetVal * V_SOUND_2 / 1000)
    else:
        RetVal = MAX_DISTANCE
        
    return RetVal

def TaskSweep(Timer):
    global distance
    LEDPin.value(0)
    SweepServo()
    distance = MeasureDistance()
    print(str(angleValues[ServoPosition])+','+str(distance),end='.')

def Task1s(Timer):
    global distance
    LEDPin.value(1)

#     SweepServo()
#     distance = MeasureDistance()
#     print('{:2}:{:2}'.format(ServoPosition,distance))

    gc.collect()
#    print(gc.mem_free())

#===============================================================================
# Main part - runs only once

# Task timers
TickSweep = Timer()
TickSweep.init(period = 100, mode = Timer.PERIODIC, callback = TaskSweep)

Tick1s = Timer()
Tick1s.init(period = 1000, mode = Timer.PERIODIC, callback = Task1s)
# Garbage collector
gc.enable()

ar = 1           # dummy value, just to have something to send to PIO buffer
# Activate the PIO statemachine
sm.active(1)

