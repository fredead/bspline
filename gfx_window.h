/* $Id: gfx_window.h,v 1.1 1997/11/06 00:30:40 simon Exp simon $
** gfx_window.h
** Copyright Simon Loader 1997
** simon@surf.org.uk http://www.surf.org.uk/
** simon 04/11/1997
** Header file for gfx_window.c
*/

#ifndef __GFXWIN_H
#define __GFXWIN_H

#include <gtk/gtk.h>
#include "main.h"
#include "mpoints.h"
#include "tvectors.h"
#include "bspline.h"



void gfx_convex_for(GtkWidget *,struct mpoint *);
void draw_points(GtkWidget *);
void gfx_draw_ton(GtkWidget *);
void gfx_dot_to_dot(GtkWidget *);
void gfx_display_tvectors(GtkWidget *);
void gfx_draw_spline(GtkWidget *);
void gfx_convex(GtkWidget *);
void gfx_draw_pon(GtkWidget *);
void gfx_draw_dot(GtkWidget *,int ,int );
gint gfx_button_press_event (GtkWidget *, GdkEventButton *);
gint configure_event (GtkWidget *, GdkEventConfigure *);
gint expose_event (GtkWidget *, GdkEventExpose *);
void gfx_refresh();
void gfx_window_destory();
void gfx_window();
int check_global(int);


#endif
