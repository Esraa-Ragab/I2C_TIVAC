/**************************************************************************************
*        File name: GPIO_Config.c
*        Auther :edited by the user
*        Date: 2/7/2019
*        Description:
*                        This file contains:
*                        - An array of structurs that containes the croups to initialize the GPIO
*        Microcontroller: TM4C123GH6PM
***************************************************************************************/

#include "GPIO.h"
#include "GPIO_Cfg.h"
const GPIO_CfgType GPIO_ConfigParam [GPIO_GROUPS_NUMBER] =
		{
				{
						0x05,1<<1,
						0,0,0,
						0xff,
						0x00,0xff,0x00,
						0xff,0x00,0x00,
						0xff



				},
				{
				         0x05,1<<2,
				         0,0,0,
				         0xff,
				         0x00,0xff,0x00,
				         0xff,0x00,0x00,
				         0xff

				 },

				 {
				          0x05,1<<3,
				          0,0,0,
				          0xff,
				          0x00,0xff,0x00,
				          0xff,0x00,0x00,
				          0xff



				    },
				      {

					0x05,1<<0,
					0,0,0,
					0x00,
					0xff,0x00,0x00,
					0x00,0x00,0x00,
					0xff

			         },

		           	{
								0x05,1<<4,
								0,0,0,
								0x00,
								0xff,0x00,0x00,
								0x00,0x00,0x00,
								0xff

				    }
				
		};
