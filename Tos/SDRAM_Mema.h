#ifndef _SDRAM_MEMA_H_
#define _SDRAM_MEMA_H_
#include <Include.h>

typedef struct TOS_RMema_Ptr
{
	struct TOS_RMema_Ptr *NextPtr;
	uint32 Size;
}TOS_RMema_Ptr;

void RMema_Init(uint8 *Addr);
void *RMema_Malloc(uint32 Size);
void RMema_Free(void *Addr);
uint32 RMema_Length(void *Addr);
uint32 RMema_Count(void);
void *RMema_Extend(void *Addr,uint32 Size);
#endif
