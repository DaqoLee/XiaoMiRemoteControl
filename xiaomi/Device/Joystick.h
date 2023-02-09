#ifndef __JOYSTICK_H__
#define __JOYSTICK_H__

#include "stm32f1xx_hal.h"
#pragma anon_unions


#define ADC_CHANNEL_NUM 7
#define ADC_SAMPLE_NUM 10
#define ADC_BUFFER_SIZE (ADC_CHANNEL_NUM*ADC_SAMPLE_NUM)

typedef struct
{
  uint16_t ADCBuff[ADC_BUFFER_SIZE];
  union
  {
    uint16_t JoystickBuff[ADC_CHANNEL_NUM];
		struct
		{
			uint16_t Ly;																		
			uint16_t Lx;    
			uint16_t Ry;
			uint16_t Rx;
			uint16_t Rz;
			uint16_t Lz;
      uint16_t Battery;
		};
  };

}Joystick_t;


extern Joystick_t Joystick;


void Joystick_Init(void);
void Joystick_GetData(void);
#endif


