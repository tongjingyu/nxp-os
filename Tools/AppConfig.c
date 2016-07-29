#include <Include.h>
#include <AppConfig.h>
#include <CheakOut.h>
/**************************************************************************************
声明:在引用应用配置文件时需要在应用参数结构体头部放置ConfigHeadStruct实体

**************************************************************************************/





/**************************************************************************************
 Func: 泛型存储配置
 Time: 2015-09-5
 Ver.:	1.0  	
 Note: Sector存储扇区
**************************************************************************************/
void Save_VoidConfig(void(*Save)(uint32 Addr,void *Data,uint16 Size),uint32 Addr,void *Data,uint16 Sector)
{
	uint16 *S;
	ConfigHeadStruct *CHS;
	S=(uint16 *)Data;
	CHS=(ConfigHeadStruct *)S;
	CHS->CrcValue=Tools_GetCRC16((uint8*)(uint32)((uint32)Data+sizeof(ConfigHeadStruct)),CHS->Size-sizeof(ConfigHeadStruct));
	Save(Addr+Sector*CONFIG_SECTOR_SPACE,S,CHS->Size);
}
/**************************************************************************************
 Func: 存储应用程序掉电数据
 Time: 2015-09-5
 Ver.:	1.0  	
 Note: Sector存储扇区
**************************************************************************************/
void Save_AppConfig(void *Data,uint16 Sector)
{
	//assert_param(Sector<2);//对于本地配置只允许使用两个配置单位
	Save_VoidConfig(Flash_WriteData,0,Data,Sector);
}
/**************************************************************************************
 Func: 获取泛型配置
 Time: 2015-09-5
 Ver.:	1.0  	
 Note: 
**************************************************************************************/
BOOL Load_VoidConfig(void(*Load)(uint32 Addr,void *Data,uint16 Size),uint32 Addr,void *Data,uint16 Sector)
{
	uint8 *P;
	uint16 CrcValue;
	ConfigHeadStruct *CHS;
//	assert_param(Sector<2);
	P=(uint8 *)Data;
	Load(Addr+Sector*CONFIG_SECTOR_SPACE,Data,4 );//获取头部
	CHS=(ConfigHeadStruct *)P;
	if(CHS->Size>2048|CHS->Size<4)goto Error;
	Load(Addr+Sector*CONFIG_SECTOR_SPACE,Data,CHS->Size);
	CrcValue=Tools_GetCRC16((uint8*)(uint32)((uint32)P+sizeof(ConfigHeadStruct)),CHS->Size-sizeof(ConfigHeadStruct));
	if(CrcValue!=CHS->CrcValue)goto Error;
	return True;
Error:
	return False;
}
/**************************************************************************************
 Func: 获取本地配置
 Time: 2015-09-5
 Ver.:	1.0  	
 Note: 
**************************************************************************************/
BOOL Load_AppConfig(void *Data,uint16 Sector)
{
//	assert_param(Sector<2);//对于本地配置只允许使用两个配置单位
	return Load_VoidConfig(Flash_ReadData,0,Data,Sector);
}
/**************************************************************************************
 Func: 创建发送消息
 Time: 2015-09-5
 Ver.:	1.0  	
 Note: 
**************************************************************************************/
void Create_Message(void *Buf,uint8 Length)
{
	ConfigHeadStruct *CHS;
	CHS=(ConfigHeadStruct *)Buf;
	CHS->Size=Length;
	CHS->CrcValue=Tools_GetCRC16((uint8*)(uint32)((uint32)Buf+sizeof(ConfigHeadStruct)),CHS->Size-sizeof(ConfigHeadStruct));
}
/**************************************************************************************
 Func: 解析消息
 Time: 2015-09-5
 Ver.:	1.0  	
 Note: 
**************************************************************************************/
BOOL Export_Message(void *Buf,uint8 Length)
{
	uint16 CrcValue;
	ConfigHeadStruct *CHS;
	if(Length<sizeof(ConfigHeadStruct))return False;
	CHS=(ConfigHeadStruct *)Buf;
	if(CHS->Size!=Length)return False;
	CrcValue=Tools_GetCRC16((uint8*)(uint32)((uint32)Buf+sizeof(ConfigHeadStruct)),CHS->Size-sizeof(ConfigHeadStruct));
	if(CrcValue!=CHS->CrcValue)return False;
	return True;
}

















