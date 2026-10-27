#include <Servo.h>

class Airbrake {
  private:
    float velocity = 0;
    float altitude = 0;
    float heading = 0;
    float previous = 0;
    float standardRotation;
    float target = 243.84; //meters
    float duration = 0.1; //Set to the time that an airbrake completes a full cycle
    int servoDelay = 1000; // how long it takes to rotate the servo


  public:
    Airbrake(float rotation){
      standardRotation = rotation;
    }

    float change;

    int deploy(Ledger ledger, float remainingTime) {
      float change = ledger.getRecentChange();
      if (velocity - change > target && (remainingTime / duration) * change < target){
        deploy(servoDelay, standardRotation); //adjust later for more precise airbrake control
        retract();
      }
    }

  //Carries out the rotation of servo. requires package
    void deploy(float delay, float rotation){
      delay(delay);
      //deploy
    }

    //carries out return of airbrake to chasis
    void retract() {
      delay(servoDelay);
    }
  
  //default constructor usage
  
};
