// konfigurasi template_id, template_name, dan auth_token yang didapatkan dari blynk
#define BLYNK_TEMPLATE_ID "TMPL6ctN0NurV"
#define BLYNK_TEMPLATE_NAME "Fire Alert Notification"
#define BLYNK_AUTH_TOKEN "lmfSYKCiLYs3FluEN1h1J9-BLSVpsPgT"

// konfigurasi serial print untuk menampilkan teks di layar dan modul wifi pada esp8266 untuk melakukan koneksi internet
#define BLYNK_PRINT Serial
#include <ESP8266WiFi.h>
#include <BlynkSimpleEsp8266.h>

// Konfigurasi token autentikasi Blynk, wifi ssid, dan password wifi
char auth[] = BLYNK_AUTH_TOKEN;
char ssid[] = "Xiaomay";  // type your wifi name
char pass[] = "12345678";  // type your wifi password

// Instansiasi Blynk Timer
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
  // Mengambil data dari sensor api pada pin D1 
  int ReadSensor = digitalRead(D1);
  // Nilai default dari sensor adalah 1, apabila sensor mendeteksi api maka nilai tersebut akan berubah menjadi 0
  if (ReadSensor==0 && flag==0) {
    // Mengirimkan log dengan nama fire_alert ke blynk cloud dengan nilai “Fire Detected”
    Serial.println("Fire in the House");  
    Blynk.logEvent("fire_alert","Fire Detected");
    // Menghidupkan kipas angin
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
  // Melakukan konfigurasi pin pada NodeMCU ESP8266
  pinMode(D1, INPUT);
  pinMode(D2, OUTPUT);
  pinMode(D3, OUTPUT);
  Serial.begin(115200);
  // Konfigurasi koneksi ke layanan cloud Blynk menggunakan token autentikasi, wifi ssid, dan wifi password
  Blynk.begin(auth, ssid, pass);
  // Konfigurasi Interval fungsi sendSensor untuk berjalan setiap 5 detik
  timer.setInterval(5000L, sendSensor);
}

void loop(){
  // Menjalankan layanan Blynk
  Blynk.run();
  // Menjalankan timer Blynk
  timer.run();
}