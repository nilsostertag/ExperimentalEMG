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
  /*
  Serial.print(200); // To freeze the lower limit
  Serial.print(" ");
  Serial.print(1200); // To freeze the upper limit
  Serial.print(" ");
  Serial.println(emgAverage);

  */
  // Use the adaptive threshold for muscle tension detection
  if (emgValue > emgMaxThreshold * 0.8) {
    // on Hold
    // Muscle tense, simulate spacebar press
    // Keyboard.write(32);
    // Keyboard.print(KEY_SPACE);
    //digitalWrite(LED_PIN, HIGH);
    Serial.println("#"); 
    //delay(500);
    //digitalWrite(LED_PIN, LOW);
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
  // need to check but can be ignore 
  for (int i = 0; i < numReadings; i++) {
    emgReadings[i] = 0;
  }
  //-------------------------------------------------------
}

void loop() {
  if((digitalRead(nLO) == 1)||(digitalRead(pLO) == 1)){
    // Signal lost 
    Serial.println('!');
  }
  else{
    AdaptiveThresholdAveraging();    
  }
  //Wait for a bit to keep serial data from saturating
  delay(10);
}

