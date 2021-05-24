//////////////////////////////////////////////////////////////////////////////////////
// By Rob F. / Entire Group
//////////////////////////////////////////////////////////////////////////////////////

#ifndef __HDI2C_CFG_H
#define __HDI2C_CFG_H


#include "SysType.h"
#include "hardware.h"


//Timeout for I2C
#define hdI2C_TIMEOUT                     2000

// I2C1 settings, change them in defines.h project file 
#define hdI2C1_ACKNOWLEDGED_ADDRESS       I2C_AcknowledgedAddress_7bit
#define hdI2C1_MODE                       I2C_Mode_I2C
#define hdI2C1_OWN_ADDRESS                0x00
#define hdI2C1_ACK                        I2C_Ack_Disable
#define hdI2C1_DUTY_CYCLE                 I2C_DutyCycle_2

// I2C2 settings, change them in defines.h project file 
#define hdI2C2_ACKNOWLEDGED_ADDRESS       I2C_AcknowledgedAddress_7bit
#define hdI2C2_MODE                       I2C_Mode_I2C
#define hdI2C2_OWN_ADDRESS                0x00
#define hdI2C2_ACK                        I2C_Ack_Disable
#define hdI2C2_DUTY_CYCLE                 I2C_DutyCycle_2

// I2C3 settings, change them in defines.h project file 
#define hdI2C3_ACKNOWLEDGED_ADDRESS       I2C_AcknowledgedAddress_7bit
#define hdI2C3_MODE                       I2C_Mode_I2C
#define hdI2C3_OWN_ADDRESS                0x00
#define hdI2C3_ACK                        I2C_Ack_Disable
#define hdI2C3_DUTY_CYCLE                 I2C_DutyCycle_2

#define hdI2C_CLOCK_STANDARD              100000  //!< I2C Standard speed 
#define hdI2C_CLOCK_FAST_MODE             400000  //!< I2C Fast mode speed 
#define hdI2C_CLOCK_FAST_MODE_PLUS        1000000 //!< I2C Fast mode plus speed 
#define hdI2C_CLOCK_HIGH_SPEED            1500000 //3400000 //!< I2C High speed 


hdPin_O_DefineSetup(I2C1_SCL,       B,  8, hd_gptp_AF_PP,      0);     //hd_gptp_AF_PPU
hdPin_O_DefineSetup(I2C1_SDA,       B,  9, hd_gptp_AF_PP,      0);      //hd_gptp_AF_OD
hdPin_O_DefineSetup(TINT,           E,  5, hd_gptp_IN_PPD,     1);
hdPin_O_DefineSetup(TRST,           E,  6, hd_gptp_OUT_PP,     1);
#define TRST(_v)                    dH_PORT_Write(TRST,_v)
#define TRST_OFF()          TRST(0)
#define TRST_ON()           TRST(1)

extern void hdI2C1_INT_InitPins(u8 isON);
extern void hdI2C2_INT_InitPins(u8 isON);
extern void hdI2C3_INT_InitPins(u8 isON);

#endif
