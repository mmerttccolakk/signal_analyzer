#define SAMPLESIZE 1000

unsigned long timings[SAMPLESIZE];
unsigned int pos = 0;
unsigned long lastTime = 0;
#define receiverPin D2
bool completed = false;

void IRAM_ATTR timeControl() {
  const long time = micros();
  timings[pos] = time - lastTime;
  lastTime = time;
  if (++pos > SAMPLESIZE-1) {
    pos = 0;
  }
}
void setup() {
  Serial.begin(9600); 
  attachInterrupt(digitalPinToInterrupt(receiverPin), timeControl, CHANGE);
  pinMode(LED_BUILTIN, OUTPUT);
  digitalWrite(LED_BUILTIN, LOW);
  Serial.println();
  Serial.println();
}

void loop() {
    for (int i = 5; i>0; i--) {
      Serial.print(i);
      Serial.print("... ");
      delay(900);
      digitalWrite(LED_BUILTIN, HIGH);
      delay(100);
      digitalWrite(LED_BUILTIN, LOW);
    }
    Serial.println();
      
    detachInterrupt(digitalPinToInterrupt(receiverPin));
    delay(500);
    Serial.println("DATA:");
    Serial.println();
      for (int i = 0; i< SAMPLESIZE; i++) {
        Serial.print( timings[i] );
        Serial.print(",");
      }

    Serial.println("");
    Serial.println("Reset your Arduino to scan again...");

    ESP.restart();

  
}
