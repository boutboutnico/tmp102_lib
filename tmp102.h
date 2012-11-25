/*************************************************************************//**
 * @file 	tmp102.h
 * @brief	xx
 * @author	Nicolas BOUTIN
 * @date	22/11/2012
 * @module	SFR05
 *****************************************************************************/
#ifndef __LCDI2C__
#define __LCDI2C__

/*****************************************************************************
 * INCLUDE
 *****************************************************************************/
#include <Arduino.h>
#include <Wire.h>

/*****************************************************************************
 * DEFINITION
 *****************************************************************************/

/*****************************************************************************
 * CLASS
 *****************************************************************************/
/**
 * @class 	TMP102
 * @brief	xx
 * @author	Nicolas BOUTIN
 * @date	22/11/2012
 */
class TMP102
{
public:
	typedef enum
	{
		GND = 0x48,
		VCC = 0x49,
		SDA = 0x4A,
		SCL = 0x4B
	} E8_ADD0_PIN;

private:
	uint8_t ui8_address;

	static const uint8_t tmp_reg_addr;
	static const uint8_t conf_reg_addr;
	static const uint8_t tmp_low_reg_addr;
	static const uint8_t tmp_high_reg_addr;

public:
	TMP102(const E8_ADD0_PIN i_e8_address);

	void begin();
	float getTempCelcius();

};

#endif //__LCDI2C__
/*****************************************************************************
 * END OF FILE
 *****************************************************************************/
