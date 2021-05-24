//////////////////////////////////////////////////////////////////////////////////////
// By Rob F. / Entire Group
//////////////////////////////////////////////////////////////////////////////////////

#ifndef __RBSTM32DEVICEINFO_H
#define __RBSTM32DEVICEINFO_H

#include "SysType.h"

typedef struct {
      u32     PAT   :4;       //pat ?
      u32     ID    :12;      //Cortex ID
      u32     INF   :4;       //???
      u32     VAR   :4;       //var ?
      u32     CORE  :8;       //0x41 = ARM
}tDeviceInfoCPUID;

typedef struct {
      u32     DEV   :12;
      u32     SIG   :4;       //???
      u32     REV   :16;
}tDeviceInfoDEVID;

typedef struct {
    tDeviceInfoCPUID      *CPU;
    tDeviceInfoDEVID      *DEV; //u32                   *DEV; //tDeviceInfoDEVID      *DEV;
    u16                   *FLASH_SIZE;
    u32                   *UID;
}tDeviceInfo;

extern tDeviceInfo STMDeviceInfo;

extern u8 rbDeviceInfoCheck(void);
extern u8 rbDeviceInfoCheckAutoInit(void);
extern u16 rbDeviceInfoGetDEVID(void);
extern u16 rbDeviceInfoGetREVID(void);
extern u32 rbDeviceInfoGetUID(u8 n);
extern u32 rbDeviceInfoGetFlashSize(void);
extern void rbDeviceInfoInit(void);

#endif
