/*****************************************************************************
* | File      	:   EPD_2Iin13_V3.h
* | Author      :   Waveshare team
* | Function    :   2.13inch e-paper V3
* | Info        :
*----------------
* |	This version:   V1.1
* | Date        :   2021-10-30
* | Info        :
* -----------------------------------------------------------------------------
#
# Permission is hereby granted, free of charge, to any person obtaining a copy
# of this software and associated documnetation files (the "Software"), to deal
# in the Software without restriction, including without limitation the rights
# to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
# copies of the Software, and to permit persons to  whom the Software is
# furished to do so, subject to the following conditions:
#
# The above copyright notice and this permission notice shall be included in
# all copies or substantial portions of the Software.
#
# THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
# IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
# FITNESS OR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
# AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
# LIABILITY WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
# OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN
# THE SOFTWARE.
#
******************************************************************************/
#ifndef __EPD_2in13_V3_H_
#define __EPD_2in13_V3_H_
#include "main.h"
#include "stdio.h" 
//#include "DEV_Config.h"

// Display resolution
#define EPD_2in13_V3_WIDTH       122
#define EPD_2in13_V3_HEIGHT      250

#define UBYTE   uint8_t
#define UWORD   uint16_t
#define UDOUBLE uint32_t

/**
 * e-Paper GPIO
**/
#define EPD_RST_PIN     ePA_RST_GPIO_Port, ePA_RST_Pin
#define EPD_DC_PIN      ePA_DC_GPIO_Port, ePA_DC_Pin
#define EPD_CS_PIN      ePA_CS_GPIO_Port, ePA_CS_Pin
#define EPD_BUSY_PIN    ePA_BUSY_GPIO_Port, ePA_BUSY_Pin

/**
 * GPIO read and write
**/
#define DEV_Digital_Write(_pin, _value) HAL_GPIO_WritePin(_pin, _value == 0? GPIO_PIN_RESET:GPIO_PIN_SET)
#define DEV_Digital_Read(_pin) HAL_GPIO_ReadPin(_pin)

/**
 * delay x ms
**/
#define DEV_Delay_ms(__xms) HAL_Delay(__xms);

#define DEBUG 1
#if DEBUG
	#define Debug(__info,...) printf("Debug: " __info,##__VA_ARGS__)
#else
	#define Debug(__info,...)  
#endif



void EPD_2in13_V3_Init(void);
void EPD_2in13_V3_Clear(void);
void EPD_2in13_V3_Display(UBYTE *Image);
void EPD_2in13_V3_Display_Base(UBYTE *Image);
void EPD_2in13_V3_Display_Partial(UBYTE *Image);
void EPD_2in13_V3_Sleep(void);

#endif
