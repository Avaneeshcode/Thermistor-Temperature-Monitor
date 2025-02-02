#include <Wire.h>
#include <LiquidCrystal_I2C.h>

LiquidCrystal_I2C lcd(0x27, 16, 2);

const int THERMISTOR_PIN = A0;  
const float VCC = 5.0;          
const float R_REF = 10.0;        
const float B_COEFFICIENT = 3950;
const float T0 = 25.0 + 273.15; 

void setup() {
  Serial.begin(9600);
  Serial.println("UNO is ready!");

  lcd.init();         
  lcd.backlight();    
  lcd.setCursor(0, 0);
  lcd.print("Temp Monitor");
}

void loop() {
  int adcVal = analogRead(THERMISTOR_PIN);
  float voltage = adcVal * VCC / 1024.0;
  float Rt = R_REF * voltage / (VCC - voltage);
  float tempK = 1 / ((log(Rt / R_REF) / B_COEFFICIENT) + (1 / T0));
  float tempC = tempK - 273.15;
  float tempF = (tempC * 9.0 / 5.0) + 32.0;

  Serial.print("Temperature: ");
  Serial.print(tempC, 2);
  Serial.print(" °C | ");
  Serial.print(tempF, 2);
  Serial.println(" °F");

  lcd.setCursor(0, 1);
  lcd.print("T: ");
  lcd.print(tempC, 1);
  lcd.print("C ");
  lcd.print(tempF, 1);
  lcd.print("F  "); 

  delay(1000);
}
