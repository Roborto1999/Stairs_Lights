#define OUT_PIN1 2
#define OUT_PIN2 3
#define ldrPin A5
#include <Arduino.h>

volatile byte state = LOW;


void interrupt_routine1(){
  state = HIGH;
  Serial.println("interrupt");
}
void interrupt_routine2(){
  state = HIGH;
  Serial.println("interrupt");
}

void setup() {
 Serial.begin(9600);
 pinMode(OUT_PIN1, INPUT);
 pinMode(OUT_PIN2, INPUT);
 attachInterrupt(digitalPinToInterrupt(OUT_PIN1),interrupt_routine1,RISING);
 attachInterrupt(digitalPinToInterrupt(OUT_PIN2),interrupt_routine2,RISING);
 pinMode(ldrPin, INPUT);
 pinMode(13,OUTPUT);
 digitalWrite(13,LOW);
 delay(60000);
 digitalWrite(13,HIGH);
 delay(1000);
 digitalWrite(13,LOW);
 
}


void loop() {

 if (state) {
   //Serial.println(analogRead(ldrPin));
   if (analogRead(ldrPin)>1000)
   {
    digitalWrite(13,HIGH);
    while(state){
      state=LOW;
      delay(20000);
    }
    digitalWrite(13,LOW);
    delay(1000);
    digitalWrite(13,HIGH);
    delay(1000);
    digitalWrite(13,LOW);
  }
 }
} 