/*********************************************************************
*                SEGGER MICROCONTROLLER GmbH & Co. KG                *
*        Solutions for real time microcontroller applications        *
**********************************************************************
*                                                                    *
*        (c) 2003-2010     SEGGER Microcontroller GmbH & Co KG       *
*                                                                    *
*        Internet: www.segger.com    Support:  support@segger.com    *
*                                                                    *
**********************************************************************

----------------------------------------------------------------------
File        : LCDConf.c
Purpose     : Display controller configuration (single layer)
---------------------------END-OF-HEADER------------------------------
*/

#include "SEGGER.h"
#include "BSP.h"
#include "GUI.h"
#include "GUIDRV_Lin.h"

#include "LPC177x_8x.h"
#include "system_LPC177x_8x.h"
#include <..\USER\Prj_Haoyu\GLCD.h>
int _TouchX,_TouchY;
#ifdef __ICCARM__
  #pragma diag_suppress=Pe188  // Avoid "enumerated type mixed with another type" warning as we are not using enumerated values from CMSIS files for NVIC_* parameters
#endif

/*********************************************************************
*
*       Layer configuration (to be modified)
*
**********************************************************************
*/

#ifndef USE_24BPP_MODE
  #define USE_24BPP_MODE  0  // Selection if using 16 BPP or 24 BPP mode
#endif

//
// Physical display size
//
#define XSIZE_PHYS GLCD_X_SIZE
#define YSIZE_PHYS GLCD_Y_SIZE

//
// Virtual display size
//
#define VXSIZE_PHYS (XSIZE_PHYS)
#define VYSIZE_PHYS (YSIZE_PHYS)

//
// Color conversion
//
#if USE_24BPP_MODE
  #define COLOR_CONVERSION  GUICC_888
#else
#define COLOR_CONVERSION  GUICC_M565/*GUICC_M565: RB SWAP GUICC_565:RB NORMAL*/
#endif

//
// Pixel width in bytes
//
#if USE_24BPP_MODE
  #define PIXEL_WIDTH  4
#else
  #define PIXEL_WIDTH  2
#endif

//
// Display driver
//
#if USE_24BPP_MODE
  #define DISPLAY_DRIVER  &GUIDRV_Lin_32_API
#else
  #define DISPLAY_DRIVER  &GUIDRV_Lin_16_API
#endif

//
// Video RAM address
//
//#define VRAM_ADDR_PHYS  (U32)&_aVRAM[0]

//
// Touch controller settings
//
#define TOUCH_AD_LEFT         220       //触摸屏最左端ADC采样值
#define TOUCH_AD_RIGHT        3910      //触摸屏最右端ADC采样值
#define TOUCH_AD_TOP          3556       //触摸屏最上端ADC采样值
#define TOUCH_AD_BOTTOM       240      //触摸屏最下端ADC采样值
#define TOUCH_TIMER_INTERVAL  10        //触摸屏采样间隔

/*********************************************************************
*
*       Configuration checking
*
**********************************************************************
*/
#ifndef   VXSIZE_PHYS
  #define VXSIZE_PHYS XSIZE_PHYS
#endif
#ifndef   VYSIZE_PHYS
  #define VYSIZE_PHYS YSIZE_PHYS
#endif
#ifndef   VRAM_ADDR_PHYS
  #define VRAM_ADDR_PHYS  0
#endif
#ifndef   VRAM_ADDR_VIRT
  #define VRAM_ADDR_VIRT  0
#endif

#ifndef   XSIZE_PHYS
  #error Physical X size of display is not defined!
#endif
#ifndef   YSIZE_PHYS
  #error Physical Y size of display is not defined!
#endif
#ifndef   COLOR_CONVERSION
  #error Color conversion not defined!
#endif
#ifndef   DISPLAY_DRIVER
  #error No display driver defined!
#endif



/*********************************************************************
*
*       Static data
*
**********************************************************************
*/

#if GUI_SUPPORT_TOUCH  // Used when touch screen support is enabled

static U8 _HasTouch;

//
// OS timers
//
// static OS_TIMER _TouchTimer;

/*********************************************************************
*
*       Function Prototypes
*
**********************************************************************
*/

/*********************************************************************
*
*       Local functions
*
**********************************************************************
*/

#endif

/*********************************************************************
*
*       _SetDisplayOrigin()
*/
static void _SetDisplayOrigin(int x, int y) {
  (void)x;
  //
  // Set start address for display data and enable LCD controller
  //
  LPC_LCD->UPBASE = LCD_VRAM_BASE_ADDR + (y * XSIZE_PHYS * PIXEL_WIDTH);  // Needs to be set, before LCDC is enabled
}

#if GUI_SUPPORT_TOUCH  // Used when touch screen support is enabled



static void _CheckTouch(void) {

}


#endif  // GUI_SUPPORT_TOUCH


static void _InitController(unsigned LayerIndex) {
  //
  // Set display size and video-RAM address
  //
  LCD_SetSizeEx (XSIZE_PHYS, YSIZE_PHYS, LayerIndex);
  LCD_SetVSizeEx(VXSIZE_PHYS, VYSIZE_PHYS, LayerIndex);
  LCD_SetVRAMAddrEx(LayerIndex, (void*)LCD_VRAM_BASE_ADDR);
  //
  // Init LCD
  //

#if GUI_SUPPORT_TOUCH  // Used when touch screen support is enabled
  {
    U32 TouchOrientation;
    TouchOrientation = (GUI_MIRROR_X * LCD_GetMirrorXEx(0)) |
                       (GUI_MIRROR_Y * LCD_GetMirrorYEx(0)) |
                       (GUI_SWAP_XY  * LCD_GetSwapXYEx (0)) ;
    GUI_TOUCH_SetOrientation(TouchOrientation);
    if (LCD_GetSwapXYEx(0)) {
      GUI_TOUCH_Calibrate(GUI_COORD_X, 0, XSIZE_PHYS, TOUCH_AD_LEFT, TOUCH_AD_RIGHT);   // x axis swapped
      GUI_TOUCH_Calibrate(GUI_COORD_Y, 0, YSIZE_PHYS, TOUCH_AD_TOP , TOUCH_AD_BOTTOM);  // y axis swapped
    } else {
      GUI_TOUCH_Calibrate(GUI_COORD_X, 0, XSIZE_PHYS, TOUCH_AD_LEFT, TOUCH_AD_RIGHT);   // x axis
      GUI_TOUCH_Calibrate(GUI_COORD_Y, 0, YSIZE_PHYS, TOUCH_AD_TOP , TOUCH_AD_BOTTOM);  // y axis
    }
  }
#endif
}

/*********************************************************************
*
*       Public code
*
**********************************************************************
*/

/*********************************************************************
*
*       LCD_X_Config
*
* Purpose:
*   Called during the initialization process in order to set up the
*   display driver configuration.
*/
void LCD_X_Config(void) {
  //
  // Set display driver and color conversion for 1st layer
  //
  GUI_DEVICE_CreateAndLink(DISPLAY_DRIVER, COLOR_CONVERSION, 0, 0);
  //
  // Display driver configuration, required for Lin-driver
  //
  LCD_SetPosEx     (0, 0, 0);
  if (LCD_GetSwapXYEx(0)) {
    LCD_SetSizeEx  (0, YSIZE_PHYS , XSIZE_PHYS);
    LCD_SetVSizeEx (0, VYSIZE_PHYS, VXSIZE_PHYS);
  } else {
    LCD_SetSizeEx  (0, XSIZE_PHYS , YSIZE_PHYS);
    LCD_SetVSizeEx (0, VXSIZE_PHYS, VYSIZE_PHYS);
  }
  LCD_SetVRAMAddrEx(0, (void*)VRAM_ADDR_VIRT);
  //
  // Set user palette data (only required if no fixed palette is used)
  //
  #if defined(PALETTE)
    LCD_SetLUTEx(0, PALETTE);
  #endif
}

/*********************************************************************
*
*       LCD_X_DisplayDriver
*
* Purpose:
*   This function is called by the display driver for several purposes.
*   To support the according task the routine needs to be adapted to
*   the display controller. Please note that the commands marked with
*   'optional' are not cogently required and should only be adapted if
*   the display controller supports these features.
*
* Parameter:
*   LayerIndex - Index of layer to be configured
*   Cmd        - Please refer to the details in the switch statement below
*   pData      - Pointer to a LCD_X_DATA structure
*
* Return Value:
*   < -1 - Error
*     -1 - Command not handled
*      0 - Ok
*/
int LCD_X_DisplayDriver(unsigned LayerIndex, unsigned Cmd, void * pData) {
  int r;
  LCD_X_SETORG_INFO      * pSetOrg;

  (void) LayerIndex;

  switch (Cmd) {
  //
  // Required
  //
  case LCD_X_INITCONTROLLER:
    _InitController(0);
    return 0;
  case LCD_X_SETORG:
    pSetOrg = (LCD_X_SETORG_INFO *)pData;
    _SetDisplayOrigin(pSetOrg->xPos, pSetOrg->yPos);
    return 0;
  default:
    r = -1;
  }
  return r;
}

/*********************************************************************
*
*       Global functions for GUI touch
*
**********************************************************************
*/

#if GUI_SUPPORT_TOUCH  // Used when touch screen support is enabled

/*********************************************************************
*
*       GUI_TOUCH_X_ActivateX()4
*
* Function decription:
*   Called from GUI, if touch support is enabled.
*   Switches on voltage on X-axis,
*   prepares measurement for Y-axis.
*   Voltage on Y-axis is switched off.
*/
void GUI_TOUCH_X_ActivateX(void) {

  _CheckTouch();
  if (_HasTouch) {
   
  }
}

/*********************************************************************
*
*       GUI_TOUCH_X_ActivateY()2
*
* Function decription:
*   Called from GUI, if touch support is enabled.
*   Switches on voltage on Y-axis,
*   prepares measurement for X-axis.
*   Voltage on X-axis is switched off.
*/
void GUI_TOUCH_X_ActivateY(void) {
  if (_HasTouch) {
   
  }
}

/*********************************************************************
*
*       GUI_TOUCH_X_MeasureX()3
*
* Function decription:
*   Called from GUI, if touch support is enabled.
*   Measures voltage of X-axis.
*/
int  GUI_TOUCH_X_MeasureX(void) {
  if (_HasTouch)
	{
    return _TouchX;
  }
  return -1;
}

/*********************************************************************
*
*       GUI_TOUCH_X_MeasureY()1
*
* Function decription:
*   Called from GUI, if touch support is enabled.
*   Measures voltage of Y-axis.
*/
int  GUI_TOUCH_X_MeasureY(void) {
  if (_HasTouch) 
	{
    return _TouchY;
  }
  return -1;
}
#include <..\USER\Prj_Haoyu\TouchPanel.h>
#include <tos.h>
void Task_Touch(void *Tags)
{
	Coordinate  *C;
	TP_Init();
	while(1)
	{
		GUI_TOUCH_Exec();
		C=Read_Ads7846();
		if((C->x<10000)&(C->y<10000))
		{	
				_HasTouch=1;
				_TouchX=C->x;
				_TouchY=C->y;
				GUI_TOUCH_Exec();
		}else _HasTouch=0;
		Tos_TaskDelay(10);
	}
}
#endif 
