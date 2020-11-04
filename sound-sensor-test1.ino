int dOut = 2;
int sample_Time = 10;
unsigned long millisCurrent;
unsigned long millisLast = 0;
unsigned long millisElapsed = 0;

int sampleBufferValue = 0;

void setup() {
   Serial.begin(9600);
   pinMode(8, OUTPUT);
}

void loop() {

  millisCurrent = millis();
  millisElapsed = millisCurrent - millisLast;

  if(digitalRead(dOut) == LOW) {
    sampleBufferValue++;
  }

  if(millisElapsed > sample_Time) {
    Serial.println(sampleBufferValue);
    sampleBufferValue = 0;
    millisLast = millisCurrent;
  }

  if(sampleBufferValue > 200) {
    digitalWrite(8, HIGH);
  } else {
    digitalWrite(8, LOW);
  }

}
