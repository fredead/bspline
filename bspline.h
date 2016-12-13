/* $Id: bspline.h,v 1.2 1997/11/09 00:31:11 simon Exp simon $
** simon 30101997
** Copyright Simon Loader 1997
** simon@surf.org.uk http://www.surf.org.uk/
** bspline.h
** Header for bspline calculation code
*/

#ifndef __BSPLINE
#define __BSPLINE

#include <stdio.h>
#include <math.h>
#include <string.h>
#include <gtk/gtk.h>
#include "main.h"
#include "gfx_label.h"
#include "mpoints.h"
#include "tvectors.h"



/* LIST O FUNCTIONS */
void bs_calculateq(struct tvector *,struct mpoint *,int,int,GtkWidget *); 

void bs_calculateq_nonmatrix(struct tvector *,struct mpoint *,int,int,GtkWidget *);
GdkPoint *bs_get_point(int,double,int,struct tvector *,struct mpoint *,GdkPoint *);

double bs_getnweight(int,int,struct tvector *,double);
void bs_calculate_at(struct tvector *,struct mpoint *,int,int,GtkWidget *);

GdkPoint *bs_get_point_matrix(int,double,int,struct tvector *,struct mpoint *,GdkPoint *);
void bs_calculateq_matrix(struct tvector *,struct mpoint *,int,int,GtkWidget *);


#endif __BSPLINE
