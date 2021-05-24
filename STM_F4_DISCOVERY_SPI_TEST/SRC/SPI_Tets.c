//////////////////////////////////////////////////////////////////////////////////////
// By Rob F. / Entire Group
//////////////////////////////////////////////////////////////////////////////////////
#include "SysType.h"
#include "SPI_Tets.h"
#include "hardware.h"
#include "interface.h"


u8 testSPIbufO[4] = {0x8F, 0xAA, 0x00, 0xF0};
u8 testSPIbufI[sizeof(testSPIbufO)];

void SPI_BuferTransferStart(void)
{
      SPI3_DMA_SetUp((u8 *)(&testSPIbufO), (u8 *)(&testSPIbufI), sizeof(testSPIbufO) ,1,0);
      SPI3_DMA_Start();
}

u32 lerfuSpiBufEvent(u32 v)
{
    if (v & SPI_FLAG_MD_ST)
    {
      SPI3_NSSA(0);
    }
    if (v & SPI_FLAG_MD_EN)
    {
      SPI3_DMA_End();
      SPI3_NSSA(1);
      testSPIbufO[2]++;
      SPI_BuferTransferStart();
    }
    return 0;
}

void SPI_BuferTransferInit(void)
{
    SPI3_Init();
    SPI3_DMA_Init();
    SPI3_GPIO_ON();
    SPI3_DMA_SetInterrupt(&lerfuSpiBufEvent);
    SPI_BuferTransferStart(); //SPI3_WriteReadBlock( (u8 *)&testSPIbufO, (u8 *)&testSPIbufI, sizeof(testSPIbufO) );
}

