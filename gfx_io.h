/* $Id$
** simon 
** Copyright Simon Loader 1997
** simon@surf.org.uk http://www.surf.org.uk/
** gfx_io.h
** Header file for graphics input windowing
** code holding the input windows for vector editing
*/

#ifndef GFXIO_H
#define GFXIO_H

#include <gtk/gtk.h>
#include "main.h"

GtkWidget *gfx_entry;   /* global entry for text input
						** this appears to be the only
						** way to allow destruction of th
						** window and stiil get the text
						*/

void gfx_getinput(char *,GtkWidget *,GtkSignalFunc );
void gfx_message(char *);

void edit_uni_tvec_expose(GtkWidget *, GdkEventExpose *);
void edit_vect_uni_start_rts(GtkWidget *,GtkWidget **);
void edit_tvec_uni_start(GtkWidget *,gpointer );
void edit_vect_uni_skip_rts(GtkWidget *,GtkWidget **);
void edit_tvec_uni_skip(GtkWidget *,gpointer );
void button_edit_uni_tvec(GtkWidget *,gpointer );

void edit_nonuni_tvec_expose(GtkWidget *, GdkEventExpose *);
void edit_vect_notuni_value_rts(GtkWidget *,GtkWidget **);
void edit_tvec_notuni_value(GtkWidget *,gpointer );
void edit_vect_notuni_number_rts(GtkWidget *,GtkWidget **);
void edit_tvec_notuni_value(GtkWidget *,gpointer );
void button_edit_nonuni_tvec(GtkWidget *,gpointer );


#endif GFXIO_H
