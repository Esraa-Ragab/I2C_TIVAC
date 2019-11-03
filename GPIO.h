/**********************************************************************************
*   File name: GPIO.h
*   Auther :  Esraa Ahmed

*   Date : 2/7/2019
*   Discription :
            this file contains:
                -prototype of the APIs of the GPIO
*   Microcontroller: TM4C123GH6PM
**********************************************************************************/

#ifndef GPIO_H
#define GPIO_H
#include <stdint.h>
#include "GPIO_Cfg.h"

/***********************************************************************************
**********                      Defined data types                          ********
***********************************************************************************/

//structure to be filled by the user to configure the GPIO
typedef struct
{
 /*Port ID */
  /* Port A -> 0x00
   * Port B -> 0x01
   * Port C -> 0x02
   * Port D -> 0x03
   * Port E -> 0x04
   * Port F -> 0x05
   */
uint8_t PortId;
/* Port Mask*/
/* Pin0 -> 1<<0
 * Pin1 -> 1<<1
 * Pin2 -> 1<<2
 * Pin3 -> 1<<3
 * Pin4 -> 1<<3
 * Pin5 -> 1<<5
 * Pin6 -> 1<<6
 * Pin7 -> 1<<7
 */
uint8_t PortMask;
/*Mode Control*/
uint8_t UseAlterFun;
uint8_t UseDMATrig;
uint8_t UseACDTrig;
/*Data Control*/
/*input -> 0
 *Output-> 1
 */
uint8_t PortDirection;
/*Pad Control*/
/*Internal Resistor*/
uint8_t UsePullUp;
uint8_t UsePullDown;
uint8_t UseOpenDrain;
/*Output current*/
uint8_t Use2mACrt;
uint8_t Use4mACrt;
uint8_t Use8mACrt;
/*Pin Type*/
/*analog -> 0
 *Digital-> 1
 */
uint8_t SetPinType;
}GPIO_CfgType;

//enumerate data type for the functions' return values
typedef enum {GPIO_OK =0, GPIO_NOK} GPIO_CheckType;


//extern constant array of GPIO_ConfigType structure of the GPIO groups
extern const GPIO_CfgType GPIO_ConfigParam [GPIO_GROUPS_NUMBER];


/***********************************************************************************
**********                      Functions prototypes                        ********
***********************************************************************************/

/*
 * This function used to initialize all the GPIO Groups in the configurations
 * Inputs:NONE
 * Output:
    - an indication of the success of the function
*/
GPIO_CheckType GPIO_Init(void);

/*
 * This function used to Digital Write data to a specific group
 * Inputs:
    - GroupId        : the index of the structure in the GPIO_ConfogParam array
    - Data           : the data to write to that specific group
 * Output:
    - an indication of the success of the function
*/

GPIO_CheckType GPIO_Write(uint8_t GroupId,uint8_t GroupData);

/*
 * This function used to Digital read data from a specific group
 * Inputs:
    - GroupId        : the index of the structure in the GPIO_ConfogParam array
    - GroupDataPtr        : a pointer to a variable to store the data read from that specific group
 * Output:
    - an indication of the success of the function
*/
GPIO_CheckType GPIO_Read(uint8_t GroupId,uint8_t* GroupDataPtr);

/*
 * This function used to select which peripheral will be connected to a GPIO pin
 * Inputs:
    - GroupId        : the index of the structure in the GPIO_ConfogParam array
    - AlternFuncId   : the ID of the alternative function
 * Output:
    - an indication of the success of the function
*/
GPIO_CheckType GPIO_SetAlternFuntion(uint8_t GroupId,uint8_t AlternFuncId);
/*
 * This function used to get the PIN number from the mask
 * Inputs:
    - PinMask        : the mask of the pin (1<< the pin number)
 * Output:
    - the number of the pin
 * */
uint8_t PIN_NUM(uint8_t Pin_Mask);
#endif
