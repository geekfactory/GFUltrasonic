/*	GFUltrasonic - Geek Factory Ultrasonic Library
	Copyright (C) 2024 Jesus Ruben Santa Anna Zamudio.

	This program is free software: you can redistribute it and/or modify
	it under the terms of the GNU General Public License as published by
	the Free Software Foundation, either version 3 of the License, or
	(at your option) any later version.

	This program is distributed in the hope that it will be useful,
	but WITHOUT ANY WARRANTY; without even the implied warranty of
	MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
	GNU General Public License for more details.

	You should have received a copy of the GNU General Public License
	along with this program.  If not, see <http://www.gnu.org/licenses/>.

	Author website: https://www.geekfactory.mx
	Author e-mail: ruben at geekfactory dot mx
 */

// include the library header file
#include <GFUltrasonic.h>

// instantiate an object to use the ultrasonic sensor using pin 4 and 5 for interfacing
GFUltrasonic ultrasonic(4, 5);

void setup()
{
	// initialize serial port
	Serial.begin(9600);

	// call begin() to get the IO pins initialized by the library
	ultrasonic.begin();
}

void loop()
{
	// call with parameter E_GFULTRASONIC_CM to get the distance in centimeters
	uint16_t distance_cm = ultrasonic.read(E_GFULTRASONIC_CM);
	// by default measurements are returned in cm, equivalent to the previous call is:
	// uint16_t distance_cm = ultrasonic.read();

	// call read with parameter E_GFULTRASONIC_INCH to get distance in inches
	uint16_t distance_in = ultrasonic.read(E_GFULTRASONIC_INCH);

	// check measurement validity and print to serial terminal
	if (distance_cm != GFULTRASONIC_INVALID_MEASUREMENT && distance_in != GFULTRASONIC_INVALID_MEASUREMENT)
	{
		// print the result to the serial terminal
		Serial.print(F("Measured distance: "));
		Serial.print(distance_cm);
		Serial.println(F("centimeters"));
		Serial.println(F(" or "));
		Serial.print(distance_in);
		Serial.println(F("inches"));
	}
	else
	{
		Serial.println(F("Measurement timeout"));
	}

	// wait before doing the next measurement
	delay(1000);
}