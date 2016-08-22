#include <Include.h>
#include <SDRAM_K4S561632C_32M_16BIT.h>
#include <..\USER\Prj_Haoyu\AsciiLib.c>
#include <..\USER\Prj_Haoyu\GLCD.c>
#include <..\USER\Prj_Haoyu\GBK_Lib.c>
#include <LCD_Driver.c>
#include <GUI_Include.c>
#include <Tos_Mema.h>
#include <..\MGUI\Menu_Base.c>
#include <..\USER\Prj_Haoyu\IO_Driver.c>
#include <..\USER\Prj_Haoyu\TouchPanel.c>
#include <..\USER\Prj_Haoyu\Page.c>
#include <..\USER\Prj_Haoyu\PageApp.c>
#include <ADC_Driver.c>
#include <Usart_Driver.h>
#include <WM.h>
#include <SDRAM_Mema.c>
#include <..\USER\Prj_Haoyu\Font_Manage.c>
#include <DialogBox.c>
#include <History.c>
#include <MywindowDLG.c>
#include <Login.c>
#include <UsartFunc.c>
#include <FileExplorer.c>
#include <Windows1.c>
#include <Windows.c>
extern DeviceMount_GUI(void);
extern void Task_Touch(void *Tags);
extern int _TouchX,_TouchY;
extern void USB_Task(void *Tags);
void DebugCall(void *Buf,uint8 Length)
{
	USART_WriteLine(UART_0,(char *)Buf,Length);
}
void Task0(void *Tags)
{
	CLKPWR_ConfigPPWR(CLKPWR_PCONP_PCGPIO, ENABLE);
	GPIO_SetDir(2, 1<<21, GPIO_DIRECTION_OUTPUT);
	GPIO_OutputValue(2,1<<21,0);
	DeBug_SetCallBack(DebugCall);
	while(1)
	{
		Tos_TaskDelay(1000);
		GPIO_OutputValue(2,1<<21,0);
		Tos_TaskDelay(10);
		GPIO_OutputValue(2,1<<21,1);
		Tos_TaskDelay(100);
		GPIO_OutputValue(2,1<<21,0);
		Tos_TaskDelay(10);
		GPIO_OutputValue(2,1<<21,1);
		Tos_TaskDelay(100);
		//DeBug("GUI_ALLOC_GetNumUsedBlocks=%d",GUI_ALLOC_GetNumUsedBlocks(),Infor_Infor);
	}
}

static GUI_POINT aPoints[]={
{0,0},
{70,-30},
{0,50},
{-70,-30}
};
void EMC_NAND_Test(void);
void Task1(void *Tags)
{

//		GUI_AA_SetFactor(3);
//	GUI_AA_DrawArc(60*3,60*3,50*3,50*3,0,180);
//	GUI_SetBkColor(GUI_WHITE);
//	GUI_Clear();
//	GUI_SetColor(GUI_DARKBLUE);
//	GUI_AA_FillRoundedRect(10,10,54,54,5);
//	GUI_SetPenSize(10);
//	GUI_SetColor(GUI_RED);
//	GUI_AA_FillPolygon(aPoints,countof(aPoints),150,40);
//	
//	GUI_AA_EnableHiRes();
//	GUI_SetBkColor(GUI_WHITE);
//	GUI_SetColor(GUI_DARKBLUE);
//	GUI_SetPenSize(5);
//	GUI_AA_SetFactor(3);
//	GUI_AA_FillCircle(160*3,120*3,80*3);
//	main1();
	//Tos_TaskDelay(100);
//		EMC_NAND_Test();	
//	USB_Task(0);

	while(1)
	{
		Tos_TaskDelay(100);
	}
}
GUI_FONT SIF_Font;
uint8 *LoadFile_ToRAM(char *Name);
extern void _InitController(unsigned LayerIndex);
void Task3(void *Tags)
{	
	uint8 *P_SIFA,*P_SIFB;
	uint32 Length;
	WM_HWIN hWin;
	
	WM_SetCreateFlags(WM_CF_MEMDEV);
	hWin=CreateLogin();
	Login_SetProgbar(hWin,0);
	Login_SetText(hWin,"Load Font...");
	P_SIFA=LoadFile_ToRAM("songti16.sif");
	if(P_SIFA==0){Login_SetText(hWin,"Load Font Fail!");GUI_Delay(10000);}
	Login_SetProgbar(hWin,50);
	P_SIFB=LoadFile_ToRAM("songti12.sif");
	if(P_SIFB==0){Login_SetText(hWin,"Load Font Fail!");GUI_Delay(10000);}
	Login_SetProgbar(hWin,100);
	GUI_SIF_CreateFont((void*)P_SIFA, &SIFA_Font, GUI_SIF_TYPE_PROP);
	GUI_SIF_CreateFont((void*)P_SIFB, &SIFB_Font, GUI_SIF_TYPE_PROP);
	GUI_EndDialog(hWin,0);
	
	CreateWindow();
	GUI_CURSOR_Show();
	while(1)
	{
//			hItem=WM_GetDialogItem(hWin, ID_PROGBAR_0);
//			PROGBAR_SetValue(hItem, Tos_CPUInfor.Userate_CPU);
//		  hItem=WM_GetDialogItem(hWin, ID_EDIT_0);
//			GetStringByFmt(&Buf[0],"%d",adc_value);
//			EDIT_SetText(hItem, &Buf[0]);
//			// CreateMywindow();
//	GUI_Exec();
////		GUI_AA_SetFactor(3);
////		GUI_SetColor(GUI_BLACK);
////		GUI_AA_FillRoundedRect(10,10,54,54,5);
////		Tos_TaskDelay(1000);
////		GUI_SetColor(GUI_WHITE);
////		GUI_AA_FillRoundedRect(10,10,54,54,5);
////		GUI_AA_FillRoundedRect(100,100,154,154,5);
////		GUI_AA_DrawLine(50,50,70,70);
////		GUI_AA_DrawLine(70,50,50,70);
////		GUI_DispDecAt(i++,20,20,4);
//				P_SIFA=LoadFile_ToRAM("c.gif");
//	GUI_GIF_Draw(P_SIFA,RMema_Length(P_SIFA),0,0);
		GUI_Delay(10);
		//GUI_SendKeyMsg('a',1);
	}
}

const TaskInitList TaskList[]={
{
Task0,Null,"Task0",2000},
//{MUI_Task,(void *)&MenuHome[0],"MUI_Task",2000},
{Task1,Null,"Task0",3000},
{Task3,Null,"Task0",9000},
{Task_Touch,Null,"Task0",2000},
{Task_GetKey,Null,"Task0",2000},
//{Task_ADC,Null,"Task0",2000},
{Null},
};

int main(void)
{
	Mema_Init(&MemBuf[0]);
	DeviceList_Init();
	DeviceMount_GUI();
  DeviceMount_RAM();
	DeviceMount_Usart(UART_0);
	Tos_ListCreate(TaskList);
	while(1);
}



