//////////////////////////////////////////////////////////////////////////////////////
// 
// Low level for STM32F100
// 
// By Rob F. / Entire Group
// 
//////////////////////////////////////////////////////////////////////////////////////

#include "SysType.h"
#include "hdadc.h"
#include "hardware.h"


void Setup_ADC(void)
{
    ADC_InitTypeDef ADC_init_structure; //Structure for adc confguration
    //Clock configuration
    RCC_APB2PeriphClockCmd(RCC_APB2Periph_ADC1, ENABLE); //The ADC1 is connected the APB2 peripheral bus thus we will use its clock source
    RCC_AHB1PeriphClockCmd(RCC_AHB1ENR_GPIOCEN, ENABLE); //Clock for the ADC port!! Do not forget about this one ;)
    //Analog pin configuration
//    GPIO_InitTypeDef GPIO_initStructre; //Structure for analog input pin
//    GPIO_StructInit(&GPIO_initStructre);
//    GPIO_initStructre.GPIO_Pin = GPIO_Pin_1 | GPIO_Pin_2; //The channel 11,12 is connected to PC1,2
//    GPIO_initStructre.GPIO_Mode = GPIO_Mode_AN; //The PC1,2 pin is configured in analog mode
//    GPIO_initStructre.GPIO_PuPd = GPIO_PuPd_NOPULL; //We don't need any pull up or pull down
//    GPIO_Init(GPIOC, &GPIO_initStructre); //Affecting the port with the initialization structure configuration
    GpioInit_ADCINX();
    GpioInit_ADCINY();
    //ADC structure configuration
    ADC_DeInit();
    ADC_init_structure.ADC_DataAlign = ADC_DataAlign_Right; //data converted will be shifted to right
    ADC_init_structure.ADC_Resolution = ADC_Resolution_12b; //Input voltage is converted into a 12bit number giving a maximum value of 4096
    ADC_init_structure.ADC_ContinuousConvMode = ENABLE; //the conversion is continuous, the input data is converted more than once
    ADC_init_structure.ADC_ExternalTrigConv = ADC_ExternalTrigConv_T1_CC1; // conversion is synchronous with TIM1 and CC1 (actually I'm not sure about this one :/)
    ADC_init_structure.ADC_ExternalTrigConvEdge = ADC_ExternalTrigConvEdge_None; //no trigger for conversion
    ADC_init_structure.ADC_NbrOfConversion = 1; //I think this one is clear :p
    ADC_init_structure.ADC_ScanConvMode = DISABLE; //The scan is configured in one channel
    ADC_Init(ADC1, &ADC_init_structure); //Initialize ADC with the previous configuration
    //Enable ADC conversion
    ADC_Cmd(ADC1, ENABLE);
    //Select the channel to be read from
    ADC_RegularChannelConfig(ADC1, ADC_Channel_11, 1, ADC_SampleTime_144Cycles);
    
    ADC_TempSensorVrefintCmd(ENABLE); 
}

u16 Read_ADC_GroupBIT(u32 sel)
{
  u8 channel=0;
  switch (sel)
  {
    case ADCINXwp_bit: channel=ADC_Channel_11;          break;
    case ADCINYwp_bit: channel=ADC_Channel_12;          break;
    case 0xFFFF      : channel=ADC_Channel_TempSensor;  break;
    case 0xFFFE      : channel=ADC_Channel_Vrefint;     break;
    case 0xFFFD      : channel=ADC_Channel_Vbat;        break;
  }
  ADC_RegularChannelConfig(ADC1, channel, 1, ADC_SampleTime_144Cycles);
  // Start the conversion
  ADC_SoftwareStartConv(ADC1);//Start the conversion
  
  // Wait until conversion completion
  while(!ADC_GetFlagStatus(ADC1, ADC_FLAG_EOC));//Processing the conversion
  DelayMS(5);
  // Get the conversion value
  return ADC_GetConversionValue(ADC1);
}

//u32 hdADC_ConvertVCC(u16 adcv, u16 vccref, u16 adcmuller)
//{
//      u32 adcT;
//      adcT *= 3000*adcmuller;
//      adcT /= 0x0FFF;
//      return adcT;
//}


