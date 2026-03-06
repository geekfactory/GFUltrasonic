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
	_singlepin = (_triggerpin == _echopin);
	_timeout = timeout;
	_triggerPulseLen = GFULTRASONIC_DEFAULT_TRIGGER_PULSE;
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

	// measure the response pulse length
	uint32_t pulsewidth = measurePulse();

	// check for invalid measurement (timeout)
	if (pulsewidth == 0)
		return GFULTRASONIC_INVALID_MEASUREMENT;
	// return the distance in the requested units by dividing the pulse width by the corresponding conversion factor
	return pulsewidth / ((units == E_GFULTRASONIC_CM) ? GFULTRASONIC_US_PER_CM : GFULTRASONIC_US_PER_INCH);
}

uint16_t GFUltrasonic::readMedian(uint8_t samples, enum GFUltrasonicUnits units)
{
	uint16_t measurements[9]; // maximum of 9 samples
	uint16_t valid = 0;	  // count of valid measurements

	// ensure the number of samples is odd and between 3 and 9 to have a single median value and avoid dynamic memory allocation
	if (samples < 3)
		samples = 3;
	if ((samples & 1) == 0)
		samples++;
	if (samples > 9)
		samples = 9;

	for (uint8_t i = 0; i < samples; i++)
	{
		// read a measurement and store it if it's valid
		uint16_t d = read(units);

		if (d != GFULTRASONIC_INVALID_MEASUREMENT)
			measurements[valid++] = d;

		// add a small delay between samples to avoid interference between measurements
		delay(10);
	}

	// if we don't have any valid measurement, return the invalid measurement value
	if (valid == 0)
		return GFULTRASONIC_INVALID_MEASUREMENT;

	// sort the measurements using insertion sort
	for (uint8_t i = 1; i < valid; i++)
	{
		uint16_t key = measurements[i];
		int j = i - 1;
		while (j >= 0 && measurements[j] > key)
		{
			measurements[j + 1] = measurements[j];
			j--;
		}
		measurements[j + 1] = key;
	}

	// return the median value
	return measurements[valid / 2];
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
	while (LOW == digitalRead(_echopin))
	{
		// return 0 (invalid measurement) if we have waited too long for the pulse to start
		if ((micros() - pulse) > _timeout)
			return 0;
	}

	// start measurement of the echo pulse (high level)
	pulse = micros();
	while (HIGH == digitalRead(_echopin))
	{
		// return 0 (invalid measurement) if we have waited too long for the pulse to end
		if ((micros() - pulse) > _timeout)
			return 0;
	}

	// return the time of the high pulse
	return micros() - pulse;
}
