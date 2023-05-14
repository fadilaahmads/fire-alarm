#define BLYNK_TEMPLATE_ID "TMPL6ctN0NurV"
#define BLYNK_TEMPLATE_NAME "Fire Alert Notification"
#define BLYNK_AUTH_TOKEN "lmfSYKCiLYs3FluEN1h1J9-BLSVpsPgT"


#define BLYNK_PRINT Serial
#include <ESP8266WiFi.h>
#include <BlynkSimpleEsp8266.h>

 
char auth[] = BLYNK_AUTH_TOKEN;

char ssid[] = "Xiaomay";  // type your wifi name
char pass[] = "12345678";  // type your wifi password
 

BlynkTimer timer;
int flag=0;

// BLYNK_WRITE(V1) // this command is listening when something is written to V1
// {
//   int pinValue = param.asInt(); // assigning incoming value from pin V1 to a variable
  
//   if (pinValue == 1){
//     flag = 1;
//   } else if (pinValue == 0) {
//     flag = 0;
//   }
  
//   Serial.print("Fan switch value is: "); // printing value to serial monitor
//   Serial.println(pinValue);
// }

void sendSensor(){ 
  int ReadSensor = digitalRead(D1);
  if (ReadSensor==0 && flag==0) {
    Serial.println("Fire in the House");  
    Blynk.logEvent("fire_alert","Fire Detected");
    digitalWrite(D2, HIGH);
    digitalWrite(D3, LOW);
    flag=1;
  }
  else if (ReadSensor==1)
  {
    flag=0; 
  }
}

void setup(){
  pinMode(D1, INPUT);
  pinMode(D2, OUTPUT);
  pinMode(D3, OUTPUT);
  Serial.begin(115200);
  Blynk.begin(auth, ssid, pass);
  timer.setInterval(5000L, sendSensor);
}

void loop(){
  Blynk.run();
  timer.run();
}