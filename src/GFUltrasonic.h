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

#ifndef GFULTRASONIC_H
#define GFULTRASONIC_H

#include <Arduino.h>

/**
 * Defines the units of the distance measurement
 */
enum GFUltrasonicUnits
{
	/**
	 * Use centimeters for measurement result
	 */
	E_GFULTRASONIC_CM,

	/**
	 * Use inches for measurement result
	 */
	E_GFULTRASONIC_INCH,
};

/**
 * @brief Class used to abstract the ultrasonic sensor operation from the main program.
 *
 * This class allows the manipulation of various ultrasonic distance sensors using a unified
 * API. The library is designed to be easy to use and very lightweight.
 */
class GFUltrasonic
{
public:
	/**
	 * @brief Construct a new GFUltrasonic object.
	 *
	 * Constructor for use with single pin interface sensors. The same pin is used for
	 * trigger and echo signals.
	 *
	 * @param pin The pin number where the sensor is connected.
	 * @param timeout The maximum time the echo pulse can be high or low.
	 */
	GFUltrasonic(int pin, uint32_t timeout = 20000UL) : GFUltrasonic(pin, pin, timeout){};

	/**
	 * @brief Construct a new GFUltrasonic object.
	 *
	 * Constructor for use with two pin interface. A dedicated pin is used for trigger
	 * and echo signals.
	 *
	 * @param triggerpin The pin number where the trigger signal is connected.
	 * @param echopin The pin number where the echo signal is connected.
	 * @param timeout The maximum time the echo pulse can be high or low.
	 */
	GFUltrasonic(int triggerpin, int echopin, uint32_t timeout = 20000UL);

	/**
	 * @brief Prepares the object for use.
	 *
	 * Prepares the objet for use by initializing the sensor pin(s) to the required state.
	 */
	void begin();

	/**
	 * @brief Read the distance.
	 *
	 * Reads the distance from the ultrasonic sensor by asserting the trigger signal and
	 * reading the length of the echo pulse.
	 *
	 * @param units A value (as defined in GFUltrasonicUnits enum) indicating if we want
	 * to read the distance in cm or inches.
	 *
	 * @return The measured distance in either cm (default) or inches.
	 */
	uint16_t read(enum GFUltrasonicUnits units = E_GFULTRASONIC_CM);

	/**
	 * @brief Set the timeout for the pulse signal.
	 *
	 * @param timeout The maximum time to wait for the echo pulse in microseconds.
	 */
	void setTimeout(uint32_t timeout);

	/**
	 * @brief Set the trigger pulse length.
	 *
	 * Configures the trigger pulse length, default length is 10 microseconds but can be
	 * changed using this funcion member.
	 *
	 * @param length
	 */
	void setTriggerPulse(uint32_t length);

private:
	int _echopin = -1;
	int _triggerpin = -1;
	bool _singlepin = false;
	uint32_t _timeout = 20000UL;
	uint32_t _triggerPulseLen = 10UL;

	void triggerPulse();
	uint32_t measurePulse();
};

#endif