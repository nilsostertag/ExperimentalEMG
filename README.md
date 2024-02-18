## ExperimentalEMG
Exploratory application fields of GRV-EMG sensors for an interactive human-computer interface created for the subject "Advanced Human-Machine-Interaction" at Aalen University.


### Contents
- Overall goals of the project
- Theoretical scheme
- Circuit diagram
- Usage
- Documentation

### Overall goals of the project
The goal of the project is to use an Arduino microcontroller equipped with an AD8232 module to detect muscle activity of a person/user.
If the user flexes the specific muscle which the electrode patches of the AD8232 are attached to, there should be an input sent to the computer
which the microcontroller is connected to.
This should enable the user to communicate with the computer for different purposes, like testing reaction time, mind-muscle-coordination or even playing games.

### Theoretical Scheme
Working on it...

### Circuit diagram
Working on it...

### Usage
Working on it...

### Documentation

<details>
  <summary>Adaptive threshold averaging</summary>
  
  ```ino
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
    }
  }
  ```
</details>
