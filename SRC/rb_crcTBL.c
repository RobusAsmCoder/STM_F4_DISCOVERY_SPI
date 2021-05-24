//////////////////////////////////////////////////////////////////////////////////////
// By Rob F. / Entire Group
//////////////////////////////////////////////////////////////////////////////////////

#include "SysType.h"
#include "rb_crcTBL.h"
#include <string.h>
//#include "rb_crc16.h"

//crcTblCheckListDefine(crcPtrList, 10);

#define TBCRC16TBV__1(_b, _crc)       TBCRC16P(((_b)+0x00), _crc)
#define TBCRC16TBV__2(_b, _crc)       TBCRC16TBV__1(((_b)+   0), _crc),   \
                                      TBCRC16TBV__1(((_b)+   1), _crc)
#define TBCRC16TBV__4(_b, _crc)       TBCRC16TBV__2(((_b)+   0), _crc),   \
                                      TBCRC16TBV__2(((_b)+   2), _crc)
#define TBCRC16TBV__8(_b, _crc)       TBCRC16TBV__4(((_b)+   0), _crc),   \
                                      TBCRC16TBV__4(((_b)+   4), _crc)
#define TBCRC16TBV_16(_b, _crc)       TBCRC16TBV__8(((_b)+   0), _crc),   \
                                      TBCRC16TBV__8(((_b)+   8), _crc)
#define TBCRC16TBV_32(_b, _crc)       TBCRC16TBV_16(((_b)+   0), _crc),   \
                                      TBCRC16TBV_16(((_b)+  16), _crc)
#define TBCRC16TBV_64(_b, _crc)       TBCRC16TBV_32(((_b)+   0), _crc),   \
                                      TBCRC16TBV_32(((_b)+  32), _crc)
#define TBCRC16TBV128(_b, _crc)       TBCRC16TBV_64(((_b)+   0), _crc),   \
                                      TBCRC16TBV_64(((_b)+  64), _crc)
#define TBCRC16TBV256(_b, _crc)       TBCRC16TBV128(((_b)+   0), _crc),   \
                                      TBCRC16TBV128(((_b)+ 128), _crc)

#define TBCRC16STEP(_tbl, _b, _crc)   ((_crc)<<8) ^ _tbl[((_crc)>>8)^(_b)]

const u16 TBL16TBLCCITT[257] = {
  TBCRC16TBV256(0x00 ,TBCRC16CCITT),
  TBCRC16CCITT
};

u16 TBCRC16_BYTE(u16 *tbl, u8 b, u16 crc)
{
//    const u8 pos = (crc>>8)^b;
//    return (crc<<8) ^ tbl[pos];
    return TBCRC16STEP(tbl, b, crc);
}

u16 TBCRC16_BUF(u16 *tbl, u8 *buf, u32 siz)
{
    u16 crc = tbl[256];
    while(siz)
    {
      crc = TBCRC16STEP(tbl, *buf++, crc);
      siz--;
    }
    return crc;
}

////////////////////////


u16 TBCRC16_BlockCheck(tcrcPointerCheckList *CPL, u8 *buf, u16 size)
{
    u16 res = 1;
    u32 n;
    const u16 sizchk = sizeof(tcrcPointerCheck);
    const u16 sizlst = sizchk * CPL->cnt;
    if (!CPL->isInited)
    {
      memset( &CPL->LST[0], 0, sizlst);
      CPL->isInited = 1;
    }
    for(n=0; n<CPL->cnt; n++)
    {
      if ( CPL->LST[n].p )
      {
        if ( (CPL->LST[n].p==buf) && (CPL->LST[n].size==size) )
        {
          const u16 crc = TBCRC16_BUFCCITT(buf, size);
          if (CPL->LST[n].crc == crc)
          {
            res = 0;
          } else {
            CPL->LST[n].crc = crc;
          }
          break;
        }
      } else {
        const u16 crc = TBCRC16_BUFCCITT(buf, size);
        CPL->LST[n].p = buf;
        CPL->LST[n].size = size;
        CPL->LST[n].crc = crc;
        break;
      }
    }
    if (n==CPL->cnt)
    {
      n--;
      memcpy(&CPL->LST[0], &CPL->LST[1], sizlst-sizchk);
      const u16 crc = TBCRC16_BUFCCITT(buf, size);
      CPL->LST[n].p = buf;
      CPL->LST[n].size = size;
      CPL->LST[n].crc = crc;
    }
    return res;
}


//#define lcdsblocks    32
//tcrcPointerCheck lcdsblockList[lcdsblocks];



/*
vu16 TBL16TEST[256];
void TBCRC16_Test(void)
{
    for (u32 n=0; n<256; n++)
    {
      u8 b=n;
      //vu16 c16 = TBCRC16_BYTE((u16 *)(&TBL16TBLCCITT), b, TBCRC16CCITT); //TBL16TBLCCITT[b];//TBCRC16P(b, TBCRC16CCITT);
      TBL16TEST[n] = crc16_byte(b, TBCRC16CCITT);
    }
    char buf[] = "Hello World";
    vu16 crc16A = TBCRC16CCITT;
    vu16 crc16B = TBCRC16CCITT;
    vu16 crc16C = TBCRC16CCITT;
    for (u32 n=0; n<sizeof(buf); n++)
    {
      u8 b = buf[n];
      crc16A = TBCRC16_BYTE((u16 *)(&TBL16TBLCCITT[0]), b, crc16A);
      crc16B = crc16_byte(b, crc16B);
      crc16C = TBCRC16_BYTE((u16 *)(&TBL16TEST[0]), b, crc16C);
      __nop();
    }
    
    
    __nop();
}
*/
