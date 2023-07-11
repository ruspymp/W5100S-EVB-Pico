#include <Wire.h>
#include <Adafruit_GFX.h>
#include <Adafruit_SSD1306.h>
#include <Adafruit_Sensor.h>
#include <DHT.h>

#define DHTPIN 2
#define DHTTYPE DHT11
DHT dht(DHTPIN, DHTTYPE);

#define SCREEN_WIDTH 128
#define SCREEN_HEIGHT 64

Adafruit_SSD1306 display(SCREEN_WIDTH, SCREEN_HEIGHT, &Wire, -1);

const int LED = 0;
const int buzzer = 6;
const int pas_button = 3;
const int act_button = 4;
const int onoff = 5;
int onoff_mode = 0; // On Off mode
int pasact_mode = 0; // Passive Active mode

void setup() {
  // put your setup code here, to run once:
  pinMode(LED, OUTPUT);
  pinMode(buzzer, OUTPUT);
  pinMode(pas_button, INPUT);
  pinMode(act_button, INPUT);
  pinMode(onfoff, INPUT);

  Wire.setSDA(12);
  Wire.setSCL(13);
  Wire.begin();

  Serial.begin(115200);
  dht.begin();

  if(!display.begin(SSD1306_SWITCHCAPVCC, 0x3C)){
    Serial.println(F("SSD1306 allocation failed"));
  }
  delay(2000);
  display.clearDisplay();
  display.setTextSize(1);
  display.setTextColor(WHITE);
  display.setCursor(0, 10);

  display.println("Hellow world!");
  display.display();
  delay(1000); 
}

void loop() {
  delay(10000);

  float hum = dht.readHumidity();
  float temp = dht.readTemperature();
  float F = dht.readTemperature(true);

  if(isnan(hum) || isnan(temp) || isnan(F))
  {
    Serial.println("Failed to read from DHT sensor");
    display.display();
    return;
  }

  //Define Passive or Active mode
  int pas = digitalRead(pas_button);
  int act = digitalRead(act_button);
  if (pas == low)
  {
    pasact_mode = 0; //passive mode
  }
  if (act == low)
  {
    pasact_mode = 1; //active mode
  }

    Serial.print("Humidity : ");
    Serial.print(hum);
    Serial.println("%");
    Serial.print("Temeprature : ");
    Serial.print(temp);
    Serial.println("C");
    Serial.print("Mode : ");
    Serial.println(mode);

  
  if (pasact_mode == 1)
  {
    if (hum > 80 && onoff_mode == 0)
    {
      delay(3000);
      // On mode
      onoff_mode = 1;

      //LED and Buzzer control
      digitalWrite(LED, HIGH);
      tone(buzzer, 200);
      delay(500);
      noTone(buzzer);
      delay(100);

      //display Present state at OLED
      display.clearDisplay();

      display.print("Humidity : ");
      display.print(hum);
      display.println("%");
      display.print("Temeprature : ");
      display.print(temp);
      display.println("C");

      display.display();
    }
    else if (hum > 80 && onoff_mode == 1)
    {
      delay(3000);
      //display Present state at OLED
      display.clearDisplay();

      display.print("Humidity : ");
      display.print(hum);
      display.println("%");
      display.print("Temeprature : ");
      display.print(temp);
      display.println("C");

      display.display();
    }
    else if (hum <= 80 && onoff_mode == 0)
    {
      delay(3000);
      //display Present state at OLED
      display.clearDisplay();

      display.print("Humidity : ");
      display.print(hum);
      display.println("%");
      display.print("Temeprature : ");
      display.print(temp);
      display.println("C");

      display.display();
    }
    else if (hum <= 80 && onoff_mode == 1)
    {
      delay(3000);
      // On mode
      onoff_mode = 0;

      //LED and Buzzer control
      digitalWrite(LED, LOW);
      tone(buzzer, 200);
      delay(500);
      noTone(buzzer);
      delay(100);

      //display Present state at OLED
      display.clearDisplay();
      
      display.print("Humidity : ");
      display.print(hum);
      display.println("%");
      display.print("Temeprature : ");
      display.print(temp);
      display.println("C");

      display.display();
    }
  }
}
