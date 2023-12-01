
// all Pin 
#define OUTPUT_PIN A0
#define nLO 5 // SCL 
#define pLO 4 // SDA 



// Threshold 
const int THRESHOLD_MA = 900; 
const int THRESHOLD_MIN = 550;



const int bufferSize = 10;  // Size of the rolling average buffer
int sensorValues[bufferSize];  // Array for storing sensor values

int calculateRollingAverage(int newValue) {
  static int index = 0;  // Current index in the array
  static int sum = 0;    // Sum of values in the array

  // Subtract the oldest element from the sum
  sum -= sensorValues[index];

  // Add the new element to the sum
  sum += newValue;

  // Store the new element in the array
  sensorValues[index] = newValue;

  // Increment the index and set it to 0 if it reaches the end of the array
  index = (index + 1) % bufferSize;

  // Calculate the rolling average
  int average = sum / bufferSize;

  return average;
}


void setup() {
  // initialize the serial communication:
  Serial.begin(9600);
  pinMode(pLO, INPUT); // Setup for leads off detection LO +
  pinMode(nLO, INPUT); // Setup for leads off detection LO -
  pinMode(OUTPUT_PIN, OUTPUT); 


 
  delay(5000); 
  
}

void loop() {
  
  if((digitalRead(nLO) == 1)||(digitalRead(pLO) == 1)){
    Serial.println('!');
  }
  else{
    // send the value of analog input 0:
      Serial.print(200); // To freeze the lower limit
      Serial.print(" ");
      Serial.print(1200); // To freeze the upper limit
      Serial.print(" ");
      // Calculate the rolling average
      int rollingAverage = calculateRollingAverage(analogRead(OUTPUT_PIN));
      Serial.println(rollingAverage);  // To send all three 'data' points to the plotter
  }
  //Wait for a bit to keep serial data from saturating
  delay(1);
} 

