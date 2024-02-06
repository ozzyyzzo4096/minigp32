//////////////


/*Depending on your colour system choice, 8bpp or 16 bpp,should be either 
#define __8 8*/
/*or 
#define __16 16*/

// Si je choisi le mode 8 bit t
//#define __8 8  
#define __16 16

/*then you can include definition library*/////
#include "defineIt.h"
   
void GpMain(void *arg)
{
	int				i;
	
	
#ifdef __8
	createSurfaces(8);
#else 
	createSurfaces(16);
#endif
	
	
	
	Fill(0,0,320,240,0xFFFF);//fffffff
	
	
	GpTextOut16(NULL, &gpDraw[nflip], 16,200,(char*)"essais de texte en 16 bits",0);
		
	DrawLine(0,0,100,100,0);
	//DrawBar(x1,y1,x2,y2,epaisseur/thickness, color)
	DrawBar(100,100,160,100,3,0xfaff);
	
		
	
	while(1)
	{
		//key (GPC_VK_FA)
				
	}
	
}
