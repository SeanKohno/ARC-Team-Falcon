//Servo is attached to pin 0

#include "Ledger.h"
#include "Airbrake.h"
#include <Servo.h>

Ledger* ledger;
Airbrake* airbrake;

//Variables to assign closer to launch-day -------------------------------------
float standardRotation = 5; //degrees of regular servo rotation while opening. adjust positive/negative to associated vector
int collectionRate = 1000; // number of coast-phase change collections
int duration = 1000; // number of data collections after launch
float collectionDelay = 100; //how many milliseconds between each collection that will be recorded
float coastTime = 8; //delay before chute deployment

boolean launched = false;
boolean burnout = false;
boolean landed = false;

float a = 0; // acceleration current
float v = 0; // velocity current - at prev acceleration

float timeToBurnout = 0; //running
float bootTime;
float startingAltitude;
float startCoast = 0;
float launchTime = 0;

void setup() {
  Serial.begin(9600);
  Serial.println("ARC Team Falcon, system booting;");

  Servo airbrakeServo;
  airbrakeServo.attach(0); //ataches Servo to pin 0
  airbrake = new Airbrake(standardRotation, airbrakeServo);
  
  /*
    Attach IMU pins, Attach barometer pins
  */
  ledger = new Ledger(collectionRate, duration);
  bootTime = millis();
  //startingAltitude = barometricReadingAltitude;
  Serial.println("  System boot complete.");
}

void loop() {
  if (launched) {
    //ledger->addData(); data from sensors
  }
  
  if (burnout) {
    startCoast = millis();
    burnout = coastPhase();
  }

  if (landed){
    delay(30000); //wait 30 seconds to not overflow monitor
    ledger->data(bootTime - startCoast, bootTime - launchTime, bootTime, collectionDelay);
  }
}

boolean coastPhase(){
  float timeBurnout = millis();
  while (millis() - timeBurnout < coastTime) {
    ledger->addChange(airbrake->deploy(ledger&, coastTime - millis() + startCoast));
  }
  airbrake->deploy(10000, standardRotation); //final extension
  return false;
}
