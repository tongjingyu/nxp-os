#include <Include.h>
#include "SDRAM_K4S561632C_32M_16BIT.h"
#include <..\USER\Prj_Haoyu\AsciiLib.c>
#include <..\USER\Prj_Haoyu\GLCD.c>



















void Task0(void *Tags)
{
	SDRAM_32M_16BIT_Init();	  
	GLCD_Init();
		GLCD_Clear(Black);
	Tos_TaskDelay(1000);

	GLCD_Clear(White);
Tos_TaskDelay(1000);

	GLCD_Clear(Red);
Tos_TaskDelay(1000);

	GLCD_Clear(Green);
Tos_TaskDelay(1000);
	GLCD_Clear(Blue);
Tos_TaskDelay(1000);
	GUI_Text((GLCD_X_SIZE - 120 ) / 2, GLCD_Y_SIZE / 2 - 8, "http://www.trtos.com", White, Blue);
	GUI_Text( ( GLCD_X_SIZE - 136 ) / 2, GLCD_Y_SIZE / 2 + 8, "Embeded System Development", White, Blue);
	while(1)
	{
		Tos_TaskDelay(100);
	}
}
void Task1(void *Tags)
{

	while(1)
	{
		Tos_TaskDelay(100);
	}
}
const TaskInitList TaskList[]={
{Task0,Null,"Task0",2000},
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



