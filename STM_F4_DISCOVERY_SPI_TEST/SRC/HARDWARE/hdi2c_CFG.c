//////////////////////////////////////////////////////////////////////////////////////
// 
// Low level for STM32F4xx
// 
// By Rob F. / Entire Group
// 
//////////////////////////////////////////////////////////////////////////////////////

#include "SysType.h"
#include "hdi2c_CFG.h"


void hdI2C1_INT_InitPins(u8 isON)
{
      static u8 isInited=0;
      if (isON)
      {
        if (!isInited)
        {
          GpioInAM_I2C1_SCL(hd_gptp_AF_PP, GPIO_AF_I2C1);
          GpioInAM_I2C1_SDA(hd_gptp_AF_OD, GPIO_AF_I2C1);
          GpioInit_TINT();
          GpioInit_TRST();
          isInited = 1;
        }
      } else {
        GpioIniM_I2C1_SCL(hd_gptp_OUT_PP);
        GpioIniM_I2C1_SDA(hd_gptp_OUT_PP);
        isInited = 0;
      }
}

void hdI2C2_INT_InitPins(u8 isON)
{
      static u8 isInited=0;
      if (isON)
      {
        if (!isInited)
        {
          isInited = 1;
        }
      } else {
        isInited = 0;
      }
}

void hdI2C3_INT_InitPins(u8 isON)
{
      static u8 isInited=0;
      if (isON)
      {
        if (!isInited)
        {
          isInited = 1;
        }
      } else {
        isInited = 0;
      }
}
