/*****************************************************************************
* | File      	:   EPD_2in13_V2.h
* | Author      :   Waveshare team
* | Function    :   2.13inch e-paper V2
* | Info        :
*----------------
* |	This version:   V3.0
* | Date        :   2019-06-13
* | Info        :
* -----------------------------------------------------------------------------
* V3.0(2019-06-13):
* 1.Change name:
*    EPD_Reset() => EPD_2IN13_V2_Reset()
*    EPD_SendCommand() => EPD_2IN13_V2_SendCommand()
*    EPD_SendData() => EPD_2IN13_V2_SendData()
*    EPD_WaitUntilIdle() => EPD_2IN13_V2_ReadBusy()
*    EPD_Init() => EPD_2IN13_V2_Init()
*    EPD_Clear() => EPD_2IN13_V2_Clear()
*    EPD_Display() => EPD_2IN13_V2_Display()
*    EPD_Sleep() => EPD_2IN13_V2_Sleep()
* 2.add:
*    EPD_2IN13_V2_DisplayPartBaseImage()
* -----------------------------------------------------------------------------
* V2.0(2018-11-14):
* 1.Remove:ImageBuff[EPD_HEIGHT * EPD_WIDTH / 8]
* 2.Change:EPD_2IN13_V2_Display(UBYTE *Image)
*   Need to pass parameters: pointer to cached data
* 3.Change:
*   EPD_RST -> EPD_RST_PIN
*   EPD_DC -> EPD_DC_PIN
*   EPD_CS -> EPD_CS_PIN
*   EPD_BUSY -> EPD_BUSY_PIN
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
#ifndef _EPD_2IN13_V2_H_
#define _EPD_2IN13_V2_H_

//#include "DEV_Config.h"

// Display resolution

#include "main.h"
#include "stm32f1xx_hal.h"
#include "stm32f1xx_hal_gpio.h"
#include <stdint.h>
#include <stdio.h>
#include "spi.h"



#define EPD_2IN13_V2_WIDTH       122
#define EPD_2IN13_V2_HEIGHT      250

#define EPD_2IN13_V2_FULL			0
#define EPD_2IN13_V2_PART			1

/**
 * data
 
 
 #define ePA_DC_Pin GPIO_PIN_14
#define ePA_DC_GPIO_Port GPIOB
#define ePA_CS_Pin GPIO_PIN_8
#define ePA_CS_GPIO_Port GPIOA
#define ePA_RST_Pin GPIO_PIN_11
#define ePA_RST_GPIO_Port GPIOA
#define ePA_BUSY_Pin GPIO_PIN_12
#define ePA_BUSY_GPIO_Port GPIOA
**/
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


void EPD_2IN13_V2_Init(UBYTE Mode);
void EPD_2IN13_V2_Clear(void);
void EPD_2IN13_V2_Display(UBYTE *Image);
void EPD_2IN13_V2_DisplayPart(UBYTE *Image);
void EPD_2IN13_V2_DisplayPartBaseImage(UBYTE *Image);
void EPD_2IN13_V2_Sleep(void);

#endif
