#include "Display.h"
#include "main.h"
#include "GUI_Paint.h"
#include "EPD_2in13_V3.h"
#include "stdio.h"
#include "stdlib.h"
#include "joystick.h"
#include "Remote.h"
UBYTE BlackImage[((EPD_2in13_V3_WIDTH % 8 == 0)? (EPD_2in13_V3_WIDTH / 8 ): (EPD_2in13_V3_WIDTH / 8 + 1)) * EPD_2in13_V3_HEIGHT];

int Display_Init(void)
{

    Debug("EPD_2in13_V3_test Demo\r\n");
    if(DEV_Module_Init()!=0){
        return -1;
    }

    Debug("e-Paper Init and Clear...\r\n");
		EPD_2in13_V3_Init();
    EPD_2in13_V3_Clear();
    
    Paint_NewImage(BlackImage, EPD_2in13_V3_WIDTH, EPD_2in13_V3_HEIGHT, 180, WHITE);
		Paint_Clear(WHITE);
    
    EPD_2in13_V3_Display_Base(BlackImage);
    DEV_Delay_ms(1000);
    
//  	Paint_NewImage(BlackImage, EPD_2in13_V3_WIDTH, EPD_2in13_V3_HEIGHT, 180, WHITE);  
//    Debug("Partial refresh\r\n");
//    Paint_SelectImage(BlackImage);
//    
//    DEV_Delay_ms(2000);
    return 0;
}

int Display_test(void)
{
   //Create a new image cache
//    UBYTE *BlackImage;
//    UWORD Imagesize = ((EPD_2in13_V3_WIDTH % 8 == 0)? (EPD_2in13_V3_WIDTH / 8 ): (EPD_2in13_V3_WIDTH / 8 + 1)) * EPD_2in13_V3_HEIGHT;
//   
//  if((BlackImage = (UBYTE *)malloc(Imagesize)) == NULL) {
//        Debug("Failed to apply for black memory...\r\n");
//       return -1;
//    }
    Debug("Paint_NewImage\r\n");
    Paint_NewImage(BlackImage, EPD_2in13_V3_WIDTH, EPD_2in13_V3_HEIGHT, 180, WHITE);
		Paint_Clear(WHITE);
   // DEV_Delay_ms(1000);
#if 0   //show image for array    
    Debug("show image for array\r\n");
    Paint_SelectImage(BlackImage);
//    Paint_Clear(WHITE);
//    Paint_DrawBitMap(gImage_2in13);

    EPD_2in13_V3_Display(BlackImage);
    DEV_Delay_ms(2000);
#endif

#if 1 // Drawing on the image
    DEV_Delay_ms(3000);
  	Paint_NewImage(BlackImage, EPD_2in13_V3_WIDTH, EPD_2in13_V3_HEIGHT, 90, WHITE);  	
    Debug("Drawing\r\n");
    //1.Select Image
    Paint_SelectImage(BlackImage);
    Paint_Clear(WHITE);
	
    // 2.Drawing on the image
    Paint_DrawPoint(5, 10, BLACK, DOT_PIXEL_1X1, DOT_STYLE_DFT);
    Paint_DrawPoint(5, 25, BLACK, DOT_PIXEL_2X2, DOT_STYLE_DFT);
    Paint_DrawPoint(5, 40, BLACK, DOT_PIXEL_3X3, DOT_STYLE_DFT);
    Paint_DrawPoint(5, 55, BLACK, DOT_PIXEL_4X4, DOT_STYLE_DFT);

    Paint_DrawLine(20, 10, 70, 60, BLACK, DOT_PIXEL_1X1, LINE_STYLE_SOLID);
    Paint_DrawLine(70, 10, 20, 60, BLACK, DOT_PIXEL_1X1, LINE_STYLE_SOLID);
    Paint_DrawRectangle(20, 10, 70, 60, BLACK, DOT_PIXEL_1X1, DRAW_FILL_EMPTY);
    Paint_DrawRectangle(85, 10, 135, 60, BLACK, DOT_PIXEL_1X1, DRAW_FILL_FULL);

    Paint_DrawLine(45, 15, 45, 55, BLACK, DOT_PIXEL_1X1, LINE_STYLE_DOTTED);
    Paint_DrawLine(25, 35, 70, 35, BLACK, DOT_PIXEL_1X1, LINE_STYLE_DOTTED);
    Paint_DrawCircle(45, 35, 20, BLACK, DOT_PIXEL_1X1, DRAW_FILL_EMPTY);
    Paint_DrawCircle(110, 35, 20, WHITE, DOT_PIXEL_1X1, DRAW_FILL_FULL);

    Paint_DrawString_EN(140, 15, "waveshare", &Font16, BLACK, WHITE);
    Paint_DrawNum(140, 40, 123456789, &Font16, BLACK, WHITE);

    Paint_DrawString_CN(140, 60, "ÄãºÃabc", &Font12CN, BLACK, WHITE);
    Paint_DrawString_CN(5, 65, "Î¢Ñ©µç×Ó", &Font24CN, WHITE, BLACK);

    EPD_2in13_V3_Display_Base(BlackImage);
    DEV_Delay_ms(3000);
#endif

#if 1   //Partial refresh, example shows time

    EPD_2in13_V3_Display_Base(BlackImage);
    DEV_Delay_ms(1000);
    
  	Paint_NewImage(BlackImage, EPD_2in13_V3_WIDTH, EPD_2in13_V3_HEIGHT, 180, WHITE);  
    Debug("Partial refresh\r\n");
    Paint_SelectImage(BlackImage);
	  //DEV_Delay_ms(3000);
    PAINT_TIME sPaint_time;
    sPaint_time.Hour = 12;
    sPaint_time.Min = 34;
    sPaint_time.Sec = 56;
    UBYTE num = 10;
    for (;;) {
        sPaint_time.Sec = sPaint_time.Sec + 1;
        if (sPaint_time.Sec == 60) {
            sPaint_time.Min = sPaint_time.Min + 1;
            sPaint_time.Sec = 0;
            if (sPaint_time.Min == 60) {
                sPaint_time.Hour =  sPaint_time.Hour + 1;
                sPaint_time.Min = 0;
                if (sPaint_time.Hour == 24) {
                    sPaint_time.Hour = 0;
                    sPaint_time.Min = 0;
                    sPaint_time.Sec = 0;
                }
            }
        }
        Paint_ClearWindows(150, 80, 150 + Font20.Width * 4, 80 + Font20.Height, WHITE);
        Paint_DrawTime(150, 80, &sPaint_time, &Font20, WHITE, BLACK);

        num = num - 1;
        if(num == 0) {
            break;
        }
		EPD_2in13_V3_Display_Partial(BlackImage);
        DEV_Delay_ms(500);//Analog clock 1s
    }
#endif

	Debug("Clear...\r\n");
	EPD_2in13_V3_Init();
    EPD_2in13_V3_Clear();
	
    Debug("Goto Sleep...\r\n");
    EPD_2in13_V3_Sleep();
    free(BlackImage);
//    BlackImage = NULL;
    DEV_Delay_ms(2000);//important, at least 2s
    // close 5V
    Debug("close 5V, Module enters 0 power consumption ...\r\n");
    DEV_Module_Exit();
    
    return 0;

}


int EPD_test(void)
{
   static uint16_t lx=2,ly=15;
   static char batStr[20];
    
    sprintf(batStr, "Bat:%d.%dV", Joystick.Battery/10, Joystick.Battery%10);
    Paint_ClearWindows(65, 0, 65 + Font12.Width * 8, 0 + Font12.Height, WHITE);
    Paint_DrawString_EN(65, 0, batStr, &Font12, WHITE, BLACK);
  
//    Paint_DrawRectangle(45, 15, 115, 45, BLACK, DOT_PIXEL_1X1, DRAW_FILL_EMPTY);
    Paint_ClearWindows(65, 20, 65 + Font20.Width * 4, 20 + Font20.Height, WHITE);
    Paint_DrawNum(65, 20, Remote.ch1, &Font20, BLACK, WHITE);
    Paint_DrawString_EN(20, 20, "Lx:", &Font16, WHITE, BLACK);
//    EPD_2in13_V3_Display_Partial(BlackImage);
//    DEV_Delay_ms(400);
 
//    Paint_DrawRectangle(45, 15, 115, 45, WHITE, DOT_PIXEL_1X1, DRAW_FILL_EMPTY);
//    Paint_DrawRectangle(45, 45, 115, 75, BLACK, DOT_PIXEL_1X1, DRAW_FILL_EMPTY);  
    Paint_ClearWindows(65, 50, 65 + Font20.Width * 4, 50 + Font20.Height, WHITE);
    Paint_DrawNum(65, 50, Remote.ch2, &Font20, BLACK, WHITE);
    Paint_DrawString_EN(20, 50, "Ly:", &Font16, WHITE, BLACK);
//    EPD_2in13_V3_Display_Partial(BlackImage);
//    DEV_Delay_ms(400);
  
//    Paint_DrawRectangle(45, 45, 115, 75, WHITE, DOT_PIXEL_1X1, DRAW_FILL_EMPTY);  
//    Paint_DrawRectangle(45, 75, 115, 115, BLACK, DOT_PIXEL_1X1, DRAW_FILL_EMPTY);  
    Paint_ClearWindows(65, 80, 65 + Font20.Width * 4, 80 + Font20.Height, WHITE);
    Paint_DrawNum(65, 80, Remote.ch3, &Font20, BLACK, WHITE);
    Paint_DrawString_EN(20, 80, "Lz:", &Font16, WHITE, BLACK);
  
    Paint_ClearWindows(65, 110, 65 + Font20.Width * 4, 110 + Font20.Height, WHITE);
    Paint_DrawNum(65, 110, Remote.ch4, &Font20, BLACK, WHITE);
    Paint_DrawString_EN(20, 110, "Rx:", &Font16, WHITE, BLACK);
  
    Paint_ClearWindows(65, 140, 65 + Font20.Width * 4, 140 + Font20.Height, WHITE);
    Paint_DrawNum(65, 140, Remote.ch5, &Font20, BLACK, WHITE);
    Paint_DrawString_EN(20, 140, "Ry:", &Font16, WHITE, BLACK);
  
    Paint_ClearWindows(65, 170, 65 + Font20.Width * 4, 170 + Font20.Height, WHITE);
    Paint_DrawNum(65, 170, Remote.ch6, &Font20, BLACK, WHITE);
    Paint_DrawString_EN(20, 170, "Rz:", &Font16, WHITE, BLACK);
  
    Paint_ClearWindows(65, 200, 65 + Font20.Width * 4, 200 + Font20.Height, WHITE);
    Paint_DrawNum(65, 200, Remote.KeyStatusL , &Font20, BLACK, WHITE);
    Paint_DrawString_EN(20, 200, "Kl:", &Font16, WHITE, BLACK);
  
    Paint_ClearWindows(65, 230, 65 + Font20.Width * 4, 230 + Font20.Height, WHITE);
    Paint_DrawNum(65, 230, Remote.KeyStatusR, &Font20, BLACK, WHITE);
    Paint_DrawString_EN(20, 230, "Kr:", &Font16, WHITE, BLACK);   
    
//    Paint_DrawRectangle(lx, ly-30, lx+15, ly, WHITE, DOT_PIXEL_1X1, DRAW_FILL_FULL);  
//    Paint_DrawRectangle(lx, ly, lx+15, ly+15, BLACK, DOT_PIXEL_1X1, DRAW_FILL_FULL);  
		EPD_2in13_V3_Display_Partial(BlackImage);
    DEV_Delay_ms(100);
    
 //   ly=ly+30;
    
 //   ly=ly>200?15:ly+30;
    
    return 0;
}

