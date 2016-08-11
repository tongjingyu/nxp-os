#include <..\USER\Prj_Haoyu\Font_Manage.h>
#include <emc_nand.h>
#include <..\USB\NXP_USBHOST\usbhost_fat.c>
#include <..\USB\NXP_USBHOST\usbhost_main.c>
#include <..\USB\NXP_USBHOST\usbhost_ms.c>
GUI_FONT SIFA_Font;
GUI_FONT SIFB_Font;

uint32 LoadFile_ToSDRAM(char *FileName,uint32 Addr)
{
	int32_t  rc;
	uint32 USB_BaseAddr;
	uint32_t  numBlks, blkSize;					
  uint8_t  inquiryResult[INQUIRY_LENGTH];
	int32_t  fdr;
	uint32  length=0;
	uint32_t  bytes_read;
	uint8 *P=(uint8 *)Addr;
	Tos_TaskDelay(100);
	USB_BaseAddr =(uint32)RMema_Malloc(10000);
  Host_Init(USB_BaseAddr);
	DeBug("初始化Host",Infor_Infor);
	Tos_TaskDelay(100);
  rc = Host_EnumDev();    
	DeBug("初始化usb设备",Infor_Infor);
 if ((rc == USB_HOST_FUNC_OK) && (Host_GetDeviceType() == MASS_STORAGE_DEVICE)) 
	{  
			DeBug("发现U盘",Infor_Infor);
			Tos_TaskDelay(1000);
			rc = MS_Init( &blkSize, &numBlks, inquiryResult );
			DeBug("块大小%d 块个数%d",blkSize,numBlks,Infor_Infor);
			if (rc == MS_FUNC_OK) 
			{
				 rc = FAT_Init();   
				 if (rc == FAT_FUNC_OK) 
					 {
						DeBug("初始化完毕\r\n",Infor_Infor);
						} 
			}else  DeBug("没有发现U盘\n",Infor_Infor);					
		if ((rc == USB_HOST_FUNC_OK) && (Host_GetDeviceType() == MASS_STORAGE_DEVICE))
		 {
				fdr = FILE_Open(FileName, RDONLY);
				if(fdr>0)DeBug("文件读取成功",Infor_Infor);
				while(1)
				{
					bytes_read = FILE_Read(fdr, P, NAND_PAGE_SIZE);
					length+=bytes_read;
					Tos_TaskDelay(1);
					if(!bytes_read)break;
					P+=NAND_PAGE_SIZE;
				}
				FILE_Close(fdr);
			}
	}
	DeBug("加载[%s]大小[%d]",FileName,length,Infor_Infor);
	RMema_Free((void*)USB_BaseAddr);
	return length;
}
void Get_NandAddr(uint32 Offset,NAND_ADDRESS *WriteReadAddr)
{
	WriteReadAddr->Block=Offset/NAND_PAGE_SIZE/NAND_BLOCK_SIZE;
	Offset-=(WriteReadAddr->Block*NAND_PAGE_SIZE*NAND_BLOCK_SIZE);
	WriteReadAddr->Page=Offset/NAND_PAGE_SIZE;
	WriteReadAddr->Zone=0;
}
void PrintfBuf(uint8 *Buf,uint16 Length)
{
	uint16 i=0;
	while(Length--)DeBug("Buf[%d]%02x",i,Buf[i++],Infor_Infor);
}
//SDRAM绝对地址  Length文件长度，Offset NandFalsh绝对地址
uint32 SaveFile_ToNand(uint32 Addr,uint32 Length,uint32 Offset)
{
	NAND_ADDRESS WriteReadAddr;
	uint32 Block,i;
	uint8 *P=(uint8 *)Addr;
	Block=Length/NAND_PAGE_SIZE/NAND_BLOCK_SIZE;
	EMC_NAND_Init();
	Tos_TaskDelay(100);
	DeBug("从SDRAM[%x]复制数据到NAND[%d]数据大小[%d]",Addr,Offset,Length,Infor_Infor);
	if(Length%NAND_PAGE_SIZE)Block++;
	Get_NandAddr(Offset,&WriteReadAddr);
	DeBug("Page[%d]Block[%d]Zone[%d]",WriteReadAddr.Page,WriteReadAddr.Block,WriteReadAddr.Zone,Infor_Infor);
	DeBug("擦除块%d",Block,Infor_Infor);
	for(i=0;i<Block;i++)
	{
		EMC_NAND_EraseBlock(WriteReadAddr);
		WriteReadAddr.Block++;
		Tos_TaskDelay(100);
	}
	Get_NandAddr(Offset,&WriteReadAddr);
	Block=Length/NAND_PAGE_SIZE;
	if(Length%NAND_PAGE_SIZE)Block++;
	DeBug("写页%d",Block,Infor_Infor);
	for(i=0;i<Block;i++)
	{
		EMC_NAND_WriteSmallPage((void*)P, WriteReadAddr, 1);
		Tos_TaskDelay(10);
		P+=NAND_PAGE_SIZE;
		WriteReadAddr.Page++;
		if(WriteReadAddr.Page>=NAND_BLOCK_SIZE)
		{
			WriteReadAddr.Page=0;
			WriteReadAddr.Block++;
		}
	}
	return Length;
}
void LoadFile_FromNand(uint32 Addr,uint32 Length,uint32 Offset)
{
	NAND_ADDRESS WriteReadAddr;
	uint32 Block,i;
	uint8 *P=(uint8 *)Addr;
	DeBug("SDRAM[%x]从NAND[%d]复制数据大小[%d]",Addr,Offset,Length,Infor_Infor);
	EMC_NAND_Init();
	Tos_TaskDelay(100);
	Get_NandAddr(Offset,&WriteReadAddr);
	DeBug("Page[%d]Block[%d]Zone[%d]",WriteReadAddr.Page,WriteReadAddr.Block,WriteReadAddr.Zone,Infor_Infor);
	Block=Length/NAND_PAGE_SIZE;
	for(i=0;i<Block;i++)
	{
		EMC_NAND_ReadSmallPage((void*)P, WriteReadAddr, 1);
		P+=NAND_PAGE_SIZE;
		WriteReadAddr.Page++;
		if(WriteReadAddr.Page>=NAND_BLOCK_SIZE)
		{
			Tos_TaskDelay(1);
			WriteReadAddr.Page=0;
			WriteReadAddr.Block++;
		}
	}
}
#include "fs_mci.h"
#include "efs.h"
#include "ls.h"
void CoppyFile_UpanToSDCard(char *SName,char DName)
{
	EmbeddedFileSystem  efs;
EmbeddedFile filer, filew;
DirList             list;
	int8_t res;
	uint32_t n, m, p, cnt;
	uint32_t cclk = CLKPWR_GetCLK(CLKPWR_CLKTYPE_CPU);
	uint32_t filesize = 0;
	DeBug("init",Infor_Infor);
	if ( ( res = efs_init( &efs, 0 ) ) != 0 ) {
		xprintf("failed with %d\n",res);
	}
}
