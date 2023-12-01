#include <Keyboard.h>


// all Pin 
#define OUTPUT_PIN A0
#define nLO PD0 // SCL 
#define pLO PD1// SDA 



// Threshold 
const int THRESHOLD_MA = 900; 
const int THRESHOLD_MIN = 550;



//-------------------------------------------------------
const int numReadings = 10;
int emgReadings[numReadings];
int emgIndex = 0;
int emgMaxThreshold = 1;
//-------------------------------------------------------


void AdaptiveThresholdAveraging(){
  int emgValue = analogRead(OUTPUT_PIN);

  // Aktualisiere den maximalen Schwellenwert
  emgMaxThreshold = max(emgMaxThreshold, emgValue);

  // Aktualisiere den gleitenden Durchschnitt
  emgReadings[emgIndex] = emgValue;
  emgIndex = (emgIndex + 1) % numReadings;

  // Berechne den Durchschnittswert
  int emgAverage = 0;
  for (int i = 0; i < numReadings; i++) {
    emgAverage += emgReadings[i];
  }
  emgAverage /= numReadings;
  /*
  Serial.print(200); // To freeze the lower limit
  Serial.print(" ");
  Serial.print(1200); // To freeze the upper limit
  Serial.print(" ");
  Serial.println(emgAverage); 
  */
   // Verwende den adaptiven Schwellenwert für die Muskelanspannungserkennung
  if (emgValue > emgMaxThreshold * 0.8) {
    // Muskel angespannt, simuliere Leertaste
    Keyboard.write(KEY_SPACE);
    delay(300);


    //Serial.println("Ahhhhhh Hilfe"); 
  }
}

void setup() {
  // initialize the serial communication:
  Serial.begin(9600);
  pinMode(pLO, INPUT); // Setup for leads off detection LO +
  pinMode(nLO, INPUT); // Setup for leads off detection LO -
  pinMode(OUTPUT_PIN, OUTPUT); 


 
  delay(5000); 
  


 
  //-------------------------------------------------------
  for (int i = 0; i < numReadings; i++) {
    emgReadings[i] = 0;
  }
  //-------------------------------------------------------
}

void loop() {
  
  if((digitalRead(nLO) == 1)||(digitalRead(pLO) == 1)){
    Serial.println('!');
  }
  else{
    /*
    // send the value of analog input 0:
      Serial.print(200); // To freeze the lower limit
      Serial.print(" ");
      Serial.print(1200); // To freeze the upper limit
      Serial.print(" ");
      // Calculate the rolling average
      // int rollingAverage = calculateRollingAverage(analogRead(OUTPUT_PIN));
      Serial.println(analogRead(OUTPUT_PIN));  // To send all three 'data' points to the plotter
    */
    AdaptiveThresholdAveraging();    
  }
  //Wait for a bit to keep serial data from saturating
  delay(1);
} 

