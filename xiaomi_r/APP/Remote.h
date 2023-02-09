#ifndef __REMOTE_H
#define __REMOTE_H

#include "main.h"

#define RX_WIDTH 32

#pragma anon_unions

typedef struct
{
  union
  {
    uint8_t RxBuff[13];
		struct
		{
			uint16_t ch1;																		
			uint16_t ch2;    
			uint16_t ch3;
			uint16_t ch4;
			uint16_t ch5;
			uint16_t ch6;
      
      uint8_t KeyStatusL:1;
      uint8_t KeyPressedJumpL:1;
      uint8_t KeylongPressedJumpL:1;
      uint8_t KeylongPressedL:1;
      uint8_t KeyStatusR:1;
      uint8_t KeyPressedJumpR:1;
      uint8_t KeylongPressedJumpR:1;
      uint8_t KeylongPressedR:1;
		};
  };
}Remote_t;

extern Remote_t Remote;



void Remote_Init(void);
void Remote_Transmit(void);
uint8_t Remote_Receive(void);

/*-------------------------G L O B A L - T Y P E S----------------------------*/


#endif /* __REMOTE */

