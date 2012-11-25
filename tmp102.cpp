/*************************************************************************//**
 * @file 	lcd_I2C.cpp
 * @brief	xx
 * @author	Nicolas BOUTIN
 * @date	01/11/2012
 * @module	LCD_I2C
 *****************************************************************************/

/*****************************************************************************
 * INCLUDE
 *****************************************************************************/
#include <Arduino.h>
#include <Wire.h>

#include "tmp102.h"
/*****************************************************************************
 * GLOBALE VARIABLE
 *****************************************************************************/
const uint8_t TMP102::tmp_reg_addr = 0b00;
const uint8_t TMP102::conf_reg_addr = 0b01;
const uint8_t TMP102::tmp_low_reg_addr = 0b10;
const uint8_t TMP102::tmp_high_reg_addr = 0b11;

/*****************************************************************************
 * PUBLIC IMPLEMENTATION
 *****************************************************************************/

TMP102::TMP102(const E8_ADD0_PIN i_e8_address)
{
	ui8_address = i_e8_address;
}

/**
 *
 */
void TMP102::begin()
{
	Wire.begin(ui8_address);
}

float TMP102::getTempCelcius()
{
	// Set Pointer Register to Temperature register
	Wire.beginTransmission(ui8_address);
	Wire.write(tmp_reg_addr);
	Wire.endTransmission();

	// Read MSB and LSB register temperature
	Wire.requestFrom(ui8_address, (uint8_t) 2, (uint8_t) true);
	uint8_t ui8_MSB = Wire.read();
	uint8_t ui8_LSB = Wire.read();

	//it's a 12bit int, using two's compliment for negative
	uint16_t ui16_temperature = ((ui8_MSB << 8) | ui8_LSB) >> 4;

	return ((float) ui16_temperature) * 0.0625;
}

/*****************************************************************************
 * PRIVATE IMPLEMENTATION
 *****************************************************************************/

/*****************************************************************************
 * END OF FILE
 *****************************************************************************/
