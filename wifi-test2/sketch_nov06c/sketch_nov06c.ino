int dOut = D3;//DOUT接D3号引脚
int led = D5;//led接D1号引脚
int sample_Time = 1000;//每隔10毫秒对声音取个样
unsigned long millisCurrent;//当前时间
unsigned long millisLast = 0;//上次的时间
unsigned long millisElapsed = 0;//经过的时间

int sampleBufferValue = 0;//在时间段内取了多少样

void setup() {
   Serial.begin(9600);
   pinMode(led, OUTPUT);
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

//声音超过threshold，点亮led灯
  if(sampleBufferValue > 200) {
    digitalWrite(led, HIGH);
    //delay(1000);
  } else {
    digitalWrite(led, LOW);
  }
}
