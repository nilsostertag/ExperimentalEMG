
// all Pin 
#define OUTPUT_PIN A0
#define nLO 5 // SCL 
#define pLO 4 // SDA 



// Threshold 
const int THRESHOLD_MA = 900; 
const int THRESHOLD_MIN = 550;

// 
int global_counter = 0; 
const 


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
      Serial.println(analogRead(OUTPUT_PIN));  // To send all three 'data' points to the plotter
  }
  //Wait for a bit to keep serial data from saturating
  delay(10);
} 

