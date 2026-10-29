//returns 0 if successfully executed
class DataCollection {
    private:
        float stallInterval; 

        int callLedger(){
            
        }

    public:

        DataCollection(){

        }

        int strictStall(unsigned long wait){
            callLedger();
            int code = 0;

            while (millis() < wait + startingTime){
                //insert data collections here at interval
            }
            Serial.println("strictStall executed with code: " + String(code));
            return code;
        }

        int airbrakeStall(unsigned long wait){
            callLedger();
            int code = 0;

            while (millis() < wait + startingTime){
                //insert data collections here at interval
            }

            Serial.println("airbrakeStall executed with code: " + String(code));
            return code;
        }

};