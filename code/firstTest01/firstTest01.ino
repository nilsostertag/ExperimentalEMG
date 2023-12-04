// Feature on hold -> need to check... BUG/ERROR
//#include <Keyboard.h>

// all Pin
#define OUTPUT_PIN A0
#define nLO 5 // SCL
#define pLO 4 // SDA
#define LED_PIN 14 // Test LED

/* Nano
#define OUTPUT_PIN A0
#define nLO PD5         // SCL
#define pLO PD6         // SDA
#define LED_PIN PD7     // Test LED
*/

// Threshold
// const int THRESHOLD_MA = 900; 
// const int THRESHOLD_MIN = 550;

//-------------------------------------------------------
const int numReadings = 10;
int emgReadings[numReadings];
int emgIndex = 0;
int emgMaxThreshold = 0;
//-------------------------------------------------------

void AdaptiveThresholdAveraging(){
  int emgValue = analogRead(OUTPUT_PIN);

  // Update the maximum threshold
  emgMaxThreshold = max(emgMaxThreshold, emgValue);

  // Update the rolling average
  emgReadings[emgIndex] = emgValue;
  emgIndex = (emgIndex + 1) % numReadings;

  // Calculate the average value
  int emgAverage = 0;
  for (int i = 0; i < numReadings; i++) {
    emgAverage += emgReadings[i];
  }
  emgAverage /= numReadings;
  Serial.print(200); // To freeze the lower limit
  Serial.print(" ");
  Serial.print(1200); // To freeze the upper limit
  Serial.print(" ");
  Serial.println(emgAverage);

  // Use the adaptive threshold for muscle tension detection
  if (emgValue > emgMaxThreshold * 0.8) {

    // on Hold
    // Muscle tense, simulate spacebar press
    // Keyboard.write(32);
    // Keyboard.print(KEY_SPACE);
    digitalWrite(LED_PIN, HIGH);
    delay(500);
    digitalWrite(LED_PIN, LOW);

    //Serial.println("Help, muscle tension!");
  }
}

void setup() {
  // initialize the serial communication:
  Serial.begin(9600);
  pinMode(pLO, INPUT);        // Setup for leads off detection LO +
  pinMode(nLO, INPUT);        // Setup for leads off detection LO -
  pinMode(OUTPUT_PIN, OUTPUT); 
  pinMode(LED_PIN, OUTPUT);

  delay(5000);

  // on hold 
  // init the Keyboard in with German Layout
  // Keyboard.begin(); 
  
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
  delay(10);
}

