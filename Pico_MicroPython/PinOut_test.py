from machine import PWM, Pin, Timer

#---------------------------------
Servo_1 = PWM(Pin(2))
Servo_2 = PWM(Pin(3))
Servo_3 = PWM(Pin(4))
Servo_4 = PWM(Pin(5))

Servo_1.freq(50)
Servo_2.freq(50)
Servo_3.freq(50)
Servo_4.freq(50)

Servo = [Servo_1, Servo_2, Servo_3, Servo_4]
#---------------------------------
Motor_L_1 = PWM(Pin(6))
Motor_L_2 = PWM(Pin(7))
Motor_R_1 = PWM(Pin(8))
Motor_R_2 = PWM(Pin(9))

Motor_L_1.freq(1000)
Motor_L_2.freq(1000)
Motor_R_1.freq(1000)
Motor_R_2.freq(1000)
#---------------------------------
MOTOR_L_ACTIVITY_TIME = 5000 / 20   # time periods in ms, here 5s
MOTOR_R_ACTIVITY_TIME = 5000 / 20   # 7.5s

Motor_L_ActivityCounter = MOTOR_L_ACTIVITY_TIME
Motor_R_ActivityCounter = MOTOR_R_ACTIVITY_TIME

Motor_L_Status = 0
Motor_R_Status = 0

MOTOR_STATUS = {0:50,1:100,2:50,3:0,4:-50,5:-100,6:-50,7:0}
#---------------------------------
def SetServoDuty(servoNumber,dutyCycle):
    global Servo
    if (dutyCycle < 5):
        dutyCycle = 5
    if (dutyCycle > 10):
        dutyCycle = 10
    if servoNumber not in range(1,5):
        print("Wrong servo selected")
    else:
        Servo[servoNumber-1].duty_u16(int(dutyCycle*655.4))
#---------------------------------
def Motor_L(speed):
    if speed > 100:
        speed = 100
    if speed < -100:
        speed = -100
    if speed > 0:
        Motor_L_1.duty_u16(int(speed*65535/100))
        Motor_L_2.duty_u16(0)
    elif speed < 0:
        Motor_L_1.duty_u16(0)
        Motor_L_2.duty_u16(int(-speed*65535/100))
    else:
        Motor_L_1.duty_u16(0)
        Motor_L_2.duty_u16(0)
#---------------------------------
def Motor_R(speed):
    if speed > 100:
        speed = 100
    if speed < -100:
        speed = -100
    if speed > 0:
        Motor_R_1.duty_u16(int(speed*65535/100))
        Motor_R_2.duty_u16(0)
    elif speed < 0:
        Motor_R_1.duty_u16(0)
        Motor_R_2.duty_u16(int(-speed*65535/100))
    else:
        Motor_R_1.duty_u16(0)
        Motor_R_2.duty_u16(0)
#---------------------------------
def Task20ms(timer):
    global Motor_L_ActivityCounter
    global MOTOR_L_ACTIVITY_TIME
    global Motor_R_ActivityCounter
    global MOTOR_R_ACTIVITY_TIME
    global Motor_L_Status
    global Motor_R_Status
    global MOTOR_STATUS
    
    Motor_L_ActivityCounter = Motor_L_ActivityCounter - 1

    if Motor_L_ActivityCounter == 0:
        Motor_L_ActivityCounter = MOTOR_L_ACTIVITY_TIME
        Motor_L_Status = Motor_L_Status + 1
        if Motor_L_Status == 8:
            Motor_L_Status = 0
        print('L:',MOTOR_STATUS[Motor_L_Status])

    if ((Motor_L_Status == 0) | (Motor_L_Status == 2)): # half speed forward
        Motor_L(50)
    if (Motor_L_Status == 1):                           # full speed forward
        Motor_L(100)
    if ((Motor_L_Status == 3) | (Motor_L_Status == 7)): # stop
        Motor_L(0)
    if ((Motor_L_Status == 4) | (Motor_L_Status == 6)): # half speed reverse
        Motor_L(-50)
    if (Motor_L_Status == 5):                           # full speed reverse
        Motor_L(-100)
#----------------------------------------------------------
    Motor_R_ActivityCounter = Motor_R_ActivityCounter - 1
 
    if Motor_R_ActivityCounter == 0:
        Motor_R_ActivityCounter = MOTOR_R_ACTIVITY_TIME
        Motor_R_Status = Motor_R_Status + 1
        if Motor_R_Status == 8:
            Motor_R_Status = 0
        print('R:',MOTOR_STATUS[Motor_R_Status])

    if ((Motor_R_Status == 0) | (Motor_R_Status == 2)): # half speed forward
        Motor_R(50)
    if (Motor_R_Status == 1):                           # full speed forward
        Motor_R(100)
    if ((Motor_R_Status == 3) | (Motor_R_Status == 7)): # stop
        Motor_R(0)
    if ((Motor_R_Status == 4) | (Motor_R_Status == 6)): # half speed reverse
        Motor_R(-50)
    if (Motor_R_Status == 5):                           # full speed reverse
        Motor_R(-100)
#---------------------------------
tim20ms = Timer()
tim20ms.init(freq = 50, mode = Timer.PERIODIC, callback = Task20ms)


SetServoDuty(1,5)
SetServoDuty(2,7.5)
SetServoDuty(3,10)
SetServoDuty(4,6.6)

Motor_L_1.duty_u16(0)
Motor_L_2.duty_u16(0)
Motor_R_1.duty_u16(0)
Motor_R_2.duty_u16(0)
