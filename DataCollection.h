//returns 0 if successfully executed
class DataCollection {
    private:
        float stallInterval; 
        int collectFrequency;
        int changeFrequency = 0;
        unsigned long lastTime = 0ul;
        unsigned long startCoast = 0ul;

        int callLedger(){
            Serial.println("Collector calls Ledger");
        }

    public:

        DataCollection(int frequency){
            frequency = collectFrequency;
            Serial.println("DataCollection initialized.");
        }
        
        //collects IMU and barometric data
        int collectData(unsigned long wait){
            int code = 0;

            
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