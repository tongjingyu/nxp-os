/*********************************************************************
*                SEGGER MICROCONTROLLER GmbH & Co. KG                *
*        Solutions for real time microcontroller applications        *
**********************************************************************
*                                                                    *
*        (c) 2003-2010     SEGGER Microcontroller GmbH & Co KG       *
*                                                                    *
*        Internet: www.segger.com    Support:  support@segger.com    *
*                                                                    *
**********************************************************************

----------------------------------------------------------------------
File    : BSP.c
Purpose : BSP for IAR LPC1788-SK
--------  END-OF-HEADER  ---------------------------------------------
*/

#define BSP_C
#include "BSP.h"
#include "LPC177x_8x.h"         // Device specific header file, contains CMSIS
#include "system_LPC177x_8x.h"  // Device specific header file, contains CMSIS

/*********************************************************************
*
*       SDRAM settings
*/


/*********************************************************************
*
*       Defines
*
**********************************************************************
*/

//
// Not used
//

/*********************************************************************
*
*       Typedefs
*
**********************************************************************
*/

//
// Not used
//

/*********************************************************************
*
*       Static data
*
**********************************************************************
*/

//
// Not used
//

/*********************************************************************
*
*       Global functions
*
**********************************************************************
*/

/*********************************************************************
*
*       BSP_Init()
*/
void BSP_Init(void) {
}

/*********************************************************************
*
*       LED switching routines
*       LEDs are switched on with low level on port lines
*/


void BSP_ClrLED(int Index) {
  BSP_USE_PARA(Index);
  //
  // No dedicated LEDs available
  //
}

void BSP_ToggleLED(int Index) {
  BSP_USE_PARA(Index);
  //
  // No dedicated LEDs available
  //
}


/*********************************************************************
*
*       __low_level_init()
*
*       Initialize memory controller, clock generation and pll
*
*       Has to be modified, if another CPU clock frequency should be
*       used. This function is called during startup and
*       has to return 1 to perform segment initialization
*/
extern SDRAM_32M_16BIT_Init(void);
#ifdef __cplusplus
extern "C" {
#endif
int __low_level_init(void);  // Avoid "no ptototype" warning
#ifdef __cplusplus
  }
#endif
int __low_level_init(void) {
  SystemCoreClockUpdate();  // Ensure, the SystemCoreClock is set
  //
  // Init SDRAM, NAND- and NOR-flash
  //
  //_EMC_Init();
  SDRAM_32M_16BIT_Init();
  //
  //  Perform other initialization here, if required
  //
  return 1;
}

/****** End of File *************************************************/
