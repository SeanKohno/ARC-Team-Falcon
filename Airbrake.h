#include <Servo.h> //assumes a 360 degree servo

class Airbrake {
  private:
    float velocity = 0;
    float altitude = 0;
    float heading = 0;
    float previous = 0;
    float change;
    float standardRotation;

    //assign near launch day---------------------------------------
    float target = 243.84; //meters
    float duration = 0.1; //Set to the time that an airbrake completes a full cycle
    int servoDelay = 100; // how long it takes to rotate the servo a standardRotation degrees

    Servo airbrakeServo;

  public:
    Airbrake(float rotation, Servo servo){
      airbrakeServo = servo;
      standardRotation = rotation;

      //ensures Servo is properly zeroed
      retract(standardRotation);
      retract(standardRotation);
      retract(standardRotation);
      Serial.println("Airbrake Instantialized");
    }


    int deploy(Ledger ledger, float remainingTime) {
      change = ledger.getRecentChange();
      if (velocity - change > target && (remainingTime / duration) * change < target){
        deploy(servoDelay, standardRotation); //adjust later for more precise airbrake control
        retract(standardRotation);
      }
      Serial.println("Airbrake deployment change of " + String(0)); //update once sensors can collect change to store change
      return 0; //update once sensors can collect change to store change
    }

  //Carries out the rotation of servo. requires package
    void deploy(float delay, float rotation){
      airbrakeServo.write(90 + rotation);
      collector->stall(delay);
      airbrakeServo.write(90); //stops the servo
      Serial.println("Airbrake Deployment Method Complete");
    }

    //carries out return of airbrake to chasis
    void retract(float rotation) {
      airbrakeServo.write(90 - standardRotation); 
      collector->stall(servoDelay);
      airbrakeServo.write(90); //stops the servo
      Serial.println("Airbrake Retraction Method Complete");
    }
  
};
