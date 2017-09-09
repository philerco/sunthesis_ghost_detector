#define NOTE_D8  400

int RPi_input = 7;
int input_value = 0;
int led = 13;

// the setup routine runs once when you press reset:
void setup() {                
  // initialize the digital pin as an output.
  pinMode(RPi_input, INPUT);     
  pinMode(led, OUTPUT);
}

// the loop routine runs over and over again forever:
void loop() {
  input_value = digitalRead(RPi_input);   // turn the LED on (HIGH is the voltage level)

  if(input_value == HIGH){
    
    digitalWrite(led, HIGH);    // turn the LED off by making the voltage LOW
    tone(8, NOTE_D8);
  }else{
    digitalWrite(led, LOW);
    noTone(8);
  }
  delay(5); 
}
