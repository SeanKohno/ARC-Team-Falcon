# ARC-Team-Falcon
Avionic systems for the American Rocketry Challenge Team Falcon at Yorktown High School, Arlington Virginia.

Currently, this repository is set to public. 
HOWEVER, that is subject to change. 
The current provisions are for ease of collaboration in an academic setting. 
NO Technical implementation details are accessible in the public version. 

This repository hosts the avionics for the upcoming ARC Challenge in 2027 as a High-School competition. 
This program is designed for amateur rocketry in unrestricted levels (pre class 1), and should not, nor is intended for, high power rocketry.

---

The current main version is ARC_Version1.ino
  There are two associated header files, Airbrake.h and Ledger.h
  Both Airbrake and Ledger are instantialized once in main. 

Ledger records data from throughout the flight. Upon landing, the entirety of the data will be printed to the Serial monitor once every 30 seconds.
  - Constructor:
      - Ledger(int rate, int flightCounter) where rate is the hz collections of data after coast phase starts, and flightCounter is number of data collections after launch.
  - Methods: 
      - float getRecentChange() returns the most recent change in altitude from the most recent airbrake deployment.
      - void addChange(float change) adds the change in altitude from recent airbrake deployment to the first open index in Ledger array.
      - void addData(float a, float o, float b) adds the accelerometer, gyroscope, and barometer data to the first available index on the ledger.
      - void data(float startCoast, float launch, float boot, float collectionDelay) prints the data to the serial monitor

Airbrake controls the actuation of airbrakes used to lower the velocity of the rocket. There are NO active guidance systems.
  - Constructor:
      - Airbrake(float rotation) where rotation is the standard rotation value of servo deployment
  - Methods:
      - int deploy(Ledger ledger, float remainingTime) calculates and deploys airbrakes and calls addChange(float change) to add the change data to the ledger.
      - void deploy(float delay) deploys the airbrake for the delay time
      - void retract() retracts the airbrake. Uses servoDelay field variable.

---

Packages & Libraries Used: <Servo.h>

Given the absence of further known packages that will be used to collect data from sensors and control servos, the values that would otherwise be collected by sensors are left as constants.
