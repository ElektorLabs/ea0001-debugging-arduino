// I2C Temperature Sensor

#include <Wire.h>

void setup()
{
  Serial.begin(9600); // start serial communication at 9600bps
  Wire.begin(); // join i2c bus
  pinMode(6, OUTPUT);
  digitalWrite(6, LOW);
}

int temp = 0;

void loop()
{
  digitalWrite(6, HIGH);
  
  Wire.beginTransmission(0x49); // 0x92 or 0x49
  Wire.write(byte(0x00));       // select temperature register
  Wire.endTransmission();     // stop transmitting
  
  delay(75);

  Wire.requestFrom(0x49, 2);    // request 2 bytes from slave device #112
  if(2 <= Wire.available())    // if two bytes were received
  {
    temp = Wire.read();  // receive high byte (overwrites previous reading)
    temp = temp << 8;    // shift high byte to be high 8 bits
    temp |= Wire.read(); // receive low byte as lower 8 bits
    temp = temp >> 8;
    Serial.println(temp);   // print the reading
  }
  
  digitalWrite(6, LOW);
}
