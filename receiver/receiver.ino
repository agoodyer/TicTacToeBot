#include <ESP8266WiFi.h>
#include <espnow.h>
#include <Servo.h>

Servo myservo; 
int servoPos = 0;   

// Pin Assignment
int enableRightMotor=0;
int rightMotorPin1=5;
int rightMotorPin2=4;

int enableLeftMotor=2;
int leftMotorPin1=14;
int leftMotorPin2=12;

#define SIGNAL_TIMEOUT 1000 

unsigned long lastRecvTime = 0;


typedef struct struct_message {
int forward; 
int reverse;
int left; 
int right; 
int servo_up; 
int servo_down; 
int spin; 
} struct_message;
struct_message myData;

void OnDataRecv(uint8_t * mac, uint8_t *incomingData, uint8_t len) {
  memcpy(&myData, incomingData, sizeof(myData));

    if(myData.forward == 1){
      moveForward(); 
    }
    else if(myData.reverse == 1){
      moveBackward(); 
    }
    else if(myData.left == 1){
      turn_left(); 
    }
    else if(myData.right == 1){
      turn_right(); 
    }
    else if(myData.servo_up == 1){
      go_up(); 
    }
    else if(myData.servo_down == 1){
      go_down(); 
    }
    else if(myData.spin == 1){
      do_spin(); 
    }else{
      stop(); 
    }


lastRecvTime = millis();
}
void setup() {
// Initialize Serial Monitor
Serial.begin(115200);
pinMode(enableRightMotor, OUTPUT);
pinMode(enableLeftMotor, OUTPUT);
pinMode(rightMotorPin1, OUTPUT);
pinMode(rightMotorPin2, OUTPUT);
pinMode(leftMotorPin1, OUTPUT);
pinMode(leftMotorPin2, OUTPUT);
digitalWrite(enableRightMotor, HIGH); // set full speed
digitalWrite(enableLeftMotor, HIGH); // set full speed


myservo.attach(13);

Serial.print("ESP Board MAC Address:  ");
Serial.println(WiFi.macAddress());

// Set device as a Wi-Fi Station
WiFi.mode(WIFI_STA);
// Init ESP-NOW
if (esp_now_init() != 0) {
Serial.println("Error initializing ESP-NOW");
return;
}
// Once ESPNow is successfully Init, we will register for recv CB to
// get recv packer info
esp_now_set_self_role(ESP_NOW_ROLE_SLAVE);


esp_now_register_recv_cb(OnDataRecv);
}


void moveForward(){

  digitalWrite(rightMotorPin1, LOW);
  digitalWrite(rightMotorPin2, HIGH);
  digitalWrite(leftMotorPin1, HIGH);
  digitalWrite(leftMotorPin2, LOW);

}

void stop(){
  digitalWrite(rightMotorPin1, LOW);
  digitalWrite(rightMotorPin2, LOW);
  digitalWrite(leftMotorPin1, LOW);
  digitalWrite(leftMotorPin2, LOW);

}

void moveBackward(){
  digitalWrite(rightMotorPin1, HIGH);
  digitalWrite(rightMotorPin2, LOW);
  digitalWrite(leftMotorPin1, LOW);
  digitalWrite(leftMotorPin2, HIGH);

}

void turn_left(){
  digitalWrite(leftMotorPin1, HIGH);
  digitalWrite(leftMotorPin2, LOW);

} 

void turn_right(){
  digitalWrite(rightMotorPin1, LOW);
  digitalWrite(rightMotorPin2, HIGH);
}

void do_spin(){
  digitalWrite(rightMotorPin1, HIGH);
  digitalWrite(rightMotorPin2, LOW);
  digitalWrite(leftMotorPin1, HIGH);
  digitalWrite(leftMotorPin2, LOW);

}

void go_up(){

 if (servoPos > 170){ return; } 
 servoPos+=6;
 myservo.write(servoPos); 
}

void go_down(){

   if(servoPos < 10){ return; } 
  servoPos-=6;
   myservo.write(servoPos); 
}


void printData(struct struct_message myData ){

  Serial.println("~~~~~~~~~~~~~~~~~~~~~"); 

  Serial.printf("Forward: %d, Reverse: %d \n",
  myData.forward,myData.reverse ); 

  Serial.printf("Left: %d, Right: %d \n", 
  myData.left,myData.right ); 


  Serial.printf("Up: %d, Down: %d, Spin: %d \n",
  myData.servo_up,myData.servo_down, myData.spin ); 

  Serial.println("~~~~~~~~~~~~~~~~~~~~~"); 

}



void loop() {
//Check Signal lost.
unsigned long now = millis();
if ( now - lastRecvTime > SIGNAL_TIMEOUT )
{

}




printData(myData); 

}