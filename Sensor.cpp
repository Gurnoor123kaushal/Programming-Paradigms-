int pinSpeaker = 12; // Pin connected to the piezo buzzer
int ledPin = 13;     // Pin connected to the LED
int inputPin = 2;    // Pin connected to the PIR sensor
int pirState = LOW;  // Start with PIR state LOW (no motion detected)

int val = 0; 

void setup() {
  pinMode(ledPin, OUTPUT);        pinMode(inputPin, INPUT);     
  pinMode(pinSpeaker, OUTPUT);  
  Serial.begin(9600);           
}

void loop() {
  val = digitalRead(inputPin); 

  if (val == HIGH) { // Check if the PIR sensor detects motion
    digitalWrite(ledPin, HIGH); // Turn ON the LED
    playTone(300, 160);        
    delay(150);                

    if (pirState == LOW) {
      
      Serial.println("Motion detected!");
      pirState = HIGH;
    }
  } else {
    digitalWrite(ledPin, LOW); 
    playTone(0, 0);            
    delay(300);                

    if (pirState == HIGH) {
      
      Serial.println("Motion ended!");
      pirState = LOW;
    }
  }
}

void playTone(long duration, int freq) {
  
  if (freq == 0) return; 

  duration *= 1000;                    
  int period = 1000000 / freq;         
  long elapsed_time = 0;               

  while (elapsed_time < duration) {
    digitalWrite(pinSpeaker, HIGH);    
    delayMicroseconds(period / 2);     
    digitalWrite(pinSpeaker, LOW);     
    delayMicroseconds(period / 2);     
    elapsed_time += period;            
  }
}
