#include "User.h"
#include "main.h"
#include "stdio.h"
#include "usart.h"
#include "joystick.h"
#include "Remote.h"
#include "nRF24L01.h"
//CAN_RxHeaderTypeDef RXHeader;

//uint8_t TXmessage[8] = {0x00,0x11,0x22,0x33,0x44,0x55,0x66,0x77};
//uint8_t RXmessage[8];
//uint32_t pTxMailbox = 0;

int Yspeed=0, Rspeed=0;
void UserLoop(void)
{

//	PS2_ReadData();  

//  Yspeed=Joystick.Joystick_Y*10 + PS2.Ly *10;
//  Rspeed=Joystick.Joystick_X*10 + PS2.Lx *10;
//  printf("%d %d %d \r\n", Joystick.Joystick_X, Joystick.Joystick_Y, Joystick.Joystick_Z);

	HAL_Delay(10);	
    
    
//    printf("PS2Rx:%03d \t",PS2.Rx);   
//    printf("PS2Lx:%03d \t",PS2.Lx);   
//    printf("PS2Ry:%03d \t",PS2.Ry);   
//    printf("PS2Ly:%03d \t",PS2.Ly);   
//    printf("PS2Key:%d  \r\n",PS2.Ly);   

}




void HAL_TIM_PeriodElapsedCallback(TIM_HandleTypeDef *htim)
{
  if(htim->Instance == TIM1 )
	{
    Remote_Transmit();
    Key_Process();
//    NRF24L01_TxPacket((uint8_t*) Remote.ADCBuff);
    //ChassisCtrl(1000 , PS2.Ry ,  PS2.Ry);
	}
}


