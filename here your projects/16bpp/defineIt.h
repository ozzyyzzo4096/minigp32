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
#include "gpgraphic16.h"
#include "gpmain.h"
#include "gpfont.h"
#include "gpfont16.h"
#include "gpmem.h"
#include "gpstdio.h" 
#include "gpmm.h"

// variables globales pour fn grapphiques

#define sgn(x) ((x==0)?(0):((x<0)?(-1):(1)))
#define abs(x) ((x<0)?(-(x)):(x))

static int ftab[240]; // nombre de ligne
//table trigo 
static int tsn[320]={
	0,402,804,1205,1606,2006,2404,2801,
	3196,3590,3981,4370,4756,5139,5520,5897,
	6270,6639,7005,7366,7723,8076,8423,8765,
	9102,9434,9760,10080,10394,10702,11003,11297,
	11585,11866,12140,12406,12665,12916,13160,13395,
	13623,13842,14053,14256,14449,14635,14811,14978,
	15137,15286,15426,15557,15679,15791,15893,15986,
	16069,16143,16207,16261,16305,16340,16364,16379,
	16384,16379,16364,16340,16305,16261,16207,16143,
	16069,15986,15893,15791,15679,15557,15426,15286,
	15137,14978,14811,14635,14449,14256,14053,13842,
	13623,13395,13160,12916,12665,12406,12140,11866,
	11585,11297,11003,10702,10394,10080,9760,9434,
	9102,8765,8423,8076,7723,7366,7005,6639,
	6270,5897,5520,5139,4756,4370,3981,3590,
	3196,2801,2404,2006,1606,1205,804,402,
	0,-402,-804,-1205,-1606,-2006,-2404,-2801,
	-3196,-3590,-3981,-4370,-4756,-5139,-5520,-5897,
	-6270,-6639,-7005,-7366,-7723,-8076,-8423,-8765,
	-9102,-9434,-9760,-10080,-10394,-10702,-11003,-11297,
	-11585,-11866,-12140,-12406,-12665,-12916,-13160,-13395,
	-13623,-13842,-14053,-14256,-14449,-14635,-14811,-14978,
	-15137,-15286,-15426,-15557,-15679,-15791,-15893,-15986,
	-16069,-16143,-16207,-16261,-16305,-16340,-16364,-16379,
	-16384,-16379,-16364,-16340,-16305,-16261,-16207,-16143,
	-16069,-15986,-15893,-15791,-15679,-15557,-15426,-15286,
	-15137,-14978,-14811,-14635,-14449,-14256,-14053,-13842,
	-13623,-13395,-13160,-12916,-12665,-12406,-12140,-11866,
	-11585,-11297,-11003,-10702,-10394,-10080,-9760,-9434,
	-9102,-8765,-8423,-8076,-7723,-7366,-7005,-6639,
	-6270,-5897,-5520,-5139,-4756,-4370,-3981,-3590,
	-3196,-2801,-2404,-2006,-1606,-1205,-804,-402,
	0,402,804,1205,1606,2006,2404,2801,
	3196,3590,3981,4370,4756,5139,5520,5897,
	6270,6639,7005,7366,7723,8076,8423,8765,
	9102,9434,9760,10080,10394,10702,11003,11297,
	11585,11866,12140,12406,12665,12916,13160,13395,
	13623,13842,14053,14256,14449,14635,14811,14978,
	15137,15286,15426,15557,15679,15791,15893,15986,
	16069,16143,16207,16261,16305,16340,16364,16379
};
static int ttg[65]={
	-16384,-15599,-14850,-14133,-13446,-12786,-12151,-11539,
	-10947,-10375,-9820,-9281,-8757,-8247,-7749,-7263,
	-6786,-6320,-5862,-5413,-4970,-4534,-4104,-3679,
	-3259,-2843,-2430,-2021,-1614,-1209,-805,-402,
	0,402,805,1209,1614,2021,2430,2843,
	3259,3679,4104,4534,4970,5413,5862,6320,
	6786,7263,7749,8247,8757,9281,9820,10375,
	10947,11539,12151,12786,13446,14133,14850,15599,
	16384
};
int *sn=tsn;
int *cs=tsn+64;
int *tg=ttg+32;

//fin variables globales

#ifdef __8
	GP_HPALETTE pals[256];
	unsigned char *bg0;
	unsigned char *bgs[200]; //up to 200 backgrounds	
	
	
	unsigned char *sprite0,sprite0_w,sprite0_h;
	unsigned char *spritesList[200][40]; //up to 200 different characters, with 40 moves
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

#define FlipAndShow 		GpSurfaceFlip(&gpDraw[nflip++]);		nflip %= 2; 	p_bufConnect;

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
	return getPIX;\
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
#define keyAnd(c,b) if (( keydata & c) &&( keydata & b))


// primitives *(p_buf + x*240 + (239-y)) = c;


//trace une ligne verticale - draw a vertical  line
void vline(int x,int y,int y1,int c)
{
	register int dy=sgn(y1-y);
	register int i;
        if (!dy) dy++;
	
	for(i=y;i!=y1+dy;i+=dy) *(p_buf + x*240 + (239-i)) = c;
}

//trace une ligne horizontale-horizontal line
void hline(int x,int y,int x1,int c)
{
	register int n=x1-x;
	register int i;
		
		if (n>=0)
		{
			for(i=0;i<=n;i++)  *(p_buf + (x+i)*240 + (239-y)) = c;
		}
	else
	{
		n= -n-1;
		for(i=0;i<=n;i++) *(p_buf + (x-i)*240 + (239-y)) = c;
	}
}

//trace une ellipse pleine-Fill ellipse
void pellipse(int x,int y,int lx,int ly,int c)
{
	register int i,r,a,s;
	register int ry=(ly+1)>>1;
	register int rx=lx>>1;
	
	for(i=0,a=64;i<ry;i++)
	{
		s=(int)(((long)(ry-i)<<14L)/ry);
		while(sn[a]>s) a++;
		r=rx+(int)((cs[a]*(long)rx)>>14L);
		hline(x+r,y+i,x+lx-1-r,c);
		hline(x+r,y+ly-i-1,x+lx-1-r,c);
	}
}

//trace un cadre
void dbox(int x,int y,int lx,int ly,int c)
{
	hline(x,y,x+lx-1,c);
	hline(x,y+ly-1,x+lx-1,c);
	vline(x,y,y+ly-1,c);
	vline(x+lx-1,y,y+ly-1,c);
}

//trace un rectangle remplit
void pbox(int x,int y,int lx,int ly,int c)
{
	register int i;
	
	for(i=y;i<y+ly;i++) hline(x,i,x+lx-1,c);
}


void DrawLine(int x1,int y1,int x2,int y2, unsigned short color)
{
   int dx = abs(x2-x1);
   int dy = abs(y2-y1);
   int npixel;
   int dinc1;
   int dinc2;
   int xinc1;
   int xinc2;
   int yinc1;
   int yinc2;
   int x;
   int y;
   int d;
	int i;
 
   if (dx >= dy) {
     npixel = dx;
     d = (2*dy)-dx;
    dinc1 = dy << 1;
     dinc2 = (dy-dx) << 1;
     xinc1 = 1;
     xinc2 = 1;
     yinc1 = 0;
     yinc2 = 1;
     }
   else {
    npixel = dy;
     d = (2*dx)-dy;
     dinc1 = dx << 1;
     dinc2 = (dx-dy) << 1;
     xinc1 = 0;
     xinc2 = 1;
     yinc1 = 1;
     yinc2 = 1;
     }
 
   if (x1>x2) {
     xinc1 = -xinc1;
     xinc2 = -xinc2;
     }
   if (y1>y2) {
     yinc1 = -yinc1;
     yinc2 = -yinc2;
     }
 
   x = x1;
   y = y1;
   for (i=0; i < npixel; i++)
	   { 
     PutPixel(x,y,color);
     if (d<0) {
       d += dinc1;
       x += xinc1;
       y += yinc1;
       }
     else {
       d += dinc2;
       x += xinc2;
       y += yinc2;
       }
     }
   }
   
 
//trace une ligne brisée-polygon n=nbre de sommet tp=tableau de coordonnées des points.
void polyline(int n,int *tp,int c)
{
	register int i;
	
	for(i=0;i<n-1;i++) DrawLine(tp[i*2],tp[i*2+1],tp[i*2+2],tp[i*2+3],c);
}



/* trace un segment horizontal x=longueur du segment x=ordonnée*/
void fplot(int x,int y, int c)
{
	register int l=ftab[y];
	register int d;

	if (l>=0)
	{
		d=l-x;
		if ((!d)||(d==1)||(d== -1))
		{
			*(p_buf + x*240 + (239-y)) = c;
			ftab[y]=x;
		}
		else
		{
			hline(x,y,l,c);
			ftab[y]=-1;
		}
	}
	else
	{
		*(p_buf + x*240 + (239-y)) = c;
		ftab[y]=x;
	}
}

/* trace une ligne qui délimite l'extrémité d'une zone zemplie fill line */
void fline(int x1,int y1,int x2,int y2, int c)
{
	register long a,x,y;
	register int i;
	register int d;
	register int dx=(x2-x1);
	register int dy=(y2-y1);

	if (dx|dy)
		if (abs(dx)>abs(dy))
		{
			d=sgn(dx);
			a=((long)dy<<16L)/abs(dx);
			for(i=x1,y=32768L+((long)y1<<16L);i!=x2;i+=d,y+=a)
				fplot(i,(int)(y>>16),c);
		}
		else
		{
			d=sgn(dy);
			a=((long)dx<<16L)/abs(dy);
			for(i=y1,x=32768L+((long)x1<<16L);i!=y2;i+=d,x+=a)
				fplot((int)(x>>16),i,c);
		}

	fplot(x2,y2,c);

}

/*draw polygone **** usage :
for a triangle :
int num_vertices=3;
int vertices[6]={5,0,    /*(x1,y1) 
                 7,5,    /* (x2,y2) 
                 1,4};   /* (x3,y3) 
polygon(3,vertices,15);*/

void polygon(int num_PIC, int *PIC, char color)
{
  int i;

  for(i=0;i<num_PIC-1;i++)
  {
    DrawLine(PIC[(i<<1)+0],
        PIC[(i<<1)+1],
         PIC[(i<<1)+2],
         PIC[(i<<1)+3],
         color);
  }
  DrawLine(PIC[0],
      PIC[1],
      PIC[(num_PIC<<1)-2],
      PIC[(num_PIC<<1)-1],
       color);
}

void polyfill(int n,int *tp,int c)
{
	register int i;
	
	for(i=0;i<200;i++) ftab[i]= -1;
	for(i=0;i<(n-1);i++) fline(tp[i*2],tp[(i*2)+1],tp[(i*2)+2],tp[(i*2)+3],c);
}


void FCircle(int x, int y, int radius, unsigned short color)
{
  int balance, xoff, yoff;

  xoff = 0;
  yoff = radius;
  balance = -radius;

  do {
   *(p_buf + (x+xoff)*240 + (239-(y+yoff))) = color;
*(p_buf + (x-xoff)*240 + (239-(y+yoff))) = color;
 *(p_buf + (x-xoff)*240 + (239-(y-yoff))) = color;
  *(p_buf + (x+xoff)*240 + (239-(y-yoff))) = color;
*(p_buf + (x+yoff)*240 + (239-(y+xoff))) = color;
 *(p_buf + (x-yoff)*240 + (239-(y+xoff))) = color;
*(p_buf + (x-yoff)*240 + (239-(y-xoff))) = color;
*(p_buf + (x+yoff)*240 + (239-(y-xoff))) = color;

    if ((balance += xoff++ + xoff) >= 0)
      balance -= --yoff + yoff;

  } while (xoff <= yoff);
} // FCircle //

void CircleThick(int x, int y, int radius,int p, unsigned short color)
{
  int balance, xoff, yoff;

  xoff = 0;
  yoff = radius;
  balance = -radius;

  do {
   Fill( (x+xoff),(y+yoff),p,p,color);
Fill((x-xoff) ,(y+yoff),p,p,color);
 Fill((x-xoff) ,(y-yoff),p,p,color);
  Fill((x+xoff) ,(y-yoff),p,p,color);
Fill((x+yoff) ,(y+xoff),p,p,color);
 Fill((x-yoff) ,(y+xoff),p,p,color);
Fill((x-yoff) ,(y-xoff),p,p,color);
Fill((x+yoff) ,(y-xoff),p,p,color);

    if ((balance += xoff++ + xoff) >= 0)
      balance -= --yoff + yoff;

  } while (xoff <= yoff);
} // FCircle //
short getPixel( int x, int y)
{
	getPIX=(int)*(p_buf + x*240 + (239-y));
	return getPIX;
}
   
void remplissage(int xx,int yy,unsigned short c,unsigned short lim) { 
  int x,y,xi,xf ;
  int psp = 1 ;
 int *px;
int *py;			 
  px = (int *) gm_calloc(1000,sizeof(int)) ;
  py = (int *)gm_calloc(1000,sizeof(int)) ;

int countdown=560;
 px[0] = xx ;
 py[0] = yy ;
  //setcolor(c) ;
  while ( psp != 0 ) {
	  countdown--;
    xi = xf = x = (px[psp-1]) ;
    y =( py[psp-1] );
    x++ ;
    short cp = (getPixel(x,y)) ;
    while ( ( cp != lim ) )  {
      xf = x ;
      x++ ;
      cp = (getPixel(x,y)) ; }
    x =( px[psp-1]-1) ;
     cp = (getPixel(x,y)) ;
    while ( ( cp != lim )  )  {
      xi = x ;
      x-- ;
       cp = (getPixel(x,y)) ; }
    DrawLine(xi,y,xf,y,c) ;
    psp-- ;
    x = xf ;
    while ( x >= xi  ) {
      cp = (getPixel(x,y+1)) ;
      while ( ((cp == lim) || (cp == c)) // ||
              && (x >= xi) ){
        x-- ;
        cp = (getPixel(x,y+1)) ; }
      if ( (x >= xi) && (cp != lim)
           && (cp != c) ) {
        px[psp] = x ;
        py[psp] = (y+1) ;
        psp++ ; }
       cp = (getPixel(x,y+1)) ;
      while ( ( cp != lim )
              && ( x >= xi ) ) {
        x-- ;
         cp = (getPixel(x,y+1)) ; } }
    x = xf ;
    while ( x >= xi  ) {
       cp = (getPixel(x,y-1)) ;
      while ( ((cp == lim) || (cp == c)) // ||
              && (x >= xi) ){
        x-- ;
        cp = (getPixel(x,y-1)) ; }
      if ( (x >= xi)
           && (cp != lim)
           && (cp != c) ) {
        px[psp] = x ;
        py[psp] = (y-1 );
        psp++ ; }
      cp = (getPixel(x,y-1)) ;
      while ( ( cp != lim ) 
              && ( x >= xi ) ) {
        x-- ;
        cp = (getPixel(x,y-1)) ; } } if (countdown==0)break;}
  gm_free(px) ;
  gm_free(py) ;
}  
 

void DrawBar(int x1,int y1,int x2,int y2,int p, unsigned short color)
{
   int dx = abs(x2-x1);
   int dy = abs(y2-y1);
   int npixel;
   int dinc1;
   int dinc2;
   int xinc1;
   int xinc2;
   int yinc1;
   int yinc2;
   int x;
   int y;
   int d;
	int i;
 
   if (dx >= dy) {
     npixel = dx;
     d = (2*dy)-dx;
    dinc1 = dy << 1;
     dinc2 = (dy-dx) << 1;
     xinc1 = 1;
     xinc2 = 1;
     yinc1 = 0;
     yinc2 = 1;
     }
   else {
    npixel = dy;
     d = (2*dx)-dy;
     dinc1 = dx << 1;
     dinc2 = (dx-dy) << 1;
     xinc1 = 0;
     xinc2 = 1;
     yinc1 = 1;
     yinc2 = 1;
     }
 
   if (x1>x2) {
     xinc1 = -xinc1;
     xinc2 = -xinc2;
     }
   if (y1>y2) {
     yinc1 = -yinc1;
     yinc2 = -yinc2;
     }
 
   x = x1;
   y = y1;
   for (i=0; i < npixel; i++)
	   { 
     pbox(x,y,p,p,color);
     if (d<0) {
       d += dinc1;
       x += xinc1;
       y += yinc1;
       }
     else {
       d += dinc2;
       x += xinc2;
       y += yinc2;
       }
     }
   }

void polybar(int num_PIC, int *PIC,int p, char color)
{
  int i;

  for(i=0;i<num_PIC-1;i++)
  {
    DrawBar(PIC[(i<<1)+0],
        PIC[(i<<1)+1],
         PIC[(i<<1)+2],
         PIC[(i<<1)+3],
         p,color);
  }
  DrawBar(PIC[0],
      PIC[1],
      PIC[(num_PIC<<1)-2],
      PIC[(num_PIC<<1)-1],
       p,color);
}

void rectbar(int x,int y,int lx,int ly,int p,int c)
{
	DrawBar(x,y,x+lx-1,y,p,c);
	DrawBar(x,y+ly-1,x+lx-1,y+ly,p,c);
	DrawBar(x,y,x,y+ly-1,p,c);
	DrawBar(x+lx-1,y,x+lx-1,y+ly-1,p,c);
}

