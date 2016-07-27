/****************************************Copyright (c)**************************************************                         
**
**                                 http://www.powermcu.com
**
**--------------File Info-------------------------------------------------------------------------------
** File name:			GLCD.h
** Descriptions:		None
**
**------------------------------------------------------------------------------------------------------
** Created by:			AVRman
** Created date:		2012-6-20
** Version:				1.0
** Descriptions:		The original version
**
**------------------------------------------------------------------------------------------------------
** Modified by:			
** Modified date:	
** Version:
** Descriptions:		
********************************************************************************************************/

#ifndef __GLCD_H 
#define __GLCD_H

/* Includes ------------------------------------------------------------------*/
#include "lpc_types.h"
#include "SDRAM_K4S561632C_32M_16BIT.h"

/* Private define ------------------------------------------------------------*/
#define LCD_VRAM_BASE_ADDR 	    ((uint32_t)SDRAM_BASE_ADDR + 0x00100000)
#define LCD_CURSOR_BASE_ADDR 	((uint32_t)0x20088800)


#define GLCD_X_SIZE        480	         /* LCD Horizontal length */
#define GLCD_Y_SIZE        272		     /* LCD Vertical length */
#define LCD_XSIZE        480	         /* LCD Horizontal length */
#define LCD_YSIZE        272		     /* LCD Vertical length */
#define LCD_XMAX         479
#define LCD_YMAX         271
#define PPL                GLCD_X_SIZE   /* Pixels per line */

#define HSW                20             /* HSYNC pulse width */
#define HFP                2             /* Horizontal front porch */
#define HBP                2            /* Horizontal back porch */

#define LPP                GLCD_Y_SIZE   /* Lines per panel */
#define VSW                15             /* VSYNC pulse width */
#define VFP                2             /* Vertical front porch */
#define VBP                2             /* Vertical back porch */

#define ACB                1             /* AC bias frequency (not used) */
#define IVS				   1             /* ? Invert VSYNC */
#define IHS                1             /* ? Invert HSYNC */
#define IPC                0             /* ? Invert panel clock */
#define CPL                PPL           /* Clock per line (identical to pixels per line) */
#define BPP                6             /* Bits per pixel b110 = 16 bpp 5:6:5 mode */
#define BGR                1             /* Swap red and blue */
#define LCDTFT             1             /* LCD TFT panel */
#define OPT_CLK            (8*1000000)      /* Optimal clock rate (Hz) between 1-8.22 MHz */



#define BCD_BIT            26        /* Bypass pixel clock divider */

#define GLCD_PWR_ENA_DIS_DLY  10000

/* LCD color */
#define Black           0x0000      /*   0,   0,   0 */
#define Navy            0x000F      /*   0,   0, 128 */
#define DarkGreen       0x03E0      /*   0, 128,   0 */
#define DarkCyan        0x03EF      /*   0, 128, 128 */
#define Maroon          0x7800      /* 128,   0,   0 */
#define Purple          0x780F      /* 128,   0, 128 */
#define Olive           0x7BE0      /* 128, 128,   0 */
#define LightGrey       0xC618      /* 192, 192, 192 */
#define DarkGrey        0x7BEF      /* 128, 128, 128 */
#define Blue            0x001F      /*   0,   0, 255 */
#define Green           0x07E0      /*   0, 255,   0 */
#define Cyan            0x07FF      /*   0, 255, 255 */
#define Red             0xF800      /* 255,   0,   0 */
#define Magenta         0xF81F      /* 255,   0, 255 */
#define Yellow          0xFFE0      /* 255, 255, 0   */
#define White           0xFFFF      /* 255, 255, 255 */
/* Private function prototypes -----------------------------------------------*/
void GLCD_Cursor_Config(int config);
void GLCD_Cursor_Enable(int cursor);
void GLCD_Cursor_Disable(void);
void GLCD_Move_Cursor(int x, int y);
void GLCD_Copy_Cursor (const uint32_t *pCursor, int cursor, int size);
void GLCD_Init (void);
void GLCD_Clear(uint16_t color);
void GLCD_SetPixel_16bpp (uint16_t Xpos, uint16_t Ypos, uint16_t color);
void GLCD_DrawLine( uint16_t x0, uint16_t y0, uint16_t x1, uint16_t y1 , uint16_t color );

#endif

/*********************************************************************************************************
      END FILE
*********************************************************************************************************/
