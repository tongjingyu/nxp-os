#include <Include.h>
#include <CPU.h>
#include "lpc177x_8x_systick.h"
void MCU_Reset()
{
	
}
void SysTick_Set()
{
	SYSTICK_InternalInit(1);

	//Enable System Tick interrupt
	SYSTICK_IntCmd(ENABLE);

	//Enable System Tick Counter
	SYSTICK_Cmd(ENABLE);
}
void SysTick_Handler(void)
{

	SYSTICK_ClearCounterFlag();
	Tos_SysTick();

}
