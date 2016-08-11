#include "DIALOG.h"

#define ID_FRAMEWIN_0   (GUI_ID_USER + 0x00)
#define ID_TREEVIEW_0   (GUI_ID_USER + 0x01)

static const GUI_WIDGET_CREATE_INFO FileExplorer_aDialogCreate[] = {
    { FRAMEWIN_CreateIndirect, "文件浏览", ID_FRAMEWIN_0, 0, 0, 482, 272, 0, 0, 0 },
    { TREEVIEW_CreateIndirect, "Treeview", ID_TREEVIEW_0, 0, 0, 475, 260, 0, 0, 0 },
};
static uint8 ScanFiles(char* path,WM_HWIN hTree, TREEVIEW_ITEM_Handle hNode)
{
//    FRESULT res;
//    FILINFO fno;
//    DIR dir;
//    UINT rw;
//    int i;
//    char *fn;   /* This function is assuming non-Unicode cfg. */
//    char file_name[FILE_PATH_MAX]={0};
//    TREEVIEW_ITEM_Handle hItem;
//    
//#if _USE_LFN
//    static char lfn[FILE_PATH_MAX]={0};   /* Buffer to store the LFN */
//    fno.lfname = lfn;
//    fno.lfsize = sizeof(lfn);
//#endif

//    res = f_opendir(&dir, (const TCHAR*)path);                       /* Open the directory */
//    if (res == FR_OK)
//    {
//        i = strlen((const char*)path);
//        for (;;) 
//        {
//            res = f_readdir(&dir, &fno);                   /* Read a directory item */
//            if (res != FR_OK || fno.fname[0] == 0) break;  /* Break on error or end of dir */
//            if (fno.fname[0] == '.') continue;             /* Ignore dot entry */ //忽略上级目录
//#if _USE_LFN
//            fn = *fno.lfname ? fno.lfname : fno.fname;
//#else
//            fn = fno.fname;
//#endif
//            if (fno.fattrib & AM_DIR) /* It is a directory */
//            {
//                if(hTree != NULL && hNode != NULL)
//                {
//                    //目录，创建结点
//                    hItem = TREEVIEW_ITEM_Create(TREEVIEW_ITEM_TYPE_NODE,fn,0);
//                    //把结点加入到目录树中
//                    TREEVIEW_AttachItem(hTree,hItem,hNode,TREEVIEW_INSERT_FIRST_CHILD);
//                }
//                //在路径最后添加文件夹路径名
//                sprintf(&path, "/%s", fn);
//                //遍历此新文件夹下的文件
//                res = ScanFiles(path,hTree,hItem,fileType,fileNum);
//                if (res != FR_OK) break;//打开失败，跳出循环
//                path = 0;//末尾添加结束字符
//            } 
//            else /* It is a file. */
//            {
//                if(fileType == TEXTFILE )
//                {
//                    //判断如果不是txt文件，跳出本函数
//                    if(!(strstr(fn,".txt")||strstr(fn,".TXT")
//                        ||strstr(fn,".c")||strstr(fn,".c")
//                        ||strstr(fn,".cpp")||strstr(fn,".CPP")
//                        ||strstr(fn,".h")||strstr(fn,".h")))
//                    {
//                        return res;
//                    }
//                }
//                //判断如果不是Image文件，跳出本函数
//                else if(fileType ==IMAGEFILE)
//                {
//                    if(!(strstr(fn,".bmp")||strstr(fn,".BMP")||
//                        strstr(fn,".jpg")||strstr(fn,".JPG")||
//                        strstr(fn,".gif")||strstr(fn,".GIF")||
//                        strstr(fn,".png")||strstr(fn,".PNG")))
//                    {
//                        return res;
//                    }
//                }
//                /* 根据要求是否创建目录树 */
//                if(hTree != NULL && hNode != NULL)//创建目录树
//                {
//                    hItem = TREEVIEW_ITEM_Create(TREEVIEW_ITEM_TYPE_LEAF,fn,0);//文件，创建树叶
//                    TREEVIEW_AttachItem(hTree,hItem,hNode,TREEVIEW_INSERT_FIRST_CHILD);//把树叶添加到目录树
////                    (*fileNum)++;//记录文件数目
//                }
//                else
//                {
//                    (*fileNum)++;//记录文件数目
//                }
//            }

//        }
//        f_closedir(&dir);
//    }
//    return res;
}
void Fill_FileList(char *path,WM_HWIN hTree, TREEVIEW_ITEM_Handle hNode)
{
//	TREEVIEW_ITEM_Handle hTreeItem_Flash;
//	TREEVIEW_ITEM_Handle hTreeItemCur;
//	char p_path[FILE_PATH_MAX]={0};  //目录名 指针
//	// FIL hFile;  //文件句柄
//	FRESULT fres;   //返回结果

//	hTreeItemCur=hNode;
//	strcpy(p_path,path);    //复制目录名到指针
//	fres = ScanFiles(p_path,hTree,hNode,fileType,fileNum);    //递归扫描文件

//	hTreeItem_Flash = TREEVIEW_ITEM_Create(TREEVIEW_ITEM_TYPE_NODE, "Flash[1:]", 0);
//	TREEVIEW_AttachItem(hTree, hTreeItem_Flash, hTreeItemCur, TREEVIEW_INSERT_BELOW);
//	strcpy(p_path,"1:");    //复制目录名到指针
//	fres = ScanFiles(p_path,hTree,hTreeItem_Flash,fileType,fileNum);    //递归扫描文件
}
static void File_cbDialog(WM_MESSAGE * pMsg) {
    
  TREEVIEW_ITEM_Handle   hTreeItem_SDCard;
  TREEVIEW_ITEM_Handle   hTreeItemCur;
  TREEVIEW_ITEM_INFO ItemInfo;
  TREEVIEW_ITEM_Handle hNode;
  WM_HWIN hItem;
  WM_HWIN hTree;
  int     NCode;
  int     Id;
  u32 FileNum=0;
  u8 *pathname;

  GUI_HMEM hMem_pathname;

  switch (pMsg->MsgId) {
  case WM_INIT_DIALOG:
    //
    // Initialization of 'FileBrower'
    //
    hItem = pMsg->hWin;
    FRAMEWIN_SetFont(hItem, &SIFA_Font);
    FRAMEWIN_SetTitleHeight(hItem, 20);
    FRAMEWIN_SetTextAlign(hItem, GUI_TA_LEFT | GUI_TA_VCENTER);
    //
    // Initialization of 'Treeview'
    //
	    hTree = WM_GetDialogItem(pMsg->hWin, ID_TREEVIEW_0);
    TREEVIEW_SetAutoScrollV(hTree, 1);    
    TREEVIEW_SetAutoScrollH(hTree, 1);   
    TREEVIEW_SetSelMode(hTree, TREEVIEW_SELMODE_ROW);
    TREEVIEW_SetFont(hTree,&SIFA_Font);
//  
    hTreeItemCur = TREEVIEW_GetItem(hTree, 0, TREEVIEW_GET_LAST);
     hTreeItem_SDCard = TREEVIEW_ITEM_Create(TREEVIEW_ITEM_TYPE_NODE, "SDCard[/:]", 0);
     //TREEVIEW_AttachItem(hTree, hTreeItem_SDCard, hTreeItemCur, TREEVIEW_INSERT_BELOW);
    //FLASH
   Fill_FileList("0:",hTree,hTreeItem_SDCard);
    break;
  case WM_NOTIFY_PARENT:
    Id    = WM_GetId(pMsg->hWinSrc);
    NCode = pMsg->Data.v;
    switch(Id) {
    case ID_TREEVIEW_0: // Notifications sent by 'Treeview'
      hNode = TREEVIEW_GetSel(pMsg->hWinSrc);
      TREEVIEW_ITEM_GetInfo(hNode,&ItemInfo);
      switch(NCode) {
      case WM_NOTIFICATION_CLICKED:
        break;
      case WM_NOTIFICATION_RELEASED:
        if(ItemInfo.IsNode == 0)
        {
           // hMem_pathname = GUI_ALLOC_AllocZero(256);
            pathname = GUI_ALLOC_h2p(hMem_pathname);
           // get_pathname(hTree, hNode,pathname);
            printf("\r\n%s\r\n",pathname);
            GUI_ALLOC_Free(hMem_pathname);
        }
        break;
      case WM_NOTIFICATION_MOVED_OUT:
        break;
      case WM_NOTIFICATION_SEL_CHANGED:
        break;
      }
      break;
    }
    break;
  default:
    WM_DefaultProc(pMsg);
    break;
  }
}

void CreateFileBrower();
void CreateFileBrower() 
{

	WM_HWIN hItem;
  hItem=GUI_CreateDialogBox(FileExplorer_aDialogCreate, GUI_COUNTOF(FileExplorer_aDialogCreate), File_cbDialog, WM_HBKWIN, 0, 0);
	FRAMEWIN_AddCloseButton(hItem, FRAMEWIN_BUTTON_RIGHT, 0);
	FRAMEWIN_AddMinButton(hItem, FRAMEWIN_BUTTON_RIGHT, 0);
	GUI_ExecCreatedDialog(hItem);
}