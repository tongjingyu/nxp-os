#include <..\USER\Prj_Haoyu\Font_Manage.h>
#include <emc_nand.h>
#include <fs_mci.h>
#include <efs.h>
#include <ls.h>
#include <SDRAM_Mema.h>
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
	USB_BaseAddr =(uint32)RMema_Malloc(11000);
  Host_Init(USB_BaseAddr+1000);
	DeBug("初始化Host",Infor_Infor);
	Tos_TaskDelay(100);
  rc = Host_EnumDev(); 
	if(rc == USB_HOST_FUNC_OK)DeBug("初始化usb设备成功",Infor_Infor);else DeBug("初始化usb设备失败",Infor_Infor);
 if(Host_GetDeviceType()==MASS_STORAGE_DEVICE) 
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
	}else DeBug("挂载失败",Infor_Infor);
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

#define FILE_RW_SIZE    (4*1024)

uint8 *LoadFile_ToRAM(char *Name)
{
	uint32 res,p,z=0;
	uint8 *File_P;
	EmbeddedFileSystem  efs;
  EmbeddedFile filer;
	if((res =efs_init(&efs,0))!=0){DeBug("SD Card Init Fail %d\n",res,Infor_Infor);return 0;}
	DeBug("SD Card Init Ok",Infor_Infor);
	if(file_fopen(&filer,&efs.myFs,Name,'r')==0)
	{
		DeBug("File name=%s",Name,Infor_Infor);
		DeBug("FileSize=%d",filer.FileSize,Infor_Infor);
		File_P=(uint8 *)RMema_Malloc(filer.FileSize);
		file_read( &filer, filer.FileSize, &File_P[z]);
		file_fclose(&filer);  
		fs_umount(&efs.myFs);		
		return File_P;
	}else DeBug("Open Fail",Infor_Infor);
	return 0;
}
BOOL SaveFile_ToSD(char *Name,uint32 Addr)
{
	uint32 res,p;
	EmbeddedFileSystem  efs;
  EmbeddedFile  filew;
	uint8 *File_P=(uint8 *)Addr;
	if((res =efs_init(&efs,0))!=0){DeBug("SD Card Init Fail %d\n",res,Infor_Infor);return False;}
	DeBug("SD Card Init Ok %d\n",res,Infor_Infor);
	if (file_fopen(&filew,&efs.myFs ,Name ,'w')== 0)
	{
		DeBug("File name=%s",Name,Infor_Infor);
		res=RMema_Length((void*)Addr);
		DeBug("Append Text Length=%d",res,Infor_Infor);
		while(1)
		{
			if(res>=FILE_RW_SIZE)
			{
				p=file_write( &filew, FILE_RW_SIZE, File_P);
				DeBug("Write File Length=%d",p,Infor_Infor);
				res-=FILE_RW_SIZE;
				File_P+=FILE_RW_SIZE;
			}
			else 
			{
				p=file_write( &filew,res, File_P);
				DeBug("Write File Length=%d",p,Infor_Infor);
				res-=res;
				File_P+=res;
			}
			if(res==0)break;
		}
		file_fclose(&filew); 
		fs_umount(&efs.myFs);		
		return True;
	}else DeBug("Open Fail",Infor_Infor);
	return False;
}
BOOL CoppyFile_UpanToSD(char *Name1,char *Name2)
{
	uint8 *P_SIFA,r;
	DeBug("CoppyFile %s to %s",Name1,Name2,Infor_Infor);
	P_SIFA=RMema_Malloc(3260992);
	LoadFile_ToSDRAM(Name1,(uint32)P_SIFA);
	r=SaveFile_ToSD(Name2,(uint32)P_SIFA);
	RMema_Free(P_SIFA);
	return r;
}
BOOL UPan_Init()
{
	int32_t  rc;
	uint32 USB_BaseAddr;
	uint32_t  numBlks, blkSize;					
  uint8_t  inquiryResult[INQUIRY_LENGTH];
	int32_t  fdr;
	uint32  length=0;
	uint32_t  bytes_read;
	Tos_TaskDelay(100);
	USB_BaseAddr =(uint32)RMema_Malloc(11000);
  Host_Init(HOST_BASE_ADDR);
	DeBug("初始化Host",Infor_Infor);
	Tos_TaskDelay(100);
  rc = Host_EnumDev(); 
	if(rc == USB_HOST_FUNC_OK)DeBug("初始化usb设备成功",Infor_Infor);else DeBug("初始化usb设备失败",Infor_Infor);
  if(Host_GetDeviceType()==MASS_STORAGE_DEVICE) 
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
						DeBug("文件系统初始化成功\r\n",Infor_Infor);
						 return True;
						} 
			}else  DeBug("文件系统初始化失败\n",Infor_Infor);					
	}
	return False;
}
uint32 SaveFile_ToUPan(char *FileName,uint32 Addr)
{
	int32_t  rc;
	uint32 USB_BaseAddr;
	uint32_t  numBlks, blkSize;					
  uint8_t  inquiryResult[INQUIRY_LENGTH];
	int32_t  fdr;
	uint32  length=0;
	uint32_t  bytes_read;
	uint8 *P=(uint8 *)Addr;
	fdr = FILE_Open(FileName, RDWR);
	if(fdr>0)
	{
		DeBug("文件打开成功",Infor_Infor);
		//length=RMema_Length((void*)Addr);
		//while(length)
		{
			//if(length>=NAND_PAGE_SIZE)
			{
				FILE_Write(fdr, "123456789\0", 10);
				length-=NAND_PAGE_SIZE;
			}
	//		else 
	//		{
	//			bytes_read = FILE_Write(fdr, P, length);
	//			length-=length;
	//		}
		}
			DeBug("文件写入",Infor_Infor);
			FILE_Close(fdr);
	}else DeBug("文件打开失败",Infor_Infor);

	return length;
}
