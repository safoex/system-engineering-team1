#include <Adafruit_BMP085.h>

#include <Wire.h>
#include <Adafruit_BMP085.h>

/*************************************************** 
  This is an example for the BMP085 Barometric Pressure & Temp Sensor

  Designed specifically to work with the Adafruit BMP085 Breakout 
  ----> https://www.adafruit.com/products/391

  These displays use I2C to communicate, 2 pins are required to  
  interface
  Adafruit invests time and resources providing this open source code, 
  please support Adafruit and open-source hardware by purchasing 
  products from Adafruit!

  Written by Limor Fried/Ladyada for Adafruit Industries.  
  BSD license, all text above must be included in any redistribution
 ****************************************************/

// Connect VCC of the BMP085 sensor to 3.3V (NOT 5.0V!)
// Connect GND to Ground
// Connect SCL to i2c clock - on '168/'328 Arduino Uno/Duemilanove/etc thats Analog 5
// Connect SDA to i2c data - on '168/'328 Arduino Uno/Duemilanove/etc thats Analog 4
// EOC is not used, it signifies an end of conversion
// XCLR is a reset pin, also not used here

Adafruit_BMP085 bmp;
#define M 60
const int PERIOD_SECONDS = 60;
double last[M];  
void setup() {
  Serial.begin(9600);
  if (!bmp.begin()) {
	Serial.println("Could not find a valid BMP085 sensor, check wiring!");
	while (1) {}
  }
  for (int i =0; i < M; i++) last[i] = 0;
}

void add_measurement(double T) {
  for(int i = M-1; i > 0 ; i--) last[i] = last[i-1];
  last[0] = T;
}

void print_measured() {
  Serial.println();
  for(int i = 0; i < M; i++) {
    Serial.print(last[i]);
    Serial.print('\t');
  }
  Serial.println();
}

void loop() {
    //Serial.print("Temperature = ");
    add_measurement(bmp.readTemperature());
    //Serial.println(" *C");
    print_measured();
    
    for(int i = 0; i < PERIOD_SECONDS;i++)
      delay(1000);
}
