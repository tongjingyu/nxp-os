/**********************************************************************
* $Id$		usbhost_main.c			2011-09-05
*//**
* @file		usbhost_main.c
* @brief	Demo for USB Host Controller.
* @version	1.0
* @date		05. September. 2011
* @author	NXP MCU SW Application Team
* 
* Copyright(C) 2011, NXP Semiconductor
* All rights reserved.
*
***********************************************************************
* Software that is described herein is for illustrative purposes only
* which provides customers with programming information regarding the
* products. This software is supplied "AS IS" without any warranties.
* NXP Semiconductors assumes no responsibility or liability for the
* use of the software, conveys no license or title under any patent,
* copyright, or mask work right to the product. NXP Semiconductors
* reserves the right to make changes in the software without
* notification. NXP Semiconductors also make no representation or
* warranty that such application will be suitable for the specified
* use without further testing or modification.
* Permission to use, copy, modify, and distribute this software and its
* documentation is hereby granted, under NXP Semiconductors'
* relevant copyright in the software, without fee, provided that it
* is used in conjunction with NXP Semiconductors microcontrollers.  This
* copyright, permission, and disclaimer notice must appear in all copies of
* this code.
**********************************************************************/

/*
**************************************************************************************************************
*                                       INCLUDE HEADER FILES
**************************************************************************************************************
*/
#include "debug_frmwrk.h"
#include  "usbhost_main.h"
#include "ff.h"	
/** @defgroup USBHost_MassStorage	USB Host Controller for Mass Storage Device
 * @ingroup USBHostLite_Examples 
 * @{
 */

/** @defgroup USBHost_Fat	 Fat File System
 * @ingroup USBHost_MassStorage
 * @{
 */

/**
 * @}
 */


/** @defgroup USBHost_Ms  USB Host Mass Storage Class
 * @ingroup USBHost_MassStorage
 * @{
 */

/**
 * @}
 */

/** @defgroup USBHost_Uart  USB Host Debug
 * @ingroup USBHost_MassStorage
 * @{
 */

/**
 * @}
 */

uint8_t menu[]=
"\n\r********************************************************************************\n\r"
" Hello NXP Semiconductors \n\r"
" UART Host Lite example \n\r"
"\t - MCU: LPC177x_8x \n\r"
"\t - Core: ARM CORTEX-M3 \n\r"
"\t - UART Communication: 115200 bps \n\r"
" This example used to test USB Host function.\n\r"
"********************************************************************************\n\r";
static uint8_t file_w[80];
static uint8_t* file_r;

/*********************************************************************//**
 * @brief		Print menu
 * @param[in]	None
 * @return 		None
 **********************************************************************/
void print_menu(void)
{
	_DBG_(menu);
}
/*********************************************************************//**
 * @brief 			This function is the main function where the execution begins
 * @param[in]		None
 * @return 		    None
 **********************************************************************/
int main()
{
    int32_t  rc;
    uint32_t  numBlks, blkSize;	
		uint8_t buffer[30];
		UINT nun;
    uint8_t  inquiryResult[INQUIRY_LENGTH];
		FATFS fs;
	   FIL fsrc, fdst;
  
		const TCHAR  a=1;
  
		  SystemInit();
	  debug_frmwrk_init();
			print_menu();
		
    Host_Init();               /* Initialize the lpc17xx host controller                                    */

    PRINT_Log("Host Initialized\r\n");
    PRINT_Log("Connect a Mass Storage device\r\n");
    rc = Host_EnumDev();       /* Enumerate the device connected                                            */
		 PRINT_Log("连接设备\r\n");
    if ((rc == USB_HOST_FUNC_OK) && (Host_GetDeviceType() == MASS_STORAGE_DEVICE))
			{
					
					PRINT_Log("Mass Storage device connected\r\n");

				rc = 	f_mount(&fs,"0:",1);  
				if(rc==0)
				{
					  rc = f_open(&fdst, "0:read.txt", FA_READ);
					if(rc==0)
					{
						PRINT_Log("open ok\r\n");
						f_read (&fdst,   buffer, 30, &nun );
						PRINT_Log(buffer);
						f_close(&fdst);
					}
				}
    
    } 
		else {
	    PRINT_Log("Not a Mass Storage device\n");							
        return (0);
    }


   return 0;
}

/*********************************************************************//**
 * @brief 			Read directory 
 * @param[in]		None
 * @return 		    None
 **********************************************************************/
