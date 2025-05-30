  const int IN_MIC = 8;
  const int OUT_MOTOR = 9;
  const int LED_PIN = 6;
  const int SAMPLE_TIME = 120;

  unsigned long millisCurrent;
  unsigned long millisLast = 0;
  unsigned long millisElapsed = 0;
  int outputVoltage;
  int sampleBufferValue = 0;

  void setup(){
    Serial.begin(9600);
    pinMode(OUT_MOTOR, OUTPUT);
    pinMode(IN_MIC, INPUT);        // Set microphone pin as input
    pinMode(LED_PIN, OUTPUT);      // Set LED pin as output
  }

  void loop(){
    millisCurrent = millis();
    millisElapsed = millisCurrent - millisLast;
    
    // Count LOW pulses from LM393 audio sensor
    if (digitalRead(IN_MIC) == LOW) {
      sampleBufferValue++;
    }
    
    if (millisElapsed > SAMPLE_TIME) {
      Serial.println(sampleBufferValue);
      
      // Map pulse count to motor speed (0-255 PWM)
      if (sampleBufferValue > 0 && sampleBufferValue < 510) {
        outputVoltage = sampleBufferValue / 2;
      } else if (sampleBufferValue >= 510) {
        outputVoltage = 255;
      } else {
        outputVoltage = 0;
      }
      
      analogWrite(OUT_MOTOR, outputVoltage);
      
      sampleBufferValue = 0;
      millisLast = millisCurrent;
    }
  }
