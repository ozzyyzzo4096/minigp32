unsigned short getPIX;
unsigned char *fileImage;
int ticks;
int keydata;
#ifdef __16
unsigned short Transparent;
unsigned short colour;
#endif 

#ifdef __8
unsigned char Transparent;
unsigned char colour;
#endif


//#include "GPLib.h" /*disconnect from the SDK */

#include "gpdef.h"
#include "gpstdlib.h"
#include "gpgraphic.h"
#include "gpmain.h"
#include "gpfont.h"
#include "gpmem.h"
#include "gpstdio.h" 
#include "gpmm.h"

#ifdef __8
	GP_HPALETTE pals[256];
	unsigned char *bgs[200]; //up to 200 backgrounds	
	unsigned char *bg0;
	
	unsigned char *sprite0,sprite0_w,sprite0_h;
	unsigned char *spritesList[200][40] //up to 200 different characters, with 40 moves
#endif 

#ifdef __16
unsigned short *bg0;
unsigned short *bgs[200]; //up to 200 backgrounds

unsigned short *sprite0,sprite0_w,sprite0_h;
unsigned short *spritesList[200][40]; //up to 200 different characters, with 40 moves
#endif 

int spritesTiming[200];
short spritesW[200];
short spritesH[200];

int iConnect;
unsigned short c;
char line[20];

#ifdef FALSE
#undef FALSE
#endif

#define FALSE -1
#define NO 0
#define YES 1

GPDRAWSURFACE	gpDraw[2];
int				nflip;

#ifdef __8
	unsigned char *p_buf;
	#define 	p_bufConnect	p_buf = (unsigned char *)(gpDraw[nflip].ptbuffer);
#endif 

#ifdef __16
	unsigned short *p_buf;
	#define	p_bufConnect p_buf = (unsigned short *)(gpDraw[nflip].ptbuffer);	
#endif 


	/*request 8 or 16 format and creates LCD surfaces (one for primary & the other for back), sets gpDraw[0] as primary surface*/
#define createSurfaces(bpp) \
{\
	int i;\
	\
	GpGraphicModeSet(bpp, NULL);\
	GpLcdSurfaceGet(&gpDraw[0], 0);   \
   	GpLcdSurfaceGet(&gpDraw[1], 1);\
	if (bpp==8)\
	{\
		GpLcdSurfaceGet(&gpDraw[2], 2);   \
		GpLcdSurfaceGet(&gpDraw[3], 3);\
	}\
	GpSurfaceSet(&gpDraw[0]);\
	nflip=0; \
	initKeyPad; \
	p_bufConnect;\
}

#define ActiveSurfaceIsTop nflip=0;
#define ActiveSurfaceIsBelow nflip=1;


#define Show 		GpSurfaceFlip(&gpDraw[nflip]);

#define FlipAndShow 		GpSurfaceFlip(&gpDraw[nflip++]);		nflip = (nflip) & 1; 	p_bufConnect;

#define tick ticks=GpTickCountGet();

#define Delay( ms) \
{\
	tick\
	while(GpTickCountGet()-ticks<ms);\
}

	
#define AddBG(aBG,a) 	bgs[a]=aBG;

#define AddPAL(aPAL,a)  pals[a] = GpPaletteCreate(256, (GP_PALETTEENTRY*)aPAL);

#define SizeSprite(anObject, aW, anH) spritesW[anObject]=aW; spritesH[anObject]=anH;
#define AddSprite(anObject,anImage,anIndex) 	spritesList[anObject][anIndex]=anImage;
#define TimeSprite(anObject,aTime) 	spritesTiming[anObject]=aTime;	

#define SetTransparency2Black Transparent=0;
#define SetTransparency2White Transparent=0xFFFF;
#define SetTransparency2Pink Transparent=0xFAFF;
#define SetTransparency2Blue Transparent=0x87F;
#define SetTransparency2Green Transparent=0x0400;
#define SetTransparency2Red Transparent=0x4000;


#define UsePAL(a) \
	  GpPaletteSelect(pals[a]);\
	  GpPaletteRealize();
	  
#define ShowBG(c)\
	bg0=bgs[c];\
    	for ( iConnect=0; iConnect <320*240; ++iConnect)\
	    			*(p_buf + iConnect) =*(bg0 + iConnect);


#define PutPixel( x,  y,  c)\
{\
	*(p_buf + x*240 + (239-y)) = c;\
}

#define GetPixel( x,  y)\
{\
	getPIX=(int)*(p_buf + x*240 + (239-y));\
}

#define FillTo( x0,  y0 , x1 , y1,c)\
{\
	int i,j;\
    	for ( i=x0; i<x1; ++i)\
    		for ( j=y0; j<y1; ++j )\
	    			*(p_buf + i*240 + (239-j)) = c;\
}


#define Fill( x0,  y0 , w , h,c)\
{\
	int i,j;\
    	for ( i=x0; i<x0+w; ++i)\
    		for ( j=y0; j<y0+h; ++j )\
	    			*(p_buf + i*240 + (239-j)) = c;\
}

#define FillWithHoles( x0,  y0 , w , h, holeSizeW,holeSizeH,c)\
{\
	int i,j;\
    	for ( i=x0; i<x0+w; i+=holeSizeW)\
    		for ( j=y0; j<y0+h; j+=holeSizeH )\
	    			*(p_buf + i*240 + (239-j)) = c;\
}

#define PlaceBody(x0,y0,sprite0,aW, anH)\
{\
	int i0,iSp,j0,jSp;\
		sprite0_w=aW;\
		sprite0_h=anH;\
		\
    	for ( i0=x0, iSp=sprite0_w-1; i0<x0+sprite0_w; ++i0,--jSp)\
    		for ( j0=y0, jSp=sprite0_h-1; j0<y0+sprite0_h; ++j0 ,--iSp)\
			{\
			if (*(sprite0 + jSp*sprite0_w + iSp) != Transparent)\
	    			*(p_buf + i0*240 + (239-j0)) = *(sprite0 + jSp*sprite0_w + iSp);\
				}\
}

#define Spirit( theObject,IndexedSprite,x0,y0)\
{\
	int i0,iSp,j0,jSp;\
		sprite0=spritesList[theObject][IndexedSprite];\
		sprite0_w=spritesW[theObject];\
		sprite0_h=spritesH[theObject];\
		\
    	for ( i0=x0, iSp=sprite0_w-1; i0<x0+sprite0_w; ++i0,--jSp)\
    		for ( j0=y0, jSp=sprite0_h-1; j0<y0+sprite0_h; ++j0 ,--iSp)\
			{\
			if (*(sprite0 + jSp*sprite0_w + iSp) != Transparent)\
	    			*(p_buf + i0*240 + (239-j0)) = *(sprite0 + jSp*sprite0_w + iSp);\
				}\
}


#define Spirit270( theObject,IndexedSprite,x0,y0)\
{\
	int i0,iSp,j0,jSp;\
		sprite0=spritesList[theObject][IndexedSprite];\
		sprite0_w=spritesW[theObject];\
		sprite0_h=spritesH[theObject];\
		\
    	for ( i0=x0, iSp=0; i0<x0+sprite0_w; ++i0,++jSp)\
    		for ( j0=y0, jSp=0; j0<y0+sprite0_h; ++j0 ,++iSp)\
			{\
			if (*(sprite0 + jSp*sprite0_w + iSp) != Transparent)\
	    			*(p_buf + j0*240 + i0) = *(sprite0 + jSp*sprite0_w + iSp);\
				}\
}


#define Spirit270Mirror( theObject,IndexedSprite,x0,y0)\
{\
	int i0,iSp,j0,jSp;\
		sprite0=spritesList[theObject][IndexedSprite];\
		sprite0_w=spritesW[theObject];\
		sprite0_h=spritesH[theObject];\
		\
    	for ( i0=x0, iSp=0; i0<x0+sprite0_w; ++i0,++jSp)\
    		for ( j0=y0, jSp=0; j0<y0+sprite0_h; ++j0 ,++iSp)\
			{\
			if (*(sprite0 + jSp*sprite0_w + iSp) != Transparent)\
	    			*(p_buf + j0*240 + (239-i0)) = *(sprite0 + jSp*sprite0_w + iSp);\
				}\
}


// utilise AddTimer ou tick ...
#define Animate( anObject,x0,y0)\
{\
	int i0,iSp,j0,jSp;\
		sprite0_timing=spritesTiming[anObject]\
		sprite0=spritesList[theObject][IndexedSprite];\
		sprite0_w=spritesW[theObject];\
		sprite0_h=spritesH[theObject];\
		\
    	for ( i0=x0, iSp=0; i0<x0+sprite0_w; ++i0,++jSp)\
    		for ( j0=y0, jSp=0; j0<y0+sprite0_h; ++j0 ,++iSp)\
			{\
			if (*(sprite0 + jSp*sprite0_w + iSp) != Transparent)\
	    			*(p_buf + i0*240 + (239-j0)) = *(sprite0 + jSp*sprite0_w + iSp);\				}\
}


#define rotoGolpa(angleF,anObject,IndexedSprite,whereX,whereY,centreOx,centreOy)\
{\
\
float c,s;\
short imagePlus,xImage,yImage;\
	\
c=cosf(angleF);\
s=sinf(angleF);\
imagePlus=0;\
		sprite0=spritesList[anObject][IndexedSprite];\
		sprite0_w=spritesW[anObject];\
		sprite0_h=spritesH[anObject];\
for ( xImage=0;  xImage<sprite0_w; ++xImage) \
		{\
			for ( yImage=0; yImage<sprite0_h;++yImage,++imagePlus)\
					{\
				\
						colour=sprite0[imagePlus];\
						xR = (short)(((xImage+centreOx)*c) + ((yImage+centreOy)*s));\
						yR = (short)(((yImage+centreOy)*c) - ((xImage+centreOx)*s));\
						xR+=whereX;\
						yR+=whereY;\
						if (xR > 0 && yR > 0 && xR < 320 && yR < 240)\
						{\
          					  if (colour != Transparent)\
						  {\
						*(p_buf +xR*240 + (239-yR)) =colour;\
						  }\
\
						}\
					}\
	      }\
}


#define read_image( name )\
{\
\
	int size, rcount;\
	F_HANDLE h_file;\
	GpFileGetSize( name, &size );\
\
	GpFileOpen( name, OPEN_R, &h_file );\
	fileImage = gp_mem_func.malloc( size );\
	GpFileRead( h_file, image, size, &rcount );\
	GpFileClose( h_file );\
}
#define initKeyPad keydata = 0;
#define getKeyEx	GpKeyGetEx(&keydata);
#define WaitForKey initKeyPad while (!keydata) { GpKeyGetEx(&keydata); }
#define key(c) if ( keydata & c)
#define keyOr(c,b) if (( keydata & c) ||( keydata & b))
