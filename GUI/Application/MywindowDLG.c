/*********************************************************************
*                                                                    *
*                SEGGER Microcontroller GmbH & Co. KG                *
*        Solutions for real time microcontroller applications        *
*                                                                    *
**********************************************************************
*                                                                    *
* C-file generated by:                                               *
*                                                                    *
*        GUI_Builder for emWin version 5.12                          *
*        Compiled Jun 29 2011, 15:28:47                              *
*        (c) 2011 Segger Microcontroller GmbH & Co. KG               *
*                                                                    *
**********************************************************************
*                                                                    *
*        Internet: www.segger.com  Support: support@segger.com       *
*                                                                    *
**********************************************************************
*/

// USER START (Optionally insert additional includes)
// USER END

#include "DIALOG.h"

/*********************************************************************
*
*       Defines
*
**********************************************************************
*/

#define ID_FRAMEWIN_0   (GUI_ID_USER + 0x00)
#define ID_PROGBAR_0   (GUI_ID_USER + 0x01)
#define ID_TEXT_0   (GUI_ID_USER + 0x02)
#define ID_SLIDER_0   (GUI_ID_USER + 0x03)
#define ID_BUTTON_0   (GUI_ID_USER + 0x04)
#define ID_BUTTON_1   (GUI_ID_USER + 0x05)
#define ID_EDIT_0   (GUI_ID_USER + 0x06)
// USER START (Optionally insert additional defines)
// USER END

/*********************************************************************
*
*       Static data
*
**********************************************************************
*/

// USER START (Optionally insert additional static data)
// USER END

/*********************************************************************
*
*       _aDialogCreate
*/
static const GUI_WIDGET_CREATE_INFO _aDialogCreate[] = {
  { FRAMEWIN_CreateIndirect, "Mywindow", ID_FRAMEWIN_0, 0, 0, 480, 272, 0, 100, 0 },
  { PROGBAR_CreateIndirect, "Progbar", ID_PROGBAR_0, 56, 53, 339, 20, 0, 0, 0 },
  { TEXT_CreateIndirect, "Text", ID_TEXT_0, 118, 10, 199, 21, 0, 100, 0 },
  { SLIDER_CreateIndirect, "Slider", ID_SLIDER_0, 57, 100, 335, 20, 0, 0, 0 },
  { BUTTON_CreateIndirect, "Button", ID_BUTTON_0, 61, 152, 80, 40, 0, 0, 0 },
	{ BUTTON_CreateIndirect, "Next", ID_BUTTON_1, 180, 152, 80, 40, 0, 0, 0 },
	{	EDIT_CreateIndirect,"Edit",ID_EDIT_0,300, 152, 80, 40, 0, 0, 0 },
  // USER START (Optionally insert additional widgets)
  // USER END
};

/*********************************************************************
*
*       Static code
*
**********************************************************************
*/

// USER START (Optionally insert additional static code)
// USER END

/*********************************************************************
*
*       _cbDialog
*/
static void _cbDialog(WM_MESSAGE * pMsg) {
	static char Stop;
  WM_HWIN hItem,hTtem1;
  int Id, NCode;
  // USER START (Optionally insert additional variables)
  // USER END

  switch (pMsg->MsgId) {
  case WM_INIT_DIALOG:
    //
    // Initialization of 'Mywindow'
    //
    hItem = pMsg->hWin;
    FRAMEWIN_SetTextColor(hItem, 0x00000000);
    FRAMEWIN_SetTitleHeight(hItem, 20);
    FRAMEWIN_SetText(hItem, "Emwin");
    FRAMEWIN_SetFont(hItem, GUI_FONT_13HB_1);
    //
    // Initialization of 'Text'
    //
    hItem = WM_GetDialogItem(pMsg->hWin, ID_TEXT_0);
    TEXT_SetText(hItem, "Toprie");
    TEXT_SetTextAlign(hItem, GUI_TA_HCENTER | GUI_TA_VCENTER);
    TEXT_SetFont(hItem, GUI_FONT_20_ASCII);
    TEXT_SetTextColor(hItem, 0x00000000);
    //
    // Initialization of 'Button'
    //
    hItem = WM_GetDialogItem(pMsg->hWin, ID_BUTTON_0);
    BUTTON_SetText(hItem, "Start");
		hItem = WM_GetDialogItem(pMsg->hWin, ID_EDIT_0);
		EDIT_SetFont(hItem, GUI_FONT_20_ASCII);
    // USER START (Optionally insert additional code for further widget initialization)
    // USER END
    break;
  case WM_NOTIFY_PARENT:
    Id    = WM_GetId(pMsg->hWinSrc);
    NCode = pMsg->Data.v;
    switch(Id) {
    case ID_SLIDER_0: // Notifications sent by 'Slider'
      switch(NCode) {
      case WM_NOTIFICATION_CLICKED:
        // USER START (Optionally insert code for reacting on notification message)
        // USER END
        break;
      case WM_NOTIFICATION_RELEASED:
        // USER START (Optionally insert code for reacting on notification message)
        // USER END
        break;
      case WM_NOTIFICATION_VALUE_CHANGED:
				hItem = WM_GetDialogItem(pMsg->hWin, ID_SLIDER_0);
				hTtem1=WM_GetDialogItem(pMsg->hWin, ID_PROGBAR_0);
				PROGBAR_SetValue(hTtem1, SLIDER_GetValue(hItem));
        // USER START (Optionally insert code for reacting on notification message)
        // USER END
        break;
      // USER START (Optionally insert additional code for further notification handling)
      // USER END
      }
      break;
    case ID_BUTTON_0: // Notifications sent by 'Button'
      switch(NCode) {
      case WM_NOTIFICATION_CLICKED:
					hItem = WM_GetDialogItem(pMsg->hWin, ID_BUTTON_0);
				Stop=!Stop;
				BUTTON_SetFont(hItem, &GUI_Font24B_ASCII);
				if(Stop)BUTTON_SetText(hItem, "Stop");
				else BUTTON_SetText(hItem, "Start");
				hItem=WM_GetDialogItem(pMsg->hWin, ID_PROGBAR_0);
				PROGBAR_SetValue(hItem, 66);
        // USER START (Optionally insert code for reacting on notification message)
        // USER END
        break;
      case WM_NOTIFICATION_RELEASED:
        // USER START (Optionally insert code for reacting on notification message)
        // USER END
        break;
      // USER START (Optionally insert additional code for further notification handling)
      // USER END
      }
      break;
		case ID_BUTTON_1:
			switch(NCode){
				case WM_NOTIFICATION_CLICKED:
					hItem = WM_GetDialogItem(pMsg->hWin, ID_BUTTON_1);
				  //BUTTON_SetFont(hItem, &GUI_Font24B_ASCII);
					BUTTON_SetText(hItem, "Clicked");
        // USER START (Optionally insert code for reacting on notification message)
        // USER END
        break;
      case WM_NOTIFICATION_RELEASED:
					hItem = WM_GetDialogItem(pMsg->hWin, ID_BUTTON_1);
					BUTTON_SetText(hItem, "Released");
					hItem = WM_GetDialogItem(pMsg->hWin, ID_EDIT_0);
					EDIT_AddKey(hItem, 66);
        // USER START (Optionally insert code for reacting on notification message)
        // USER END
        break;
      // USER START (Optionally insert additional code for further notification handling)
      // USER END
			}
    // USER START (Optionally insert additional code for further Ids)
    // USER END
    }
    break;
  // USER START (Optionally insert additional message handling)
  // USER END
  default:
    WM_DefaultProc(pMsg);
    break;
  }
}

/*********************************************************************
*
*       Public code
*
**********************************************************************
*/
/*********************************************************************
*
*       CreateMywindow
*/
WM_HWIN CreateMywindow(void);
WM_HWIN CreateMywindow(void) {
  WM_HWIN hWin;

  hWin = GUI_CreateDialogBox(_aDialogCreate, GUI_COUNTOF(_aDialogCreate), &_cbDialog, WM_HBKWIN, 0, 0);
  return hWin;
}

// USER START (Optionally insert additional public code)

// USER END

/*************************** End of file ****************************/
