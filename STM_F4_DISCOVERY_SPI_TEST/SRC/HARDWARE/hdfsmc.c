//////////////////////////////////////////////////////////////////////////////////////
// 
// Low level for STM32F100
// 
// By Rob F. / Entire Group
// 
//////////////////////////////////////////////////////////////////////////////////////

#include "SysType.h"
#include "hdfsmc.h"
#include "hardware.h"

//////////////////////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////////////////


//////////////////////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////////////////
void FSMC_Init(u8 en)
{
  
  
//    GPIO_InitTypeDef GPIO_InitStructure;
    FSMC_NANDInitTypeDef FSMC_NANDInitStructure;
    FSMC_NAND_PCCARDTimingInitTypeDef p;
//    FSMC_NORSRAMTimingInitTypeDef pp;

//    const vu16 mdAFPX = en ? hd_gptp_OUT_PP : hd_gptp_IN_OD;
    const u16 mdAFPP = en ? hd_gptp_AF_PP  : hd_gptp_IN_OD;
    const u16 mdIPU  = en ? hd_gptp_AF_PPU : hd_gptp_IN_OD;
    const u8 af      = en ? GPIO_AF_FSMC   : GPIO_AF_EVENTOUT;
  
//////    RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOD | RCC_APB2Periph_GPIOE, ENABLE);
//////    GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
//////    if (en==0)
//////    {
//////      RCC_AHBPeriphClockCmd(RCC_AHBPeriph_FSMC, DISABLE);//OFF ????????.
//////      
//////      GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AIN;
//////      GPIO_InitStructure.GPIO_Pin = GPIO_Pin_0 | GPIO_Pin_1 | GPIO_Pin_14 | GPIO_Pin_15 | GPIO_Pin_11 | GPIO_Pin_12 | GPIO_Pin_4 | GPIO_Pin_5 | GPIO_Pin_7;
//////      GPIO_Init(GPIOD, &GPIO_InitStructure);
//////    
//////      GPIO_InitStructure.GPIO_Pin = GPIO_Pin_7 | GPIO_Pin_8 | GPIO_Pin_9 | GPIO_Pin_10;
//////      GPIO_Init(GPIOE, &GPIO_InitStructure);

//////      return;
//////    }
    
    //!< SRAM Data lines configuration
//////    GPIO_InitStructure.GPIO_Pin = GPIO_Pin_0 | GPIO_Pin_1 | GPIO_Pin_14 | GPIO_Pin_15;
//////    GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF_PP;
//////    GPIO_Init(GPIOD, &GPIO_InitStructure);
//////    GPIO_InitStructure.GPIO_Pin = GPIO_Pin_7 | GPIO_Pin_8 | GPIO_Pin_9 | GPIO_Pin_10;
//////    GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF_PP;
//////    GPIO_Init(GPIOE, &GPIO_InitStructure);
//    GPIO_PinAFConfig(GPIOD, GPIO_PinSource0, GPIO_AF_FSMC); 
    if (en)
    {
      RCC_AHB3PeriphClockCmd(RCC_AHB3Periph_FSMC, ENABLE);
    }
    
    GpioInAM_FSMCD0(mdAFPP, af);
    GpioInAM_FSMCD1(mdAFPP, af);
    GpioInAM_FSMCD2(mdAFPP, af);
    GpioInAM_FSMCD3(mdAFPP, af);
    GpioInAM_FSMCD4(mdAFPP, af);
    GpioInAM_FSMCD5(mdAFPP, af);
    GpioInAM_FSMCD6(mdAFPP, af);
    GpioInAM_FSMCD7(mdAFPP, af);
    
//    GpioIniM_FSMCNCE2(mdAFPP);
//    GpioIniM_FSMCD13(mdAFPP);
//    GpioIniM_FSMCD14(mdAFPP);
//    GpioIniM_FSMCD15(mdAFPP);

    //!< SRAM Address lines configuration
    //A16 - pin 11
    //A17 - pin 12
//////    GPIO_InitStructure.GPIO_Pin = GPIO_Pin_11 | GPIO_Pin_12;
//////    GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF_PP;
//////    GPIO_Init(GPIOD, &GPIO_InitStructure);
    GpioInAM_FSMCA16(mdAFPP, af);
    GpioInAM_FSMCA17(mdAFPP, af);
    
    //!< NOE and NWE configuration
//////    GPIO_InitStructure.GPIO_Pin = GPIO_Pin_4 | GPIO_Pin_5;
//////    GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF_PP;
//////    GPIO_Init(GPIOD, &GPIO_InitStructure);
    GpioInAM_FSMCNOE(mdAFPP, af);
    GpioInAM_FSMCNWE(mdAFPP, af);
    
    //!< NE1 configuration CS chip select
//////    GPIO_InitStructure.GPIO_Pin = GPIO_Pin_7;
//////    GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF_PP;
//////    GPIO_Init(GPIOD, &GPIO_InitStructure);
    GpioInAM_FSMCNCE2(mdAFPP, af);

    //!< NWAIT NAND pin configuration
//////    GPIO_InitStructure.GPIO_Pin = GPIO_Pin_6;
//////    GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IPU;
//////    GPIO_Init(GPIOD, &GPIO_InitStructure);
    GpioInAM_FSMCNWAIT(mdIPU, af);
    
    //!< CLOCK OUTPUT pin configuration
//////    //GPIO_InitStructure.GPIO_Pin = GPIO_Pin_3;
//////    //GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF_PP;
//////    //GPIO_Init(GPIOD, &GPIO_InitStructure);
    //GpioIniM_FSMCCLK(mdAFPP);
    
//-- FSMC Configuration ------------------------------------------------------

//RCC_AHBPeriphClockCmd(RCC_AHBPeriph_FSMC, ENABLE);//???????? ????????.
    if (!en)
    {
      RCC_AHB3PeriphClockCmd(RCC_AHB3Periph_FSMC, DISABLE);
      return;
    }

//-- FSMC Configuration ------------------------------------------------------
FSMC_NANDInitStructure.FSMC_CommonSpaceTimingStruct = &p;
FSMC_NANDInitStructure.FSMC_AttributeSpaceTimingStruct = &p;
FSMC_NANDStructInit(&FSMC_NANDInitStructure);

/*
p.FSMC_SetupTime = 0x1;
p.FSMC_WaitSetupTime = 0x1;
p.FSMC_HoldSetupTime = 0x2;
p.FSMC_HiZSetupTime = 0x2;
*/
/*
// Max Speed Maybe not stable
p.FSMC_SetupTime = 0x0;
p.FSMC_WaitSetupTime = 0x1;
p.FSMC_HoldSetupTime = 0x1;
p.FSMC_HiZSetupTime = 0x0;
*/
p.FSMC_SetupTime     = 0x14;
p.FSMC_WaitSetupTime = 0x14;
p.FSMC_HoldSetupTime = 0x14;
p.FSMC_HiZSetupTime  = 0x10;


FSMC_NANDInitStructure.FSMC_Bank = FSMC_Bank2_NAND;
FSMC_NANDInitStructure.FSMC_Waitfeature = FSMC_Waitfeature_Enable;
FSMC_NANDInitStructure.FSMC_MemoryDataWidth = FSMC_MemoryDataWidth_8b;
FSMC_NANDInitStructure.FSMC_ECC = FSMC_ECC_Disable;
FSMC_NANDInitStructure.FSMC_ECCPageSize = FSMC_ECCPageSize_256Bytes;
FSMC_NANDInitStructure.FSMC_TCLRSetupTime = 0x00;
FSMC_NANDInitStructure.FSMC_TARSetupTime = 0x00;

//FSMC_NANDInitStructure.FSMC_AddressLowMapping = FSMC_AddressLowMapping_Direct;

FSMC_NANDInit(&FSMC_NANDInitStructure);



//RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOD | RCC_APB2Periph_GPIOC | RCC_APB2Periph_GPIOB | RCC_APB2Periph_GPIOE | RCC_APB2Periph_AFIO, ENABLE);
//RCC_AHBPeriphClockCmd(RCC_AHBPeriph_FSMC, ENABLE);

//!< FSMC NAND Bank Cmd Test 
FSMC_NANDCmd(FSMC_Bank2_NAND, ENABLE);

FSMC_NANDECCCmd(FSMC_Bank2_NAND,ENABLE);



}


