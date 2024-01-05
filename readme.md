# GFUltrasonic - Geek Factory Ultrasonic Library #

This library is designed as a minimal abstraction layer between simple and cheap **ultrasonic sensor modules** and the user's high-level code. **This library is designed to be used with the Arduino framework using the Arduino IDE or PlatformIO**.

The sensor modules are readily available in most countries for a couple dollars each. They're an excellent solution when a cheap and "precise" sensor for distance is required. 

We designed and tested the library using the very cheap **HC-SR04 ultrasonic module** and the **Seeedstudio ultrasonic sensor module (Grove)**. Both modules can be obtained in México in our online electronics store:

* [HC-SR04 ultrasonic sensor module](https://www.geekfactory.mx/tienda/sensores/hc-sr04-sensor-ultrasonico-de-distancia/)
* [Ultrasonic Sensor - Grove](https://www.geekfactory.mx/tienda/tarjetas/grove/sensor-ultrasonico-grove/)

## Project Objectives ##

Our library should fulfill the following goals:

* Code should be very simple and have no dependencies other than the functions provided by the Arduino framework
* Should not directly rely on timers or other architecture dependent features
* We should be able to use this code in courses to demonstrate how to create an Arduino library
* Be able to use the code in other platforms beside the AVR Arduino boards (i.e. ESP32, ATSAMD21, Raspberry Pi Pico)
* Provide simple, clean, usable code

## Basic library usage ##

In order to use the library, we need to include the library header file and then instantiate an object from the class GFUltrasonic.

The constructor will accept the pin numbers used for communication with the sensor as parameters. Multiple instances can be created simultaneously to handle multiple sensors.

```cpp
// include the library header file
#include <GFUltrasonic.h>

// instantiate an object to use the ultrasonic sensor using pin 4 for communication
// this is the constructor overload for sensors that use a single pin for echo and trigger signals
GFUltrasonic ultrasonic(4);
```

We also need to call the begin function member in order to initialize the pins used for the sensor communication. This should be done on the setup() function.

```cpp
void setup()
{
  // call begin() to get the IO pins initialized by the library
  ultrasonic.begin();
}
```

To measure distance we just call the read() method:

```cpp
void loop()
{
	// call read() to get the distance in centimeters
	uint32_t distance = ultrasonic.read();
	
	// print the result to the serial terminal
	Serial.print(F("Measured distance: "));
	Serial.print(distance);
	Serial.println(F("cm"));
	
	// wait before doing the next measurement
	delay(1000);
}
```

The method can return the result in inches (E_GFULTRASONIC_INCH) or centimeters (E_GFULTRASONIC_CM) by passing the appropriate parameter. If no parameter is passed to the read method, the distance is returned in centimeters.

## Supported devices ##

This library was developed/tested on the following boards:

* Arduino UNO R3
* Arduino Mega 2560 R3
* Raspberry Pi Pico
* ESP32 based devices

## Contact me ##

* Feel free to write for any inquiry: ruben at geekfactory.mx
* Check our website: https://www.geekfactory.mx
