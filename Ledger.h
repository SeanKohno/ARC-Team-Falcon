class Ledger {
  private:
    int collectionRate;
    float* airbrakeChanges;
    float (*collectedData)[3];
    int changeIndex = 0;
    int coast = 8; //delay
    int duration; //number of collections recorded accross the flight. leaves open to erase if incorrectly assigned
    int dataIndex = 0;

  public:
    // Accepts both new Ledger() and new Ledger(refreshRate)
    Ledger(int rate, int flightCounter) {
      collectionRate = rate;
      duration = flightCounter;
      airbrakeChanges = new float[coast * collectionRate];
      collectedData = new float[flightCounter][3]; // 1, acceleration - 2, orientation - 3, barometer
    }
    
    //Returns the change in altitude caused by the most recent interval of airbrake deployment.
    float getRecentChange(){
      if (changeIndex > 0 && changeIndex < coast * collectionRate) {
        float change = airbrakeChanges[changeIndex - 1];
        Serial.println("Change: " + change);
        return change;
      }
      Serial.println("Either changeIndex = 0 or exceeds length of airbrakeChanges in getRecentChange");
      return aibrakeChanges[changeIndex - 1];
    }
    
    //Adds the most recent interval of change caused by airbrake to the data array
    void addChange(float change) {
      if (changeIndex < coast * collectionRate) {
        airbrakeChanges[changeIndex] = change;
        changeIndex++;
      }  else  {
        Serial.println("addChange index exceeded at: " + String(millis()));
      }
    }
    
    //Accepts the acceleration, orientation, and air pressure values and 
    // adds them to the respective index in data array
    void addData(float a, float o, float b){
      if (dataIndex < duration) {
        collectedData[dataIndex][0] = a;
        collectedData[dataIndex][1] = o;
        collectedData[dataIndex][2] = b;

        dataIndex ++;
      }
    }
    
    //Prints all flight data to the Serial monitor.
    void data(float startCoast, float launch, float boot, float collectionDelay){
      //introduction      
      Serial.println("ARC Team Falcon");
      Serial.println("System booted at " + String(boot));
      Serial.println("Launch at " + String(launch));
      Serial.println("Coast at " + String(startCoast));
      Serial.println();
      Serial.println("Assumed values: ");
      Serial.println("  duration: " + String(duration));
      Serial.println("  collectionRate: " + String(collectionRate));
      Serial.println("  coast: " + String(coast));
      Serial.println("  collectionDelay: " + String(collectionDelay));
      Serial.println("Final indices: ");
      Serial.println("  changeIndex: " + String(changeIndex));
      Serial.println("  dataIndex: " + String(dataIndex));
      Serial.println();
      Serial.println("begin data stream");
      Serial.println();
      
      //prints data from the coast to the serial monitor
      Serial.println("Launch + " + String(startCoast) + "; Coast-phase metrics:");
      for (int i = 0; i < changeIndex; i++){
        Serial.println("  " + String(airbrakeChanges[i]) + " | coast + " );
      }
      Serial.println();

      //prints acceleration, orientation, and barometer data to serial monitor
      Serial.println("Metrics post launch:");
      Serial.println("  Accelerometer  |  Barometer  |  Gyroscope  |  Post-Launch Time");
      for (int i = 0; i < dataIndex; i++){
        Serial.println("  " + String(collectedData[i][0]) + "  |  " + String(collectedData[i][1]) + "  |  " + String(collectedData[i][2]) + "  |  " + String(i * collectionDelay));
      }
      Serial.println();
      Serial.println();
      Serial.println("--------------------------------------------------------------------------------");
      Serial.println();
      Serial.println();
      Serial.println();
    }
};
