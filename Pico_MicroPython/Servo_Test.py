from machine import PWM, Pin, Timer

#---------------------------------
Servo_1 = PWM(Pin(15))
Servo_1.freq(50)

taskCounter = 0
state = 0
DutyValues = [600000, 1000000, 1500000, 2000000, 2400000, 2000000, 1500000, 1000000]
#---------------------------------
def SetServoDuty(dutyCycle):
# 0 degree   :  500000
#180 degrees : 2500000
    global Servo_1
    if (dutyCycle < 500000):
        dutyCycle = 500000
    if (dutyCycle > 2500000):
        dutyCycle = 2500000
    Servo_1.duty_ns(dutyCycle)
#---------------------------------
def Task20ms(timer):
    global taskCounter
    global state
    
    taskCounter = taskCounter + 1
    if (taskCounter == 50):
        taskCounter = 0
        state = state + 1
        if (state == 8):
            state = 0
    SetServoDuty(DutyValues[state])

#---------------------------------
SetServoDuty(DutyValues[state])

tim20ms = Timer()
tim20ms.init(freq = 50, mode = Timer.PERIODIC, callback = Task20ms)