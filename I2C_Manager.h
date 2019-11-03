#ifndef I2C_MANAGER_H
#define I2C_MANAGER_H

#include "I2C_Driver.h"

typedef enum
{
  I2C_WRITE = 0,
  I2C_READ  = 1
}I2C_Direction;



typedef enum
{
    I2C_UN_INIT                     = 0 ,
    I2C_IDLE                        = 1 ,
    I2C_SetOwnSlaveAddress          = 2 ,
    I2C_SlaveActive                 = 3 ,
    I2C_Slave_Get_Data_Status       = 4 ,
    I2C_Slave_Set_Data_Status       = 5 ,
    I2C_Slave_Get_Data              = 6 ,
    I2C_Slave_Set_Data              = 7 ,
    I2C_Slave_GET_DATA_MANAGER      = 8 ,
    I2C_Slave_Stop_Status           = 9 ,
    I2C_Slave_Stop_Clear            = 10
}I2C_States;


void I2C_Manager(void);
void I2C_Slave_Write(uint8_t Peripheral_ID,uint8_t* DataPointer);
void I2C_Slave_Read( uint8_t Peripheral_ID,uint8_t* DataPointer);
#endif
