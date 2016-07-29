#include <Include.h>
#include <Driver_Include.h>
#include <Tools_Include.h>

uint8 KeyIn_Tos_TaskID=Tos_TaskNull;




uint8 Tos_GetKeyValue()
{
	uint8 Value=0;
	if( !(GPIO_ReadValue(0)&(1<<17)))Value=Key_Up;
	if( !(GPIO_ReadValue(0)&(1<<18)))Value=Key_Down;
	if( !(GPIO_ReadValue(0)&(1<<19)))Value=Key_Left;
	if( !(GPIO_ReadValue(0)&(1<<20)))Value=Key_Right;
	if( !(GPIO_ReadValue(0)&(1<<21)))Value=Key_Right;
	return Value;
}

/******************************************************************************
 Func:钩子
 Time: 2014年国庆节前夕
 Ver.: V1.0
 Note:获取键盘
******************************************************************************/
void Tos_TaskGetIO_InPut()
{
	KeyIn_Tos_TaskID=Tos_TaskCurrent;
}
void Task_GetKey(void *Tags)
{
	uint8 Value;
	MGUI_KeyMsg KeyMsg;
	PINSEL_ConfigPin(0,17,0);	   /* P0.17 - GPIO */
	PINSEL_ConfigPin(0,18,0);	   /* P0.18 - GPIO */
	PINSEL_ConfigPin(0,19,0);	   /* P0.19 - GPIO */
	PINSEL_ConfigPin(0,20,0);	   /* P0.20 - GPIO */
	PINSEL_ConfigPin(0,21,0);	   /* P0.21 - GPIO */
	PINSEL_ConfigPin(0,22,0);	   /* P0.22 - GPIO */
	GPIO_SetDir(0, (1<<17), 0);    /* Input Mode */
	GPIO_SetDir(0, (1<<18), 0);	   /* Input Mode */
	GPIO_SetDir(0, (1<<19), 0);	   /* Input Mode */
	GPIO_SetDir(0, (1<<20), 0);	   /* Input Mode */
	GPIO_SetDir(0, (1<<21), 0);	   /* Input Mode */
	GPIO_SetDir(0, (1<<22), 0);	   /* Input Mode */
	while(1)
	{
		 Tos_TaskDelay(10);
		 Value=Tos_GetKeyValue();
		 if(Value)
		 {
			KeyMsg.KeyValue=Value; 
		 Tos_TaskPutQmsg(KeyIn_Tos_TaskID,KeyBoard_Hand,sizeof(MGUI_KeyMsg),&KeyMsg);
		 Tos_TaskDelay(300);
		 }
	}
}
