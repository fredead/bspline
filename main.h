
#ifndef __MAIN_H
#define __MAIN_H

#include "tvectors.h"
#include "mpoints.h"

struct gfx_settings {
    int doton;			/* join the dots on / off */
    int dot_no;			/* which dots to do 0= all */
    int bsplineon;		/* Display bspline on/off */
    int bspline_no;		/* which bspline 0 = all */
    int convexon;		/* Convex hull on/off */
    int convex_no;		/* Whic onvex hull 0 = all */
	

		/* and for the P point effects */
	int p_dot_no;         /* which dots to do 0= all */
	int p_bspline_no;     /* which bspline 0 = all */
	int p_convex_no;      /* Whic onvex hull 0 = all */


    int pointson;		/* Display points on/off */
	int dis_tvec;		/* display T vector */
    int placeing;		/* are we placing a point 1 = next 2 = before 3 = after*/
	int disq;			/* Display Q */
	int dist;			/* Display TT */
	int disp;			/* Display P values */


	double valuet;		/* value t to look at*/
	int t_on;			/* do we want to see t */
	int p_on;			/* Are we looking at selected P only */


	int kvalue;  		/* the Kvalue initial 4 */
	int no_o_points;	/* Number of points */
	int no_o_vectors;
	int current_t;		/* current t being edited */
	int matrix;			/* matrix mode yes */
	int uniform;		/* Is it uniform */
	double uni_start;		/* start value for uniform */
	double uni_skip;		/* How much do we skip for uniform */
	int gran;			/* how many pixels do we plot */
		/* will includ pointer to points tree and tvector tree */
};

struct gfx_settings global_settings;
struct mpoint *the_points;
struct tvector *the_vectors;
static struct mpoint *which_point;
GdkColormap *global_cmap;


void destroy_window (GtkWidget  *, GtkWidget **);
void file_quit_cmd_callback(GtkWidget *widget, gpointer data);
void help_info(GtkWidget *widget,gpointer data);
void switch_convex(GtkWidget *widget,gpointer data);
void button_convex_inc(GtkWidget *widget,gpointer data);
void button_convex_dec(GtkWidget *widget,gpointer data);
void switch_bspline(GtkWidget *widget,gpointer data);
void button_bspline_inc(GtkWidget *widget,gpointer data);
void button_bspline_dec(GtkWidget *widget,gpointer data);
void switch_dtd(GtkWidget *widget,gpointer data);
void button_dtd_inc(GtkWidget *widget,gpointer data);
void button_dtd_dec(GtkWidget *widget,gpointer data);
void button_new_dot(GtkWidget *widget,gpointer data);
void button_disq(GtkWidget *widget,gpointer data);
void button_dist(GtkWidget *widget,gpointer data);
void button_set_p(GtkWidget *widget,gpointer data);
void button_set_k(GtkWidget *widget,gpointer data);
void k_return(GtkWidget *,GtkWidget **);
void button_set_gran(GtkWidget *,gpointer );
void gran_return(GtkWidget *,GtkWidget **);
void switch_tvector(GtkWidget *,gpointer);
void button_disp(GtkWidget *,gpointer);
void switch_points(GtkWidget *,gpointer);
void switch_matrix(GtkWidget *,gpointer);
void switch_uniform(GtkWidget *,gpointer);
void switch_p_on(GtkWidget *,gpointer);
void switch_t_on(GtkWidget *,gpointer);
void button_clear(GtkWidget *,gpointer);
void tvalue_return(GtkWidget *,GtkWidget **);
void button_set_tpoint(GtkWidget *,gpointer );
void switch_after(GtkWidget *,gpointer);
void switch_before(GtkWidget *,gpointer);





#endif
