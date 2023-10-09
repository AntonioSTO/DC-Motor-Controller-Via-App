#define BLYNK_TEMPLATE_ID "TMPL2Ayjmckre"
#define BLYNK_TEMPLATE_NAME "DC motor speed control"
#define BLYNK_AUTH_TOKEN "PRFl4GIHtJwfsTWrYFD0DnKbRapyF71X"
#include <Wire.h>
#include <WiFi.h>
#include <WiFiClient.h>
#include <BlynkSimpleEsp32.h>
#include <LiquidCrystal_I2C.h>

// set the LCD number of columns and rows
int lcdColumns = 16;
int lcdRows = 2;
LiquidCrystal_I2C lcd(0x27, lcdColumns, lcdRows); 


char auth[] = BLYNK_AUTH_TOKEN;
const char* ssid = "PET ELETRICA";
const char* pass = "#Lenz160@";
BlynkTimer timer;

// Set the motor driver pins
const int freq = 5000;
const int ledChannel = 0;
const int resolution = 8;
int DCMTOR = 15;
int IN1 = 2;


void setup() {
  Serial.begin(115200);
 
  Serial.println();
  Serial.print("Conectando-se a ");
  Serial.println(ssid);
  WiFi.begin(ssid, pass);
 
  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print(".");
  }
 
  Serial.println("");
  Serial.println("WiFi conectada.");
  Serial.println("Endereço de IP: ");
  Serial.println(WiFi.localIP());

  lcd.init();
  lcd.backlight();
  ledcSetup(ledChannel, freq, resolution);
  ledcAttachPin(DCMTOR, ledChannel);
 
  Blynk.begin(auth, ssid, pass);
  pinMode(IN1, OUTPUT);
  digitalWrite(IN1, HIGH);
}

  

void loop(){
  Blynk.run();
  timer.run();
}
BLYNK_WRITE(V0) {
  int data = param.asInt();
  int pwmWave = map(data,  0, 4095, 0, 255);

  Serial.println(data);
  analogWrite(DCMTOR, data/16);
  // set the cursor to position
  lcd.clear();
  lcd.setCursor(0, 0);
  lcd.print("MOTOR SPEED:");
  lcd.setCursor(0, 1);
  lcd.print(pwmWave); 
  // wait for 150 ms
  delay(150);
  ledcWrite(ledChannel, pwmWave);
  }

