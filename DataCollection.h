/** 

    Barometer methods:

  Adafruit_MPL3115A2();
  boolean begin(TwoWire *twoWire = &Wire);
  float getPressure(void);
  float getAltitude(void);
  int8_t getAltitudeOffset(void);
  void setAltitudeOffset(int8_t offset);
  float getTemperature(void);
  void setSeaPressure(float SLP);

  void setMode(mpl3115a2_mode_t mode = MPL3115A2_BAROMETER);
  void startOneShot(void);
  bool conversionComplete(void);
  float getLastConversionResults(mpl3115a2_meas_t value = MPL3115A2_PRESSURE);

  void write8(uint8_t a, uint8_t d); */


#include <Adafruit_MPL3115A2.h> //barometer header
#include "Ledger.h"

//returns 0 if successfully executed
class DataCollection {
    private:
        float stallInterval; 
        int collectFrequency;
        int changeFrequency = 0;
        unsigned long lastTime = 0ul;
        unsigned long startCoast = 0ul;
        Ledger ledger;
        float startingAltitude;

        Adafruit_MPL3115A2 barometer;

        int callLedger(){
            Serial.println("Collector calls Ledger");
        }

    public:
    
    //includes initialization of collector means
    DataCollection(int frequency, Ledger temp){ //lowkey dont remember the original parameter I was going to pass in for frequency, though I think 100hz
        frequency = collectFrequency;
        ledger = temp;
        barometer.begin();
        startingAltitude = barometer.;

        Serial.println("DataCollection initialized, at initial pressure of " + startingAltitude);
    }
    
    //collects IMU and barometric data
    int collectData(){
        int code = 0;
        ledger.addData( , , barometer.getAltitude() - startingAltitude);
        
        Serial.println("collectData executed with code: " + String(code));
        return code;
    }
    
    //executes a delay for unsigned long wait time, while collecting measurements in respective increments
    int strictStall(unsigned long wait){
        callLedger();
        int code = 0;

        while (millis() < wait + startingTime){
            //insert data collections here at interval
        }
        Serial.println("strictStall executed with code: " + String(code));
        return code;
    }
    
    //executes a delay for unsigned long wait time, while collecting measurements in respective increments 
    // w/ airbrake change data calculated
    int airbrakeStall(unsigned long wait){

        callLedger();
        int code = 0;

        while (millis() < wait + startingTime){
            //insert data collections here at interval
        }

        Serial.println("airbrakeStall executed with code: " + String(code));
        return code;
    }

    void startCoast(int changeFreq){
        changeFrequency = changeFreq;
        startCoast = millis();
        Serial.println("Coast collection started at " + String(startCoast));
    }
};