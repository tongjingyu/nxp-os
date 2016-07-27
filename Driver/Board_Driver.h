#ifndef _BOARD_DRIVER_H_
#define _BOARD_DRIVER_H_

#include <Include.h>



void Sys_Standby(void);
void BareDelay(uint32 i);
void MCU_Reset(void);
void Sys_Enter_Standby(void);

void assert_failed(uint8* file, uint32 line);
void Remap_SWJ_JTAGDisable(void);

void IWDG_Configuration(void);
void IWDG_Reload(void);
void Standby_Init(void);
void SysTick_Set(void);
#endif
