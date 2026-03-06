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

// instantiate an object to use the ultrasonic sensor using pin 4 for trigger and pin 5 for echo
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
	// call readMedian() to get the distance measurement using the median of multiple samples.
	// the first argument is the number of samples to take for the median calculation, and the second argument is the units for the measurement
	uint16_t distance = ultrasonic.readMedian(9, E_GFULTRASONIC_CM);

	if (distance != GFULTRASONIC_INVALID_MEASUREMENT)
	{
		// print the result to the serial terminal
		Serial.print(F("Measured distance: "));
		Serial.print(distance);
		Serial.println(F("cm"));
	}
	else
	{
		Serial.println(F("Measurement failed: timeout occurred"));
	}

	// wait before doing the next measurement
	delay(1000);
}