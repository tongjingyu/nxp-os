#include <Include.h>
#include <Tools_Include.h>
#include <Usart_Driver.h>
#include <Tos_Mema.h>
#include "lpc177x_8x_pinsel.h"
uint8 DeviceId_USART_TX[USART_DEF_CH_SIZE];
uint8 DeviceId_USART_RX[USART_DEF_CH_SIZE];
uint8  USART_TX_TaskID[USART_DEF_CH_SIZE];
uint8  USART_RX_TaskID[USART_DEF_CH_SIZE];
uint8  *USART_RX_Buffer[USART_DEF_CH_SIZE];
uint8  *USART_TX_Buffer[USART_DEF_CH_SIZE];
uint16 USART_RX_Count[USART_DEF_CH_SIZE];
uint16 USART_RX_Index[USART_DEF_CH_SIZE];
void USART_GPIO_InitAll(uint8 GPIOx_TXD,uint8 GPIO_Pin_TXD,uint8 GPIOx_RXD,uint8 GPIO_Pin_RXD,uint8  FUNCNUM)
{
	PINSEL_ConfigPin (GPIOx_TXD, GPIO_Pin_TXD, FUNCNUM);
	PINSEL_ConfigPin (GPIOx_RXD, GPIO_Pin_RXD, FUNCNUM);
}
UART_ID_Type USART_GetTypeDef(uint8 Index)
{
	switch(Index)
	{
		case 0:return UART_0;
		case 1:return UART_1;
		case 2:return UART_2;
		case 3:return UART_3;
		case 4:return UART_4;
		default:return UART_0;
	}
}
 uint8 USART_GetIndex(UART_ID_Type USARTx)
{
	switch(USARTx)
	{
		case UART_0:return 0;
		case UART_1:return 1;
		case UART_2:return 2;
		case UART_3:return 3;
		case UART_4:return 4;
		default:return Null;
	}
}
void USART_GPIO_Init(UART_ID_Type USARTx)
{
	
	switch(USARTx)
	{
		case UART_0:USART_GPIO_InitAll(0,2,0,3,1);break;
		case UART_1:USART_GPIO_InitAll(0,15,0,16,1);break;
		case UART_2:USART_GPIO_InitAll(0,10,0,11,1);break;
		case UART_3:USART_GPIO_InitAll(0,2,0,3,2);break;
		case UART_4:USART_GPIO_InitAll(0,22,2,9,3);break;
		default:break;
	}
}
void USART_ConfigurationAll(UART_ID_Type USARTx,uint32_t USART_BaudRate,IRQn_Type IRQn)
{
	UART_CFG_Type UARTConfigStruct;
	UART_FIFO_CFG_Type UARTFIFOConfigStruct;
	UARTConfigStruct.Baud_rate = USART_BaudRate;
	UARTConfigStruct.Databits = UART_DATABIT_8;
	UARTConfigStruct.Parity = UART_PARITY_NONE;
	UARTConfigStruct.Stopbits = UART_STOPBIT_1;
	UART_ConfigStructInit(&UARTConfigStruct);
	UART_Init(USARTx, &UARTConfigStruct);
	UART_TxCmd(USARTx, ENABLE);
	UART_FIFOConfigStructInit(&UARTFIFOConfigStruct);
	UART_FIFOConfig(USARTx, &UARTFIFOConfigStruct);
	UART_TxCmd(USARTx, ENABLE);
	UART_IntConfig(USARTx, UART_INTCFG_RBR, ENABLE);
	UART_IntConfig(USARTx, UART_INTCFG_RLS, ENABLE);
  NVIC_SetPriority(IRQn, ((0x01<<3)|0x01));
  NVIC_EnableIRQ(IRQn);
}

void USART_Configuration(uint8 UsartCH)
{
	USART_GPIO_Init(USART_GetTypeDef(UsartCH));//公共初始化端口
	switch(UsartCH)
	{
		case 0:USART_ConfigurationAll(UART_0,115200,UART0_IRQn);break;
		case 1:USART_ConfigurationAll(UART_1,115200,UART1_IRQn);break;
		case 2:USART_ConfigurationAll(UART_2,115200,UART2_IRQn);break;
		case 3:USART_ConfigurationAll(UART_3,115200,UART3_IRQn);break;
		case 4:USART_ConfigurationAll(UART_4,115200,UART4_IRQn);break;
	}
}
void UART0_IRQHandler(void)
{
	u8 c;
	c=UART_ReceiveByte(UART_0); 
	if(USART_RX_Index[0]<USART_RX_Count[0])
	{
		USART_RX_Buffer[0][USART_RX_Index[0]++]=c;
		Tos_TaskTimeout(USART_RX_TaskID[0],10);
	}
}
void USART_WriteData(UART_ID_Type USARTx,uint16 Data)
{
	UART_SendByte(USARTx, Data);
}
void USART_WriteDatas(UART_ID_Type USARTx,u8* Data,u16 Length)
{
 	
 	UART_Send(USARTx,Data,Length,BLOCKING);
}
uint16 USART_WriteLine(UART_ID_Type USARTx,char *fmt,...)
{
	va_list ap;
	uint16 Length;
  char Buf[200];
  va_start(ap,fmt);
  vsprintf(Buf,fmt,ap);
  va_end(ap);
	Length=GetTextLength(Buf);
	USART_WriteDatas(USARTx,(uint8 *)&Buf[0],Length);
	return Length;
}
uint16 USART_ReadDatas(UART_ID_Type USARTx,uint8 *Buf,uint16 Length,uint32 TimeOut)
{
	BOOL R;
	uint8 UsartCH;
	UsartCH=USART_GetIndex(USARTx);
	R=Tos_TaskGetDev(DeviceId_USART_RX[UsartCH],0);
  if(R)
	{
		
		USART_RX_TaskID[UsartCH]=Tos_TaskCurrent;
		if(Length>=USART_RX_BUFFER_SIZE)Length=USART_RX_BUFFER_SIZE;
		USART_RX_Count[UsartCH]=Length;
		USART_RX_Index[UsartCH]=0;
		if(TimeOut)Tos_TaskDelay(TimeOut);
		else Tos_TaskSuspend(USART_RX_TaskID[UsartCH]); 
	  Tos_TaskDropDev(DeviceId_USART_RX[UsartCH]);
	
	}
	if(Buf!=Null)BufferCoppy(&USART_RX_Buffer[UsartCH][0],&Buf[0],USART_RX_Index[UsartCH]);
	return USART_RX_Index[UsartCH];
}

void DeviceMount_Usart(UART_ID_Type USARTx)
{
	uint8 UsartCH;
	UsartCH=USART_GetIndex(USARTx);
	if(DeviceId_USART_RX[UsartCH]==DeviceNull)DeviceId_USART_RX[UsartCH]=DeviceId_Index++;
	Tos_Device_Tab[DeviceId_USART_RX[UsartCH]].DeviceName="USARRx";
	Tos_Device_Tab[DeviceId_USART_RX[UsartCH]].DeviceOwnerId=Null;
	Tos_Device_Tab[DeviceId_USART_RX[UsartCH]].DeviceVirtue=DV_Array;//格外注意，组设备非字节设备
	Tos_Device_Tab[DeviceId_USART_RX[UsartCH]].DeviceState=Ready;
	Tos_Device_Tab[DeviceId_USART_RX[UsartCH]].Init=USART_Configuration;
	Tos_Device_Tab[DeviceId_USART_RX[UsartCH]].Note=UsartCH;//初始化参数

	Tos_Device_Tab[DeviceId_USART_RX[UsartCH]].Exit=Null;
	USART_RX_Count[UsartCH]=0;
	USART_RX_Buffer[UsartCH]=Mema_Malloc(USART_RX_BUFFER_SIZE);
	UsartCH=USART_GetIndex(USARTx);
	if(DeviceId_USART_TX[UsartCH]==DeviceNull)DeviceId_USART_TX[UsartCH]=DeviceId_Index++;
	Tos_Device_Tab[DeviceId_USART_TX[UsartCH]].DeviceName="USARTx";
	Tos_Device_Tab[DeviceId_USART_TX[UsartCH]].DeviceOwnerId=Null;
	Tos_Device_Tab[DeviceId_USART_TX[UsartCH]].DeviceVirtue=DV_Array;//格外注意，组设备非字节设备
	Tos_Device_Tab[DeviceId_USART_TX[UsartCH]].DeviceState=Ready;
	Tos_Device_Tab[DeviceId_USART_TX[UsartCH]].Init=USART_Configuration;
	Tos_Device_Tab[DeviceId_USART_TX[UsartCH]].Note=UsartCH;//初始化参数

	Tos_Device_Tab[DeviceId_USART_TX[UsartCH]].Exit=Null;
	USART_TX_Buffer[UsartCH]=Mema_Malloc(USART_TX_BUFFER_SIZE);
}
