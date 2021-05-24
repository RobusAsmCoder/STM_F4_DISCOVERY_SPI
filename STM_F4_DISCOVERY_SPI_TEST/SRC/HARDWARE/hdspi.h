//////////////////////////////////////////////////////////////////////////////////////
// By Rob F. / Entire Group
//////////////////////////////////////////////////////////////////////////////////////

#ifndef __HDPSPI_H
#define __HDPSPI_H

#include "SysType.h"
#include "hdports.h"
#include "hdspi_CFG.h"
#include "stm32f4xx_rcc.h"
#include "stm32f4xx_spi.h"
#include "stm32f4xx_dma.h"

////////////////////////////////////////////////////////////////////////////////

enum{
  hdSPI_WorkMode_Hardware       = 0 ,
  hdSPI_WorkMode_HardSoft           ,
  hdSPI_WorkMode_HardSoftNext       ,
  hdSPI_GPIOMode_ON             = 0 ,
  hdSPI_GPIOMode_OFF                ,
  hdSPI_GPIOMode_ENABLE             ,
  hdSPI_GPIOMode_DISABLE            ,
  hdSPI_GPIOMode_NSS_SOFT           ,
  hdSPI_GPIOMode_NSS_FRAME          ,
  hdSPI_GPIOMode_SFT_ON             ,
  hdSPI_GPIOMode_SFT_OFF            ,
  hdSPI_GPIOMode_ReadMISO           ,
  hdSPI_GPIOMode_WriteMOSI_0        ,
  hdSPI_GPIOMode_WriteMOSI_1        ,
  hdSPI_GPIOMode_WriteCLK_0         ,
  hdSPI_GPIOMode_WriteCLK_1         ,
  hdSPI_SoftState_NOP           = 0 ,
  hdSPI_SoftState_UpdateGPIO    = 1 ,
  hdSPI_SoftState_Start         = 2 ,
  hdSPI_SoftState_End           = 4 ,
  hdSPI_SoftState_Byte          = 8 ,
  hdSPI_SoftGPIO_MOSI_0         = 0x0200  | hdSPI_SoftState_UpdateGPIO,
  hdSPI_SoftGPIO_MOSI_1         = 0x0300  | hdSPI_SoftState_UpdateGPIO,
  hdSPI_SoftGPIO_CLK_0          = 0x0800  | hdSPI_SoftState_UpdateGPIO,
  hdSPI_SoftGPIO_CLK_1          = 0x0C00  | hdSPI_SoftState_UpdateGPIO,
};

typedef struct {
  u16       Mode;
  u16       Step;
  u16       Cnt;
  u32       EventState;
  u8       *BUFTX;
  u8       *BUFRX;
  u16       BUFSize;
  u16       BUFTXWORD;
  u16       BUFRXWORD;
  u8        incTX;
  u8        incRX;
  u8        cfHoldCountST;
  u8        cfHoldCountSTSES;
  u8        cfHoldCountEN;
  u8        HoldCNT;
  u16       BaudDiv;
  u16       BaudCounter;
   u16      cfCPOL          :1;
   u16      cfCPHA          :1;
   u16      cfFirstMSBLSB   :1;
   u16      doInt           :1;
   u16                      :4;
   u16                      :8;
}thdSPIWorkStruct;

////////////////////////////////////////////////////////////////////////////////
//#define dH_SPI_REG_CR(_spi, _spi_CPOL, _spi_CPHA, _spi_FIRBIT, _spi_NSS, _spi_BAUD, _spi_DSIZE )       _spi->CR1 = (_spi->CR1 & (~(SPI_CPOL_High | SPI_CPHA_2Edge | SPI_FirstBit_LSB | SPI_NSS_Soft | SPI_BaudRatePrescaler_256 | SPI_DataSize_16b ))) | (_spi_CPOL | _spi_CPHA | _spi_FIRBIT | _spi_NSS | _spi_BAUD | _spi_DSIZE)
////////////////////////////////////////////////////////////////////////////////
//  tmpreg |= DMA_InitStruct->DMA_Channel |             = _ch_
//            DMA_InitStruct->DMA_DIR |                 = _val_
//            DMA_InitStruct->DMA_PeripheralInc |       = _val_
//            DMA_InitStruct->DMA_MemoryInc |           = _val_
//            DMA_InitStruct->DMA_PeripheralDataSize |  = DMA_PeripheralDataSize_Byte
//            DMA_InitStruct->DMA_MemoryDataSize |      = DMA_MemoryDataSize_Byte
//            DMA_InitStruct->DMA_Mode |                = DMA_Mode_Normal
//            DMA_InitStruct->DMA_Priority |            = DMA_Priority_VeryHigh
//            DMA_InitStruct->DMA_MemoryBurst |         = DMA_MemoryBurst_Single
//            DMA_InitStruct->DMA_PeripheralBurst;      = DMA_PeripheralBurst_Single
//#define SPI_DMA_CCR(_val_)    (DMA_M2M_Disable | DMA_Priority_VeryHigh | DMA_MemoryDataSize_Byte | DMA_PeripheralDataSize_Byte | DMA_PeripheralInc_Disable | DMA_Mode_Normal | _val_)
//DMA_PeripheralDataSize_HalfWord
#define SPI_DMA_CCR(_val_)      ( DMA_Mode_Normal | DMA_Priority_VeryHigh | DMA_MemoryBurst_Single | DMA_PeripheralBurst_Single | (_val_))
#define DmaMemSel(_MemInc)      (_MemInc==0 ? DMA_MemoryInc_Disable : DMA_MemoryInc_Enable)

////////////////////////////////////////////////////////////////////////////////
//Procedures Events Defines
////////////////////////////////////////////////////////////////////////////////
typedef u32 (tSPI_EventProc)(u32);

#define HIGH_ISR_MASK               ((u32)0x20000000)
#define SPI_CR2_FRF                 ((u8)0x10)               //FRF Interrupt Enable
////////////////////////////////////////////////////////////////////////////////
//SPI Defines
////////////////////////////////////////////////////////////////////////////////
#define SPIxDefineCFG(_SPIx,_DMAN,_STRX,_STTX,_CHRX,_CHTX)                                                                                                \
enum {                                                                                                                                                    \
  SPI##_SPIx##vDMA        = (s32)(DMA##_DMAN),                                                                                                            \
  SPI##_SPIx##CCR         = (s32)( ((SPI##_SPIx##_CFG_DSIZE)==SPI_DataSize_16b) ? (DMA_PeripheralDataSize_HalfWord | DMA_MemoryDataSize_HalfWord) :       \
                                                                                  (DMA_PeripheralDataSize_Byte     | DMA_MemoryDataSize_Byte)    ),       \
  SPI##_SPIx##vSTRX       = (s32)(DMA##_DMAN##_Stream##_STRX),                                                                                            \
  SPI##_SPIx##vSTTX       = (s32)(DMA##_DMAN##_Stream##_STTX),                                                                                            \
  SPI##_SPIx##vCHRX       = (s32)(DMA_Channel_##_CHRX),                                                                                                   \
  SPI##_SPIx##vCHTX       = (s32)(DMA_Channel_##_CHTX),                                                                                                   \
  SPI##_SPIx##iCHRX       = (s32)(DMA##_DMAN##_Stream##_STRX##_IRQn),                                                                                     \
  SPI##_SPIx##iCHTX       = (s32)(DMA##_DMAN##_Stream##_STTX##_IRQn),                                                                                     \
  SPI##_SPIx##vFLAGRXL    = (s32)( (DMA_FLAG_TCIF##_STRX)&HIGH_ISR_MASK ? 0:(DMA_FLAG_TCIF##_STRX)&0x0FFFFFFF   ),                                        \
  SPI##_SPIx##vFLAGRXH    = (s32)( (DMA_FLAG_TCIF##_STRX)&HIGH_ISR_MASK ?   (DMA_FLAG_TCIF##_STRX)&0x0FFFFFFF:0 ),                                        \
  SPI##_SPIx##vFLAGTXL    = (s32)( (DMA_FLAG_TCIF##_STTX)&HIGH_ISR_MASK ? 0:(DMA_FLAG_TCIF##_STTX)&0x0FFFFFFF   ),                                        \
  SPI##_SPIx##vFLAGTXH    = (s32)( (DMA_FLAG_TCIF##_STTX)&HIGH_ISR_MASK ?   (DMA_FLAG_TCIF##_STTX)&0x0FFFFFFF:0 ),                                        \
}

//SPIxDefineCFG(0, 1,2,3);
#ifdef SPI0_CFG_DSIZE
SPIxDefineCFG(0, 2, 0,5, 3,3);
#endif
#ifdef SPI1_CFG_DSIZE
SPIxDefineCFG(1, 2, 0,5, 3,3);
#endif
#ifdef SPI2_CFG_DSIZE
SPIxDefineCFG(2, 1, 3,4, 0,0);
#endif
#ifdef SPI3_CFG_DSIZE
SPIxDefineCFG(3, 1, 0,7, 0,0);
#endif

enum {
  SPI_FLAG_MD_ST            = (s32)(1<<0),
  SPI_FLAG_MD_EN            = (s32)(1<<1),
  SPI_FLAG_MD_RX_EN         = (s32)(1<<2),
  SPI_FLAG_MD_TX_EN         = (s32)(1<<3),
};

#define SPI0_DMA_AHB_INIT(_en)  RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_DMA2, _en)

#define SPI1_DMA_RX_IRQ         void DMA2_Stream0_IRQHandler(void) __irq
#define SPI1_DMA_TX_IRQ         void DMA2_Stream5_IRQHandler(void) __irq
#define SPI1_DMA_RX_IRQ_CLR()   *(u64 *)(&SPIxDMAx(1)->LIFCR) = SPIx_DMA_FLAGRX(1)
#define SPI1_DMA_TX_IRQ_CLR()   *(u64 *)(&SPIxDMAx(1)->LIFCR) = SPIx_DMA_FLAGTX(1)
#define SPI1_DMA_AHB_INIT(_en)  RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_DMA2, _en)

#define SPI2_DMA_RX_IRQ         void DMA1_Stream3_IRQHandler(void) __irq
#define SPI2_DMA_TX_IRQ         void DMA1_Stream4_IRQHandler(void) __irq
#define SPI2_DMA_RX_IRQ_CLR()   *(u64 *)(&SPIxDMAx(2)->LIFCR) = SPIx_DMA_FLAGRX(2)
#define SPI2_DMA_TX_IRQ_CLR()   *(u64 *)(&SPIxDMAx(2)->LIFCR) = SPIx_DMA_FLAGTX(2)
#define SPI2_DMA_AHB_INIT(_en)  RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_DMA1, _en)

#define SPI3_DMA_RX_IRQ         void DMA1_Stream0_IRQHandler(void) __irq
#define SPI3_DMA_TX_IRQ         void DMA1_Stream7_IRQHandler(void) __irq
#define SPI3_DMA_RX_IRQ_CLR()   *(u64 *)(&SPIxDMAx(3)->LIFCR) = SPIx_DMA_FLAGRX(3)
#define SPI3_DMA_TX_IRQ_CLR()   *(u64 *)(&SPIxDMAx(3)->LIFCR) = SPIx_DMA_FLAGTX(3)
#define SPI3_DMA_AHB_INIT(_en)  RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_DMA1, _en)


#define SPIxDMAx(_SPIx)                   ((DMA_TypeDef *)SPI##_SPIx##vDMA)
#define SPIxDMAxFLAGx(_SPIx,_IOx)         (u64)((u64)(SPI##_SPIx##vFLAG##_IOx##L)|((u64)(SPI##_SPIx##vFLAG##_IOx##H)<<32))
#define SPIxDMAxFLAGxRX(_SPIx)            (u64)(SPIxDMAxFLAGx(_SPIx,RX))
#define SPIxDMAxFLAGxTX(_SPIx)            (u64)(SPIxDMAxFLAGx(_SPIx,TX))
#define SPIxDMAxFLAGxRXTX(_SPIx)          (u64)(SPIxDMAxFLAGx(_SPIx,RX) | SPIxDMAxFLAGx(_SPIx,TX))
#define SPIxDMAxCHANNELx(_SPIx,_IOx)      ((DMA_Stream_TypeDef *)SPI##_SPIx##vST##_IOx)       //DMA_Channel_TypeDef

#define DMA_DIR_PeripheralDST       DMA_DIR_MemoryToPeripheral
#define DMA_DIR_PeripheralSRC       DMA_DIR_PeripheralToMemory

#define SPIx_DMA_IsDisable(_SPIx)    (SPIxDMAxCHANNELx(_SPIx,TX)->PAR==0)
#define SPIx_DMA_IsEnable(_SPIx)     (SPIxDMAxCHANNELx(_SPIx,TX)->PAR!=0)
#define SPIx_DMA_SetUp(_SPIx, _TX_MemAdr, _RX_MemAdr, _Size, _TX_MemInc, _RX_MemInc)              do{                                       \
  SPIxDMAxCHANNELx(_SPIx,TX)->NDTR = ((SPI##_SPIx##_CFG_DSIZE)==SPI_DataSize_16b) ? (_Size)>>1 : (_Size);                                   \
  SPIxDMAxCHANNELx(_SPIx,TX)->M0AR = (u32)(_TX_MemAdr);                                                                                     \
  SPIxDMAxCHANNELx(_SPIx,TX)->CR   = SPI_DMA_CCR(DmaMemSel(_TX_MemInc) | DMA_DIR_PeripheralDST | SPI##_SPIx##vCHTX | SPI##_SPIx##CCR);      \
  SPIxDMAxCHANNELx(_SPIx,RX)->NDTR = ((SPI##_SPIx##_CFG_DSIZE)==SPI_DataSize_16b) ? (_Size)>>1 : (_Size);                                   \
  SPIxDMAxCHANNELx(_SPIx,RX)->M0AR = (u32)(_RX_MemAdr);                                                                                     \
  SPIxDMAxCHANNELx(_SPIx,RX)->CR   = SPI_DMA_CCR(DmaMemSel(_RX_MemInc) | DMA_DIR_PeripheralSRC | SPI##_SPIx##vCHRX | SPI##_SPIx##CCR);      \
                                                                                                    }while(0)
#define SPIx_DMA_FLAGRX(_SPIx)       (SPIxDMAxFLAGxRX(_SPIx))
#define SPIx_DMA_FLAGTX(_SPIx)       (SPIxDMAxFLAGxTX(_SPIx))
#define SPIx_DMA_FLAG(_SPIx)         (SPIxDMAxFLAGxRXTX(_SPIx))
#define SPIx_DMA_Start(_SPIx)                                                                     do{               \
  ((SPI_TypeDef *)SPI##_SPIx)->CR2 |= (SPI_I2S_DMAReq_Rx | SPI_I2S_DMAReq_Tx);                                      \
  SPIxDMAxCHANNELx(_SPIx,RX)->CR |= DMA_SxCR_EN | DMA_SxCR_TCIE;                                                    \
  SPIxDMAxCHANNELx(_SPIx,TX)->CR |= DMA_SxCR_EN | DMA_SxCR_TCIE;                                                    \
                                                                                                    }while(0)
#define SPIx_DMA_IsBusy(_SPIx)       ((*(u64 *)(&SPIxDMAx(_SPIx)->LISR) & SPIx_DMA_FLAG(_SPIx))!=SPIx_DMA_FLAG(_SPIx))
#define SPIx_DMA_IsBusyRX(_SPIx)     ((*(u64 *)(&SPIxDMAx(_SPIx)->LISR) & SPIx_DMA_FLAGRX(_SPIx))!=SPIx_DMA_FLAGRX(_SPIx))
#define SPIx_DMA_IsBusyTX(_SPIx)     ((*(u64 *)(&SPIxDMAx(_SPIx)->LISR) & SPIx_DMA_FLAGTX(_SPIx))!=SPIx_DMA_FLAGTX(_SPIx))
#define SPIx_DMA_End(_SPIx)                                                                       do{               \
  *(u64 *)(&SPIxDMAx(_SPIx)->LIFCR) = SPIx_DMA_FLAG(_SPIx);                                                         \
  SPIxDMAxCHANNELx(_SPIx,TX)->CR &=~DMA_SxCR_EN;                                                                    \
  SPIxDMAxCHANNELx(_SPIx,RX)->CR &=~DMA_SxCR_EN;                                                                    \
  ((SPI_TypeDef *)SPI##_SPIx)->CR2 &=~(SPI_I2S_DMAReq_Rx | SPI_I2S_DMAReq_Tx);                                      \
                                                                                                    }while(0)
#define SPIx_DMA_InitM(_SPIx)                                                                     do{               \
  SPI##_SPIx##_DMA_AHB_INIT(ENABLE);                                                                                \
  SPIxDMAxCHANNELx(_SPIx,RX)->FCR  = DMA_FIFOMode_Disable | DMA_FIFOThreshold_1QuarterFull;                                 \
  SPIxDMAxCHANNELx(_SPIx,TX)->FCR  = DMA_FIFOMode_Disable | DMA_FIFOThreshold_1QuarterFull;                                 \
  SPIxDMAxCHANNELx(_SPIx,RX)->PAR  = (u32)(&(SPI##_SPIx->DR));                                                      \
  SPIxDMAxCHANNELx(_SPIx,TX)->PAR  = (u32)(&(SPI##_SPIx->DR));                                                      \
                                                                                                    }while(0)
#define SPIx_DMA_InitInterrupt(_SPIx)                                                             do{               \
      NVIC_InitTypeDef NVIC_InitStructure;                                                                          \
      NVIC_PriorityGroupConfig(NVIC_PriorityGroup_2);                                                               \
      NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = 0;                                                     \
      NVIC_InitStructure.NVIC_IRQChannelSubPriority = 0;                                                            \
      NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;                                                               \
      NVIC_InitStructure.NVIC_IRQChannel = SPI##_SPIx##iCHRX;                                                       \
      NVIC_Init(&NVIC_InitStructure);                                                                               \
      NVIC_InitStructure.NVIC_IRQChannel = SPI##_SPIx##iCHTX;                                                       \
      NVIC_Init(&NVIC_InitStructure);                                                                               \
                                                                                                    }while(0)


////////////////////////////////////////////////////////////////////////////////
//extern CONFIG
////////////////////////////////////////////////////////////////////////////////

#define spi_SPI_MacroFunctionGeneratorConfig(_SPIx)                                         \
extern thdSPIWorkStruct SPI##_SPIx##hsSPI_Work;                                             \
extern void SPI##_SPIx##_CFG_SOFT(u8 delST, u8 delEN, u8 baudDIV);                          \
extern void SPI##_SPIx##_GPIO_SOFT_ON(void);                                                \
extern void SPI##_SPIx##_GPIO_OFF(void);                                                    \
extern void SPI##_SPIx##_GPIO_ON(void);                                                     \
extern void SPI##_SPIx##_Init(void);                                                        \
extern void SPI##_SPIx##_DMA_FrameMode(u8 isActive);                                        \
extern void SPI##_SPIx##_DMA_Start(void);                                                   \
extern void SPI##_SPIx##_DMA_WaitEnd(void);                                                 \
extern void SPI##_SPIx##_DMA_StartWaitEnd(void);                                            \
extern u8 SPI##_SPIx##_DMA_IsBusy(void);                                                    \
extern void SPI##_SPIx##_DMA_End(void);                                                     \
extern u8 SPI##_SPIx##_DMA_IsDisable(void);                                                 \
extern u8 SPI##_SPIx##_DMA_IsEnable(void);                                                  \
extern void SPI##_SPIx##_DMA_SetUp(u8 *bpTX, u8 *bpRX, u32 size, u8 incTX, u8 incRX);       \
extern void SPI##_SPIx##_WriteReadBlock(u8 *bufo, u8 *bufi, u32 size);                      \
extern void SPI##_SPIx##_WriteBlock(u8 *buf, u32 size);                                     \
extern void SPI##_SPIx##_ReadBlock(u8 *buf, u32 size);                                      \
extern void SPI##_SPIx##_Send_String(char *s);                                              \
extern void SPI##_SPIx##_DMA_DoInterruptRX(void);                                           \
extern void SPI##_SPIx##_DMA_DoInterruptTX(void);                                           \
extern void SPI##_SPIx##_DMA_SetInterrupt(tSPI_EventProc *Event);                           \
extern void SPI##_SPIx##_InitREG(void);                                                     \
extern void SPI##_SPIx##_DMA_Init(void);                                                    \
extern u32 SPI##_SPIx##_GPIO(u8 isOn)

#ifdef SPI0_CFG_DSIZE
spi_SPI_MacroFunctionGeneratorConfig(0);
#endif
#ifdef SPI1_CFG_DSIZE
spi_SPI_MacroFunctionGeneratorConfig(1);
#endif
#ifdef SPI2_CFG_DSIZE
spi_SPI_MacroFunctionGeneratorConfig(2);
#endif
#ifdef SPI3_CFG_DSIZE
spi_SPI_MacroFunctionGeneratorConfig(3);
#endif


////////////////////////////////////////////////////////////////////////////////
// SPI0/1 Swithcer
////////////////////////////////////////////////////////////////////////////////

extern u8 SPI0_AB_SEL;
static __inline void ON_SPI0_ACTIVE(void)
{
#ifdef SPI0_CFG_DSIZE
#ifdef SPI1_CFG_DSIZE
      SPI1_GPIO(hdSPI_GPIOMode_DISABLE);
#endif
      SPI0_GPIO(hdSPI_GPIOMode_ENABLE);
#endif
      SPI0_AB_SEL=0;
}
static __inline void ON_SPI1_ACTIVE(void)
{
#ifdef SPI1_CFG_DSIZE
#ifdef SPI0_CFG_DSIZE
      SPI0_GPIO(hdSPI_GPIOMode_DISABLE);
#endif
      SPI1_GPIO(hdSPI_GPIOMode_ENABLE);
#endif
      SPI0_AB_SEL=1;
}
static __inline void ON_SPI_ACTIVE(u8 num)
{
      if (num==0)
      {
        if (SPI0_AB_SEL!=0) ON_SPI0_ACTIVE();
      } else {
        if (SPI0_AB_SEL==0) ON_SPI1_ACTIVE();
      }
}



extern void SPIT_ReadBlock(u8 *buf, u32 size)                                      ;
extern void SPIT_WriteBlock(u8 *buf, u32 size)                                     ;
extern void SPIT_WriteReadBlock(u8 *bufo, u8 *bufi, u32 size)                      ;

#define SPI_NSS(_val_)      SPI0_NSSA(_val_)
extern vu8 SPI_CRC8;
extern u8 SPI_WriteReadByte(u8 b);
extern u8 SPI_WriteReadByte_mc_CRC(u8 b);
extern u8 SPI_WriteByte(u16 b);
extern void SPI_ReadBlock(u8 *buf, u32 size);
extern void SPI_WriteBlock(u8 *buf, u32 size);

extern void hdSPI_SoftPoolGoToSTART(thdSPIWorkStruct *HSW);
extern void hdSPI_SoftPoolGoToBYTEPROCESS(thdSPIWorkStruct *HSW);
extern u32 hdSPI_SoftPool(thdSPIWorkStruct *HSW, u32 MISOBIT);

#endif
