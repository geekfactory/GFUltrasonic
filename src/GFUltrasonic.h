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
 * Conversion factor from microseconds to centimeters
 */
constexpr uint32_t GFULTRASONIC_US_PER_CM = 58UL;

/**
 * Conversion factor from microseconds to inches
 */
constexpr uint32_t GFULTRASONIC_US_PER_INCH = 148UL;

/**
 * Invalid measurement value returned by the library when a timeout occurs while waiting for the echo pulse to start or end.
 */
constexpr uint16_t GFULTRASONIC_INVALID_MEASUREMENT = 0xFFFF;

/**
 * Invalid pin value used to initialize the class member variables that store the sensor pin numbers. This value is never used
 * in the library and can be used by the user to check if the object was properly initialized with valid pin numbers.
 */
constexpr uint8_t GFULTRASONIC_INVALID_PIN = 0xFF;

/**
 * Default timeout for the pulse signal in microseconds. This value corresponds to a maximum measurable distance of around
 * 5 meters, which is the maximum range of most low-cost ultrasonic sensors.
 */
constexpr uint32_t GFULTRASONIC_DEFAULT_TIMEOUT = 29000UL;

/**
 * Default trigger pulse length in microseconds. This value is suitable for most ultrasonic sensors, but can be changed
 * using the setTriggerPulse() member function.
 */
constexpr uint32_t GFULTRASONIC_DEFAULT_TRIGGER_PULSE = 10UL;

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
	GFUltrasonic(int pin, uint32_t timeout = GFULTRASONIC_DEFAULT_TIMEOUT) : GFUltrasonic(pin, pin, timeout) {};

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
	GFUltrasonic(int triggerpin, int echopin, uint32_t timeout = GFULTRASONIC_DEFAULT_TIMEOUT);

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
	 * @brief Read the distance using the median of multiple samples.
	 * 
	 * Reads the distance from the ultrasonic sensor by taking multiple samples and returning
	 * the median value. This can help to reduce the effect of outliers and improve the accuracy
	 * of the measurement.
	 * 
	 * @param samples The number of samples to take for the median calculation. Default is 3,
	 * minimum is 3 and maximum is 9. If an even number is provided, it will be incremented to
	 * the next odd number to ensure a single median value.
	 * @param units A value (as defined in GFUltrasonicUnits enum) indicating if we want to read
	 * the distance in cm or inches.
	 * 
	 * @return The median of the measured distance samples in either cm (default) or inches.
	 */
	uint16_t readMedian(uint8_t samples = 3, enum GFUltrasonicUnits units = E_GFULTRASONIC_CM);

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
	uint8_t _echopin = GFULTRASONIC_INVALID_PIN;
	uint8_t _triggerpin = GFULTRASONIC_INVALID_PIN;
	bool _singlepin = false;
	uint32_t _timeout = GFULTRASONIC_DEFAULT_TIMEOUT;
	uint32_t _triggerPulseLen = GFULTRASONIC_DEFAULT_TRIGGER_PULSE;

	void triggerPulse();
	uint32_t measurePulse();
};

#endif