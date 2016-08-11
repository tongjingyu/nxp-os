#include <SDRAM_Mema.h>
#include <TTS.h>
#define  FONT_BASE_ADDR (0xA0000000 + 0x00100000+(1024*1024*14))
TOS_RMema_Ptr *RootRMema;
uint8 DeviceId_RAM=DeviceNull;
/********************************************************************************
 Func: 内存初始化
 Time: 2015-09-14
 Ver.: V1.0
 Note; 传入内存堆地址
********************************************************************************/
void RMema_Init(uint8 *Addr)
{
	RootRMema=(TOS_RMema_Ptr *)Addr;//绑定位置到内存块头
	RootRMema->NextPtr=0;
	RootRMema->Size=sizeof(TOS_RMema_Ptr);
}
/********************************************************************************
 Func: 分配内存
 Time: 2015-09-14
 Ver.: V1.0
 Note; 去掉了父节点
********************************************************************************/
void *RMema_Malloc(uint32 Size)
{
	TOS_RMema_Ptr *P=RootRMema,*TP;
	Size+=sizeof(TOS_RMema_Ptr);
	while(P->NextPtr!=0)
	{
		if(((uint32)P->NextPtr-(uint32)P-P->Size)>=Size)//当当前节点和后节点之间能插入请求块
		{
			TP=(TOS_RMema_Ptr *)((uint32)P+P->Size);
			TP->Size=Size;
			TP->NextPtr=P->NextPtr;
			P->NextPtr=TP;
			return (uint8 *)((uint32)TP+sizeof(TOS_RMema_Ptr));
		}
		P=P->NextPtr;
	}
	TP=(TOS_RMema_Ptr *)((uint32)P+P->Size);
	TP->NextPtr=0;
	TP->Size=Size;
	P->NextPtr=TP;
	
	return (uint8 *)((uint32)TP+sizeof(TOS_RMema_Ptr));
}
/********************************************************************************
 Func: 计算内存使用情况
 Time: 2015-09-14
 Ver.: V1.0
 Note; 去掉了父节点
********************************************************************************/
uint32 RMema_Count()
{
	TOS_RMema_Ptr *P=RootRMema;
	uint32 Size=P->Size;
	while(P->NextPtr!=0)
	{
		P=P->NextPtr;
		Size+=P->Size;
	}
	return Size;
}
/********************************************************************************
 Func:释放占用内存
 Time: 2015-09-14
 Ver.: V1.0
 Note; 去掉了父节点
********************************************************************************/
void RMema_Free(void *Addr)
{
	TOS_RMema_Ptr *P=RootRMema,*TP=0;
	while(P->NextPtr)
	{
		if((uint32)P==((uint32)(uint8 *)Addr-sizeof(TOS_RMema_Ptr)))goto Free;
		TP=P;
		P=P->NextPtr;
	}
	if(TP)TP->NextPtr=0;return;
Free:
	TP->NextPtr=P->NextPtr;//当本节点存在子节点父节点的子节点等于自身节点子节点
}
uint32 RMema_Length(void *Addr)
{
	TOS_RMema_Ptr *P=RootRMema;
	while(P->NextPtr)
	{
		if((uint32)P==((uint32)(uint8 *)Addr-sizeof(TOS_RMema_Ptr)))break;
		P=P->NextPtr;
	}
	return (P->Size-sizeof(TOS_RMema_Ptr));
}
/********************************************************************************
 Func:改变容量
 Time: 2015-11-12
 Ver.: V1.0
 Note; 
********************************************************************************/
void *RMema_Extend(void *Addr,uint32 Size)
{
	uint8 *PR;
	TOS_RMema_Ptr *P;
	PR=RMema_Malloc(Size);
	P=(TOS_RMema_Ptr *)((uint8 *)Addr-sizeof(TOS_RMema_Ptr));
	BufferCoppy(Addr,PR,P->Size-sizeof(TOS_RMema_Ptr));
	RMema_Free(Addr);
	return PR;
}
void RMema1_Init()
{
	SDRAM_32M_16BIT_Init();	  
	RMema_Init((void *)FONT_BASE_ADDR);
}
void DeviceMount_RAM()
{
	if(DeviceId_RAM==DeviceNull)DeviceId_RAM=DeviceId_Index++;
	Tos_Device_Tab[DeviceId_RAM].DeviceName="GUI";
	Tos_Device_Tab[DeviceId_RAM].DeviceOwnerId=Null;
	Tos_Device_Tab[DeviceId_RAM].DeviceVirtue=DV_Task;//格外注意，组设备非字节设备
	Tos_Device_Tab[DeviceId_RAM].DeviceState=Ready;
	Tos_Device_Tab[DeviceId_RAM].Init=RMema1_Init;
	Tos_Device_Tab[DeviceId_RAM].Exit=Null;
}
