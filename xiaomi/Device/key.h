#ifndef __KEY_H
#define __KEY_H

#include "main.h"

#define	KEY_ON	 1		//按键按下
#define	KEY_OFF	 0		//按键放开

typedef struct{
	uint32_t Clk;
	GPIO_TypeDef* Port;
	uint16_t Pin;
}GPIOPins_t;

typedef enum
{
  KEY_1 = 0,
  KEY_2,
  KEY_3,
  KEY_COUNT,
} key_item_t;

typedef struct{
  
//  GPIOPins_t KeyGPIO;
	uint16_t Status;
	uint16_t lastStatus;
  
	uint16_t PressedJump;
	uint16_t ReleaseJump;
  
	uint16_t longPressed;
  uint16_t longPressedJump;
  uint16_t longReleaseJump;
  
	uint16_t timer;
}Key_t;


extern Key_t KeyList[KEY_COUNT];

void Key_Init(void);
void Key_Process(void);

//extern TaskHandle_t xHandleTaskKey;
//void vTaskKey(void *pvParameters);

#endif /* __KEY_H */
