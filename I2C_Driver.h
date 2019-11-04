/*
 *
 *	Authors: Esraa Ahmed 
 *	Date:2/2/2019
 *	Microcontroller: TM4C123GH6PM
 *
*/


#ifndef I2C_DRIVER_H
#define I2C_DRIVER_H

#include <stdint.h>
#include "I2C_Config.h"
#include "GPIO.h"

#define MAX_SCL_FREQUENCY_SM		(100000U)
#define MAX_SCL_FREQUENCY_FM		(400000U)
#define MAX_SCL_FREQUENCY_FMP       (1000000U)
#define MAX_SCL_FREQUENCY_HSM       (3330000U)
#define WRITE 						(0U)
#define READ						(1U)
#define	I2C_DELAY_PARAMETER			(50U)

typedef volatile uint32_t* const I2C_RegisterAddressType;

/*
 ******************************************************************************
 *            						BASES						              *
 ******************************************************************************
 */
#define PERIPHERAL_BASE    						(0x40020000U)
#define SYS_CTRL_BASE_ADDRESS                   (0x400FE000U)
#define I2C_BASE								(PERIPHERAL_BASE+0x0000U)

/*
 ******************************************************************************
 *            						OFFSETS						              *
 ******************************************************************************
 */
#define I2C_RCGCI2C_OFFSET						(0x620)
#define I2C_MSA_OFFSET  						(0x000)  
#define I2C_MCS_OFFSET  						(0x004)  
#define I2C_MDR_OFFSET 						    (0x008)  
#define I2C_MTPR_OFFSET 						(0x00C)  
#define I2C_MIMR_OFFSET   						(0x010)  
#define I2C_MRIS_OFFSET  						(0x014)  
#define I2C_MMIS_OFFSET  						(0x018)  
#define I2C_MICR_OFFSET  						(0x01C)  
#define I2C_MCR_OFFSET						    (0x020)  
#define I2C_MCLKOCNT_OFFSET						(0x024)
#define I2C_MBMON_OFFSET						(0x02C)
#define I2C_MCR2_OFFSET						    (0x038)
#define I2C_SOAR_OFFSET						    (0x800)
#define I2C_SCSR_OFFSET						    (0x804)
#define I2C_SDR_OFFSET						    (0x808)
#define I2C_SIMR_OFFSET						    (0x80C)
#define I2C_SRIS_OFFSET						    (0x810)
#define I2C_SMIS_OFFSET						    (0x814)
#define I2C_SICR_OFFSET						    (0x818)
#define I2C_SOAR2_OFFSET						(0x81C)
#define I2C_SACKCTL_OFFSET						(0x820)
#define I2C_PP_OFFSET						    (0xFC0)
#define I2C_PC_OFFSET						    (0xFC4)

/******************************************************************/
#define I2C_MAXIMUM_NUMBER						(4U)	//Number of Maximum I2C peripherals used

/*
 ******************************************************************************
 *            						ADDRESSES					              *
 ******************************************************************************
 */
#define I2C_RCGCI2C   									*((I2C_RegisterAddressType) (SYS_CTRL_BASE_ADDRESS + I2C_RCGCI2C_OFFSET))
#define I2C_MSA(PERIPHERAL_ID)  						*((I2C_RegisterAddressType) (I2C_BASE + (0x1000*(PERIPHERAL_ID)) + I2C_MSA_OFFSET))
#define I2C_MCS(PERIPHERAL_ID) 							*((I2C_RegisterAddressType) (I2C_BASE + (0x1000*(PERIPHERAL_ID)) + I2C_MCS_OFFSET))
#define I2C_MDR(PERIPHERAL_ID)							*((I2C_RegisterAddressType) (I2C_BASE + (0x1000*(PERIPHERAL_ID)) + I2C_MDR_OFFSET))
#define I2C_MTPR(PERIPHERAL_ID) 						*((I2C_RegisterAddressType) (I2C_BASE + (0x1000*(PERIPHERAL_ID)) + I2C_MTPR_OFFSET))
#define I2C_MIMR(PERIPHERAL_ID)   					    *((I2C_RegisterAddressType) (I2C_BASE + (0x1000*(PERIPHERAL_ID)) + I2C_MIMR_OFFSET))
#define I2C_MRIS(PERIPHERAL_ID)  						*((I2C_RegisterAddressType) (I2C_BASE + (0x1000*(PERIPHERAL_ID)) + I2C_MRIS_OFFSET))
#define I2C_MMIS(PERIPHERAL_ID)  						*((I2C_RegisterAddressType) (I2C_BASE + (0x1000*(PERIPHERAL_ID)) + I2C_MMIS_OFFSET))
#define I2C_MICR(PERIPHERAL_ID)  						*((I2C_RegisterAddressType) (I2C_BASE + (0x1000*(PERIPHERAL_ID)) + I2C_MICR_OFFSET))
#define I2C_MCR(PERIPHERAL_ID)							*((I2C_RegisterAddressType) (I2C_BASE + (0x1000*(PERIPHERAL_ID)) + I2C_MCR_OFFSET))
#define I2C_MCLKOCNT(PERIPHERAL_ID)						*((I2C_RegisterAddressType) (I2C_BASE + (0x1000*(PERIPHERAL_ID)) + I2C_MCLKOCNT_OFFSET))
#define I2C_MBMON(PERIPHERAL_ID)						*((I2C_RegisterAddressType) (I2C_BASE + (0x1000*(PERIPHERAL_ID)) + I2C_MBMON_OFFSET))
#define I2C_MCR2(PERIPHERAL_ID)							*((I2C_RegisterAddressType) (I2C_BASE + (0x1000*(PERIPHERAL_ID)) + I2C_MCR2_OFFSET))
#define I2C_SOAR(PERIPHERAL_ID)							*((I2C_RegisterAddressType) (I2C_BASE + (0x1000*(PERIPHERAL_ID)) + I2C_SOAR_OFFSET))
#define I2C_SCSR(PERIPHERAL_ID)							*((I2C_RegisterAddressType) (I2C_BASE + (0x1000*(PERIPHERAL_ID)) + I2C_SCSR_OFFSET))
#define I2C_SDR(PERIPHERAL_ID)							*((I2C_RegisterAddressType) (I2C_BASE + (0x1000*(PERIPHERAL_ID)) + I2C_SDR_OFFSET))
#define I2C_SIMR(PERIPHERAL_ID)							*((I2C_RegisterAddressType) (I2C_BASE + (0x1000*(PERIPHERAL_ID)) + I2C_SIMR_OFFSET))
#define I2C_SRIS(PERIPHERAL_ID)							*((I2C_RegisterAddressType) (I2C_BASE + (0x1000*(PERIPHERAL_ID)) + I2C_SRIS_OFFSET))
#define I2C_SMIS(PERIPHERAL_ID)							*((I2C_RegisterAddressType) (I2C_BASE + (0x1000*(PERIPHERAL_ID)) + I2C_SMIS_OFFSET))
#define I2C_SICR(PERIPHERAL_ID)							*((I2C_RegisterAddressType) (I2C_BASE + (0x1000*(PERIPHERAL_ID)) + I2C_SICR_OFFSET))
#define I2C_SOAR2(PERIPHERAL_ID)						*((I2C_RegisterAddressType) (I2C_BASE + (0x1000*(PERIPHERAL_ID)) + I2C_SOAR2_OFFSET))
#define I2C_SACKCTL(PERIPHERAL_ID)						*((I2C_RegisterAddressType) (I2C_BASE + (0x1000*(PERIPHERAL_ID)) + I2C_SACKCTL_OFFSET))
#define I2C_PP(PERIPHERAL_ID)							*((I2C_RegisterAddressType) (I2C_BASE + (0x1000*(PERIPHERAL_ID)) + I2C_PP_OFFSET))
#define I2C_PC(PERIPHERAL_ID)							*((I2C_RegisterAddressType) (I2C_BASE + (0x1000*(PERIPHERAL_ID)) + I2C_PC_OFFSET))


/*
 *********************************************************************************************
 *  The following are defines for the bit fields in the GPIO_PCTL register for I2C peripheral *
 *********************************************************************************************
 */
#define AF_I2C   3  // I2C PMCx value
/*************************************************************************************
**********	  the bit fields in the I2CMSA register               **********
*************************************************************************************/
#define R_S                 					      	            (0U)

/*************************************************************************************
**********	  the bit fields in the I2CMCS register               **********
*************************************************************************************/
#define CLKTO                    					      			(7U)
#define BUSBSY          								  			(6U)                                         
#define IDLE 										  				(5U)      
#define ARBLST         								  				(4U)                                         
#define DATACK         								  				(3U)                                         
#define ADRACK          								  			(2U)                                       
#define ERROR  														(1U)
#define BUSY														(0U)
#define HS_MCS         								  				(4U)
#define ACK         								  				(3U)
#define STOP          								  				(2U)
#define START  														(1U)
#define RUN															(0U)

/*************************************************************************************
**********	  the bit fields in the I2CMTPR register               **********
*************************************************************************************/
#define HS_MTPR  														(7U)

/*************************************************************************************
**********	  the bit fields in the I2CMIMR register               **********
*************************************************************************************/                                        
#define CLKIM   													(1U)                                         
#define IM  													    (0U)  
  
/*************************************************************************************
**********	  the bit fields in the I2CMRIS register               **********
*************************************************************************************/                                       									
#define CLKRIS														(1U)                                         																							
#define RIS  														(0U)

/*************************************************************************************
**********	  the bit fields in the I2CMMIS register               **********
*************************************************************************************/                                         													
#define CLKMIS       				 								(1U)                                         
#define MIS       				 									(0U)  

/*************************************************************************************
**********	  the bit fields in the I2CMICR register               **********
*************************************************************************************/                                      
#define CLKIC       				 								(1U)
#define IC        													(0U)  

/*************************************************************************************
**********	  the bit fields in the I2CMCR register               **********
*************************************************************************************/                                     
#define GFE           												(6U)   
#define SFE															(5U)
#define MFE															(4U)
#define LPBK														(0U)

/*************************************************************************************
**********	  the bit fields in the I2CMBMON register               **********
*************************************************************************************/
#define SDA															(1U)
#define SCL															(0U)

/*************************************************************************************
**********	  the bit fields in the I2CSCSR register               **********
*************************************************************************************/
#define OAR2SEL															(3U)
#define FBR															    (2U)
#define TREQ															(1U)
#define RREQ															(0U)
#define DA															    (0U)

/*************************************************************************************
**********	  the bit fields in the I2CSIMR register               **********
*************************************************************************************/
#define STOPIM															(2U)
#define STARTIM															(1U)
#define DATAIM															(0U)

/*************************************************************************************
**********	  the bit fields in the I2CSRIS register               **********
*************************************************************************************/
#define STOPRIS															(2U)
#define STARTRIS														(1U)
#define DATARIS															(0U)

/*************************************************************************************
**********	  the bit fields in the I2CSMIS register               **********
*************************************************************************************/
#define STOPMIS															(2U)
#define STARTMIS														(1U)
#define DATAMIS															(0U)

/*************************************************************************************
**********	  the bit fields in the I2CSICR register               **********
*************************************************************************************/
#define STOPIC															(2U)
#define STARTIC														    (1U)
#define DATAIC															(0U)

/*************************************************************************************
**********	  the bit fields in the I2CSOAR2 register               **********
*************************************************************************************/
#define OAR2EN															(7U)

/*************************************************************************************
**********	  the bit fields in the I2CSACKCTL register               **********
*************************************************************************************/
#define ACKOVAL															(1U)
#define ACKOEN															(0U)

/*************************************************************************************
**********	  the bit fields in the I2CPP register               **********
*************************************************************************************/
#define HS_PP															(0U)

/*************************************************************************************
**********	  the bit fields in the I2CPC register               **********
*************************************************************************************/
#define HS_CPC															(0U)

#define RCC_APB1ENR_I2CEN_POS(PERIPHERAL_ID)              (21U+PERIPHERAL_ID-1)   ///////////////////////////////////          

/*
 ******************************************************************************
 *                                                                            *
 *                                                                            *
 *               -enums containing:						              				  *
 *               - I2C_CheckType                                              *
 *               - enums for configuration by the user                        *
 *                                                                            *
 *                                                                            *
 *                                                                            *
 ******************************************************************************
 */

typedef enum 
{
	I2C_NOK=0,
	I2C_OK=1,
	I2C_BUSY
}I2C_CheckType;

typedef enum
{	
	PERIPHERAL_DISABLE=0,
	PERIPHERAL_ENABLE=1
}PeripheralEnable;
	
typedef enum 
{
	STANDARD_MODE=0,
	FAST_MODE=0,
	FAST_MODE_PLUS=0,
	HIGH_SPEED_MODE=1
}SpeedMode;

typedef enum //////////////////////////////////
{
	I2C_MASTER=0,
	I2C_SLAVE=1,
	I2C_Loopback=2
}I2cMode;

/*typedef enum
{
	DISABLE_Loopback=0,
	ENABLE_Loopback=1
}Loopback;*/


typedef enum 
{
	DISABLE_ACK=0,
	ENABLE_ACK=1
}Acknowledge;

typedef enum
{
	PERIPHERAL_CLOCK_4MHz=4,
	PERIPHERAL_CLOCK_6MHz=6,
	PERIPHERAL_CLOCK_12MKHz=12,
	PERIPHERAL_CLOCK_16MHz=16,
	PERIPHERAL_CLOCK_20MHz=20,
	PERIPHERAL_CLOCK_25MHz=25,
	PERIPHERAL_CLOCK_33MHz=33,
	PERIPHERAL_CLOCK_40MHz=40,
	PERIPHERAL_CLOCK_50MHz=50,
	PERIPHERAL_CLOCK_80MHz=80
}PeripheralFrequency;
/*
 ******************************************************************************
 *                                                                            *
 *                                                                            *
 *            				Configuration Structure				              *
 *                                                                            *
 *                                                                            *
 ******************************************************************************
 */
typedef void (*I2C_CallBackFunctionType)(void);

typedef struct
{
	/*used to choose from I2Cx, x=0,1,2,3*/
	uint8_t								I2C_Peripheral_ID;
	/*the device address when configure as a slave */
	uint8_t                             Address_As_Slave;
	/*SCL operating frequency */
	uint32_t							I2C_FrequencyOf_SCL;
	/*I2C operating frequency */
	PeripheralFrequency		            I2C_PeripheralFrequency;

	/**/
	PeripheralEnable			        I2C_PeripheralEnable; /////////////////////////
	/**/
	SpeedMode							I2C_SpeedMode;
	/**/
	I2cMode								I2C_I2cMode;
	/**/
	Acknowledge						    I2C_Acknowledge;
	/**/
	I2C_CallBackFunctionType	        I2C_TransmissionDoneCallBack;

	I2C_CallBackFunctionType	        I2C_ReceptionDoneCallBack;
	
}I2C_ConfigType;

extern const I2C_ConfigType I2C_ConfigParam[I2C_PERIPHERAL_NUMBER];

/*
 ******************************************************************************
 *                                                                            *                                                                            *
 *            				Functions Prototypes				              *
 *                                                                            *                                                                            *
 ******************************************************************************
 */

I2C_CheckType I2C_Init(void);

/*
 ****************************************************************************
 *                                                                          *
 *                          Slave Functions                                 *
 *                                                                          *
 ****************************************************************************
 */

void I2C_Write_OwnSlaveAddress(uint8_t Peripheral_ID,uint8_t OwnSlaveAddress);
void I2C_SlaveDeviceActive(uint8_t Peripheral_ID);
void I2C_Slave_SetData(uint8_t* DataPtr, uint8_t Peripheral_ID);  //Finished
void I2C_Slave_GetData(uint8_t *Data, uint8_t Peripheral_ID);     //Finished
I2C_CheckType I2C_Slave_GetDataStatus(uint8_t Peripheral_ID);     //Finished
I2C_CheckType I2C_Slave_SetDataStatus(uint8_t Peripheral_ID);     //Finished
I2C_CheckType I2C_Slave_StopCheck(uint8_t Peripheral_ID);     //Finished
void I2C__Slave_NOTAcknowledge(uint8_t Peripheral_ID); //Finished
void I2C_Slave_Acknowledge(uint8_t Peripheral_ID);  //Finished
void I2C_Slave_TurnOffAcknowledge(uint8_t Peripheral_ID);  //Finished
void I2C_Slave_InterruptClear(uint8_t Peripheral_ID);      //Finished

/*
 *****************************************************************************
 *                                                                           *                                                                           *
 *            				Call Back Function					             *
 *                                                                           *                                                                            *
 *****************************************************************************
 */

extern uint8_t I2C_InitFlag;

#endif /*end of I2C_DRIVER_H*/


