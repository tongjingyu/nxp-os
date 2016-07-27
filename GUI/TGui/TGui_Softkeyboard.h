#ifndef _TGUI_SOFTKEYBOARD_H_
#define _TGUI_SOFTKEYBOARD_H_

#include <Include.h>

extern TGUI_Window Window_KeyBoard;
extern uint8  TGUI_SoftKeyboardLoad;					//ϵͳ�������Ƿ��Ѽ���

/*---------------------------------------------------------------------------------------------
 Func: ��ʼ����Ļ������
 Time: 2011-6-13
 Ver.: V1.0
 Note:
---------------------------------------------------------------------------------------------*/
void TGUI_SoftKeyboard_Create(void);

/*---------------------------------------------------------------------------------------------
 Func: ��ʾ��Ļ������
 Time: 2011-6-13
 Ver.: V1.0
 Note:
---------------------------------------------------------------------------------------------*/
void TGUI_SoftKeyboard_Show(void);

/*---------------------------------------------------------------------------------------------
 Func: ������Ļ������
 Time: 2011-6-13
 Ver.: V1.0
 Note:
---------------------------------------------------------------------------------------------*/
void TGUI_SoftKeyboard_Hidden(void);

#endif
