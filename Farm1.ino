#include <Sensirion.h>
#include <Wire.h>
#include <LiquidCrystal_I2C.h>

#define Relay1 4  //순환팬
#define Relay2 5  //
#define Relay3 6  //환기팬
#define Relay4 7  //
#define Relay5 8  //측창 좌  열림
#define Relay6 9  //측창 좌  닫힘
#define Relay7 10 //측창 우  열림 
#define Relay8 11 //측창 우  닫힘
const uint8_t dataPin  =  2;  //초록색
const uint8_t clockPin =  3;  //하얀색

Sensirion tempSensor = Sensirion(dataPin, clockPin);
LiquidCrystal_I2C lcd(0x27, 16, 2); // 0x27, ox20, 0x3F


float temperature;
float humidity;
float dewpoint;

void setup()
{
  pinMode(Relay1, OUTPUT);
  pinMode(Relay2, OUTPUT);
  pinMode(Relay3, OUTPUT);
  pinMode(Relay4, OUTPUT);
  pinMode(Relay5, OUTPUT);
  pinMode(Relay6, OUTPUT);
  pinMode(Relay7, OUTPUT);
  pinMode(Relay8, OUTPUT);
  Serial.begin(9600);
  lcd.init();                      // initialize the lcd
  lcd.init();
  // Print a message to the LCD.
  lcd.backlight();
  lcd.setCursor(0, 0);
  lcd.print("Hello, world!");
  lcd.setCursor(0, 1);
  lcd.print("Ywrobot Arduino!");
  digitalWrite(Relay1, HIGH);
  digitalWrite(Relay2, HIGH);
  digitalWrite(Relay3, HIGH);
  digitalWrite(Relay4, HIGH);
  digitalWrite(Relay5, HIGH);
  digitalWrite(Relay6, HIGH);
  digitalWrite(Relay7, HIGH);
  digitalWrite(Relay8, HIGH);
  delay(5000);
}

void loop()
{
  tempSensor.measure(&temperature, &humidity, &dewpoint);

  Serial.print("Temperature: ");
  Serial.print(temperature);
  Serial.print(" C, Humidity: ");
  Serial.print(humidity);
  Serial.print(" %, Dewpoint: ");
  Serial.print(dewpoint);
  Serial.println(" C");

  lcd.clear();
  lcd.setCursor(0, 0);
  lcd.print("Temp : ");
  lcd.print(temperature);
  lcd.print(" oC");
  lcd.setCursor(0, 1);
  lcd.print("Humi : ");
  lcd.print(humidity);
  lcd.print(" %");

  delay(5000);

  if (temperature >= 18) {         //ON
    digitalWrite(Relay1, LOW);    //유동팬
    delay(1000);
  } 

    if (temperature <= 13) {       //OFF
    digitalWrite(Relay1, HIGH);    //유동팬
    delay(1000);
  } 

    if (temperature >= 25) {         //환기팬 ON
    digitalWrite(Relay3, LOW);   //환기팬
    delay(1000); 
  } 

    if (temperature <= 20) {       //환기팬 OFF
    digitalWrite(Relay3, HIGH);   //환기팬
    delay(1000); 
  } 
 
  
  if (temperature >= 20) {          //측창 열림
    digitalWrite(Relay5, HIGH);
    digitalWrite(Relay6, LOW);
    delay(1000); 
    digitalWrite(Relay7, HIGH);
    digitalWrite(Relay8, LOW);
    delay(1000);
  } 
  
  if (temperature <= 15) {          //측창 닫힘
    digitalWrite(Relay5, LOW);
    digitalWrite(Relay6, HIGH);
    delay(1000);
    digitalWrite(Relay7, LOW);
    digitalWrite(Relay8, HIGH);
    delay(1000);
  }

}
