#include "Ledger.h"
#include "Airbrake.h"
#include <Servo.h>

Ledger* ledger;
Airbrake* airbrake;

float standardRotation = 5; //degrees of regular servo rotation
int collectionRate = 1000; // number of coast-phase change collections
int duration = 1000; // number of data collections after launch

boolean launched = false;
boolean burnout = false;
boolean landed = false;

float a = 0; // acceleration current
float v = 0; // velocity current - at prev acceleration

float timeToBurnout = 0; //running
float bootTime;
float coastTime = 8; //delay before chute deployment
float startingAltitude;
float startCoast = 0;
float launchTime = 0;
float collectionDelay = 100; //how many milliseconds between each collection

void setup() {
  
  /*
    Attach IMU pins, Attach barometer pins
  */
  ledger = new Ledger(collectionRate, duration);
  airbrake = new Airbrake(standardRotation);
  bootTime = millis();
  //startingAltitude = barometricReadingAltitude;
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
    ledger->addChange(airbrake->deploy(*ledger, coastTime - millis() + startCoast));
  }
  airbrake->deploy();
  return false;
}
