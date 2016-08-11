#include <ADC_Driver.h>
#include "lpc177x_8x_adc.h"
#include "lpc177x_8x_pinsel.h"
#include "lpc177x_8x_gpdma.h"
#include "debug_frmwrk.h"
#include "bsp.h"
volatile uint32_t adc_value;
void Task_ADC(void *Tags)
{
	uint32_t tmp=1000;
	PINSEL_ConfigPin (BRD_ADC_PREPARED_CH_PORT, BRD_ADC_PREPARED_CH_PIN, BRD_ADC_PREPARED_CH_FUNC_NO);
	PINSEL_SetAnalogPinMode(BRD_ADC_PREPARED_CH_PORT,BRD_ADC_PREPARED_CH_PIN,ENABLE);
	ADC_Init(LPC_ADC, 400000);
	ADC_IntConfig(LPC_ADC, BRD_ADC_PREPARED_INTR, DISABLE);
	ADC_ChannelCmd(LPC_ADC, BRD_ADC_PREPARED_CHANNEL, ENABLE);
	while (tmp--)
	{
		ADC_StartCmd(LPC_ADC, ADC_START_NOW);
		while (!(ADC_ChannelGetStatus(LPC_ADC, BRD_ADC_PREPARED_CHANNEL, ADC_DATA_DONE)))Tos_TaskDelay(10);
		adc_value = ADC_ChannelGetData(LPC_ADC, BRD_ADC_PREPARED_CHANNEL);
		DeBug("%d",adc_value,Infor_Infor);
		Tos_TaskDelay(100);
	}
	ADC_DeInit(LPC_ADC);
	DeBug("Ïß³Ì[%d]ÍË³ö",Tos_TaskCurrent,Infor_Infor);
	Tos_TaskDelete(Tos_TaskCurrent);
}
