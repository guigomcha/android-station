#include <SimpleDHT.h>
#include  <Wire.h>
#include  <LiquidCrystal_I2C.h>
#include <Servo.h>

// Assign pins to LCD PCF8574
LiquidCrystal_I2C lcd(0x27, 2, 1, 0, 4, 5, 6, 7, 3, POSITIVE);

// Teperature and humidity sensor
int pinDHT11 = 2;
SimpleDHT11 dht11(pinDHT11);

// servo
Servo servoMotor;

 
int option;
int count;
int servoON = 30;
int servoOFF = 60;

 
void setup() {
  Serial.begin(9600);
  servoMotor.attach(9);
  servoMotor.write(servoOFF);
  count=0;
  // 16x2
  lcd.begin(16, 2);
  lcd.home ();
  lcd.print("Hola Guille");
  lcd.setCursor ( 0, 1 );
  lcd.print("Hola Machu");
  delay(5000);
  lcd.clear();
}

void loop() {
  
  if (Serial.available()>0){
    char inChar = Serial.read();
    switch(inChar) {
      case '1':
        servoMotor.write(servoON);
      break;
      case '0':
        servoMotor.write(servoOFF);
      break;
    }
  }
  
  // Update Sensor read every 10 seconds
  if (count==0){
    count = 10;
  } else {
    count-=1;
    delay(1000);
    return;
  }
  
  byte temperature = 0;
  byte humidity = 0;
  int err = SimpleDHTErrSuccess;
  
  if ((err = dht11.read(&temperature, &humidity, NULL)) != SimpleDHTErrSuccess) {
    Serial.print("Read DHT11 failed, err="); Serial.println(err);delay(1000);
    return;
  }
  lcd.setCursor( 0, 0 );
  lcd.print("Temperatura:"); lcd.print((int)temperature); lcd.print((char)223); lcd.print("C");
  lcd.setCursor( 0, 1 );
  lcd.print("Humedad: "); lcd.print((int)humidity); lcd.print("%");

}
