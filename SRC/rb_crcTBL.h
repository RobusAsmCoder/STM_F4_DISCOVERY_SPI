//////////////////////////////////////////////////////////////////////////////////////
// By Rob F. / Entire Group
//////////////////////////////////////////////////////////////////////////////////////
#ifndef __RB_CRCTBL_H__
#define __RB_CRCTBL_H__

#include "SysType.h"

#define TBCRC16CCITT            ((u16)(0x15AE))
#define TBCRC16X(_b,_crc)       ((u16)(((u16)(_crc))^((u8)(_b))))
#define TBCRC16T(_b,_crc)       ((TBCRC16X(_b,_crc)^(TBCRC16X(_b,_crc)<<4))&0x00FF)
#define TBCRC16P(_b,_crc)       ((TBCRC16X(_b,_crc)>>8)^(TBCRC16T(_b,_crc)<<8)^(TBCRC16T(_b,_crc)<<3)^(TBCRC16T(_b,_crc)>>4))



typedef struct {
  u8     *p;
  u16     size;
  u16     crc;
}tcrcPointerCheck;

typedef struct {
  u16                   cnt;
  u16                   isInited;
  tcrcPointerCheck     *LST;
}tcrcPointerCheckList;

#define crcTblCheckListDefine(_name, _cnt)          \
  tcrcPointerCheck      _name##List[_cnt];          \
  tcrcPointerCheckList  _name={                     \
    .isInited = 0,                                  \
    .cnt      = _cnt,                               \
    .LST      = _name##List,                        \
  }

//extern tcrcPointerCheckList crcPtrList;
  
extern const u16 TBL16TBLCCITT[257];

#define TBCRC16_BUFCCITT(_buf, _siz)    TBCRC16_BUF((u16 *)(&TBL16TBLCCITT), _buf, _siz)

extern u16 TBCRC16_BYTE(u16 *tbl, u8 b, u16 crc);
extern u16 TBCRC16_BUF(u16 *tbl, u8 *buf, u32 siz);
//extern void TBCRC16_Test(void);
extern u16 TBCRC16_BlockCheck(tcrcPointerCheckList *CPL, u8 *buf, u16 size);


#endif
