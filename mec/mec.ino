#include <ESP8266WiFi.h>
#include <espnow.h>
int button0 = 99;

uint8_t broadcastAddress[] = {0xAA, 0xAA, 0xAA, 0xAA, 0xAA, 0xAA};
typedef struct struct_message {
int d_zero; 
} struct_message;

// Create a struct_message called myData
struct_message myData;

unsigned long lastTime = 0;
unsigned long timerDelay = 500; 

void OnDataSent(uint8_t *mac_addr, uint8_t sendStatus) {
Serial.print("Last Packet Send Status: ");
if (sendStatus == 0){
Serial.println("Delivery success");
}
else{
Serial.println("Delivery fail");
}
}




void setup() {
// Init Serial Monitor. CHECK THIS FOR TROUBLESHOOTING.
Serial.begin(115200);
//Set button0 as an input for the ESP8266
pinMode(button0, INPUT);
// Set device as a Wi-Fi Station
WiFi.mode(WIFI_STA);



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
myData.d_zero = digitalRead(button0); 

esp_now_send(broadcastAddress, (uint8_t *) &myData, sizeof(myData));
lastTime = millis();
}
}



