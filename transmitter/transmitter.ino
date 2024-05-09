#include <ESP8266WiFi.h>
#include <espnow.h>
// int button0 = 99;

int forw =5 ; 
int rev = 4;

int l = 16; 
int r = 2; 

int up = 14; 
int down = 12; 

int sp = 13; 






uint8_t broadcastAddress[] = {0xEC, 0xFA, 0xBC, 0xC8, 0x32, 0xA4};
typedef struct struct_message {
// int d_zero;

int forward; 
int reverse;

int left; 
int right; 

int servo_up; 
int servo_down; 

int spin; 


} struct_message;

// Create a struct_message called myData
struct_message myData;

unsigned long lastTime = 0;
unsigned long timerDelay = 50; 

void OnDataSent(uint8_t *mac_addr, uint8_t sendStatus) {
Serial.print("Last Packet Send Status: ");
if (sendStatus == 0){
Serial.println("Delivery success");
}
else{
Serial.println("Delivery fail");
}
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



void setup() {
// Init Serial Monitor. CHECK THIS FOR TROUBLESHOOTING.
Serial.begin(115200);
//Set button0 as an input for the ESP8266
// pinMode(button0, INPUT);

pinMode(forw,INPUT); 
pinMode(rev,INPUT); 

pinMode(l,INPUT); 
pinMode(r,INPUT); 

pinMode(up,INPUT); 
pinMode(down,INPUT); 

pinMode(sp, INPUT); 

// Set device as a Wi-Fi Station
WiFi.mode(WIFI_STA);

Serial.print("ESP Board MAC Address:  ");
Serial.println(WiFi.macAddress());


if (esp_now_init() != 0) {
Serial.println("Error initializing ESP-NOW");
return;
}


esp_now_set_self_role(ESP_NOW_ROLE_CONTROLLER);
esp_now_register_send_cb(OnDataSent);
// Register peer
esp_now_add_peer(broadcastAddress, ESP_NOW_ROLE_SLAVE, 1, NULL, 0);
}
void loop() {
if ((millis() - lastTime) > timerDelay) {
// myData.d_zero = digitalRead(button0); 


myData.forward = digitalRead(forw); 
myData.reverse = digitalRead(rev); 




myData.left = digitalRead(l); 
myData.right = digitalRead(r);  

myData.servo_up = digitalRead(up); 
myData.servo_down = digitalRead(down); 

myData.spin = digitalRead(sp); 

if(myData.left ==1  && myData.right ==1){

  myData.left =0;
  myData.right = 0; 
  myData.forward = 1; 

}

printData(myData); 


esp_now_send(broadcastAddress, (uint8_t *) &myData, sizeof(myData));
lastTime = millis();
}
}



