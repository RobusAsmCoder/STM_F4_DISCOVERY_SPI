//////////////////////////////////////////////////////////////////////////////////////
// By Rob F. / Entire Group
//////////////////////////////////////////////////////////////////////////////////////

#ifndef __HDFSMC_H
#define __HDFSMC_H

#include "SysType.h"
#include "hdports.h"


//////////////////////////////////////////////////////////////////////////////////////
// FSMC Config
//////////////////////////////////////////////////////////////////////////////////////

  hdPin_O_DefineSetup(FSMCD0,             D, 14, hd_gptp_AF_PP,      1);
  hdPin_O_DefineSetup(FSMCD1,             D, 15, hd_gptp_AF_PP,      1);
  hdPin_O_DefineSetup(FSMCD2,             D,  0, hd_gptp_AF_PP,      1);
  hdPin_O_DefineSetup(FSMCD3,             D,  1, hd_gptp_AF_PP,      1);
  hdPin_O_DefineSetup(FSMCD4,             E,  7, hd_gptp_AF_PP,      1);
  hdPin_O_DefineSetup(FSMCD5,             E,  8, hd_gptp_AF_PP,      1);
  hdPin_O_DefineSetup(FSMCD6,             E,  9, hd_gptp_AF_PP,      1);
  hdPin_O_DefineSetup(FSMCD7,             E, 10, hd_gptp_AF_PP,      1);
  
  hdPin_O_DefineSetup(FSMCA16,            D, 11, hd_gptp_AF_PP,      1);
  hdPin_O_DefineSetup(FSMCA17,            D, 12, hd_gptp_AF_PP,      1);
  
  hdPin_O_DefineSetup(FSMCNOE,            D,  4, hd_gptp_AF_PP,      1);
  hdPin_O_DefineSetup(FSMCNWE,            D,  5, hd_gptp_AF_PP,      1);
  
  hdPin_O_DefineSetup(FSMCNCE2,           D,  7, hd_gptp_AF_PP,      1);
  hdPin_O_DefineSetup(FSMCNWAIT,          D,  6, hd_gptp_AF_PPU,     1);
  
  hdPin_O_DefineSetup(FSMCCLK,            D,  3, hd_gptp_AF_PP,      1);    //Not USED But In The Schematic
  hdPin_O_DefineSetup(FSMCD13,            D,  8, hd_gptp_AF_PP,      1);    //Not USED But In The Schematic
  hdPin_O_DefineSetup(FSMCD14,            D,  9, hd_gptp_AF_PP,      1);    //Not USED
  hdPin_O_DefineSetup(FSMCD15,            D, 10, hd_gptp_AF_PP,      1);    //Not USED

//#define CMD_AREA        (vu32)(1UL<<16)             // A16 = CLE high
//#define ADDR_AREA       (vu32)(1UL<<17)             // A17 = ALE high
//#define DATA_AREA       ((vu32)0x00000000)

#ifndef Bank2_NAND_ADDR
 #define Bank2_NAND_ADDR ((vu32)0x70000000)
#endif
#ifndef Bank_NAND_ADDR
 #define Bank_NAND_ADDR Bank2_NAND_ADDR
#endif

//#define nandaddr_CMD    

#define nandMemoryHoleSize    ((u32)0x00010000)

typedef struct {
  u8 dat[nandMemoryHoleSize];
  u8 cmd[nandMemoryHoleSize];
  u8 adr[nandMemoryHoleSize];
} NandAdr_TypeDef;

#define NandInt     ((NandAdr_TypeDef *) Bank_NAND_ADDR)

//////////////////////////////////////////////////////////////////////////////////////
// External
//////////////////////////////////////////////////////////////////////////////////////

extern void FSMC_Init(u8 en);

#endif
