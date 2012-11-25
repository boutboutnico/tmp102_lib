/************************************************
 * This example code is in the public domain.
 * @file	tmp102.ino
 * @brief	Demonstrates use of the TMP102 Library
 * @author	Nicolas BOUTIN
 * @date	22/11/2012
 ***********************************************/

// gets rid of annoying "depreciated conversion from string constant warning
#pragma GCC diagnostic ignored "-Wwrite-strings"

/*****************************************************************************
 * INCLUDE
 *****************************************************************************/
#include <stdlib.h>
#include <Wire.h>

#include "tmp102.h"
#include "lcd_I2C.h"

LCD_I2C lcd(0x00, 4, 20);
TMP102 tmp102(TMP102::SDA);

/*****************************************************************************
 * SETUP
 *****************************************************************************/
void setup()
{
	tmp102.begin();
	lcd.begin();
}

/*****************************************************************************
 * LOOP
 *****************************************************************************/
void loop()
{
	float f_temp = tmp102.getTempCelcius();
	lcd.printf(0,0,"temp : %d\n", f_temp);

	delay(500);
}
/*****************************************************************************
 * END OF FILE
 *****************************************************************************/
