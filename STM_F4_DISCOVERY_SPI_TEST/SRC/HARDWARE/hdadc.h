//////////////////////////////////////////////////////////////////////////////////////
// By Rob F. / Entire Group
//////////////////////////////////////////////////////////////////////////////////////

#ifndef __HDADC_H
#define __HDADC_H

#include "SysType.h"

#define hdADC_ConvertVCC(_adcv, _vccref, _adcmuller)      (((u32)(_adcv))*(((u32)(_vccref))*((u32)(_adcmuller))))/((u32)(0x0FFF))
#define hdADC_ConvertTEMP(_adcvcc, _adcmuller)      (   ((((s32)( ((s32)(_adcvcc)) - (760*((s32)(_adcmuller)))          ) \
                                                                * 400                                                   ) \
                                                                + (25000 * ((s32)(_adcmuller)))                         ) \
                                                                / 1000                                                  ) )
#define hdADC_ConvertTEMF(_adcvcc, _adcmuller)            ((((((double)(_adcvcc)/1000.0) - 0.760) / 0.0025) + 25.0) * (_adcmuller))
#define hdADC_CalcTemperatureD(_adcv, _vccref, _adcmuller)             hdADC_ConvertTEMP(hdADC_ConvertVCC(_adcv, _vccref, _adcmuller),_adcmuller)
#define hdADC_CalcTemperatureF(_adcv, _vccref, _adcmuller)             hdADC_ConvertTEMF(hdADC_ConvertVCC(_adcv, _vccref,          1),_adcmuller)

#define hdADC_REFIN_CONST                                                 1200


extern void Setup_ADC(void);
extern u16 Read_ADC_GroupBIT(u32 sel);

#endif
