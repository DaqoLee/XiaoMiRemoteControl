#include "User.h"
#include "main.h"
#include "stdio.h"
#include "usart.h"
#include "Remote.h"
#include "nRF24L01.h"
//CAN_RxHeaderTypeDef RXHeader;

//uint8_t TXmessage[8] = {0x00,0x11,0x22,0x33,0x44,0x55,0x66,0x77};
//uint8_t RXmessage[8];
//uint32_t pTxMailbox = 0;

int Yspeed=0, Rspeed=0;
void UserLoop(void)
{


	HAL_Delay(10);	
    
    
}




//void HAL_TIM_PeriodElapsedCallback(TIM_HandleTypeDef *htim)
//{
//  if(htim->Instance == TIM1 )
//	{
//    Remote_Transmit();

////    NRF24L01_TxPacket((uint8_t*) Remote.ADCBuff);
//    //ChassisCtrl(1000 , PS2.Ry ,  PS2.Ry);
//	}
//}


//  DMA�Ӵ��ڿ����ж�
void HAL_UARTEx_RxEventCallback(UART_HandleTypeDef *huart, uint16_t Size)
{
	if(huart->Instance == USART1)
	{
	//�����DMAΪNormalģʽ
	//HAL_UART_DMAStop(huart)//���DMAΪCircularģʽ���ص���������stop����
		//USER_FNC();//�û��Զ��庯��
//        
//        printf("[RX1:] %s\r\n",Rx1Buf);
//        
//        
//    
//        memset(Rx3Buf,0x00,sizeof(Rx1Buf));
//        
        
//		HAL_UARTEx_ReceiveToIdle_DMA(&huart1,Rx1Buf,102);//������������
	}
}

