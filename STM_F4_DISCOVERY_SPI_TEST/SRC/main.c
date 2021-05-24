//////////////////////////////////////////////////////////////////////////////////////
// By Rob F. / Entire Group
//////////////////////////////////////////////////////////////////////////////////////
#include "SysType.h"
#include "hardware.h"
#include "interface.h"
#include "hdinterrupt.h"
#include "SPI_Tets.h"

int main(void)
{
    hdIntSwitchInterruptToRAM();
    Init();
    SPI_BuferTransferInit();
    while(1)
    {
      __nop();
    }
}



