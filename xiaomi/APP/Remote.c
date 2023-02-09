#include "Remote.h"
#include "adc.h"
#include "nRF24L01.h"
#include "joystick.h"
#include "key.h"
#include "stdlib.h"
#include "string.h"


Remote_t Remote;



void Remote_Init(void)
{


}


void Remote_GetData(void)
{
  int32_t temp=0;
  
  Joystick_GetData();
#if 1
  temp=Joystick.Lx*1000/3700;
  
  temp=temp>1000?1000:temp<100?0:temp;
  Remote.ch1 = 1000+temp;
  
  temp=Joystick.Ly*1000/3700;
  temp=temp>1000?1000:temp<100?0:temp;
  Remote.ch2 = 1000+temp;
  
  temp=Joystick.Lz-600;
  temp=temp>1000?1000:temp<100?0:temp;
  Remote.ch3 = 1000+temp;
  
  temp=Joystick.Rx*1000/3700;
  temp=temp>1000?1000:temp<100?0:temp;
  Remote.ch4 = 1000+temp;
  
  temp=Joystick.Ry*1000/3700;
  temp=temp>1000?1000:temp<100?0:temp;
  Remote.ch5 = 1000+temp;
  
  temp=Joystick.Rz-2400;
  temp=temp>1000?1000:temp<100?0:temp;
  Remote.ch6 = 1000+temp;
#endif

#if 0
  Remote.ch1 = Joystick.Lx;
  Remote.ch2 = Joystick.Ly;
  Remote.ch3 = Joystick.Lz;
  Remote.ch4 = Joystick.Rx;
  Remote.ch5 = Joystick.Ry;
  Remote.ch6 = Joystick.Rz;
#endif  
  Remote.KeyStatusL = KeyList[KEY_2].Status;
  Remote.KeyPressedJumpL = KeyList[KEY_2].PressedJump;
  Remote.KeylongPressedL = KeyList[KEY_2].longPressed;
  Remote.KeylongPressedJumpL = KeyList[KEY_2].longPressedJump;
  
  Remote.KeyStatusR = KeyList[KEY_3].Status;
  Remote.KeyPressedJumpR = KeyList[KEY_3].PressedJump;
  Remote.KeylongPressedR = KeyList[KEY_3].longPressed;
  Remote.KeylongPressedJumpR = KeyList[KEY_3].longPressedJump;
  
}

uint8_t Remote_Check(uint8_t *data , uint16_t n)
{
  uint8_t temp=0;
  
  temp = data[0];
  for(int i=1; i<n; i++)
  {
    temp^=data[i];  
  }
  return temp;
}

void Remote_Transmit(void)
{
 static uint8_t txData[16];
  Remote_GetData();

  txData[0] = 0xA5;
  txData[1] = 0xA5;
  memcpy(&txData[2],Remote.TxBuff,13);
  txData[15]=Remote_Check(txData,15);
  
  if(NRF24L01_TxPacket(txData) != TX_OK)
  {
 //    HAL_GPIO_TogglePin(LED1_GPIO_Port,LED1_Pin);
    HAL_GPIO_WritePin(LED1_GPIO_Port,LED1_Pin,GPIO_PIN_RESET);
  }
  else
  {
    HAL_GPIO_WritePin(LED1_GPIO_Port,LED1_Pin,GPIO_PIN_SET);
  }

}




