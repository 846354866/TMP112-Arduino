# TMP112-Arduino
This code is used to read data from a TMP112 temperature sensor using the Arduino prototyping platform.
The connections on the chip should be as follows:

| TMP112  (pin)| Arduino MEGA 2560  (pin)|
| --------|-------------------------------|
|SCL (1)  | SCL (21)                      |
|GND (2)  | GND (GND)                     |
|ALERT (3)| (Not Connected)               |
|ADDR0 (4)| (3.3V)                        |
|V+  (5)  | (3.3V)                        |
|SDA (6)  | SDA (20)                      |

There are 5k pullup resisors on the SCL,SDA and the ALERT pins of the chip and a 0.01uF supply bypass capacitor.

This particular project uses the shutdown mode of this chip to reduce self-heating and power consumption and appears to have an accuracy close to 1°C

I created this repository because I found very little code available for using this device and in particular in altering the configuration registers to control the shutdown mode.

Hopefully this is helpful to someone else!

(all code should be compatible with the TMP102 chip)
