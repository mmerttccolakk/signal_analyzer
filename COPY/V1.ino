#define SAMPLESIZE 500 //signals sample size
#define receiverPin D2 //revice pin

unsigned long timings[SAMPLESIZE];
unsigned long lastTime = 0;
unsigned int pos = 0;// for array position int

//Interrupt calculating elapsed time
void IRAM_ATTR timeCalculator() {
  const long now_time = micros();
  timings[pos] = now_time - lastTime;
  lastTime = now_time;
  //precaution to avoid overflow in position
  if (++pos > SAMPLESIZE-1) {
    pos = 0;
  }
}

void setup() {
  Serial.begin(115200);//begin serial
  //interrupt setup
  pinMode(receiverPin, INPUT_PULLUP);
  attachInterrupt(digitalPinToInterrupt(receiverPin), timeCalculator, CHANGE);
  pinMode(LED_BUILTIN, OUTPUT);
  digitalWrite(LED_BUILTIN, HIGH);
}

void loop() {
  //wait for begin at startup
  Serial.println("starting..");
  for (int i = 5; i>0; i--) {
    Serial.print(i);
    Serial.print("...");
    delay(900);
    digitalWrite(LED_BUILTIN, HIGH);
    delay(100);
    digitalWrite(LED_BUILTIN, LOW);
  }
  Serial.println();

  detachInterrupt(digitalPinToInterrupt(receiverPin));

    if (i< SAMPLESIZE; i++) {
      Serial.print( timings[i] );
      Serial.print(",");
    }
 
    for (int i = 0; i < pos; i++) {
      Serial.print( timings[i] );
      Serial.print(",");
    }

    Serial.println("");
    Serial.println("Reset your Arduino to scan again...");

    while(true) {} 
  //detachInterrupt(digitalPinToInterrupt(receiverPin));

}


