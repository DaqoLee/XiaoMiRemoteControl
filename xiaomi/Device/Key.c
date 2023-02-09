/**
  ******************************************************************************
  * @file    key.c
  * @author  Hare
  * @version V1.0
  * @date    
  * @brief   按键应用函数接口
  ******************************************************************************
  */

#include "key.h"



Key_t KeyList[KEY_COUNT];
uint8_t keyCode = 0;

GPIOPins_t Keys_GPIO[KEY_COUNT] = 
{
	{0, KEY1_GPIO_Port, KEY1_Pin},
  {0, KEY2_GPIO_Port, KEY2_Pin},
  {0, KEY3_GPIO_Port, KEY3_Pin}
};

/**
  * @brief  按键初始化
  * @param  None
  * @retval None
  */
void Key_Init(void)
{		
//	for(int i = 0; i < KEY_COUNT; i++){
//		GPIO_QuickInit(Keys_GPIO[i].GPIO_CLK, Keys_GPIO[i].GPIOx, Keys_GPIO[i].GPIO_Pin, GPIO_Mode_IPU);
//	}
}

void Key_Process(void)
{
	keyCode = 0;
	for(int i = 0; i < KEY_COUNT; i++)
  {
    
		KeyList[i].ReleaseJump = 0;
		KeyList[i].PressedJump = 0;
    KeyList[i].longPressedJump = 0;
    KeyList[i].longReleaseJump = 0;
		
		KeyList[i].Status = !HAL_GPIO_ReadPin(Keys_GPIO[i].Port, Keys_GPIO[i].Pin);
		
		if (KeyList[i].Status != KeyList[i].lastStatus)
    {
			if(KeyList[i].Status)
      {
				keyCode = 1 << i;
				KeyList[i].PressedJump = KeyList[i].Status;
			}
			else
      {
        if(KeyList[i].longPressed)
        {
          KeyList[i].longReleaseJump = KeyList[i].lastStatus;
        }
        else
        {
          KeyList[i].ReleaseJump = KeyList[i].lastStatus;
        }
				KeyList[i].longPressed = 0;
				KeyList[i].timer = 0;
			}
		}
    else
    {
      if(KeyList[i].Status && (KeyList[i].longPressed == 0))
      {
        KeyList[i].timer++;
        if(KeyList[i].timer > 100)
        {
          KeyList[i].longPressed = KeyList[i].Status;
          KeyList[i].longPressedJump = KeyList[i].Status;
          KeyList[i].timer = 0;
        }
      }
    }
		KeyList[i].lastStatus = KeyList[i].Status;
	}
}




