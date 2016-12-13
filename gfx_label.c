/* $Id: gfx_label.c,v 1.1 1997/11/09 00:31:25 simon Exp simon $
** simon Sat Nov  8 15:15:38 GMT 1997
** Copyright Simon Loader 1997
** simon@surf.org.uk http://www.surf.org.uk/
** gfx_label.c
** A program to do labels 
** for Q and Nodes and T
*/

#include "gfx_label.h"
#include "main.h"

void gfx_label_node(int x, int y,GtkWidget *widget,int number)
{
	
	GdkGC *gc_purple;
	GdkColor *colpurple;
	GdkFont *font;
	char str[10];

	/* colours */
	colpurple = malloc(sizeof(GdkColor));
    gdk_color_parse("purple",colpurple);
	gdk_color_alloc(global_cmap,colpurple);
    gc_purple = gdk_gc_new(widget->window);
    gdk_gc_set_foreground(gc_purple,colpurple);

	gdk_draw_arc( widget->window, gc_purple, TRUE, x-2, y-2, 4, 4, 0, 64*360);


	font = gdk_font_load("-adobe-helvetica-medium-r-normal--*-80-*-*-*-*-*-*");
	sprintf(&str[0],"T%d",number);
	gdk_draw_string(widget->window, font,
			gc_purple,x+4,y+4,&str[0]);


	gdk_font_free(font);
	gdk_gc_destroy(gc_purple);
	free(colpurple);

}

void gfx_label_q(int x,int y,GtkWidget *widget,int number)
{
	char str[10];
	GdkFont *font;
		
	font = gdk_font_load("-adobe-helvetica-medium-r-normal--*-80-*-*-*-*-*-*");
	sprintf(&str[0],"Q%d",number);
	gdk_draw_string(widget->window, font,
			widget->style->black_gc,x+2,y+2,&str[0]);
	gdk_font_free(font);
}

void gfx_label_t(int x,int y,GtkWidget *widget)
{
    GdkGC *gc_orange;
    GdkColor *colorange;
    GdkFont *font;

    /* colours */
    colorange = malloc(sizeof(GdkColor));
    gdk_color_parse("orange",colorange);
    gdk_color_alloc(global_cmap,colorange);
    gc_orange = gdk_gc_new(widget->window);
    gdk_gc_set_foreground(gc_orange,colorange);

    gdk_draw_arc( widget->window, gc_orange, TRUE, x-2, y-2, 4, 4, 0, 64*360);


    font = gdk_font_load("-adobe-helvetica-medium-r-normal--*-80-*-*-*-*-*-*");
    gdk_draw_string(widget->window, font,
            gc_orange,x+4,y+4,"Tpoint");


    gdk_font_free(font);
    gdk_gc_destroy(gc_orange);
    free(colorange);

	
}

