//////////////////////////////////////////////////////////////////////////////////////
// By Rob F. / Entire Group
//////////////////////////////////////////////////////////////////////////////////////

#include "SysType.h"
#include "string.h"
#include "rb_strnum.h"
#include "rb_util.h"



trbStrNum rbStrNum={
  .flag       = 0,
};



//Out: 0x00..0x01 = value convert
//     0xF0 = error converting
u8 rbsnGetBIN(u8 b)
{
    if ((b>='0') && (b<='1')) return b-'0';
    return 0xF0;
}
//Out: 0x00..0x09 = value convert
//     0xF0 = error converting
u8 rbsnGetDEC(u8 b)
{
    if ((b>='0') && (b<='9')) return b-'0';
    return 0xF0;
}
//Out: 0x00..0x0F = value convert
//     0xF0 = error converting
u8 rbsnGetHEX(u8 b)
{
    if ((b>='0') && (b<='9')) return b-'0';
    if ((b>='A') && (b<='F')) return b-'A'+10;
    if ((b>='a') && (b<='f')) return b-'a'+10;
    return 0xF0;
}

// Format DEC
//return true(size) if done
u8 rbGetVarDEC(trbStrNum *snm, char *s, u8 maxstrsize)
{
    u8 sign=0;
    u8 md=0;
    u8 size=0;
    s64 val=0;

    if (maxstrsize==0) maxstrsize = 255;
    while (maxstrsize)
    {
      u8 c=*s;
      if (c==0) break;
      if ( (c==' ') || (c=='+') )
      {
        s++;
        maxstrsize--;
      } else if (c=='-') {
        sign^=1;
        s++;
        maxstrsize--;
      } else {
        break;
      }
    }
    while (maxstrsize)
    {
      u8 b=*s;
      if (b==0) break;
      s++;
      maxstrsize--;
      if (b==' ')
      {
         md|=0x80;
      } else if ( (md&0x80)==0 ) {
        b=rbsnGetDEC(b);
        if (b<10)
        {
          val=(val*10)+b;
          size++;
        } else {
          size=0;
          break;
        }
      } else {
        size=0;
        break;
      }
    }
    if (size!=0)
    {
      if (sign) val = -val;
      snm->Res_s64 = val;
      snm->Res_Double = val;
      snm->Res_Float = val;
      snm->flag = rbs_fl_DEC;
      size <<= 2;
      snm->Res_Size = size;
    } else {
      snm->flag = rbs_fl_NOP;
    }
    return size;
}

// Format HEX
//  1. ????H
//  2. 0x????
//  3. $????
//return true(size) if done
u8 rbGetVarHEX(trbStrNum *snm, char *s, u8 maxstrsize)
{
    u8 sign=0;
    u8 md=0;    //1-$ 2-0x
    u8 size=0;
    s64 val=0;
    if (maxstrsize==0) maxstrsize = 255;
    while (maxstrsize)
    {
      u8 c=*s;
      if (c==0) break;
      if ( (c==' ') || (c=='+') )
      {
        s++;
        maxstrsize--;
      } else if (c=='-') {
        sign^=1;
        s++;
        maxstrsize--;
      } else if (c=='$') {
        md=1;     //Detected $
        s++;
        maxstrsize--;
        break;
      } else if (c=='0') {
        if (s[1]=='x')
        {
          md=2;     //Detected 0x
          s+=2;
          maxstrsize-=2;
        }
        break;
      } else {
        break;
      }
    }
    while (maxstrsize)
    {
      u8 b=*s;
      if (b==0) break;
      s++;
      maxstrsize--;
      if (b==' ')
      {
         md|=0x80;
      } else if ( (b=='h')||(b=='H') ) {
        if (md==0)
        {
          md = 3;     //Detected H
        } else {
          size=0;
          break;
        }
      } else if ( (md&0x80)==0 ) {
        b=rbsnGetHEX(b);
        if (b<16)
        {
          val=(val<<4)|b;
          size++;
        } else {
          size=0;
          break;
        }
      } else {
        size=0;
        break;
      }
    }
    if ((size) && ((md&0x7F)!=0))
    {
      if (sign) val = -val;
      snm->Res_s64 = val;
      snm->Res_Double = val;
      snm->Res_Float = val;
      snm->flag = rbs_fl_HEX;
      size <<= 2;
      snm->Res_Size = size;
    } else {
      snm->flag = rbs_fl_NOP;
      size=0;
    }
    return size;
}


// Format BIN
//return true(size) if done
u8 rbGetVarBIN(trbStrNum *snm, char *s, u8 maxstrsize)
{
    u8 sign=0;
    u8 md=0;
    u8 size=0;
    s64 val=0;

    if (maxstrsize==0) maxstrsize = 255;
    while (maxstrsize)
    {
      u8 c=*s;
      if (c==0) break;
      if ( (c==' ') || (c=='+') )
      {
        s++;
        maxstrsize--;
      } else if (c=='-') {
        sign^=1;
        s++;
        maxstrsize--;
      } else {
        break;
      }
    }
    while (maxstrsize)
    {
      u8 b=*s;
      if (b==0) break;
      s++;
      maxstrsize--;
      if (b==' ')
      {
         md|=0x80;
      } else if ( (b=='b')||(b=='B') ) {
        if (md==0)
        {
          md = 3;     //Detected B
        } else {
          size=0;
          break;
        }
      } else if ( (md&0x80)==0 ) {
        b=rbsnGetBIN(b);
        if (b<2)
        {
          val=(val<<1)|b;
          size++;
        } else {
          size=0;
          break;
        }
      } else {
        size=0;
        break;
      }
    }
    if ((size) && ((md&0x7F)!=0))
    {
      if (sign) val = -val;
      snm->Res_s64 = val;
      snm->Res_Double = val;
      snm->Res_Float = val;
      snm->flag = rbs_fl_BIN;
      snm->Res_Size = size;
    } else {
      snm->flag = rbs_fl_NOP;
      size=0;
    }
    return size;
}


// Format FLOAT
//return true(size) if done
u8 rbGetVarFLOAT(trbStrNum *snm, char *s, u8 maxstrsize)
{
    u8 sign=0;
    u8 md=0;
    u8 size=0;
    u8 sizd=0;
    s64 valA=0;
    s64 valB=0;
    s64 valD=1;

    if (maxstrsize==0) maxstrsize = 255;
    while (maxstrsize)
    {
      u8 c=*s;
      if (c==0) break;
      if ( (c==' ') || (c=='+') )
      {
        s++;
        maxstrsize--;
      } else if (c=='.') {
        break; 
      } else if (c=='-') {
        sign^=1;
        s++;
        maxstrsize--;
      } else {
        break;
      }
    }
    while (maxstrsize)
    {
      u8 b=*s;
      if (b==0) break;
      s++;
      maxstrsize--;
      if (b==' ')
      {
         md|=0x80;
      } else if ( (b=='f')||(b=='F') ) {
        if ((md&0x0F)==0)
        {
          md|= 3;     //Detected F
        } else {
          size=0;
          break;
        }
      } else if ( b=='.') {
        if (md==0)
        {
          md|= 0x10;     //Detected '.'
        } else {
          size=0;
          break;
        }
      } else if ((md&0x8F)==0) {
        b=rbsnGetDEC(b);
        if (b<10)
        {
          if ((md&0x10)==0)
          {
            valA=(valA*10)+b;
          } else {
            valB=(valB*10)+b;
            valD= valD*10 ;
            sizd++;
          }
          size++;
        } else {
          size=0;
          break;
        }
      } else {
        size=0;
        break;
      }
    }
    if ((size) && ((md&0x1F)!=0))
    {
      if (sign)
      {
//        if (valA)
//        {
//          valA = -valA;
//        } else {
//          valD = -valD;
//        }
        valA = -valA;
        valB = -valB;
      }
      snm->Res_s64 = valA;
      snm->Res_Double = (float)valA + ((float)valB/(float)valD);
      snm->Res_Float  = (float)valA + ((float)valB/(float)valD);
      snm->flag = rbs_fl_FLOAT;
      snm->Res_Size = size;
    } else {
      snm->flag = rbs_fl_NOP;
      size=0;
    }
    return size;
}

////////////////////////////////////

u8 rbGetVar(trbStrNum *snm, char *s, u8 maxstrsize)
{
    u8 size=0;
    size=rbGetVarHEX(snm, s, maxstrsize);
    if (size==0)
    {
      size=rbGetVarBIN(snm, s, maxstrsize);
      if (size==0)
      {
        size=rbGetVarDEC(snm, s, maxstrsize);
        if (size==0)
        {
          size=rbGetVarFLOAT(snm, s, maxstrsize);
        }
      }
    }
    return size;
}



////////////////////////////////////////////////////

s32 rb_Pow(s32 x, u8 n)
{
    s32 a = x, p = 1;
    while (n > 0)
    {
        if ((n & 1) != 0)
        {
          p *= a;
        }
        a *= a;
        n >>= 1;
    }
    return p;
}

void rb_FloatToStr(double v, u8 prec, char* s)
{
      u8 preb = prec >> 4;
      prec &= 0x0F;
      if(s != 0)
      {
        u8 n=0;
        if (v<0)
        {
          s[n++]='-';
          v=-v;
        }
        u32 d = (s32)v;
        u32 dd = (v-d) * rb_Pow(10,prec+1);
        if ( (prec==0) && (dd>=5) ) d++; //round !!!
        rb_IntToStr(d, preb, &s[n]);
        n=strlen(s);
        if (prec)
        {
          s[n++]='.';
          u8 mo = dd % 10;
          d = dd / 10;
          if (mo>=5) d++; //round !!!
          rb_IntToStr(d, prec, &s[n]);
        }
      }
}

void FloatToStr(double v, u8 prec, char* s)
{
      if(s != 0)
      {
        s32 wholePart = (s32)v;
        double fraction = v - wholePart;
        rb_IntToStr(wholePart, 0, s);
        if(fraction < 0)
        {
          fraction = -fraction;
        }
        if (prec > 0)
        {
          char* endString = s;
          while(*endString != 0) endString++;
          *endString = '.';
          endString++;
          while(prec > 0)
          {
            prec--;
            fraction *= 10;
            u8 d1 = ((u8)fraction) & 0x0F;
            *endString++ = '0' + d1;
            fraction -= d1;
          }
          *endString = 0;
        }
      }
}




