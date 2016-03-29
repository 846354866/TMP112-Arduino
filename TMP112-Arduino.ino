#include "Wire.h"
#define TMP112_I2C_ADDRESS 72 /* This is the I2C address for our chip.
This value is correct if you tie the ADD0 pin to ground. See the datasheet for some other values. */

void setup() {
  Wire.begin(); // start the I2C library
  Serial.begin(115200); //Start serial communication at 115200 baud

  //configure the configuration register of the TMP112
  Wire.beginTransmission(TMP112_I2C_ADDRESS);
  Wire.write(0x01);   //set pointer to configuration register
  Wire.write(0x61);   //turn on shutdown mode
  Wire.write(0x20);   //keep the LSB as default
  Wire.endTransmission();      
}
 
 
void getTemp112(int addr){
  byte MSB, LSB;        //Bytes read from the TMP102 temperature registers
  int val;              //Storage for temperature register values
  float convertedtemp;  //The actual temperature value after being mutiplied by the resolution

  //begin a one-shot conversion
  Wire.beginTransmission(addr);
  Wire.write(0x01);   //set pointer to configuration register
  Wire.write(0xE1);   //keep in shutdown mode but set the OS bit
  Wire.write(0x20);   //keep the LSB as default
  Wire.endTransmission();  
  delay(50);         //wait for the temperature measurement to occur

  //Reset the pointer to register 0
  Wire.beginTransmission(addr); 
  Wire.write(0x00);
  Wire.endTransmission();

  //Get the data from the temperature register
  Wire.requestFrom(addr, 2); //request 2 bytes
  Wire.endTransmission();
  MSB   = (Wire.read());
  LSB   = (Wire.read());

  val   = ((MSB << 8) | LSB) >> 4;  //concatenate the bytes into a 12 bit value 
  convertedtemp = val*0.0625;       //multiply the 12 bit value by the measurement resolution
  
  //print all of the data to serial
  Serial.print("firstbyte is ");
  Serial.print("\t");
  Serial.println(MSB, BIN);
  Serial.print("secondbyte is ");
  Serial.print("\t");
  Serial.println(LSB, BIN);
  Serial.print("Concatenated byte is ");
  Serial.print("\t");
  Serial.println(val, BIN);
  Serial.print("Converted temp is ");
  Serial.print("\t");
  Serial.println(convertedtemp);
  Serial.println();
}

void loop() {
  getTemp112(TMP112_I2C_ADDRESS); //get the temperature reading from the device at the specified address
  delay(1000);     //wait 1 second before printing our next set of readings.
}

