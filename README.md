# Robot_Mihai_Durus
Several test projects in folders:
* Pico_MicroPython
- Pico_Car.py
- PinOut_test.py
- Servo_Test.py
- UltrasonicDistanceTest.py
* Pico_VSCode
- math speed
* SG90_Servo_test_arduino
* UltrasoniDistance_Arduino

Tested with nRF24L01 (PCB antenna):
* reduced Tx power (-6dB instead of 0dB)
* SPI0 with the following pinout:
	- SCK	GP6
	- MOSI	GP7
	- MISO	GP4
	- CSn	GP14
	- CE	GP17

For testing purposes copy the intended main_x.py together with nrf24l01.py to Pico.
main_RECEIVE.py is configured as receiver and main_SEND.py is configured as sender.
The main_x.py should be renamed into main.py after copying.
Start the receiver then the sender.
Successful data communication will be signaled by rapidly flashing LEDs.
