// Use this code to test your motor with the Arduino board:

// if you need PWM, just use the PWM outputs on the Arduino
// and instead of digitalWrite, you should use the analogWrite command
#include <IRremote.h>

// —————————————————————————  Motors
int motor_left[] = {2, 3};
int motor_right[] = {7, 6};
int RECV_PIN = 10;
int state;
IRrecv irrecv(RECV_PIN);
decode_results results;


// ————————————————————————— Setup
void setup() {
  Serial.begin(9600);
  // Setup motors
  state = 5; //STOPPED STATE
  int i;
  for(i = 0; i < 2; i++){
    pinMode(motor_left[i], OUTPUT);
    pinMode(motor_right[i], OUTPUT);
  }
  irrecv.enableIRIn(); // Start the receiver


}

// ————————————————————————— Loop
void loop() {
//  drive_forward();
//  delay(2000);
//      motor_stop();
//delay(1000);
//      drive_backward();
//        delay(2000);
//      motor_stop();
//delay(1000);
//    turn_left();
//      delay(2000);
//      motor_stop();
//delay(1000);
//    turn_right();
//  delay(2000);
//      motor_stop();
//delay(1000);
  
  if (irrecv.decode(&results)) {
      Serial.println(results.value, HEX);
      if (results.value == 0x91388F5C || results.value == 0x488F3CBB || results.value == 0xFF38C7){
        state = 5; //Stop
      }
      else if (results.value == 0xFF18E7 || results.value == 0x3D9AE3F7){
        state = 2; //Stop
      }
      else if (results.value == 0xFF4AB5 || results.value == 0x1BC0157B){
        state = 8; //Stop
      }
      else if (results.value == 0x8C22657B || results.value == 0xFF10EF){
        state = 4; //Stop
      }
      else if (results.value == 0xFF5AA5 || results.value == 0x449E79F){
        state = 6; //Stop
      }
      else {
        state = state;
      }
      
      //Stopped 
      if (state == 5){
        motor_stop();
        Serial.println("We have stopped");
      }
      
      //Left
      else if (state == 4){
        turn_left();
        Serial.println("Turn Left");
      }
      
      //Right
      else if (state == 6){
        turn_right();
        Serial.println("Turn right");
      }
      
      //Forward
      else if (state == 2){
        drive_forward();
        Serial.println("Forward");
      }
      
      //Backward
      else if (state == 8){
        drive_backward();
        Serial.println("Backward");
      }
      
      irrecv.resume(); // Receive the next value
  }
  delay(25);
}

// ————————————————————————— Drive

//Button 5 on the remote
//These codes correspond
//FF38C7 - Close
/*
91388F5C
488F3CBB - FAR
*/

void motor_stop(){
  digitalWrite(motor_left[0], LOW);
  digitalWrite(motor_left[1], LOW);

  digitalWrite(motor_right[0], LOW);
  digitalWrite(motor_right[1], LOW);
  delay(25);
}

//Button 2 on the remote
//These codes correspond
//FF18E7
//3D9AE3F7

void drive_forward(){
  digitalWrite(motor_left[0], HIGH);
  digitalWrite(motor_left[1], LOW);
  
  digitalWrite(motor_right[0], HIGH);
  digitalWrite(motor_right[1], LOW);
}

//Button 8
/*
FF4AB5
1BC0157B
*/
void drive_backward(){
  digitalWrite(motor_left[0], LOW);
  digitalWrite(motor_left[1], HIGH);
  
  digitalWrite(motor_right[0], LOW);
  digitalWrite(motor_right[1], HIGH);
}

//Button 4
/*
8C22657B
FF10EF
*/
void turn_left(){
  digitalWrite(motor_left[0], LOW);
  digitalWrite(motor_left[1], HIGH);
  
  digitalWrite(motor_right[0], HIGH);
  digitalWrite(motor_right[1], LOW);
}

//Button 6
/*
FF5AA5
449E79F
*/
void turn_right(){
  digitalWrite(motor_left[0], HIGH);
  digitalWrite(motor_left[1], LOW);
  
  digitalWrite(motor_right[0], LOW);
  digitalWrite(motor_right[1], HIGH);
}
