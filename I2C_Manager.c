#include "I2C_Manager.h"

static uint8_t I2C_Write;
static uint8_t I2C_Read;
static uint8_t I2C_SlaveAddress;
//static uint8_t I2C_ByteCount;
static uint8_t* I2C_DataPointer;
static uint8_t I2C_Peripheral_ID;


void I2C_Slave_Write(uint8_t Peripheral_ID,uint8_t* DataPointer)
{
      I2C_Write = 1;
      I2C_Peripheral_ID =Peripheral_ID;
      I2C_DataPointer = DataPointer;

}

void I2C_Slave_Read( uint8_t Peripheral_ID,uint8_t* DataPointer)
{
       I2C_Read = 1;
       I2C_Peripheral_ID =Peripheral_ID;
       I2C_DataPointer = DataPointer;

}

void I2C_Manager(void)
{
    I2C_CheckType DriverReturnStatus = I2C_NOK;
    static I2C_States ManagerState = I2C_UN_INIT;
    static I2C_States OldState = I2C_UN_INIT;
    const I2C_ConfigType* ConfigPtr = &I2C_ConfigParam[0];
    
    switch(ManagerState)
    {
        case I2C_UN_INIT:
        {
            if(I2C_InitFlag == 1)
            {
                ManagerState = I2C_IDLE;
            }
            else
            {
                ManagerState = I2C_UN_INIT;
            }
        }
        break;

        case I2C_IDLE:
        {
                 if(I2C_Write == 1)
                  {
                         ManagerState = I2C_SetOwnSlaveAddress;
                  }
                 else if(I2C_Read == 1)
                 {
                         ManagerState = I2C_SetOwnSlaveAddress;
                 }
                 else
                 {
                        ManagerState = I2C_IDLE;
                 }

        }
        break;
        case I2C_SetOwnSlaveAddress:
        {
            I2C_Write_OwnSlaveAddress(I2C_Peripheral_ID,ConfigPtr->Address_As_Slave);
            ManagerState = I2C_SlaveActive;
        }
        break;
        case I2C_SlaveActive:
        {
            I2C_SlaveDeviceActive(I2C_Peripheral_ID);
            ManagerState =I2C_Slave_Get_Data_Status ;
        }
        break;
        case I2C_Slave_Get_Data_Status:
                {
                    DriverReturnStatus = I2C_Slave_GetDataStatus(I2C_Peripheral_ID);

                                if(DriverReturnStatus == I2C_OK)
                                {
                                    if(I2C_Read == 1)
                                    {
                                    ManagerState = I2C_Slave_Get_Data;
                                    }

                                    else if(I2C_Write == 1)
                                    {
                                        ManagerState = I2C_Slave_Set_Data_Status;
                                    }
                                    else
                                    {/*MISRA*/};
                                }
                                else
                                {
                                     ManagerState = I2C_Slave_Get_Data_Status;
                                }
                }
                break;
        case I2C_Slave_Set_Data_Status:
                {
                    DriverReturnStatus = I2C_Slave_SetDataStatus(I2C_Peripheral_ID);

                                if(DriverReturnStatus == I2C_OK)
                                {

                                    ManagerState = I2C_Slave_Set_Data;
                                }
                                else
                                {
                                    ManagerState = I2C_Slave_Get_Data_Status;
                                }
                }
                break;
        case I2C_Slave_Get_Data:
                {
                    I2C_Slave_GetData(I2C_DataPointer,(I2C_Peripheral_ID));
                    ManagerState = I2C_Slave_Stop_Status;
                }
                break;
        case I2C_Slave_Set_Data:
                {
                    I2C_Slave_SetData(I2C_DataPointer,(I2C_Peripheral_ID));
                    ManagerState = I2C_Slave_Stop_Status;
                }
                break;
        case I2C_Slave_Stop_Status:
                        {
                            DriverReturnStatus = I2C_Slave_StopCheck(I2C_Peripheral_ID);

                                        if(DriverReturnStatus == I2C_OK)
                                        {

                                            ManagerState = I2C_Slave_Stop_Clear;
                                        }
                                        else
                                        {
                                            ManagerState = I2C_Slave_Get_Data_Status;
                                        }
                        }
                        break;
        case I2C_Slave_Stop_Clear:
                         {
                             if(I2C_Read == 1)
                               {

                                 I2C_Slave_InterruptClear(I2C_Peripheral_ID);
                                  ManagerState = I2C_IDLE;
                                  I2C_Read=0;
                                  I2C_DataPointer = 0;
                                  (*(ConfigPtr->I2C_ReceptionDoneCallBack))();

                               }

                             else if(I2C_Write == 1)
                               {
                                 I2C_Slave_InterruptClear(I2C_Peripheral_ID);
                                 ManagerState = I2C_IDLE;
                                 I2C_Write=0;
                                 I2C_DataPointer = 0;
                                 (*(ConfigPtr->I2C_TransmissionDoneCallBack))();
                               }
                             else
                             {/*MISRA*/};

                         }
                         break;
    }
}


