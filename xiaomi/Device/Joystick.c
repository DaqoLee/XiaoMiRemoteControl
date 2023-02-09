#include "joystick.h"
#include "stdlib.h"
#include "adc.h"

Joystick_t Joystick ;




void Joystick_Init(void)
{
  
  HAL_ADCEx_Calibration_Start(&hadc1);
  HAL_ADC_Start_DMA(&hadc1,(uint32_t*)Joystick.ADCBuff,ADC_BUFFER_SIZE);
  
  
}


void Joystick_GetData(void)
{
  uint32_t temp =0;
  float battery =0;
  
  for(int i=0; i<ADC_CHANNEL_NUM; i++)
  {
    for(int j=0; j<ADC_SAMPLE_NUM; j++)
    {
      temp += Joystick.ADCBuff[i + (j * ADC_CHANNEL_NUM)];
    }
    Joystick.JoystickBuff[i] = (temp+5)/ADC_SAMPLE_NUM;
    temp = 0;
  }
  
  battery=Joystick.Battery*3.3/4096*20;
  
  Joystick.Battery = battery;
}




