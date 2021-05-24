//////////////////////////////////////////////////////////////////////////////////////
// By Rob F. / Entire Group
//////////////////////////////////////////////////////////////////////////////////////

#include "SysType.h"
#include "rbSTM32DeviceInfo.h"

//Device UID Pointers
//F0, F3                            0x1FFFF7AC
//F1                                0x1FFFF7E8
//F2, F4                            0x1FFF7A10
//F7                                0x1FF0F420
//L0                                0x1FF80050
//L0, L1 Cat.1,Cat.2                0x1FF80050
//L1 Cat.3,Cat.4,Cat.5,Cat.6        0x1FF800D0

tDeviceInfo STMDeviceInfo = {
    .CPU          = (void *)(&SCB->CPUID),//(void *)(0xE000ED00),
    .DEV          = 0,
    .FLASH_SIZE   = 0,
    .UID          = 0,
};


#define rbDeviceInfoCheckDEV()      (STMDeviceInfo.DEV==0)
#define rbDeviceInfoCheckFSI()      (STMDeviceInfo.FLASH_SIZE==0)
#define rbDeviceInfoCheckUID()      (STMDeviceInfo.UID==0)

u16 rbDeviceInfoGetDEVID(void)
{
    u16 res=0;
    if( rbDeviceInfoCheckDEV() ) rbDeviceInfoInit();
    if(!rbDeviceInfoCheckDEV() )
    {
      res = STMDeviceInfo.DEV->DEV;//((tDeviceInfoDEVID *)(STMDeviceInfo.DEV))->DEV;
    }
    return res;
}

u16 rbDeviceInfoGetREVID(void)
{
    u16 res=0;
    if( rbDeviceInfoCheckDEV() ) rbDeviceInfoInit();
    if(!rbDeviceInfoCheckDEV() )
    {
      res = STMDeviceInfo.DEV->REV;//((tDeviceInfoDEVID *)(STMDeviceInfo.DEV))->REV;
      res = res?res:0xFFFF;
    }
    return res;
}

u32 rbDeviceInfoGetUID(u8 n)
{
    if(rbDeviceInfoCheckUID()) rbDeviceInfoInit();
    return (STMDeviceInfo.UID)?STMDeviceInfo.UID[n]:0x00000000;
}

u32 rbDeviceInfoGetFlashSize(void)
{
    u32 res = 0;
    if(rbDeviceInfoCheckFSI()) rbDeviceInfoInit(); //
    if (STMDeviceInfo.FLASH_SIZE)
    {
      res = *STMDeviceInfo.FLASH_SIZE;
      if (rbDeviceInfoGetDEVID()==0x429) res &= 0x00FF;
      if (res==0)
      {
        res =384;
      } else if (res==1) {
        res =256;
      };
      res *= 1024;
    }
    return res;
}

//////////////////////////////////////////////////////////
void rbDeviceInfoSetUpPointers(void)
{
    switch (STMDeviceInfo.CPU->ID)
    {
      case 0x0C20:    //Cortex M0
      case 0x0C60:    //Cortex M0+
      case 0x0C21:    //Cortex M1
        STMDeviceInfo.DEV = (void *)(0x40015800);
        break;
      case 0x0C23:    //Cortex M3
      case 0x0C24:    //Cortex M4
      case 0x0C27:    //Cortex M7
        STMDeviceInfo.DEV = (void *)(0xE0042000);
        break;
      default:        //ERROR
        break;
    }

    if (STMDeviceInfo.DEV)
    {
      if( (STMDeviceInfo.CPU->ID==0x0C20)||(STMDeviceInfo.CPU->ID==0x0C60) )
      {
            STMDeviceInfo.FLASH_SIZE = (u16 *)(0x1FFFF7CC);
            STMDeviceInfo.UID        = (u32 *)(0x1FFFF7AC);   //???
      } else {
        switch(rbDeviceInfoGetDEVID())// (STMDeviceInfo.DEV->DEV)
        {
          case 0x000: // Blocked DEBUGREG By STM32F1xx
          case 0x410: // STM32F101/2/3 medium-density & gd32x
          case 0x412: // STM32F101/2/3 low-density
          case 0x414: // STM32F101/3 high-density
          case 0x418: // STM32F105/7 connectivity line
          case 0x420: // STM32F100 low/medium-density value line
          case 0x428: // STM32F100 high-density value line
          case 0x430: // STM32F101/3 XL-density (dual flash banks)
            STMDeviceInfo.FLASH_SIZE = (void *)(0x1FFFF7E0);
            STMDeviceInfo.UID        = (void *)(0x1FFFF7E8);
            break;
          case 0x411: // STM32F205/07/15/17
          case 0x413: // STM32F405/07/15/17
          case 0x419: // STM32F42x/3x
          case 0x421: // STM32F446
          case 0x423: // STM32F401xB/C
          case 0x431: // STM32F411
          case 0x433: // STM32F401xD/E
          case 0x434: // STM32F469/79
          case 0x441: // STM32F412
          case 0x458: // STM32F410
          case 0x463: // STM32F413/23
            STMDeviceInfo.FLASH_SIZE = (u16 *)(0x1FFF7A22);
            STMDeviceInfo.UID        = (u32 *)(0x1FFF7A10);
            break;
          case 0x440: // STM32F05x | STM32F030x8
          case 0x442: // STM32F09x | STM32F030xC
          case 0x444: // STM32F03x
          case 0x445: // STM32F04x | STM32F070x6
          case 0x448: // STM32F07x
          case 0x422: // STM32F303xB/C | STM32F358 | STM32F302xB/C
          case 0x432: // STM32F37x
          case 0x438: // STM32F303x6/8 | STM32F328 | STM32F334
          case 0x439: // STM32F301x6/8 | STM32F302x6/8
          case 0x446: // STM32F302xD/E | STM32F303xD/E | STM32F398xE
            STMDeviceInfo.FLASH_SIZE = (u16 *)(0x1FFFF7CC);
            STMDeviceInfo.UID        = (u32 *)(0x1FFFF7AC);
            break;
          case 0x449: // STM32F74x/5x
          case 0x451: // STM32F76x/7x
          case 0x452: // STM32F72x/3x
          case 0x450: // STM32H7x
            STMDeviceInfo.FLASH_SIZE = (u16 *)(0x1FF0F442);
            STMDeviceInfo.UID        = (u32 *)(0x1FF0F420);
            break;
          case 0x435: // STM32L43xxx or L44xxx              ???
          case 0x415: // STM32L475xx, L476xx or L486xx      ???
          case 0x461: // STM32L496xx or L4A6xx              ???
          case 0x462: // STM32L45xxx or L46xxx              ???
          case 0x470: // STM32L4Rxxx or L4Sxxx              ???
          case 0x416: // STM32L1xx medium-density       cat.1
          case 0x429: // STM32L1xx                      cat.2
            STMDeviceInfo.FLASH_SIZE = (u16 *)(0x1FF8004C);
            STMDeviceInfo.UID        = (u32 *)(0x1FF80050);
            break;
          case 0x417: // STM32L0 Cat 3
          case 0x447: // STM32L0 Cat 5
          case 0x427: // STM32L1xx medium-density/plus  cat.3
          case 0x437: // STM32L152re                    cat.5
          case 0x436: // STM32L1xx high-density         cat.4
            STMDeviceInfo.FLASH_SIZE = (u16 *)(0x1FF800CC);
            STMDeviceInfo.UID        = (u32 *)(0x1FF800D0);
            break;
          default:    // UNCNOWN ???
            break;
        }
      }
    }
}

void rbDeviceInfoInit(void)
{
    rbDeviceInfoSetUpPointers();
}
