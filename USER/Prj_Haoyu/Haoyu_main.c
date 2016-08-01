#include <Include.h>
#include <SDRAM_K4S561632C_32M_16BIT.h>
#include <..\USER\Prj_Haoyu\AsciiLib.c>
#include <..\USER\Prj_Haoyu\GLCD.c>
#include <..\USER\Prj_Haoyu\GBK_Lib.c>
#include <LCD_Driver.c>
#include <GUI_Include.c>
#include <Tos_Mema.h>
#include <..\MGUI\Menu_Base.c>
#include <..\USER\Prj_Haoyu\IO_Driver.c>
#include <..\USER\Prj_Haoyu\TouchPanel.c>
#include <..\USER\Prj_Haoyu\Page.c>
#include <..\USER\Prj_Haoyu\PageApp.c>
#include <Usart_Driver.h>
#include <WM.h>
#include <MywindowDLG.c>

extern void Task_Touch(void *Tags);
extern int _TouchX,_TouchY;
void DebugCall(void *Buf,uint8 Length)
{
	USART_WriteLine(UART_0,(char *)Buf,Length);
}
void Task0(void *Tags)
{
	CLKPWR_ConfigPPWR(CLKPWR_PCONP_PCGPIO, ENABLE);
	GPIO_SetDir(2, 1<<21, GPIO_DIRECTION_OUTPUT);
	GPIO_OutputValue(2,1<<21,0);
	DeBug_SetCallBack(DebugCall);
	while(1)
	{
		GPIO_OutputValue(2,1<<21,0);
		Tos_TaskDelay(100);
		GPIO_OutputValue(2,1<<21,1);
		Tos_TaskDelay(100);
	}
}

static GUI_POINT aPoints[]={
{0,0},
{70,-30},
{0,50},
{-70,-30}
};
void Task1(void *Tags)
{
	Coordinate  *C;
	TP_Init();

//		GUI_AA_SetFactor(3);
//	GUI_AA_DrawArc(60*3,60*3,50*3,50*3,0,180);
//	GUI_SetBkColor(GUI_WHITE);
//	GUI_Clear();
//	GUI_SetColor(GUI_DARKBLUE);
//	GUI_AA_FillRoundedRect(10,10,54,54,5);
//	GUI_SetPenSize(10);
//	GUI_SetColor(GUI_RED);
//	GUI_AA_FillPolygon(aPoints,countof(aPoints),150,40);
//	
//	GUI_AA_EnableHiRes();
//	GUI_SetBkColor(GUI_WHITE);
//	GUI_SetColor(GUI_DARKBLUE);
//	GUI_SetPenSize(5);
//	GUI_AA_SetFactor(3);
//	GUI_AA_FillCircle(160*3,120*3,80*3);
	while(1)
	{
		C=Read_Ads7846();
		if((C->x<10000)&(C->y<10000))
			{
				USART_WriteLine(UART_0,"x=%dy=%d\r\n",C->x,C->y);
			}
		Tos_TaskDelay(100);
	}
}
extern void _InitController(unsigned LayerIndex);
void Task3(void *Tags)
{	
	SDRAM_32M_16BIT_Init();	  
	LCD_Initializtion();
	GLCD_Clear(0);
  WM_SetCreateFlags(WM_CF_MEMDEV);
	LCD_X_DisplayDriver(0,LCD_X_INITCONTROLLER,0);
  GUI_Init();
	CreateMywindow();
	GUI_Exec();
	GUI_CURSOR_Show();
	while(1)
	{
			// CreateMywindow();
	GUI_Exec();
//		GUI_AA_SetFactor(3);
//		GUI_SetColor(GUI_BLACK);
//		GUI_AA_FillRoundedRect(10,10,54,54,5);
//		Tos_TaskDelay(1000);
//		GUI_SetColor(GUI_WHITE);
//		GUI_AA_FillRoundedRect(10,10,54,54,5);
//		GUI_AA_FillRoundedRect(100,100,154,154,5);
//		GUI_AA_DrawLine(50,50,70,70);
//		GUI_AA_DrawLine(70,50,50,70);
//		GUI_DispDecAt(i++,20,20,4);
		Tos_TaskDelay(100);
	}
}
void Task4(void *Tags)
{	
	while(1)
	{
	GUI_Exec();
	Tos_TaskDelay(100);
	}
}
const TaskInitList TaskList[]={
{
Task0,Null,"Task0",2000},
//{MUI_Task,(void *)&MenuHome[0],"MUI_Task",2000},
{Task1,Null,"Task0",2000},
{Task3,Null,"Task0",2000},
{Task_Touch,Null,"Task0",2000},
{Task_GetKey,Null,"Task0",2000},
{Task4,Null,"Task0",2000},
{Null},
};

int main(void)
{
	Mema_Init(&MemBuf[0]);
	DeviceList_Init();
	DeviceMount_Usart(UART_0);
	Tos_ListCreate(TaskList);
	while(1);
}



