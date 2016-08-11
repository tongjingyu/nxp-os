#include <Include.h>
#include <CPU.h>
#include "lpc177x_8x_systick.h"
#include "lpc177x_8x_eeprom.h"
void MCU_Reset()
{
	__disable_fault_irq();      // STM32 软复位  
	NVIC_SystemReset();
}
void SysTick_Set()
{
	SYSTICK_InternalInit(1);

	//Enable System Tick interrupt
	SYSTICK_IntCmd(ENABLE);

	//Enable System Tick Counter
	SYSTICK_Cmd(ENABLE);
}
extern volatile int OS_TimeMS;
void SysTick_Handler(void)
{
 OS_TimeMS++; 
	SYSTICK_ClearCounterFlag();
	Tos_SysTick();

}
/**************************************************************************************
 Func: 单片机内部flash编程
 Time: 2015-07-25
 Ver.:	1.0  	
 Note: Size为数据长度用sizeof（实体）
**************************************************************************************/
void Flash_WriteData(uint32 Addr,void *Data,uint16 Size)
{
	uint8 i;
	EEPROM_Init();
	for(i = 0; i < EEPROM_PAGE_NUM; i++)
	{
		EEPROM_Erase(i);
	}
	EEPROM_Write(0,Addr/64,(void*)Data,MODE_8_BIT,Size);
}
/**************************************************************************************
 Func: Flash内部falsh数据
 Time: 2015-07-25
 Ver.:	1.0  	
 Note: Size为数据长度用sizeof（实体）
**************************************************************************************/
void Flash_ReadData(uint32 Addr,void *Data,uint16 Size)
{
	EEPROM_Init();
	EEPROM_Read(0,Addr/64,(void*)Data,MODE_8_BIT,Size);
}
