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

#include <GFUltrasonic.h>

GFUltrasonic::GFUltrasonic(int triggerpin, int echopin, uint32_t timeout)
{
	// store pin data
	_triggerpin = triggerpin;
	_echopin = echopin;
	_singlepin = (_triggerpin == _echopin) ? true : false;
	_timeout = timeout;
}

void GFUltrasonic::begin()
{
	// configure the pins to the required mode of operation
	// if only a pin is used for communication it remains an input after this call
	pinMode(_triggerpin, OUTPUT);
	pinMode(_echopin, INPUT);
}

uint16_t GFUltrasonic::read(enum GFUltrasonicUnits units)
{
	// switch pin to output mode
	if (_singlepin)
		pinMode(_triggerpin, OUTPUT);

	// send trigger pulse to the sensor
	triggerPulse();

	// switch pin to input mode
	if (_singlepin)
		pinMode(_triggerpin, INPUT);

	// measure the response pulse length and calculate distance
	return measurePulse() / ((units == E_GFULTRASONIC_CM) ? 58 : 142);
}

void GFUltrasonic::setTimeout(uint32_t timeout)
{
	_timeout = timeout;
}

void GFUltrasonic::setTriggerPulse(uint32_t length)
{
	_triggerPulseLen = length;
}

void GFUltrasonic::triggerPulse()
{
	// make sure pin is low
	digitalWrite(_triggerpin, LOW);
	delayMicroseconds(2);
	// send trigger pulse
	digitalWrite(_triggerpin, HIGH);
	delayMicroseconds(_triggerPulseLen);
	digitalWrite(_triggerpin, LOW);
}

uint32_t GFUltrasonic::measurePulse()
{
	uint32_t pulse;

	// wait for the start of the high pulse
	pulse = micros();
	while (LOW == digitalRead(_echopin) && (micros() - pulse) <= _timeout)
		;

	// start measurement of the echo pulse (high level)
	pulse = micros();
	while (HIGH == digitalRead(_echopin) && (micros() - pulse) <= _timeout)
		;

	// return the time of the high pulse
	return micros() - pulse;
}
