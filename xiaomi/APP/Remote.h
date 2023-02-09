#ifndef __REMOTE_H
#define __REMOTE_H

#include "main.h"
#include "key.h"
#define TX_WIDTH 16
#pragma anon_unions

typedef struct
{ 
  union
  {
    uint8_t TxBuff[13];
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

//	uint16_t KeyStatus;
//	uint16_t lastKeyStatus;
//  
//	uint16_t keyPressedJump;
//	uint16_t keyReleaseJump;
//  
//	uint16_t longPressed;
//  uint16_t longPressedJump;
//  uint16_t longReleaseJump;
//  

void Remote_Init(void);
void Remote_Transmit(void);


/*-------------------------G L O B A L - T Y P E S----------------------------*/


#endif /* __REMOTE */

