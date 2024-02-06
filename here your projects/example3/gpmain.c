#include "gpdef.h"
#include "gpstdlib.h"
#include "gpgraphic.h"
#include "gpmain.h"
#include "gpfont.h"

GPDRAWSURFACE gpDraw;
char g_string[256];
#define	LCD_WIDTH	320
#define	LCD_HEIGHT	240

void GpMain(void *arg)
{
	int cx, cy = 10, cw, ch;
	
	GpLcdSurfaceGet(&gpDraw, 0);  
	GpRectFill(NULL, &gpDraw, 0, 0, gpDraw.buf_w, gpDraw.buf_h, 0xff);
	
	GpSurfaceSet(&gpDraw);
	
	//to draw text
	gp_str_func.strcpy(g_string, "TextOut example");
	GpTextOut(NULL, &gpDraw, 10, cy, g_string, 0x00);
	cy += GpTextHeightGet(g_string);
	
	//to draw text horizontally centered.
	gp_str_func.strcpy(g_string, "horizontally centered");
	cw = GpTextWidthGet(g_string);
	cx = (LCD_WIDTH - cw) / 2;
	GpTextOut(NULL, &gpDraw, cx, cy, g_string, 0xe0);
	
	//to draw text at the center of screen
	gp_str_func.strcpy(g_string, "screen center");
	cw = GpTextWidthGet(g_string);
	ch = GpTextHeightGet(g_string);
	cx = (LCD_WIDTH - cw) / 2;
	cy = (LCD_HEIGHT - ch) / 2;
	GpTextOut(NULL, &gpDraw, cx, cy, g_string, 0x02);

	while(1)
	;
}