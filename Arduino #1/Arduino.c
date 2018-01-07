const int ledPin = 13;
int blinkRate = 0;
int sum = 0;
int temp = 0;

void setup() {
  Serial.begin(9600);
  pinMode(ledPin, OUTPUT);
}

void loop() {
  if(Serial.available()) sum = 0;
  while(Serial.available()){
    char ch = Serial.read();
    if(isDigit(ch)){
      blinkRate = (ch - '0');
      sum = sum*10 + blinkRate;     
    }
    blinkRate = sum;
    delay(10);
  }
  if(blinkRate != 0 && blinkRate != temp){
    Serial.print("delay :");
    Serial.print(blinkRate);
    Serial.println("ms");
    temp = blinkRate;
  }
  blink();
}

void blink(){
  digitalWrite(ledPin, HIGH);
  delay(blinkRate);
  digitalWrite(ledPin, LOW);
  delay(blinkRate); 
} 

