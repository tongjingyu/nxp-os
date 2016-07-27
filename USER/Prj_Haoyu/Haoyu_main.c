#include <Include.h>
#include <SDRAM_K4S561632C_32M_16BIT.h>
#include <..\USER\Prj_Haoyu\AsciiLib.c>
#include <..\USER\Prj_Haoyu\GLCD.c>
#include <..\USER\Prj_Haoyu\GBK_Lib.c>
#include <LCD_Driver.c>
#include <GUI_Include.c>
#include <Tos_Mema.h>
#include <..\MGUI\Menu_Base.c>
#include <..\USER\Prj_Haoyu\Page.c>
#include <..\USER\Prj_Haoyu\PageApp.c>






void Task0(void *Tags)
{
	SDRAM_32M_16BIT_Init();	  
	LCD_Initializtion();
	GLCD_Clear(Green);
	while(1)
	{
		Tos_TaskDelay(100);
	}
}
void Task1(void *Tags)
{
	CLKPWR_ConfigPPWR(CLKPWR_PCONP_PCGPIO, ENABLE);
	GPIO_SetDir(2, 1<<21, GPIO_DIRECTION_OUTPUT);
	GPIO_OutputValue(2,1<<21,0);
	while(1)
	{
		GPIO_OutputValue(2,1<<21,0);
		Tos_TaskDelay(100);
		GPIO_OutputValue(2,1<<21,1);
		Tos_TaskDelay(100);
	}
}
const TaskInitList TaskList[]={
{Task0,Null,"Task0",2000},
{MUI_Task,(void *)&MenuHome[0],"MUI_Task",2000},
{Task1,Null,"Task0",2000},
{Null},
};

int main(void)
{
	Mema_Init(&MemBuf[0]);
	DeviceList_Init();
	Tos_ListCreate(TaskList);
	while(1);
}



