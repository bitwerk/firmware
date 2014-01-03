/*
 * Copyright 2012-2013 BrewPi/Elco Jacobs.
 *
 * This file is part of BrewPi.
 * 
 * BrewPi is free software: you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation, either version 3 of the License, or
 * (at your option) any later version.
 * 
 * BrewPi is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 * 
 * You should have received a copy of the GNU General Public License
 * along with BrewPi.  If not, see <http://www.gnu.org/licenses/>.
 */

#pragma once

#include "Brewpi.h"
#include "DisplayBase.h"
#include "SpiLcd.h"
#include "OLEDFourBit.h"
#include "NullLcdDriver.h"

#if BREWPI_EMULATE || !BREWPI_LCD || !ARDUINO
	typedef NullLcdDriver LcdDriver;
#elif !BREWPI_SHIFT_LCD
	typedef OLEDFourBit LcdDriver;	
#else
	typedef SpiLcd		LcdDriver;	
#endif

class LcdDisplay DISPLAY_SUPERCLASS
{
	public:
	// initializes the lcd display
	DISPLAY_METHOD void init(void);
	
	DISPLAY_METHOD void printAll() {
		printStationaryText();
		printState();
		printAllTemperatures();
		printMode();
	}
	
	// print all temperatures on the LCD
	DISPLAY_METHOD void printAllTemperatures(void);
	
	// print the stationary text on the lcd.
	DISPLAY_METHOD void printStationaryText(void);

	// print mode on the right location on the first line, after Mode:
	DISPLAY_METHOD void printMode(void);

	DISPLAY_METHOD void setDisplayFlags(uint8_t newFlags);
	DISPLAY_METHOD uint8_t getDisplayFlags(){ return flags; };

	// print beer temperature at the right place on the display
	DISPLAY_METHOD void printBeerTemp(void);

	// print beer temperature setting at the right place on the display
	DISPLAY_METHOD void printBeerSet(void);

	// print fridge temperature at the right place on the display
	DISPLAY_METHOD void printFridgeTemp(void);

	// print fridge temperature setting at the right place on the display
	DISPLAY_METHOD void printFridgeSet(void);

	// print the current state on the last line of the LCD
	DISPLAY_METHOD void printState(void);

	DISPLAY_METHOD void getLine(uint8_t lineNumber, char * buffer) { lcd.getLine(lineNumber, buffer); }

	DISPLAY_METHOD void printAt_P(uint8_t x, uint8_t y, const char* text);
	
	DISPLAY_METHOD void setBufferOnly(bool bufferOnly) {
		lcd.setBufferOnly(bufferOnly);
	}
	
	DISPLAY_METHOD void resetBacklightTimer() { lcd.resetBacklightTimer(); }
	DISPLAY_METHOD void updateBacklight() { lcd.updateBacklight(); }
	
	// print a temperature
	DISPLAY_METHOD void printTemperature(temperature temp);
	DISPLAY_METHOD void printTemperatureAt(uint8_t x, uint8_t y, temperature temp);

	// print degree sign + C/F
	DISPLAY_METHOD void printDegreeUnit(uint8_t x, uint8_t y);
		
	DISPLAY_METHOD void printAt(uint8_t x, uint8_t y, char* text);

	private:
	DISPLAY_FIELD LcdDriver lcd;
	DISPLAY_FIELD uint8_t stateOnDisplay;
	DISPLAY_FIELD uint8_t flags;		
};
