//////////////////////////////////////////////////////////////////////////////////////
// By Rob F. / Entire Group
//////////////////////////////////////////////////////////////////////////////////////

#ifndef __RB_STRNUM_H
#define __RB_STRNUM_H

#include "SysType.h"

enum {
   rbs_fl_NOP     = 0,
   rbs_fl_DEC     = 1,
   rbs_fl_HEX     = 2,
   rbs_fl_BIN     = 3,
   rbs_fl_FLOAT   = 4,
};

typedef struct {
  u16       flag;           // Flag of conversion
  s64       Res_s64;        // Result of conversion DEC-64 / HEX-64 / BIN-64
  float     Res_Float;      // Result of conversion FLOAT-32
  double    Res_Double;     // Result of conversion FLOAT-48
  u8        Res_Size;       // Size in bits of conversion result 
}trbStrNum;


extern trbStrNum rbStrNum;

extern u8 rbsnGetBIN(u8 b);
extern u8 rbsnGetDEC(u8 b);
extern u8 rbsnGetHEX(u8 b);

extern u8 rbGetVarDEC(trbStrNum *snm, char *s, u8 maxstrsize);
extern u8 rbGetVarHEX(trbStrNum *snm, char *s, u8 maxstrsize);
extern u8 rbGetVarBIN(trbStrNum *snm, char *s, u8 maxstrsize);
extern u8 rbGetVarFLOAT(trbStrNum *snm, char *s, u8 maxstrsize);

extern u8 rbGetVar(trbStrNum *snm, char *s, u8 maxstrsize);

extern void rb_FloatToStr(double v, u8 prec, char* s);
extern void FloatToStr(double v, u8 prec, char* s);

#endif
