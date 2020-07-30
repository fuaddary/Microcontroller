// the number of the LED pin
const int redPin = 18;  // 16 corresponds to GPIO16
const int greenPin = 19;  // 16 corresponds to GPIO16
const int bluePin = 21;  // 16 corresponds to GPIO16

const int sound2 = 13;

// setting PWM properties
const int freq = 5000;
const int redChannel = 0;
const int greenChannel = 1;
const int blueChannel = 2;
const int resolution = 8;

const int SAMPLE_TIME = 10;
unsigned long millisCurrent;
unsigned long millisLast = 0;
unsigned long millisElapsed = 0;

int sampleBufferValue = 0;
void setup(){
  Serial.begin(115200);

  // configure LED PWM functionalitites
  ledcSetup(redChannel, freq, resolution); 
  ledcSetup(greenChannel, freq, resolution);
  ledcSetup(blueChannel, freq, resolution);
  
  // attach the channel to the GPIO to be controlled
  ledcAttachPin(redPin, redChannel);
  ledcAttachPin(greenPin, greenChannel);
  ledcAttachPin(bluePin, blueChannel);

  pinMode(sound,INPUT);
  pinMode(sound2,INPUT);

}
 
void loop(){
  // increase the LED brightness
  
  millisCurrent = millis();
  millisElapsed = millisCurrent - millisLast;

  if (digitalRead(sound2) == HIGH) {
    sampleBufferValue++;
  }

  if (millisElapsed > SAMPLE_TIME) {
    Serial.println(sampleBufferValue);
    int norm = 255 - (sampleBufferValue * 255 / 4000);
    if (norm<=0){
      norm = 0;
    }
    ledcWrite(redChannel, norm);
    ledcWrite(greenChannel, norm);
    ledcWrite(blueChannel, norm);
    
    sampleBufferValue = 0;
    millisLast = millisCurrent;
  }
  
}
