//////////////////////////////////////////////////////////////////////////////////////
// By Rob F. / Entire Group
//////////////////////////////////////////////////////////////////////////////////////

#ifndef __HDPSPI_CFG_H
#define __HDPSPI_CFG_H

#include "SysType.h"
#include "hdports.h"
#include "stm32f4xx_spi.h"

////////////////////////////////////////////////////////////////////////////////
//SPI0 CONFIG
////////////////////////////////////////////////////////////////////////////////
#define SPI0_CFG_DSIZE      SPI_DataSize_8b
#define SPI0_CFG_CPOL       SPI_CPOL_High
#define SPI0_CFG_CPHA       SPI_CPHA_2Edge
#define SPI0_CFG_NSS        SPI_NSS_Soft
#define SPI0_CFG_BAUD       SPI_BaudRatePrescaler_64
#define SPI0_CFG_FIRSTBIT   SPI_FirstBit_MSB
hdPin_O_DefineSetup(SPI0_CLK,       A,  5, hd_gptp_AF_PPU,     1);
hdPin_O_DefineSetup(SPI0_MISO,      A,  6, hd_gptp_AF_PPU,     1);
hdPin_O_DefineSetup(SPI0_MOSI,      A,  7, hd_gptp_AF_PPU,     1);
hdPin_O_DefineSetup(SPI0_NSSA,      A,  4, hd_gptp_OUT_PP,     1);
#define SPI0_NSSA(_v)               dH_PORT_Write(SPI0_NSSA,_v)
#define SPI0_NSS_ON()               SPI0_NSS(0)
#define SPI0_NSS_OFF()              SPI0_NSS(1)
hdPin_O_DefineSetup(SPI0sCLK,       A,  5, hd_gptp_OUT_PP,     1);
hdPin_O_DefineSetup(SPI0sMISO,      A,  6, hd_gptp_IN_PPU,     1);
hdPin_O_DefineSetup(SPI0sMOSI,      A,  7, hd_gptp_OUT_PP,     1);
#define SPI0sCLK(_v)                dH_PORT_Write(SPI0sCLK,_v)
#define SPI0sMISO()                 dH_PORT_Read(SPI0sMISO)
#define SPI0sMOSI(_v)               dH_PORT_Write(SPI0sMOSI,_v)

////////////////////////////////////////////////////////////////////////////////
//SPI1 CONFIG
////////////////////////////////////////////////////////////////////////////////
#define SPI1_CFG_DSIZE      SPI_DataSize_8b
#define SPI1_CFG_CPOL       SPI_CPOL_Low
#define SPI1_CFG_CPHA       SPI_CPHA_1Edge
#define SPI1_CFG_NSS        SPI_NSS_Soft
#define SPI1_CFG_BAUD       SPI_BaudRatePrescaler_128
#define SPI1_CFG_FIRSTBIT   SPI_FirstBit_LSB
hdPin_O_DefineSetup(SPI1_CLK,       B,  3, hd_gptp_AF_PPU,     1);
hdPin_O_DefineSetup(SPI1_MISO,      B,  4, hd_gptp_AF_PPU,     1);
hdPin_O_DefineSetup(SPI1_MOSI,      B,  5, hd_gptp_AF_PPU,     1);
hdPin_O_DefineSetup(SPI1_NSSA,      A, 15, hd_gptp_OUT_PP,     1);
#define SPI1_NSSA(_v)               dH_PORT_Write(SPI1_NSSA,_v)
#define SPI1_NSS_ON()               SPI1_NSS(0)
#define SPI1_NSS_OFF()              SPI1_NSS(1)
hdPin_O_DefineSetup(SPI1sCLK,       B,  3, hd_gptp_OUT_PP,     1);
hdPin_O_DefineSetup(SPI1sMISO,      B,  4, hd_gptp_IN_PPU,     1);
hdPin_O_DefineSetup(SPI1sMOSI,      B,  5, hd_gptp_OUT_PP,     1);
#define SPI1sCLK(_v)                dH_PORT_Write(SPI1sCLK,_v)
#define SPI1sMISO()                 dH_PORT_Read(SPI1sMISO)
#define SPI1sMOSI(_v)               dH_PORT_Write(SPI1sMOSI,_v)

////////////////////////////////////////////////////////////////////////////////
//SPI2 CONFIG
////////////////////////////////////////////////////////////////////////////////
#define SPI2_CFG_DSIZE      SPI_DataSize_8b
#define SPI2_CFG_CPOL       SPI_CPOL_High
#define SPI2_CFG_CPHA       SPI_CPHA_2Edge
#define SPI2_CFG_NSS        SPI_NSS_Soft
#define SPI2_CFG_BAUD       SPI_BaudRatePrescaler_128
#define SPI2_CFG_FIRSTBIT   SPI_FirstBit_MSB
hdPin_O_DefineSetup(SPI2_CLK,       B, 13, hd_gptp_AF_PPU,     1);
hdPin_O_DefineSetup(SPI2_MISO,      B, 14, hd_gptp_AF_PPU,     1);
hdPin_O_DefineSetup(SPI2_MOSI,      B, 15, hd_gptp_AF_PPU,     1);
hdPin_O_DefineSetup(SPI2_NSSA,      B, 12, hd_gptp_OUT_PP,     1);
#define SPI2_NSSA(_v)               dH_PORT_Write(SPI2_NSSA,_v)
#define SPI2_NSS_ON()               SPI2_NSS(0)
#define SPI2_NSS_OFF()              SPI2_NSS(1)
hdPin_O_DefineSetup(SPI2sCLK,       B, 13, hd_gptp_OUT_PP,     1);
hdPin_O_DefineSetup(SPI2sMISO,      B, 14, hd_gptp_IN_PPU,     1);
hdPin_O_DefineSetup(SPI2sMOSI,      B, 15, hd_gptp_OUT_PP,     1);
#define SPI2sCLK(_v)                dH_PORT_Write(SPI2sCLK,_v)
#define SPI2sMISO()                 dH_PORT_Read(SPI2sMISO)
#define SPI2sMOSI(_v)               dH_PORT_Write(SPI2sMOSI,_v)

////////////////////////////////////////////////////////////////////////////////
//SPI3 CONFIG
////////////////////////////////////////////////////////////////////////////////
#define SPI3_CFG_DSIZE      SPI_DataSize_8b
#define SPI3_CFG_CPOL       SPI_CPOL_High
#define SPI3_CFG_CPHA       SPI_CPHA_2Edge
#define SPI3_CFG_NSS        SPI_NSS_Soft//SPI_NSS_Hard//SPI_NSS_Soft
#define SPI3_CFG_BAUD       SPI_BaudRatePrescaler_8
#define SPI3_CFG_FIRSTBIT   SPI_FirstBit_MSB
hdPin_O_DefineSetup(SPI3_CLK,       C, 10, hd_gptp_AF_PPU,     1);
hdPin_O_DefineSetup(SPI3_MISO,      C, 11, hd_gptp_AF_PPU,     1);
hdPin_O_DefineSetup(SPI3_MOSI,      C, 12, hd_gptp_AF_PPU,     1);
hdPin_O_DefineSetup(SPI3_NSSA,      A, 15, hd_gptp_OUT_PP,     1);    //FLCSA   //hd_gptp_OUT_PP
#define SPI3_NSSA(_v)               dH_PORT_Write(SPI3_NSSA,_v)
#define SPI3_NSS_ON()               SPI3_NSS(0)
#define SPI3_NSS_OFF()              SPI3_NSS(1)
hdPin_O_DefineSetup(SPI3sCLK,       C, 10, hd_gptp_OUT_PP,     1);
hdPin_O_DefineSetup(SPI3sMISO,      C, 11, hd_gptp_IN_PPU,     1);
hdPin_O_DefineSetup(SPI3sMOSI,      C, 12, hd_gptp_OUT_PP,     1);
#define SPI3sCLK(_v)                dH_PORT_Write(SPI3sCLK,_v)
#define SPI3sMISO()                 dH_PORT_Read(SPI3sMISO)
#define SPI3sMOSI(_v)               dH_PORT_Write(SPI3sMOSI,_v)



#endif
