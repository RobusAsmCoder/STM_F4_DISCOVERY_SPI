//////////////////////////////////////////////////////////////////////////////////////
// By Rob F. / Entire Group
//////////////////////////////////////////////////////////////////////////////////////

#include "SysType.h"
#include "rb_util.h"
#include "rb_util_ext.h"
#include "string.h"


u32 strIsDelimiter(char *s, const char *sd)
{
    char c;
    u32 i,n;
    i=0;
    while( (c=s[i])!=0 )//for (i=0; i<siz; i++)
    {
      char cc;
      n=0;
      while( (cc=sd[n])!=0 )
      {
        if ( c==cc ) return i | 0x80000000;
        n++;
      }
      i++;
    }
    return 0;
}

u32 strDivFixFirstZerroPoint(char *s)
{
      if (s[1]=='.')
      {
        rb_StrIns(&s[1],"0");
      }
      return strlen(s);
}

void strDivByDEC(char *s)
{
      u32 pos;
      u32 i;
      if (s[0])
      {
        if ( (s[0]!='-') && (s[0]!='+') )
        {
          rb_StrIns(&s[0],"+");
        }
        i=strDivFixFirstZerroPoint(s);
        pos = strIsDelimiter(s,".");
        if (pos>>24)  // find point
        {
          pos = pos & 255;
          s[pos]=s[pos-1];
          s[pos-1]='.';
        } else {
          rb_StrIns(&s[i-1],".");
        }
        
        strDivFixFirstZerroPoint(s);
        
        /*
        if (i<3)
        {
          rb_StrIns(&s[i-1],"0.");
        } else {
          rb_StrIns(&s[i-1],".");
        }
        */
      }
  
}

void strDelSpace(char *s)
{
    u32 i=0;
    while ( (s[i]==' ') && (s[i]) ) i++;
    strcpy(&s[0],&s[i]);
    i=strlen(s);
    while (i)
    {
      i--;
      if ( s[i]==' ' )
      {
        s[i]=0;
      } else break;
    }
}



