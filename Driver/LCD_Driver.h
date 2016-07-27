#ifndef _LCD_DRIVER_H_
#define _LCD_DRIVER_H_
#include <Include.h>



#define White          0xFFFF
#define Black          0x0000
#define Grey           0xF7DE
#define Blue           0x001F
#define Blue2          0x051F
#define Red            0xF800
#define Magenta        0xF81F
#define Green          0x07E0
#define Yellow         0xFFE0

#define WHITE          0xFFFF
#define BLACK          0x0000
#define GRAY           0xF7DE
#define BLUE           0x001F
#define BLUE2          0x051F
#define RED            0xF800
#define MAGENTA        0xF81F
#define GREEN          0x07E0
#define CYAN           0x7FFF
#define YELLOW         0xFFE0
#define DGRAY          Grey
#define DCYAN          CYAN
#define PURPLE         MAGENTA
#define DGREEN          0x07E0

void LCD_Draw_LineY(uint16 SX,uint16 SY,uint16 H,uint16 Color); 
void LCD_Draw_LineX(uint16 SX,uint16 SY,uint16 W,uint16 Color);
void LCD_Fill_LineX(uint16 SX,uint16 SY,uint16 H,uint16 *Cbuffer);
void LCD_Fill_LineY(uint16 SX,uint16 SY,uint16 H,uint16 *Cbuffer);
void LCD_Draw_DotLineY(uint16 SX,uint16 SY,uint16 H,uint16 Fcolor,uint16 Bcolor);
void LCD_Draw_DotLineX(uint16 SX,uint16 SY,uint16 W,uint16 Fcolor,uint16 Bcolor);
void LCD_Clear_Area(uint16 SX,uint16 SY,uint16 EX,uint16 EY,uint16 Color);
extern uint16 LCD_Get_Pixel(uint16 X,uint16 Y);
extern uint8 DeviceId_LCD;
void TGui_Draw_Line(uint16 X0,uint16 Y0,uint16 X1,uint16 Y1,uint16 Color);
void DeviceMount_Lcd(void);

#endif

