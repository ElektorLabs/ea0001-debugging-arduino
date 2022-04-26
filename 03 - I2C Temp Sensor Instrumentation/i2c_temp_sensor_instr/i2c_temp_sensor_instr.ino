// I2C Temperature Sensor

#include <Wire.h>

void setup()
{
  Serial.begin(9600); // start serial communication at 9600bps
  Wire.begin(); // join i2c bus
  pinMode(6, OUTPUT);
  pinMode(7, OUTPUT);
  digitalWrite(6, LOW);
  digitalWrite(7, LOW);
  Serial.println("01: Setup complete");
}

int temp = 0;

void loop()
{
  digitalWrite(7, HIGH);
  
  digitalWrite(6, HIGH);
  Serial.println("02: Entering loop");
  digitalWrite(6, LOW);
  
  digitalWrite(6, HIGH);
  Serial.println("03: Selecting MCP9800 temp register");
  digitalWrite(6, LOW);
  
  Wire.beginTransmission(0x49); // 0x92 or 0x49
  Wire.write(byte(0x00));       // select temperature register
  Wire.endTransmission();     // stop transmitting
  
  digitalWrite(6, HIGH);
  Serial.println("04: Temp register selected");
  digitalWrite(6, LOW);
  
  digitalWrite(6, HIGH);
  Serial.println("05: Wait for conversion");
  digitalWrite(6, LOW);
  
  delay(75);
  
  digitalWrite(6, HIGH);
  Serial.println("06: Start register read");
  digitalWrite(6, LOW);
  
  Wire.requestFrom(0x49, 2);    // request 2 bytes from slave device #112
  if(2 <= Wire.available())    // if two bytes were received
  {
    digitalWrite(6, HIGH);
    Serial.println("07: Data available");
    digitalWrite(6, LOW);
    
    temp = Wire.read();  // receive high byte (overwrites previous reading)
    temp = temp << 8;    // shift high byte to be high 8 bits
    temp |= Wire.read(); // receive low byte as lower 8 bits
    temp = temp >> 8;

    digitalWrite(6, HIGH);
    Serial.println("08: Data read");
    digitalWrite(6, LOW);
    
    Serial.println(temp);   // print the reading
    
    digitalWrite(6, HIGH);
    Serial.println("09: Temp output");
    digitalWrite(6, LOW);
  }
  digitalWrite(6, HIGH);
  Serial.println("10: Leaving loop");
  digitalWrite(6, LOW);
  
  digitalWrite(7, LOW);
  
}
