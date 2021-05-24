//////////////////////////////////////////////////////////////////////////////////////
// 
// Low level for STM32F1xx & STM32F4xx
// 
// By Rob F. / Entire Group
// 
//////////////////////////////////////////////////////////////////////////////////////

#include "SysType.h"
#include "hdi2c.h"

typedef struct {
  u32       BaudRate;
  s16       Error;      //0-done, 1-start error
}tI2CWorkStruct;


static tI2CWorkStruct hdI2CWork[3] = {
  {.BaudRate = hdI2C_CLOCK_STANDARD, .Error = 0, },
  {.BaudRate = hdI2C_CLOCK_STANDARD, .Error = 0, },
  {.BaudRate = hdI2C_CLOCK_STANDARD, .Error = 0, },
};

// Private defines 
#define I2C_TRANSMITTER_MODE   0
#define I2C_RECEIVER_MODE      1
#define I2C_ACK_ENABLE         1
#define I2C_ACK_DISABLE        0

void hdI2C_Init(I2C_TypeDef* I2Cx, u32 clockSpeed)
{
  I2C_InitTypeDef I2C_InitStruct;
  
  if (I2Cx == I2C1)
  { // Enable clock
     RCC_APB1PeriphClockCmd(RCC_APB1Periph_I2C1, ENABLE);
    // Enable pins
    hdI2C1_INT_InitPins(1);
    if (clockSpeed) hdI2CWork[0].BaudRate = clockSpeed;
    // Set values 
    I2C_InitStruct.I2C_ClockSpeed = hdI2CWork[0].BaudRate;
    I2C_InitStruct.I2C_AcknowledgedAddress = hdI2C1_ACKNOWLEDGED_ADDRESS;
    I2C_InitStruct.I2C_Mode = hdI2C1_MODE;
    I2C_InitStruct.I2C_OwnAddress1 = hdI2C1_OWN_ADDRESS;
    I2C_InitStruct.I2C_Ack = hdI2C1_ACK;
    I2C_InitStruct.I2C_DutyCycle = hdI2C1_DUTY_CYCLE;
#ifdef I2C2
  } else if (I2Cx == I2C2) {
    // Enable clock
    RCC_APB1PeriphClockCmd(RCC_APB1Periph_I2C2, ENABLE);
    // Enable pins
    hdI2C2_INT_InitPins(1);
    if (clockSpeed) hdI2CWork[1].BaudRate = clockSpeed;
    // Set values
    I2C_InitStruct.I2C_ClockSpeed = hdI2CWork[1].BaudRate;
    I2C_InitStruct.I2C_AcknowledgedAddress = hdI2C2_ACKNOWLEDGED_ADDRESS;
    I2C_InitStruct.I2C_Mode = hdI2C2_MODE;
    I2C_InitStruct.I2C_OwnAddress1 = hdI2C2_OWN_ADDRESS;
    I2C_InitStruct.I2C_Ack = hdI2C2_ACK;
    I2C_InitStruct.I2C_DutyCycle = hdI2C2_DUTY_CYCLE;
#endif
#ifdef I2C3
  } else if (I2Cx == I2C3) {
    // Enable clock 
    RCC_APB1PeriphClockCmd(RCC_APB1Periph_I2C3, ENABLE);
    // Enable pins 
    hdI2C3_INT_InitPins(1);
    if (clockSpeed) hdI2CWork[2].BaudRate = clockSpeed;
    // Set values 
    I2C_InitStruct.I2C_ClockSpeed = hdI2CWork[2].BaudRate;
    I2C_InitStruct.I2C_AcknowledgedAddress = hdI2C3_ACKNOWLEDGED_ADDRESS;
    I2C_InitStruct.I2C_Mode = hdI2C3_MODE;
    I2C_InitStruct.I2C_OwnAddress1 = hdI2C3_OWN_ADDRESS;
    I2C_InitStruct.I2C_Ack = hdI2C3_ACK;
    I2C_InitStruct.I2C_DutyCycle = hdI2C3_DUTY_CYCLE;
#endif
  } else return;
  // Disable I2C first 
  I2C_Cmd(I2Cx, DISABLE); //I2Cx->CR1 &= ~I2C_CR1_PE;
  // Initialize I2C 
  I2C_Init(I2Cx, &I2C_InitStruct);
  // Enable I2C 
  I2C_Cmd(I2Cx, ENABLE); //I2Cx->CR1 |= I2C_CR1_PE;
}

u8 hdI2C_Read(I2C_TypeDef* I2Cx, u8 address, u8 reg)
{
  u8 received_data = 0;
  if ( hdI2C_Start(I2Cx, address, I2C_TRANSMITTER_MODE, I2C_ACK_DISABLE) == 0)
  {
    hdI2C_WriteData(I2Cx, reg);
    hdI2C_Stop(I2Cx);
    hdI2C_Start(I2Cx, address, I2C_RECEIVER_MODE, I2C_ACK_DISABLE);
    received_data = hdI2C_ReadNack(I2Cx);
  }
  return received_data;
}

void hdI2C_ReadMulti(I2C_TypeDef* I2Cx, u8 address, u8 reg, u8* data, u16 count)
{
  if ( hdI2C_Start(I2Cx, address, I2C_TRANSMITTER_MODE, I2C_ACK_ENABLE) == 0 )
  {
    hdI2C_WriteData(I2Cx, reg);
    //hdI2C_Stop(I2Cx);
    hdI2C_Start(I2Cx, address, I2C_RECEIVER_MODE, I2C_ACK_ENABLE);
    while (count--)
    {
      if (!count)
      {
        // Last byte 
        *data = hdI2C_ReadNack(I2Cx);
      } else {
        *data = hdI2C_ReadAck(I2Cx);
      }
      data++;
    }
  }
}

u8 hdI2C_ReadNoRegister(I2C_TypeDef* I2Cx, u8 address)
{
  u8 data = 0;
  if ( hdI2C_Start(I2Cx, address, I2C_RECEIVER_MODE, I2C_ACK_ENABLE) == 0)
  {
    // Also stop condition happens 
    data = hdI2C_ReadNack(I2Cx);
  }
  return data;
}

s16 hdI2C_ReadMultiNoRegister(I2C_TypeDef* I2Cx, u8 address, u8* data, u16 count)
{
  s16 res = 0;
  if ( (res=hdI2C_Start(I2Cx, address, I2C_RECEIVER_MODE, I2C_ACK_ENABLE)) == 0)
  {
    while (count--)
    {
      if (!count)
      {
        // Last byte 
        *data = hdI2C_ReadNack(I2Cx);
      } else {
        *data = hdI2C_ReadAck(I2Cx);
      }
      data++;
    }
  }
  return res;
}

s16 hdI2C_Write(I2C_TypeDef* I2Cx, u8 address, u8 reg, u8 data)
{
  s16 res = 0;
  if ( (res=hdI2C_Start(I2Cx, address, I2C_TRANSMITTER_MODE, I2C_ACK_DISABLE)) == 0)
  {
    hdI2C_WriteData(I2Cx, reg);
    hdI2C_WriteData(I2Cx, data);
    hdI2C_Stop(I2Cx);
  }
  return res;
}

s16 hdI2C_WriteMulti(I2C_TypeDef* I2Cx, u8 address, u8 reg, u8* data, u16 count)
{
  s16 res = 0;
  if ( (res=hdI2C_Start(I2Cx, address, I2C_TRANSMITTER_MODE, I2C_ACK_DISABLE)) == 0 )
  {
    hdI2C_WriteData(I2Cx, reg);
    while (count--)
    {
      hdI2C_WriteData(I2Cx, *data++);
    }
    hdI2C_Stop(I2Cx);
  }
  return res;
}

s16 hdI2C_WriteNoRegister(I2C_TypeDef* I2Cx, u8 address, u8 data)
{
  s16 res = 0;
  if ( (res=hdI2C_Start(I2Cx, address, I2C_TRANSMITTER_MODE, I2C_ACK_DISABLE)) == 0 )
  {
    hdI2C_WriteData(I2Cx, data);
    hdI2C_Stop(I2Cx);
  }
  return res;
}

s16 hdI2C_WriteMultiNoRegister(I2C_TypeDef* I2Cx, u8 address, u8* data, u16 count)
{
  s16 res = 0;
  if ( (res=hdI2C_Start(I2Cx, address, I2C_TRANSMITTER_MODE, I2C_ACK_DISABLE)) == 0 )
  {
    while (count--)
    {
      hdI2C_WriteData(I2Cx, *data++);
    }
    hdI2C_Stop(I2Cx);
  }
  return res;
}

void hdI2C_ErrorUpdate(I2C_TypeDef* I2Cx, s16 err)
{
  if (I2Cx == I2C1)
  {
    hdI2CWork[0].Error = err;
#ifdef I2C2
  } else if (I2Cx == I2C2) {
    hdI2CWork[1].Error = err;
#endif    
#ifdef I2C3
  } else if (I2Cx == I2C3) {
    hdI2CWork[2].Error = err;
#endif    
  }
}

s16 hdI2C_ErrorLast(I2C_TypeDef* I2Cx)
{
  s16 res = -1;
  if (I2Cx == I2C1)
  {
    res = hdI2CWork[0].Error;
#ifdef I2C2
  } else if (I2Cx == I2C2) {
    res = hdI2CWork[1].Error;
#endif    
#ifdef I2C3
  } else if (I2Cx == I2C3) {
    res = hdI2CWork[2].Error;
#endif    
  }
  return res;
}


u8 hdI2C_DoError(I2C_TypeDef* I2Cx)
{
    I2C_SoftwareResetCmd(I2Cx, ENABLE); //I2Cx->CR1 |= I2C_CR1_SWRST;
     I2C_Cmd(I2Cx, DISABLE); //I2Cx->CR1 &=~I2C_CR1_PE;
     I2C_GenerateSTOP(I2Cx, ENABLE); //I2Cx->CR1 |= I2C_CR1_STOP;
    I2C_SoftwareResetCmd(I2Cx, DISABLE); //I2Cx->CR1 &=~I2C_CR1_SWRST;
    hdI2C_Init(I2Cx, 0);
    hdI2C_ErrorUpdate(I2Cx, 1);
    return 1;
}

u8 hdI2C_IsDeviceConnected(I2C_TypeDef* I2Cx, u8 address, u8 isMethodRead)
{
  u8 connected = 0;
  if (!isMethodRead)
  {
    // Try to start, function will return 0 in case device will send ACK 
    if ( hdI2C_Start(I2Cx, address, I2C_TRANSMITTER_MODE, I2C_ACK_ENABLE) == 0)
    {
      connected = 1;
      hdI2C_DoError(I2Cx); //hdI2C_Stop(I2Cx);
    }
  } else {
    if ( hdI2C_Start(I2Cx, address, I2C_RECEIVER_MODE, I2C_ACK_ENABLE) == 0 )
    {
      connected = 1;
      hdI2C_ReadNack(I2Cx);//hdI2C_Stop(I2Cx);
    }
  }
  return connected;
}

//////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////
// Private functions 
s16 hdI2C_Start(I2C_TypeDef* I2Cx, u8 address, u8 direction, u8 ack)
{
  static vu32 hdI2C_Timeout;
  hdI2C_ErrorUpdate(I2Cx, 0);
  // Generate I2C start pulse 
  I2C_GenerateSTART(I2Cx, ENABLE);
  // Wait till I2C is busy 
  hdI2C_Timeout = hdI2C_TIMEOUT;
  while(!(I2C_GetLastEvent(I2Cx) & I2C_FLAG_SB))
  {
    if (--hdI2C_Timeout == 0x00)
    {
      return hdI2C_DoError(I2Cx);
    }
  }
  // Enable ack if we select it 
  if (ack)
  {
    I2C_AcknowledgeConfig(I2Cx, ENABLE);
  }
  // Send write/read bit 
  if (direction == I2C_TRANSMITTER_MODE)
  {
    // Send address with zero last bit 
    I2C_Send7bitAddress(I2Cx, address, I2C_Direction_Transmitter);
    // Wait till finished 
    hdI2C_Timeout = hdI2C_TIMEOUT;
    while(!(I2C_GetLastEvent(I2Cx) & I2C_FLAG_ADDR))
    {
      if (--hdI2C_Timeout == 0x00)
      {
        return hdI2C_DoError(I2Cx);
      }
    }
  }
  if (direction == I2C_RECEIVER_MODE)
  {
    // Send address with 1 last bit 
    I2C_Send7bitAddress(I2Cx, address, I2C_Direction_Receiver);
    // Wait till finished 
    hdI2C_Timeout = hdI2C_TIMEOUT;
    while (!I2C_CheckEvent(I2Cx, I2C_EVENT_MASTER_RECEIVER_MODE_SELECTED))
    {
      if (--hdI2C_Timeout == 0x00)
      {
        return hdI2C_DoError(I2Cx);
      }
    }
  }
  // Read status register to clear ADDR flag 
  I2C_GetFlagStatus(I2Cx, I2C_FLAG_ADDR);
  I2Cx->SR2; //((void)(I2Cx->SR2));
  // Return 0, everything ok 
  return 0;
}

void hdI2C_WriteData(I2C_TypeDef* I2Cx, u8 data)
{
  vu32 hdI2C_Timeout;
  // Wait till I2C is not busy anymore 
  hdI2C_Timeout = hdI2C_TIMEOUT;
  while(!(I2C_GetLastEvent(I2Cx) & I2C_FLAG_TXE) && hdI2C_Timeout)
  {
    hdI2C_Timeout--;
  }
  // Send I2C data 
  I2C_SendData(I2Cx, data);
}

u8 hdI2C_ReadAck(I2C_TypeDef* I2Cx)
{
  vu32 hdI2C_Timeout;
  u8 data;
  // Enable ACK 
  I2C_AcknowledgeConfig(I2Cx, ENABLE);
  // Wait till not received 
  hdI2C_Timeout = hdI2C_TIMEOUT;
  while (!I2C_CheckEvent(I2Cx, I2C_EVENT_MASTER_BYTE_RECEIVED))
  {
    if (--hdI2C_Timeout == 0x00)
    {
      return hdI2C_DoError(I2Cx);
    }
  }
  // Read data 
  data = I2C_ReceiveData(I2Cx);
  // Return data 
  return data;
}

u8 hdI2C_ReadNack(I2C_TypeDef* I2Cx)
{
  vu32 hdI2C_Timeout;
  u8 data;
  // Disable ACK 
  I2C_AcknowledgeConfig(I2Cx, DISABLE);
  // Generate stop 
  I2C_GenerateSTOP(I2Cx, ENABLE);
  // Wait till received 
  hdI2C_Timeout = hdI2C_TIMEOUT;
  while (!I2C_CheckEvent(I2Cx, I2C_EVENT_MASTER_BYTE_RECEIVED))
  {
    if (--hdI2C_Timeout == 0x00)
    {
      return hdI2C_DoError(I2Cx);
    }
  }
  // Read data 
  data = I2C_ReceiveData(I2Cx);
  // Return data 
  return data;
}

u8 hdI2C_Stop(I2C_TypeDef* I2Cx)
{
  vu32 hdI2C_Timeout;
  // Wait till transmitter not empty 
  hdI2C_Timeout = hdI2C_TIMEOUT;
  while(!(I2C_GetLastEvent(I2Cx) & I2C_FLAG_TXE) || (!(I2C_GetLastEvent(I2Cx) & I2C_FLAG_BTF)))
  {
    if (--hdI2C_Timeout == 0x00)
    {
      return hdI2C_DoError(I2Cx);
    }
  }
  // Generate stop 
  I2C_GenerateSTOP(I2Cx, ENABLE);
  // Return 0, everything ok 
  return 0;
}
