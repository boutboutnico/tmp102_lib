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

	typedef struct
	{
		unsigned D0 :1;
		unsigned D1 :1;
		unsigned D2 :1;
		unsigned D3 :1;
		unsigned EM :1;
		unsigned AL :1;
		unsigned CR0 :1;
		unsigned CR1 :1;

		unsigned SD :1;
		unsigned TM :1;
		unsigned POL :1;
		unsigned F0 :1;
		unsigned F1 :1;
		unsigned R0 :1;
		unsigned R1 :1;
		unsigned OS :1;
	} ST_Conf_Reg;

	typedef enum
	{
		Hz_0_25 = 0x00,
		Hz_1 = 0x1,
		Hz_4 = 0x2,	// Default
		Hz_8 = 0x3,
	} E8_Conversion_Rate;

	typedef union
	{
		ST_Conf_Reg bits;
		uint16_t value;
	} U_Conf_register;

private:
	// Attributes
	uint8_t ui8_address;
	U_Conf_register u_conf_reg;

	// Constants
	static const uint8_t tmp_reg_addr;
	static const uint8_t conf_reg_addr;
	static const uint8_t tmp_low_reg_addr;
	static const uint8_t tmp_high_reg_addr;

public:
	TMP102(const E8_ADD0_PIN i_e8_address);

	void begin();
	float getTemperature_Celcius();
	U_Conf_register getConfigurationRegister();
	bool setExtendedMode(const bool i_b_extended_mode);
	bool setConversionRate(const E8_Conversion_Rate i_e8_conversion_rate);

private:
	void setPointerRegister(const uint8_t i_ui8_register);
	void updateConfigurationRegister();
};

#endif //__LCDI2C__
/*****************************************************************************
 * END OF FILE
 *****************************************************************************/
