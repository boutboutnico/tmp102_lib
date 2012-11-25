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

TMP102 tmp102(TMP102::SDA);

/*****************************************************************************
 * SETUP
 *****************************************************************************/
void setup()
{
	tmp102.begin();

	Serial.begin(9600);
}

/*****************************************************************************
 * LOOP
 *****************************************************************************/
void loop()
{
	float f_temp = tmp102.getTempCelcius();
	Serial.println(f_temp);

	delay(500);
}
/*****************************************************************************
 * END OF FILE
 *****************************************************************************/
