/* $Id$
** simon Sat Nov  8 15:15:38 GMT 1997
** Copyright Simon Loader 1997
** simon@surf.org.uk http://www.surf.org.uk/
** gfx_label.h
** A program to do labels 
** for Q and Nodes and T
*/

#include <gtk/gtk.h>

GtkWidget *gfx_entry;   /* global entry for text input
						** this appears to be the only
						** why to allow destruction of th
						** window and stiil get the text
						*/

void gfx_label_node(int ,int ,GtkWidget *,int );
void gfx_label_q(int ,int ,GtkWidget *,int );
void gfx_label_t(int ,int ,GtkWidget *);
