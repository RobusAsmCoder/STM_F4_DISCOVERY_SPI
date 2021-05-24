//////////////////////////////////////////////////////////////////////////////////////
// By Rob F. / Entire Group
//////////////////////////////////////////////////////////////////////////////////////

#ifndef __HDI2C_H
#define __HDI2C_H


#include "SysType.h"
#include "hdi2c_CFG.h"

extern void hdI2C_Init(I2C_TypeDef* I2Cx, u32 clockSpeed);
extern u8 hdI2C_Read(I2C_TypeDef* I2Cx, u8 address, u8 reg);
extern void hdI2C_ReadMulti(I2C_TypeDef* I2Cx, u8 address, u8 reg, u8* data, u16 count);
extern u8 hdI2C_ReadNoRegister(I2C_TypeDef* I2Cx, u8 address);
extern s16 hdI2C_ReadMultiNoRegister(I2C_TypeDef* I2Cx, u8 address, u8* data, u16 count);
extern s16 hdI2C_Write(I2C_TypeDef* I2Cx, u8 address, u8 reg, u8 data);
extern s16 hdI2C_WriteMulti(I2C_TypeDef* I2Cx, u8 address, u8 reg, u8* data, u16 count);
extern s16 hdI2C_WriteNoRegister(I2C_TypeDef* I2Cx, u8 address, u8 data);
extern s16 hdI2C_WriteMultiNoRegister(I2C_TypeDef* I2Cx, u8 address, u8* data, u16 count);
extern u8 hdI2C_IsDeviceConnected(I2C_TypeDef* I2Cx, u8 address, u8 isMethodRead);
extern s16 hdI2C_ErrorLast(I2C_TypeDef* I2Cx);

extern s16 hdI2C_Start(I2C_TypeDef* I2Cx, u8 address, u8 direction, u8 ack);
extern void hdI2C_WriteData(I2C_TypeDef* I2Cx, u8 data);
extern u8 hdI2C_ReadAck(I2C_TypeDef* I2Cx);
extern u8 hdI2C_ReadNack(I2C_TypeDef* I2Cx);
extern u8 hdI2C_Stop(I2C_TypeDef* I2Cx);

#endif
