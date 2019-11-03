/*
 ********************************************************************************************
 *                                                                                          *
 *        Authors: Esraa Ahmed & Mohamed Rostom                                             *
 *        Date: 11/6/2018                                                                   *
 *        Microcontroller: TM4C123GH6PM                                                     *
 *                                                                                          *
 *        Description: This file contains the implementations of initialization of          *
 *                     I2C peripheral for single master and single slave and the            *
 *                     helper functions. This code is designed for single byte write        *
 *                     or single byte read.                                                 *
 *            												                                *
 *                                                                                          *
 *                                                                                          *
 ********************************************************************************************
 */
#include "I2C_Driver.h"
 //#include "delay.h"

/*
 ********************************************************************************************
 *                                                                                          *
 *     This Function is used to initilaize the I2C peripherals                              *
 *      - It sets the clock gating for the I2C peripherals                                  *
 *      - It checks for valid I2C peripheral clock speed                                    *
 *      - It sets the GPIO Alternating function                                             *
 *      - It initializes proper registers if user asked for interrupts                      *
 *      - It returns I2C_OK for for successful initialization, and I2C_NOK for failure      *
 *                                                                                          *
 ********************************************************************************************
 */

uint8_t I2C_InitFlag = 0;

I2C_CheckType I2C_Init(void)
{
    I2C_CheckType RetVal;
    const I2C_ConfigType* I2C_ConfigPtr;

    uint8_t LoopIndex;
    for(LoopIndex = 0; LoopIndex < I2C_PERIPHERAL_NUMBER; LoopIndex++)
    {
        I2C_ConfigPtr = &I2C_ConfigParam[LoopIndex];
            
            /*Checking for a valid configuration*/
            if(       (I2C_ConfigPtr->I2C_Peripheral_ID<I2C_MAXIMUM_NUMBER)                                       &&
                      (I2C_ConfigPtr->I2C_PeripheralFrequency>=PERIPHERAL_CLOCK_4MHz)                          &&
                      (I2C_ConfigPtr->I2C_PeripheralFrequency<=PERIPHERAL_CLOCK_80MHz)                         &&
                      ((I2C_ConfigPtr->I2C_FrequencyOf_SCL<=MAX_SCL_FREQUENCY_SM && !I2C_ConfigPtr->I2C_SpeedMode)    ||
                      (I2C_ConfigPtr->I2C_FrequencyOf_SCL<=MAX_SCL_FREQUENCY_FM && !I2C_ConfigPtr->I2C_SpeedMode)     ||
                      (I2C_ConfigPtr->I2C_FrequencyOf_SCL<=MAX_SCL_FREQUENCY_FMP && !I2C_ConfigPtr->I2C_SpeedMode)    ||
                      (I2C_ConfigPtr->I2C_FrequencyOf_SCL<=MAX_SCL_FREQUENCY_HSM && I2C_ConfigPtr->I2C_SpeedMode))
                    )
                    {
                            

                            I2C_RCGCI2C  |= (((uint32_t)1)<<(I2C_ConfigPtr->I2C_Peripheral_ID));

                            //I2C_CR1(ConfigPtr->I2C_Peripheral_ID)  &=~ (((uint16_t)ConfigPtr->I2C_PeripheralEnable)<<I2C_CR1_PE_POS);

                            GPIO_SetAlternFuntion(LoopIndex*2,AF_I2C);
                            GPIO_SetAlternFuntion(LoopIndex*2+1,AF_I2C);


                            /*SET PERIPHERAL FREQUENCY*/
                            /*I2C_CR2(ConfigPtr->I2C_Peripheral_ID)        |= ((uint16_t)ConfigPtr->I2C_PeripheralFrequency); *///////////////////////

                            /*Set the mode of I2C*/
                            switch(I2C_ConfigPtr->I2C_I2cMode)
                                {
                                    case I2C_MASTER:
                                    {
                                        I2C_MCR(I2C_ConfigPtr->I2C_Peripheral_ID) |=(1<<MFE);
                                    }
                                    break;
                                    case I2C_SLAVE:
                                     {

                                         I2C_MCR(I2C_ConfigPtr->I2C_Peripheral_ID) |=(1<<SFE);
                                         /*I2C_SOAR(ConfigPtr->I2C_Peripheral_ID) |= (ConfigPtr->Address_As_Slave);
                                         I2C_SCSR(ConfigPtr->I2C_Peripheral_ID) |=(1<<DA);*/
                                     }
                                     break;
                                    case I2C_Loopback:
                                        {
                                           I2C_MCR(I2C_ConfigPtr->I2C_Peripheral_ID) |=(1<<MFE);
                                           I2C_MCR(I2C_ConfigPtr->I2C_Peripheral_ID) |=(1<<SFE);
                                           //I2C_SCSR(ConfigPtr->I2C_Peripheral_ID) |=(1<<DA);
                                           I2C_MCR(I2C_ConfigPtr->I2C_Peripheral_ID) |=(1<<LPBK);

                                        }
                                      break;
                                    default: break;
                                }



                            /*SET SPEED MODE */
                            I2C_MCS(I2C_ConfigPtr->I2C_Peripheral_ID)         |= ((I2C_ConfigPtr->I2C_SpeedMode)<< HS_MCS);
                            I2C_MTPR(I2C_ConfigPtr->I2C_Peripheral_ID)        |= ((I2C_ConfigPtr->I2C_SpeedMode)<< HS_MTPR);
                            I2C_PC(I2C_ConfigPtr->I2C_Peripheral_ID)          |= ((I2C_ConfigPtr->I2C_SpeedMode)<< HS_CPC);
                            /*SET VALUE OF TPR IN I2CMTPR REGISTER*/
                            /* TPR  = System Clock / (( 2 * (SCL_LP + SCL_HP) * SCL_CLK ) - 1)*/
                            I2C_MTPR(I2C_ConfigPtr->I2C_Peripheral_ID)        |= ((((I2C_ConfigPtr->I2C_PeripheralFrequency)*1000000)/(2*(6+4)*(I2C_ConfigPtr->I2C_FrequencyOf_SCL)))-1);

                            /*Enable/Disable Acknowledge*/
                            I2C_MCS(I2C_ConfigPtr->I2C_Peripheral_ID)          = ((I2C_ConfigPtr->I2C_Acknowledge)<<((1<<ACK)|(1<<RUN)));

                            #if(I2C_USE_INT_TO_HANDLE==1)
                                    I2C_MIMR(ConfigPtr->I2C_Peripheral_ID) |= 1<<IM;
                                    I2C_SIMR(ConfigPtr->I2C_Peripheral_ID) |= 1<<STOPIM;
                                    I2C_SIMR(ConfigPtr->I2C_Peripheral_ID) |= 1<<STARTIM;
                                    I2C_SIMR(ConfigPtr->I2C_Peripheral_ID) |= 1<<DATAIM;
                            #endif
                            RetVal = I2C_OK;
                            I2C_InitFlag = 1;
                    }
                    else
                    {
                            RetVal = I2C_NOK;
                            I2C_InitFlag = 0;
                    }
    }
    return RetVal;
}


void I2C_Write_OwnSlaveAddress(uint8_t Peripheral_ID,uint8_t OwnSlaveAddress)
    {
    const I2C_ConfigType* ConfigPtr = &I2C_ConfigParam[Peripheral_ID];
        uint8_t I2C_Peripheral_ID;
                   I2C_Peripheral_ID = Peripheral_ID ;
        /* set device address when configure as slave */
        I2C_SOAR(I2C_Peripheral_ID) |= (ConfigPtr->Address_As_Slave);
    }

void I2C_SlaveDeviceActive(uint8_t Peripheral_ID)
    {

        uint8_t I2C_Peripheral_ID;
                   I2C_Peripheral_ID = Peripheral_ID ;
        I2C_SCSR(I2C_Peripheral_ID) &= ~(1<<DA);
        I2C_SCSR(I2C_Peripheral_ID) |=(1<<DA);

    }

void I2C_Slave_SetData(uint8_t* DataPtr, uint8_t Peripheral_ID)  //Finished
    {

        uint8_t I2C_Peripheral_ID;
                   I2C_Peripheral_ID = Peripheral_ID ;
        /*Put data in the data register*/
        I2C_SDR(I2C_Peripheral_ID) = (*DataPtr);
    }
void I2C_Slave_GetData(uint8_t *Data, uint8_t Peripheral_ID)  //Finished
{

    uint8_t I2C_Peripheral_ID;
               I2C_Peripheral_ID = Peripheral_ID ;
    *Data = I2C_SDR(I2C_Peripheral_ID);
}

I2C_CheckType I2C_Slave_GetDataStatus(uint8_t Peripheral_ID) //Finished
{
    I2C_CheckType RetVal;
    uint8_t I2C_Peripheral_ID;
               I2C_Peripheral_ID = Peripheral_ID ;

    if( (I2C_SCSR(I2C_Peripheral_ID) & (1<<RREQ))== (1<<RREQ))
    {
        RetVal = I2C_OK;
    }
    else
    {
        RetVal = I2C_NOK;
    }
    return RetVal;
}

I2C_CheckType I2C_Slave_SetDataStatus(uint8_t Peripheral_ID)
{
    I2C_CheckType RetVal;

    uint8_t I2C_Peripheral_ID;
               I2C_Peripheral_ID = Peripheral_ID ;

    if( (I2C_SCSR(I2C_Peripheral_ID) & (1<<TREQ))== (1<<TREQ))
        {
            RetVal = I2C_OK;
        }
        else
        {
            RetVal = I2C_NOK;
        }
        return RetVal;
}
I2C_CheckType I2C_Slave_StopCheck(uint8_t Peripheral_ID)
{
    I2C_CheckType RetVal;
      //const I2C_ConfigType* ConfigPtr = &I2C_ConfigParam[Peripheral_ID];
      uint8_t I2C_Peripheral_ID;
              I2C_Peripheral_ID = Peripheral_ID ;

      if( (I2C_SRIS(I2C_Peripheral_ID) & (1<<STOPRIS))== (1<<STOPRIS))
          {
              RetVal = I2C_OK;
          }
          else
          {
              RetVal = I2C_NOK;
          }
          return RetVal;
}
void I2C_Slave_InterruptClear(uint8_t Peripheral_ID)
{

  //  const I2C_ConfigType* ConfigPtr = &I2C_ConfigParam[Peripheral_ID];
    uint8_t I2C_Peripheral_ID;
    I2C_Peripheral_ID = Peripheral_ID ;

    I2C_SICR(I2C_Peripheral_ID) |=(1<<STOPIC);
    I2C_SICR(I2C_Peripheral_ID) |=(1<<STARTIC);
    I2C_SICR(I2C_Peripheral_ID) |=(1<<DATAIC);
}

void I2C__Slave_NOTAcknowledge(uint8_t Peripheral_ID)
{

     // const I2C_ConfigType* ConfigPtr = &I2C_ConfigParam[Peripheral_ID];
      uint8_t I2C_Peripheral_ID;
              I2C_Peripheral_ID = Peripheral_ID ;
    I2C_SACKCTL(I2C_Peripheral_ID) |=(1<<ACKOVAL);
    I2C_SACKCTL(I2C_Peripheral_ID) |=(1<<ACKOEN);
}
void I2C_Slave_Acknowledge(uint8_t Peripheral_ID)
{

      //const I2C_ConfigType* ConfigPtr = &I2C_ConfigParam[Peripheral_ID];
      uint8_t I2C_Peripheral_ID;
              I2C_Peripheral_ID = Peripheral_ID ;
    I2C_SACKCTL(I2C_Peripheral_ID) &= ~(1<<ACKOVAL);
    I2C_SACKCTL(I2C_Peripheral_ID) |=(1<<ACKOEN);
}
void I2C_Slave_TurnOffAcknowledge(uint8_t Peripheral_ID)
{

     // const I2C_ConfigType* ConfigPtr = &I2C_ConfigParam[Peripheral_ID];
      uint8_t I2C_Peripheral_ID;
              I2C_Peripheral_ID = Peripheral_ID ;
              I2C_SACKCTL(I2C_Peripheral_ID) &= ~(1<<ACKOEN);
}
