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

/**
 *
 * @param i_e8_address
 */
TMP102::TMP102(const E8_ADD0_PIN i_e8_address)
{
	ui8_address = i_e8_address;

	u_conf_reg.value = 0;
}

/**
 *
 */
void TMP102::begin()
{
	Wire.begin(ui8_address);

	updateConfigurationRegister();
}

/**
 *
 * @return
 */
float TMP102::getTemperature_Celcius()
{
	// Set Pointer Register to Temperature register
	setPointerRegister(tmp_reg_addr);

	// Read MSB and LSB register temperature
	Wire.requestFrom(ui8_address, (uint8_t) 2, (uint8_t) true);

	// Return 0, if read has failed
	if(Wire.available() != 2) return 0.0;

	uint8_t ui8_MSB = Wire.read();
	uint8_t ui8_LSB = Wire.read();

	int16_t i16_temperature = 0;

	//12 bits
	if(u_conf_reg.bits.EM == false)
	{
		i16_temperature = ((ui8_MSB << 8) | ui8_LSB) >> 4;

		// Negative value
		if((i16_temperature & 0xC00) == 0xC00)
		{
			i16_temperature |= 0xF000;
		}
	}
	// 13 bits
	else
	{
		i16_temperature = ((ui8_MSB << 8) | ui8_LSB) >> 3;

		// Negative value
		if((i16_temperature & 0x1C00) == 0x1C00)
		{
			i16_temperature |= 0xE000;
		}
	}

	return ((float) i16_temperature) * 0.0625;
}

/**
 *
 * @return
 */
TMP102::U_Conf_register TMP102::getConfigurationRegister()
{
	updateConfigurationRegister();

	return u_conf_reg;
}

/**
 *
 * @param i_b_extended_mode
 * @return
 */
bool TMP102::setExtendedMode(const bool i_b_extended_mode)
{
	u_conf_reg.bits.EM = i_b_extended_mode;

	uint8_t ui8_MSB = (u_conf_reg.value & 0xFF00) >> 8;
	uint8_t ui8_LSB = (u_conf_reg.value & 0x00FF);

	Wire.beginTransmission(ui8_address);
	Wire.write(conf_reg_addr);
	Wire.write(ui8_MSB);
	Wire.write(ui8_LSB);
	Wire.endTransmission(true);

	return true;
}

/**
 *
 * @param i_e8_conversion_rate
 * @return
 */
bool TMP102::setConversionRate(const E8_Conversion_Rate i_e8_conversion_rate)
{
	u_conf_reg.bits.CR0 = 0x1 & i_e8_conversion_rate;
	u_conf_reg.bits.CR1 = 0x2 & i_e8_conversion_rate;

	uint8_t ui8_MSB = (u_conf_reg.value & 0xFF00) >> 8;
	uint8_t ui8_LSB = (u_conf_reg.value & 0x00FF);

	Wire.beginTransmission(ui8_address);
	Wire.write(conf_reg_addr);
	Wire.write(ui8_MSB);
	Wire.write(ui8_LSB);
	Wire.endTransmission(true);

	return true;
}

/*****************************************************************************
 * PRIVATE IMPLEMENTATION
 *****************************************************************************/

/**
 *
 * @param i_ui8_register
 * @return
 */
void TMP102::setPointerRegister(const uint8_t i_ui8_register)
{
	Wire.beginTransmission(ui8_address);
	Wire.write(i_ui8_register);
	Wire.endTransmission(true);
}

/**
 *
 */
void TMP102::updateConfigurationRegister()
{
	// Set Pointer Register to configuration register
	setPointerRegister(conf_reg_addr);

	// Read MSB and LSB register temperature
	Wire.requestFrom(ui8_address, (uint8_t) 2, (uint8_t) true);

	// Don't update register, if read has failed
	if(Wire.available() != 2) return;

	uint8_t ui8_MSB = Wire.read();
	uint8_t ui8_LSB = Wire.read();

	u_conf_reg.value = (ui8_MSB << 8) | ui8_LSB;
}

/*****************************************************************************
 * END OF FILE
 *****************************************************************************/
