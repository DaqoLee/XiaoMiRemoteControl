#include "Remote.h"
#include "nRF24L01.h"
#include "string.h"
Remote_t Remote;



void Remote_Init(void)
{


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

uint8_t Remote_Receive(void)
{
  static uint8_t rxData[32];
  if(NRF24L01_RxPacket(rxData)==0)
  {
    if(rxData[0] == 0xA5 && rxData[1] == 0xA5 && rxData[15] == Remote_Check(rxData,15) )
    {
     // if(rxData[])
      memcpy(Remote.RxBuff,&rxData[2],13);
      return 1;
    }
    else
    {
      return 0;
    }
  }
  else
  {
    return 0;
  }
  
}


void Remote_Transmit(void)
{
  uint8_t txBuffer[16];
  
  txBuffer[0] = Remote.ch1;
  txBuffer[1] = Remote.ch1 <<8;

  txBuffer[2] = Remote.ch2;
  txBuffer[3] = Remote.ch2 <<8;

  txBuffer[4] = Remote.ch3;
  txBuffer[5] = Remote.ch3 <<8;

  txBuffer[6] = Remote.ch4;
  txBuffer[7] = Remote.ch4 <<8;

  txBuffer[8] = Remote.ch5;
  txBuffer[9] = Remote.ch5 <<8;

  txBuffer[10] = Remote.ch6;
  txBuffer[11] = Remote.ch6 <<8;
  
  NRF24L01_TxPacket(txBuffer);

}




