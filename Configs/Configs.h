#ifndef _CONFIGS_H_
#define _CONFIGS_H_
/**********************************嵌入式实时操作系统配置文件*******************

                         \\\|///
                       \\  - -  //
                        (  @ @  )
+---------------------oOOo-(_)-oOOo-------------------------+
|                                  													|
|                                                 	        |
|              Real Time Operating System                   | 
|                      2014.11.8                            |
| 			  		   http://www.trtos.com                       |
|                				Config.h				                  	|
|                  				    		  	                      |             
|				  													                		 		|
|                              Oooo                         |
+-----------------------oooO--(   )-------------------------+
                       (   )   ) /
                        \ (   (_/
                         \_)     

*********************************************************************************/
#if defined(BOARD_HAOYOU)
#include <..\USER\Prj_Haoyu\Ini.h>

#else  
	#error "您首先必须配置好您的项目配置文件Ini.h放置于User目录下"
#endif

#endif
