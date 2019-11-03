#include "I2C_Manager.h"

/**
 * main.c
 */
static uint8_t TransmissionDone = 0;
static uint8_t ReceptionDone = 0;

void I2C_TxDone(void)
{
    TransmissionDone = 1;
}
void I2C_RxDone(void)
{
    ReceptionDone = 1;
}

int main(void)
{
    uint8_t ReceivedData=0;
    uint8_t x = 0;

    GPIO_Init();
    I2C_Init();
    while(1)
       {
        I2C_Manager();
        switch(x)
              {
                  case 0:
                  {
                    I2C_Slave_Read(0,&ReceivedData);
                    x=1;
                  }
                  break;
                  case 1:
                  {
                      if(ReceptionDone == 1)
                      {
                          ReceptionDone = 0;
                          x =2;
                      }
                      else
                      {
                          x = 1;
                      }
                  }
                  break;
                  case 2:
                  {
                    if(ReceivedData==1)
                     {
                         GPIO_Write(3,0x00);
                         GPIO_Write(4,0xFF);
                         GPIO_Write(2,0x00);
                         x=255;
                     }
                     else if(ReceivedData==0)
                     {
                         GPIO_Write(4,0x00);
                         GPIO_Write(3,0xFF);
                         GPIO_Write(2,0x00);
                         x=200;
                     }
                     else
                     {
                         GPIO_Write(3,0x00);
                         GPIO_Write(4,0x00);
                         GPIO_Write(2,0xFF);
                         x=100;
                     }
                  }
                  break;
                  default: break;
              }

       }
    return 0;
}
