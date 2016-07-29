#include <Include.h>


#if defined(BOARD_HAOYU)//ÍØÆÕÈğÔ¶³ÌÎÂÊª¶È
#include <..\USER\Prj_Haoyu\Haoyu_main.c>
#else  
	#error "Missing define: Check Your Project Main.c!"
#endif

int tos_main()
{
	main();//goto main file
	return Tos_TaskTotal;	//goto config ini file
}
