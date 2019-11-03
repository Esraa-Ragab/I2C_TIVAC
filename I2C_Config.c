/*
 *
 *  Authors: Esraa Ahmed & Mohamed Rostom
 *  Date:2/2/2019
 *  Microcontroller: TM4C123GH6PM
 *
*/

#include "I2C_Driver.h"

void I2C_TxDone(void);
void I2C_RxDone(void);

const I2C_ConfigType I2C_ConfigParam[I2C_PERIPHERAL_NUMBER]=
{
	{
		0,								/*Peripheral ID*/
		0x3B,                           /*Device address*/
		100000,							/*Frequency SCL=100KHz*/
		PERIPHERAL_CLOCK_16MHz,		    /*Peripheral Frequency*/
		PERIPHERAL_ENABLE,				/*enable the peripherla*/  /////////////////////////////
		STANDARD_MODE,                  /*choose the standard mode*/
		I2C_SLAVE,                       /*choose I2C mode*/
		ENABLE_ACK,                     /*choose to enable the acknowledgment*/
		I2C_TxDone,
		I2C_RxDone,
	}
};

