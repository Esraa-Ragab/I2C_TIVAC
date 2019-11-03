/**************************************************************************************
*        File name: GPIO.c
*        Auther :
*                        Esraa Ragab
*        Date: 2/7/2019
*        Description:
*                        This file contains:
*                        -macros to access GPIO registers
*                        - implementation of functions used to access GPIO register
*         Microcontroller:TM4C123GH6PM
***************************************************************************************/

#include "GPIO.h"
#include "GPIO_Cfg.h"
#include "M4MemMap.h"
#include <stdint.h>

/***********************************************************************************
 * Function to get the Pin Number  from the mask
 *************************************************************************************/
 uint8_t PIN_NUM(uint8_t Pin_Mask)
    {
        uint8_t Counter;
     for (Counter=0;Counter<=7;Counter++)
     {

         if((Pin_Mask&0x01)==0x01)
         {
             return Counter;
             break;
         }
         else
         {
             Pin_Mask = (Pin_Mask >> 1);
         }
     }
    }

/***********************************************************************************
**********                  Defined data types                              ********
***********************************************************************************/

/*define a datatype that is volatile (to privent compiler optimization)
 *and constat becouse it carries a constant address
*/
typedef volatile uint32_t* const GPIO_RegAddType;

// number of available ports
#define PORTS_NUMBER 6u
/*Register memory map*/
#define PORTA_BASE_ADDRESS 0x40004000   //address for the GPIOA
#define PORTB_BASE_ADDRESS 0x40005000   //address for the GPIOB
#define PORTC_BASE_ADDRESS 0x40006000   //address for the GPIOC
#define PORTD_BASE_ADDRESS 0x40007000   //address for the GPIOD
#define PORTE_BASE_ADDRESS 0x40024000   //address for the GPIOE
#define PORTF_BASE_ADDRESS 0x40025000   //address for the GPIOF

//array of the base addresses of the GPIO ports to acess them by an index
static const uint32_t PortsBaseAddressLut[PORTS_NUMBER] =
{   PORTA_BASE_ADDRESS,
	PORTB_BASE_ADDRESS,
	PORTC_BASE_ADDRESS,
	PORTD_BASE_ADDRESS,
	PORTE_BASE_ADDRESS,
	PORTF_BASE_ADDRESS
};
/***********************************************************************************
**********              Macro like function to control the GPIO             ********
***********************************************************************************/

//macro like function to generate the addres of the used register in the GPIO port
#define GPIO_REG_ADDRESS(CHANNEL_ID,REG_OFFSET)\
(PortsBaseAddressLut[CHANNEL_ID] + REG_OFFSET)

/*Port Control*/

//macro like function to write to the pin
#define GPIODATA_WRITE(DATA,MASK,PORT_ID)  *((GPIO_RegAddType)(GPIO_REG_ADDRESS(PORT_ID,0x000) + (MASK << 2))) = DATA
//macro like function to read from the pin
#define GPIODATA_READ(MASK,PORT_ID)        *((GPIO_RegAddType)(GPIO_REG_ADDRESS(PORT_ID,0x000) + (MASK << 2)))

#define GPIODIR_REG(PORT_ID)              *((GPIO_RegAddType)GPIO_REG_ADDRESS(PORT_ID,0x400))

/*Interrupt Control*/
#define GPIOIS_REG(PORT_ID)               *((GPIO_RegAddType)GPIO_REG_ADDRESS(PORT_ID,0x404))
#define GPIOIBE_REG(PORT_ID)              *((GPIO_RegAddType)GPIO_REG_ADDRESS(PORT_ID,0x408))
#define GPIOIEV_REG(PORT_ID)              *((GPIO_RegAddType)GPIO_REG_ADDRESS(PORT_ID,0x40C))
#define GPIOIM_REG(PORT_ID)               *((GPIO_RegAddType)GPIO_REG_ADDRESS(PORT_ID,0x410))
#define GPIORIS_REG(PORT_ID)              *((GPIO_RegAddType)GPIO_REG_ADDRESS(PORT_ID,0x414))
#define GPIOMIS_REG(PORT_ID)              *((GPIO_RegAddType)GPIO_REG_ADDRESS(PORT_ID,0x418))
#define GPIOICR_REG(PORT_ID)              *((GPIO_RegAddType)GPIO_REG_ADDRESS(PORT_ID,0x41C))

/*Mode Control*/
#define GPIOAFSEL_REG(PORT_ID)            *((GPIO_RegAddType)GPIO_REG_ADDRESS(PORT_ID,0x420))
#define GPIOPCTL_REG(PORT_ID)             *((GPIO_RegAddType)GPIO_REG_ADDRESS(PORT_ID,0x52C))
#define GPIOADCCTL_REG(PORT_ID)           *((GPIO_RegAddType)GPIO_REG_ADDRESS(PORT_ID,0x530))
#define GPIODMACTL_REG(PORT_ID)           *((GPIO_RegAddType)GPIO_REG_ADDRESS(PORT_ID,0x534))

/*Pad control*/
#define GPIODR2R_REG(PORT_ID)           *((GPIO_RegAddType)GPIO_REG_ADDRESS(PORT_ID,0x500))
#define GPIODR4R_REG(PORT_ID)           *((GPIO_RegAddType)GPIO_REG_ADDRESS(PORT_ID,0x504))
#define GPIODR8R_REG(PORT_ID)           *((GPIO_RegAddType)GPIO_REG_ADDRESS(PORT_ID,0x508))
#define GPIOODR_REG(PORT_ID)            *((GPIO_RegAddType)GPIO_REG_ADDRESS(PORT_ID,0x50C))
#define GPIOPUR_REG(PORT_ID)            *((GPIO_RegAddType)GPIO_REG_ADDRESS(PORT_ID,0x510))
#define GPIOPDR_REG(PORT_ID)            *((GPIO_RegAddType)GPIO_REG_ADDRESS(PORT_ID,0x514))
#define GPIOSLR_REG(PORT_ID)            *((GPIO_RegAddType)GPIO_REG_ADDRESS(PORT_ID,0x518))
#define GPIODEN_REG(PORT_ID)            *((GPIO_RegAddType)GPIO_REG_ADDRESS(PORT_ID,0x51C))
#define GPIOAMSEL_REG(PORT_ID)          *((GPIO_RegAddType)GPIO_REG_ADDRESS(PORT_ID,0x528))

/*Commit control*/
#define GPIOLOCK_REG(PORT_ID)          *((GPIO_RegAddType)GPIO_REG_ADDRESS(PORT_ID,0x520))
#define GPIOCR_REG(PORT_ID)            *((GPIO_RegAddType)GPIO_REG_ADDRESS(PORT_ID,0x524))

/*Internal symbols*/
#define GPIO_PORT_UNLOCK_VALUE 0x4C4F434B
#define GPIO_INT_SENCE_BIT_NUM 1
#define GPIO_INT_SENCE_MASK (1 << GPIO_INT_EVENT_BIT_NUM)
#define GPIO_INT_EVENT_BIT_NUM 0
#define GPIO_INT_EVENT_MASK (1 << GPIO_INT_EVENT_BIT_NUM)
#define GPIO_INT_BE_BIT_NUM 2
#define GPIO_INT_BR_MASK (1 << GPIO_INT_BE_BIT_NUM)

/*
 *********************************************************************************************
 *  The following are defines for the bit fields in the GPIO_PCTL register for I2C peripheral *
 *********************************************************************************************
 */
#define AF_I2C   3  // I2C PMCx value

/***********************************************************************************
**********                  Declare Globals                                 ********
***********************************************************************************/
/*a static variable to hold the state if the GPIO groups
        1 => initialized
        0 => not initialized
*/
static uint8_t GPIO_GroupState[GPIO_GROUPS_NUMBER] = {0};

/***********************************************************************************
**********                      GPIO functions' bodies                      ********
***********************************************************************************/

/*
 * This function used to initialize all the GPIO Groups in the configurations
 * Inputs:NONE
 * Output:
         - an indication of the success of the function
*/
GPIO_CheckType GPIO_Init(void)
{
    //declarations
	uint8_t LoopIndex; //loop index
	uint8_t ErrorFlag = 0;
	GPIO_CheckType RetVar; // variable to indicate the success of the initialization
	const GPIO_CfgType * CfgPtr; //declare a pointer to structur of the GPIO_ConfigType

	//loop on the number of GPIO pin configurations
	for(LoopIndex = 0; (LoopIndex < GPIO_GROUPS_NUMBER) && (ErrorFlag == 0); LoopIndex ++)
	{
	    //check if the port number withen the allowed range
		if(GPIO_ConfigParam[LoopIndex].PortId < PORTS_NUMBER)
		{


		    //assign a pointer to the configuration structure
			CfgPtr = & GPIO_ConfigParam[LoopIndex];

            /*Enable port clock gate*/
			RCGCGPIO_REG |= 1 << CfgPtr->PortId;
			/*Unlock the group*/
			GPIOLOCK_REG(CfgPtr->PortId) = GPIO_PORT_UNLOCK_VALUE;
			GPIOCR_REG(CfgPtr->PortId)  |= (CfgPtr->PortMask);
			/*Data Control*/
			GPIODIR_REG(CfgPtr->PortId) |= (CfgPtr->PortMask & CfgPtr->PortDirection);
			/*Pad Control*/
			GPIODR2R_REG(CfgPtr->PortId) |= (CfgPtr->PortMask & CfgPtr->Use2mACrt);
			GPIODR4R_REG(CfgPtr->PortId) |= (CfgPtr->PortMask & CfgPtr->Use4mACrt);
			GPIODR8R_REG(CfgPtr->PortId) |= (CfgPtr->PortMask & CfgPtr->Use8mACrt);

			GPIOPDR_REG(CfgPtr->PortId) |= (CfgPtr->PortMask & CfgPtr->UsePullDown);
			GPIOPUR_REG(CfgPtr->PortId) |= (CfgPtr->PortMask & CfgPtr->UsePullUp);
			GPIOODR_REG(CfgPtr->PortId) |= (CfgPtr->PortMask & CfgPtr->UseOpenDrain);

			GPIODEN_REG(CfgPtr->PortId)   |= (CfgPtr->PortMask & CfgPtr->SetPinType);
			GPIOAMSEL_REG(CfgPtr->PortId) |= (CfgPtr->PortMask & ~CfgPtr->SetPinType);

			/*Mode control*/
			GPIOAFSEL_REG(CfgPtr->PortId)  |= (CfgPtr->PortMask & CfgPtr->UseAlterFun);
			GPIOADCCTL_REG(CfgPtr->PortId) |= (CfgPtr->PortMask & CfgPtr->UseACDTrig);
			GPIODMACTL_REG(CfgPtr->PortId) |= (CfgPtr->PortMask & CfgPtr->UseDMATrig);

			//change the state of this group to initialized
			GPIO_GroupState[LoopIndex] = 1;
			//initialization done successfully
			RetVar = GPIO_OK;
		}
		else
		{
			/*Invalid GroupId*/
			RetVar = GPIO_NOK;
			ErrorFlag = 1;
		}


	}
	return RetVar;
}

/*
 * This function used to Digital Write data to a specific group
 * Inputs:
    - GroupId        : the index of the structure in the GPIO_ConfogParam array
    - Data           : the data to write to that specific group
 * Output:
    - an indication of the success of the function
*/
GPIO_CheckType GPIO_Write(uint8_t GroupId,uint8_t GroupData)
{
    //declarations
	const GPIO_CfgType * CfgWrhit; //declare a pointer to structur of the GPIO_ConfigType

	GPIO_CheckType RetVar; // variable to indicate the success of the writing

	//check if the group number withen the allowed range
	if (( GroupId <GPIO_GROUPS_NUMBER))
	{
	    //assign a pointer to the configuration structure
		CfgWrhit =  & GPIO_ConfigParam[GroupId];

		//check if the group mode is output and the group is initialized
		if ((CfgWrhit->PortDirection == 0xff)&&(CfgWrhit->SetPinType == 0xff)&&(CfgWrhit->UseAlterFun==0x00) &&(GPIO_GroupState[GroupId]==1 ))
		{

		    //write the data to the group
		GPIODATA_WRITE(GroupData,CfgWrhit->PortMask,CfgWrhit->PortId);
		//writing done successfully
		RetVar = GPIO_OK ;

	    }else {RetVar = GPIO_NOK ; }  //the group mode isn't output or the group isn't initialized

	}else {RetVar = GPIO_NOK ; } //the group number isn't withen the allowed range

	return RetVar;
}

/*
 * This function used to Digital read data from a specific group
 * Inputs:
         - GroupId                 : the index of the structure in the GPIO_ConfogParam array
         - DataPtr                   : a pointer to a variable to store the data read from that specific group
 * Output:
         - an indication of the success of the function
*/
GPIO_CheckType GPIO_Read(uint8_t GroupId,uint8_t* GroupDataPtr)
{
    //declarations
	const GPIO_CfgType * CfgRead; //declare a pointer to structur of the GPIO_ConfigType
	GPIO_CheckType RetVar;  // variable to indicate the success of the reading

	//check if the group number withen the allowed range
	if (( GroupId <GPIO_GROUPS_NUMBER))
	{
	    //assign a pointer to the configuration structure
		CfgRead =  & GPIO_ConfigParam[GroupId];

		 //check if the group mode is input and the group is initialized
		if ((CfgRead->PortDirection == 0x00)&&(CfgRead->SetPinType == 0xff)&&(CfgRead->UseAlterFun==0x00) &&(GPIO_GroupState[GroupId]==1 ))
		{
		    //read the data from the group
			* GroupDataPtr = GPIODATA_READ(CfgRead->PortMask,CfgRead->PortId);
			//reading done successfully
			RetVar = GPIO_OK ;

		}else {RetVar = GPIO_NOK ; }  //the group mode isn't input or the group isn't initialized

	}else {RetVar = GPIO_NOK ; }     //the group number isn't withen the allowed range

	return RetVar;


		}

/*
 * This function used to select which peripheral will be connected to a GPIO pin
 * Inputs:
 	- GroupId		 : the index of the structure in the GPIO_ConfogParam array
 	- AlternFuncId   : the ID of the alternative function
 * Output:
 	- an indication of the success of the function
*/
GPIO_CheckType GPIO_SetAlternFuntion(uint8_t GroupId,uint8_t AlternFuncId)
{
    //declarations
   GPIO_CheckType RetVar; // variable to indicate the success of the reading
   const GPIO_CfgType * CfgPtr; //declare a pointer to structur of the GPIO_ConfigType
   
   //check if the group number withen the allowed range
  if (( GroupId <GPIO_GROUPS_NUMBER))
  {
	  //assign a pointer to the configuration structure
	  CfgPtr = &GPIO_ConfigParam[GroupId];
	  //check if the group mode is altirnative function and the group is initialized
	   if( (CfgPtr->UseAlterFun == 1) && (GPIO_GroupState[GroupId] == 1) )
	   {
          // set the the PMC value
		  GPIOPCTL_REG(CfgPtr->PortId) |=AlternFuncId<<(4*(PIN_NUM (CfgPtr->PortMask)));
		  
           //setting alternative function done successfully
           RetVar = GPIO_OK;
                }
                else 
                {
                        //the group mode isn't alternative function or the group isn't initialized
                        RetVar = GPIO_NOK; 
                }
        }
        else 
        {
                //the group number isn't withen the allowed range
                RetVar = GPIO_NOK; 
        }

        return RetVar;
}





