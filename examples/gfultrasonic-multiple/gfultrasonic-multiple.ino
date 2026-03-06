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
GFUltrasonic ultrasonic1(4, 5);

// instantiate another object to use a second ultrasonic sensor using pin 6 for trigger and pin 7 for echo
GFUltrasonic ultrasonic2(6, 7);


void setup()
{
	// initialize serial port
	Serial.begin(9600);

	// call begin() to get the IO pins initialized by the library
	ultrasonic1.begin();
	ultrasonic2.begin();
}

void loop()
{
	// call read() to get the distance in centimeters
	uint16_t distance1 = ultrasonic1.read();
	delay(20); // wait a bit before reading the second sensor to avoid interference
	uint16_t distance2 = ultrasonic2.read();

	// print the result to the serial terminal
	Serial.print(F("Distance 1: "));
	Serial.print(distance1);
	Serial.println(F("cm"));
	Serial.print(F("Distance 2: "));
	Serial.print(distance2);
	Serial.println(F("cm"));

	// wait before doing the next measurement
	delay(1000);
}