/*********************************************************************
*                SEGGER Microcontroller GmbH & Co. KG                *
*        Solutions for real time microcontroller applications        *
**********************************************************************
*                                                                    *
*        (c) 1996 - 2011  SEGGER Microcontroller GmbH & Co. KG       *
*                                                                    *
*        Internet: www.segger.com    Support:  support@segger.com    *
*                                                                    *
**********************************************************************

** emWin V5.12 - Graphical user interface for embedded applications **
emWin is protected by international copyright laws.   Knowledge of the
source code may not be used to write a similar product.  This file may
only be used in accordance with a license and should not be re-
distributed in any way. We appreciate your understanding and fairness.
----------------------------------------------------------------------
File        : GUI_X.C
Purpose     : Config / System dependent externals for GUI
---------------------------END-OF-HEADER------------------------------
*/

#include "LPC177x_8x.h"
#include "system_LPC177x_8x.h"
#include "GUI.h"
#include "lpc177x_8x_systick.h"
#include <tos.h>
uint8 DeviceId_GUI=DeviceNull;
void SysTick_Handler(void);

/*********************************************************************
*
*       Global data
*/
volatile int OS_TimeMS;

/*-----------------------------------------------------------------------------
  SysTick_Handler
*----------------------------------------------------------------------------*/


/*********************************************************************
*
*      Timing:
*                 GUI_X_GetTime()
*                 GUI_X_Delay(int)

  Some timing dependent routines require a GetTime
  and delay function. Default time unit (tick), normally is
  1 ms.
*/

int GUI_X_GetTime(void) { 
  return OS_TimeMS; 
}


/*******************************************************************************
* Function Name  : DelayUS
* Description    : 延时1us
* Input          : - cnt: 延时值
* Output         : None
* Return         : None
* Attention		 : None
*******************************************************************************/

void GUI_X_Delay(int ms) 
{ 

	Tos_TaskDelay(ms);
}

/*********************************************************************
*
*       GUI_X_ExecIdle
*
* Note:
*  Called if WM is in idle state
*/

void GUI_X_ExecIdle(void) {Tos_TaskDelay(10);}
/*********************************************************************
*
*      Logging: OS dependent

Note:
  Logging is used in higher debug levels only. The typical target
  build does not use logging and does therefor not require any of
  the logging routines below. For a release build without logging
  the routines below may be eliminated to save some space.
  (If the linker is not function aware and eliminates unreferenced
  functions automatically)

*/

void GUI_X_Log     (const char *s) { GUI_USE_PARA(s); }
void GUI_X_Warn    (const char *s) { GUI_USE_PARA(s); }
void GUI_X_ErrorOut(const char *s) { GUI_USE_PARA(s); }

/*********************************************************************
*
*       GUI_X_Init()
*
* Note:
*     GUI_X_Init() is called from GUI_Init is a possibility to init
*     some hardware which needs to be up and running before the GUI.
*     If not required, leave this routine blank.
*/

void GUI_X_Init(void) { }


unsigned long GUI_X_GetTaskId(void) { return Tos_TaskCurrent;}

void GUI_X_InitOS(void) {

}

void GUI_X_Lock(void) { 
	Tos_TaskGetDev(DeviceId_GUI,0);
}

void GUI_X_Unlock(void) { 
	  Tos_TaskDropDev(DeviceId_GUI);
}
#include <SDRAM_K4S561632C_32M_16BIT.h>
#include <..\USER\Prj_Haoyu\GLCD.h>
void EMUI_Init()
{
	SDRAM_32M_16BIT_Init();	  
	LCD_Initializtion();
  GUI_Init();
}
void DeviceMount_GUI()
{
	if(DeviceId_GUI==DeviceNull)DeviceId_GUI=DeviceId_Index++;
	Tos_Device_Tab[DeviceId_GUI].DeviceName="GUI";
	Tos_Device_Tab[DeviceId_GUI].DeviceOwnerId=Null;
	Tos_Device_Tab[DeviceId_GUI].DeviceVirtue=DV_Task;//格外注意，组设备非字节设备
	Tos_Device_Tab[DeviceId_GUI].DeviceState=Ready;
	Tos_Device_Tab[DeviceId_GUI].Init=EMUI_Init;
	Tos_Device_Tab[DeviceId_GUI].Exit=Null;
}
/*************************** End of file ****************************/
