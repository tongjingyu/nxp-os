#include "fs_mci.h"
#include "efs.h"
#include "ls.h"
#include <SDRAM_Mema.h>



//int main1()
//{
//	
//	int8_t res;
//	
//DirList             list;
//    uint32_t n, m, p, cnt;
//	EmbeddedFileSystem  efs;
//  EmbeddedFile filer, filew;
//    uint32_t cclk = CLKPWR_GetCLK(CLKPWR_CLKTYPE_CPU);
//    uint32_t filesize = 0;
//    uint32_t time_end;
//	debug_frmwrk_init(); // UART0
//    xfunc_out = put_char;
//	xfunc_in  = get_char; 

// xprintf("init\n");

//	// init file system
//	if ( ( res = efs_init( &efs, 0 ) ) != 0 ) {
//		xprintf("failed with %d\n",res);
//	}
//	else 
//	{
//		xprintf("ok\n");

//        xprintf("Card type: ");
//        switch (CardConfig.CardType)
//        {
//            case MCI_MMC_CARD:
//                xprintf("MMC\n");
//                break;
//            case MCI_SDSC_V1_CARD:
//                xprintf("Version 1.x Standard Capacity SD card.\n");
//                break;
//            case MCI_SDSC_V2_CARD:
//                xprintf("Version 2.0 or later Standard Capacity SD card.\n");
//                break;
//            case MCI_SDHC_SDXC_CARD:
//                xprintf("Version 2.0 or later High/eXtended Capacity SD card.\n");
//                break;
//            default:
//                break;            
//        }
//        xprintf("Sector size: %d bytes\n", CardConfig.SectorSize);
//        xprintf("Sector count: %d\n", CardConfig.SectorCount);
//        xprintf("Block size: %d sectors\n", CardConfig.BlockSize);
//        xprintf("Card capacity: %d MByte\n\n", (((CardConfig.SectorCount >> 10) * CardConfig.SectorSize)) >> 10);
//		xprintf("\nDirectory of 'root':\n");
//		
//		/* list files in root directory */
//		ls_openDir( &list, &(efs.myFs) , "/");
//		while ( ls_getNext( &list ) == 0 ) {
//			// list.currentEntry is the current file
//			list.currentEntry.FileName[LIST_MAXLENFILENAME-1] = '\0';
//			xprintf("%s, %d bytes\n", list.currentEntry.FileName, list.currentEntry.FileSize ) ;
//		}
//        /* Read test */
//        xprintf("\nFile read test:\n");
//        xprintf("Open file %s ...", FILE_NAME_R);
//        xmemset(Buff,0,sizeof(Buff));
//        if (file_fopen( &filer, &efs.myFs , FILE_NAME_R , 'r' ) == 0 )
//        {
//            xprintf(" OK. \nReading %lu bytes ...\n", FILE_RW_SIZE);

//            n=FILE_RW_SIZE; 
//            m = 0;
//            Timer = 0;
//            xprintf("File's content:\n");
//            while (n)
//            {
//                if (n>=blen) {cnt = blen; n -= blen;}
//                else         {cnt = n; n = 0;}

//                p =  file_read( &filer, cnt, &Buff[m] );
//                xprintf("%s",&Buff[m]);
//                m += p;
//                if (p != cnt) break;                
//            }
//            filesize = m;
//            time_end = Timer;
//            xprintf("\n%lu bytes read in %lu milisec.\n", m, time_end);
//            file_fclose( &filer ); 

//        } else
//        {
//            xprintf (" Failed.\n");    
//        }
//        /* Write test*/  
//        xprintf("\nFile write test:\n");
//        xprintf("Open file %s ...", FILE_NAME_W);
//        if (file_fopen( &filew, &efs.myFs , FILE_NAME_W , 'a' ) == 0 )
//        {
//            xprintf(" OK. \nWriting %lu bytes ...\n", filesize);
//            n=filesize;
//            m = 0;
//            Timer = 0;
//            while (n)
//            {
//                if (n>=blen) {
//                    cnt = blen;
//                    n -= blen;
//                } else {
//                    cnt = n;
//                    n = 0;
//                }
//                p = file_write( &filew, 7, "aaaaabbbb" );
//                m += p;
//                if (p != cnt); break;
//            }
//            time_end = Timer;
//            xprintf("%lu bytes written in %lu milisec.\n", m, time_end);

//            file_fclose( &filew );                          

//        } else {
//            xprintf (" Failed.\n");
//        }
//        /* Read test */
//        xprintf("\nFile read test:\n");
//        xprintf("Open file %s ...", FILE_NAME_W);
//        xmemset(Buff,0,sizeof(Buff));
//        if (file_fopen( &filer, &efs.myFs , FILE_NAME_W , 'r' ) == 0 )
//        {
//            xprintf(" OK. \nReading %lu bytes ...\n", FILE_RW_SIZE);

//            n=FILE_RW_SIZE; 
//            m = 0;
//            Timer = 0;
//            xprintf("File's content:\n");
//            while (n)
//            {
//                if (n>=blen) {cnt = blen; n -= blen;}
//                else         {cnt = n; n = 0;}

//                p =  file_read( &filer, cnt, &Buff[m] );
//                xprintf("%s",&Buff[m]);
//                m += p;
//                if (p != cnt) break;                
//            }
//            filesize = m;
//            time_end = Timer;
//            xprintf("\n%lu bytes read in %lumiliseconds.\n", m, time_end);
//            file_fclose( &filer ); 

//        } else
//        {
//            xprintf (" Failed.\n");    
//        }
//        /* close file system */
//	    fs_umount( &efs.myFs ) ;
//    }

//	xprintf("\nEFSL test complete.\n");
//		return 0;
//}
////int main1()
////{
////	int8_t res;
////    uint32_t n, m, p, cnt;
////    uint32_t cclk = CLKPWR_GetCLK(CLKPWR_CLKTYPE_CPU);
////    uint32_t filesize = 0;
////    uint32_t time_end;
////	debug_frmwrk_init(); // UART0
////    xfunc_out = put_char;
////	xfunc_in  = get_char; 

//// xprintf("init\n");

////	// init file system
////	if ( ( res = efs_init( &efs, 0 ) ) != 0 ) {
////		xprintf("failed with %d\n",res);
////	}
////	else 
////	{
////		xprintf("ok\n");

////        xprintf("Card type: ");
////        switch (CardConfig.CardType)
////        {
////            case MCI_MMC_CARD:
////                xprintf("MMC\n");
////                break;
////            case MCI_SDSC_V1_CARD:
////                xprintf("Version 1.x Standard Capacity SD card.\n");
////                break;
////            case MCI_SDSC_V2_CARD:
////                xprintf("Version 2.0 or later Standard Capacity SD card.\n");
////                break;
////            case MCI_SDHC_SDXC_CARD:
////                xprintf("Version 2.0 or later High/eXtended Capacity SD card.\n");
////                break;
////            default:
////                break;            
////        }
////        xprintf("Sector size: %d bytes\n", CardConfig.SectorSize);
////        xprintf("Sector count: %d\n", CardConfig.SectorCount);
////        xprintf("Block size: %d sectors\n", CardConfig.BlockSize);
////        xprintf("Card capacity: %d MByte\n\n", (((CardConfig.SectorCount >> 10) * CardConfig.SectorSize)) >> 10);
////		xprintf("\nDirectory of 'root':\n");
////		
////		/* list files in root directory */
////		ls_openDir( &list, &(efs.myFs) , "/");
////		while ( ls_getNext( &list ) == 0 ) {
////			// list.currentEntry is the current file
////			list.currentEntry.FileName[LIST_MAXLENFILENAME-1] = '\0';
////			xprintf("%s, 0x%x bytes\n", list.currentEntry.FileName, list.currentEntry.FileSize ) ;
////		}
////#if READ_TEST_ENABLED!=0
////        /* Read test */
////        xprintf("\nFile read test:\n");
////        xprintf("Open file %s ...", FILE_NAME_R);
////        xmemset(Buff,0,sizeof(Buff));
////        if (file_fopen( &filer, &efs.myFs , FILE_NAME_R , 'r' ) == 0 )
////        {
////            xprintf(" OK. \nReading %lu bytes ...\n", FILE_RW_SIZE);

////            n=FILE_RW_SIZE; 
////            m = 0;
////            Timer = 0;
////            xprintf("File's content:\n");
////            while (n)
////            {
////                if (n>=blen) {cnt = blen; n -= blen;}
////                else         {cnt = n; n = 0;}

////                p =  file_read( &filer, cnt, &Buff[m] );
////                xprintf("%s",&Buff[m]);
////                m += p;
////                if (p != cnt) break;                
////            }
////            filesize = m;
////            time_end = Timer;
////            xprintf("\n%lu bytes read in %lu milisec.\n", m, time_end);
////            file_fclose( &filer ); 

////        } else
////        {
////            xprintf (" Failed.\n");    
////        }
////#endif
////#if WRITE_TEST_ENABLED!=0
////        /* Write test*/  
////        xprintf("\nFile write test:\n");
////        xprintf("Open file %s ...", FILE_NAME_W);
////        if (file_fopen( &filew, &efs.myFs , FILE_NAME_W , 'a' ) == 0 )
////        {
////            xprintf(" OK. \nWriting %lu bytes ...\n", filesize);
////            n=filesize;
////            m = 0;
////            Timer = 0;
////            while (n)
////            {
////                if (n>=blen) {
////                    cnt = blen;
////                    n -= blen;
////                } else {
////                    cnt = n;
////                    n = 0;
////                }
////                p = file_write( &filew, cnt, &Buff[m] );
////                m += p;
////                if (p != cnt) break;
////            }
////            time_end = Timer;
////            xprintf("%lu bytes written in %lu milisec.\n", m, time_end);

////            file_fclose( &filew );                          

////        } else {
////            xprintf (" Failed.\n");
////        }
////#endif
////#if READ_TEST_ENABLED!=0
////        /* Read test */
////        xprintf("\nFile read test:\n");
////        xprintf("Open file %s ...", FILE_NAME_W);
////        xmemset(Buff,0,sizeof(Buff));
////        if (file_fopen( &filer, &efs.myFs , FILE_NAME_W , 'r' ) == 0 )
////        {
////            xprintf(" OK. \nReading %lu bytes ...\n", FILE_RW_SIZE);

////            n=FILE_RW_SIZE; 
////            m = 0;
////            Timer = 0;
////            xprintf("File's content:\n");
////            while (n)
////            {
////                if (n>=blen) {cnt = blen; n -= blen;}
////                else         {cnt = n; n = 0;}

////                p =  file_read( &filer, cnt, &Buff[m] );
////                xprintf("%s",&Buff[m]);
////                m += p;
////                if (p != cnt) break;                
////            }
////            filesize = m;
////            time_end = Timer;
////            xprintf("\n%lu bytes read in %lumiliseconds.\n", m, time_end);
////            file_fclose( &filer ); 

////        } else
////        {
////            xprintf (" Failed.\n");    
////        }
////#endif
////        /* close file system */
////	    fs_umount( &efs.myFs ) ;
////    }

////	xprintf("\nEFSL test complete.\n");
////		return 0;
////}
///**
// * @}
// */
// 

