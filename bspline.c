/* $Id: bspline.c,v 1.2 1997/11/09 00:30:49 simon Exp simon $
** simon 30101997
** Copyright Simon Loader 1997
** bspline.c
** CODE to calculate postions for bsplines
** both matrix and recursive functions
*/

#include "bspline.h"




/* so witch version are we runnnig ??? */
void bs_calculateq(struct tvector *ts,struct mpoint *points,int i, int k,GtkWidget *widget)
{
	if ( global_settings.matrix == 1 )
	{
		bs_calculateq_matrix(ts,points,i,k,widget);
	}
	else
	{
		bs_calculateq_nonmatrix(ts,points,i,k,widget);
	}
}


/* calulate where a point T is on the curve 
** and call the label T function
*/
void bs_calculate_at(struct tvector *ts,struct mpoint *points,int i, int k,GtkWidget *widget)
{
	GdkPoint *bsxpoint;

	ts = tvector_start(ts);         /*get to beginnning*/
	points = mpoint_start(points);		/*get to the start*/
	bsxpoint = malloc(sizeof(GdkPoint));

	bsxpoint = bs_get_point(k,global_settings.valuet,i,ts,points,bsxpoint);

	gfx_label_t(bsxpoint->x,bsxpoint->y,widget);
}

/* code
** to output the defernt values of Qi from Ti to Ti+1
** suing the matrix algorithum
*/
void bs_calculateq_matrix(struct tvector *ts,struct mpoint *points,int i, int k,GtkWidget *widget)
{
	double t;	/* current T value */
	double jump;	/* jump rate for t*/
	GdkPoint *bsxpoint;
	GdkPoint *begin;

	ts = tvector_start(ts);
	points = mpoint_start(points);

	begin = malloc(sizeof(GdkPoint) * global_settings.gran+10);
	bsxpoint = begin;

	/* work out number of points to get */

	jump = 1.0 / (double)global_settings.gran;
	
	/* get the points */
	for ( t = 0 ; t <= 1 ; t += jump )
	{
		bsxpoint = bs_get_point_matrix(k,t,i,ts,points,bsxpoint);
		bsxpoint = &bsxpoint[1];
	}

	/* darw all the points */
    gdk_draw_points(widget->window,widget->style->black_gc,begin
                        ,global_settings.gran);

	/*& insert text and dot for the nodes */
    if ( global_settings.dist != 0 )
    {
        gfx_label_node(begin->x, begin->y,widget,i);

        gfx_label_node(begin[global_settings.gran-1].x,
                    begin[global_settings.gran-1].y,
                    widget,i+1);
    }
	/* stamp teh line wit h a Q */
    if ( global_settings.disq != 0 )
    {
    gfx_label_q(begin[global_settings.gran/2].x,
                    begin[global_settings.gran/2].y,
                    widget,i);
    }
    free(begin);

	
}

GdkPoint *bs_get_point_matrix(int k,double t,int i,struct tvector *vectors,struct mpoint *points ,GdkPoint *lpoint)
{
	double t_nor,t_sq,t_cub;
	double w1,w2,w3,w4;		/* 4 different weightings */
	double x,y;

	x = 0;		/* initialise to ZERO */
	y = 0;

	t_nor = t;
	t_sq = t * t;
	t_cub = t_sq * t;

	/* (( 1- t) cubede / 6 )* Pi-3
	** ((3t_c - 6t_s + 4) / 6 ) * Pi-2
	** ((-3t_c + 3t_s + 3t +1 ) / 6 ) * Pi-1
	** t_c / 6   * Pi
	*/

	/* work out each weighting 
	** from list of equations above 
	*/

	w4 = t_cub / 6;
	w3 = (-(3 * t_cub) + (3 * t_sq) + (3 * t_nor) + 1) / 6;
	w2 = (( 3 * t_cub) - (6 * t_sq) + 4 ) / 6;
	w1 = (( 1 - t_nor ) * ( 1 - t_nor ) * ( 1 - t_nor )) / 6;
	
		/* apply the weightings */
	x = w4 * getnth_mpoint(points,i)->x;
	y = w4 * getnth_mpoint(points,i)->y;
	x += w3 * getnth_mpoint(points,i-1)->x;
	y += w3 * getnth_mpoint(points,i-1)->y;
	x += w2 * getnth_mpoint(points,i-2)->x;
	y += w2 * getnth_mpoint(points,i-2)->y;
	x += w1 * getnth_mpoint(points,i-3)->x;
	y += w1 * getnth_mpoint(points,i-3)->y;

	/* right got the values send it back */	
	lpoint->x = (gint) fabs(x);
	lpoint->y = (gint) fabs(y);

	return(lpoint);

}

/* 
** Non matrix calculation for a bspline curve of segment i 
*/
void bs_calculateq_nonmatrix(struct tvector *ts,struct mpoint *points,int i, int k,GtkWidget *widget)
{ 
	
	double t;		/* current value of T */
	double jump;		/* jump rate for t*/
	int no_o_pixel = 0;
	GdkPoint *bsxpoint;
	GdkPoint *begin;

	ts = tvector_start(ts);			/*get to beginnning*/
	points = mpoint_start(points);		/*get to the start*/

	begin = malloc(sizeof(GdkPoint) * global_settings.gran+10);
	bsxpoint = begin;
				
		/* work out the number of points to get */
	jump = (getnth_tvector_val(ts,i+1) - getnth_tvector_val(ts,i)) / global_settings.gran;

	/* What if we are not jumping due to non uniform */
	if ( jump == 0 )
	{
		jump = getnth_tvector_val(ts,i+1);
		bsxpoint = bs_get_point(k,t,i,ts,points,bsxpoint);
		bsxpoint = &bsxpoint[1];
		no_o_pixel = 1;
	}

	/* Go get a list of points */
	for ( t = getnth_tvector_val(ts,i) ; t < getnth_tvector_val(ts,i+1) ; t += jump )
	{
		bsxpoint = bs_get_point(k,t,i,ts,points,bsxpoint);
		bsxpoint = &bsxpoint[1];
		no_o_pixel++;
	}

	/* draw all the points in the array
	** this uses the X drawpoints which should speed up
	** things like points at the same position
	*/
	gdk_draw_points(widget->window,widget->style->black_gc,begin
						,no_o_pixel);
	

	/* label the nodes */
	if ( global_settings.dist != 0 )
	{
		gfx_label_node(begin->x, begin->y,widget,i);

		gfx_label_node(begin[no_o_pixel-1].x,
					begin[no_o_pixel-1].y,
					widget,i+1);
	}
	/* Stamp it with a Q */
	if ( global_settings.disq != 0 )
	{
	gfx_label_q(begin[no_o_pixel/2].x,
					begin[no_o_pixel/2].y,
					widget,i);
	}
	/* free all those points */
	free(begin);
	
}

/*
** Get a point for a given position on a curve
*/
GdkPoint *bs_get_point(int k,double t,int i,struct tvector *vectors,struct mpoint *points ,GdkPoint *lpoint)
{
	int level;		/* which point are we on */
	double weight;		/* Holder for the weight */
	double x,y;
	struct mpoint *temp;	/* temp store for a point */
	struct mpoint *current; /* holder for current point being calculated */

	current = allocmpoint();
	x = 0;		/* initialise to ZERO */
	y = 0;

	/* calculate a point on the curve 
	** get each weighting for decreasing values of
	** K and weight the point down
	*/
	for ( level = k-1 ; level > 0-1 ; level-- )
	{

		weight = bs_getnweight(i-level,k,vectors,t);/* get weight for current */
		temp = getnth_mpoint(points,i-level);   /*get nth point */

			/* calculate new values :) */
		x +=  ( (double) temp->x * weight); 
		y +=  ( (double) temp->y * weight);
	}
		/* convert them into intergers and then 16 bit integers
		** ( X has some weird ideas about points )
		*/
	current->x = fabs(x);		
	current->y = fabs(y);
	
	lpoint->x = (gint16) current->x;
	lpoint->y = (gint16) current->y;
	
	/* free any memory allocated */
	free(current);
	return(lpoint);
}


/*
** Code to get the nth weight of t
** with the of a polynomial K
**
*/
double bs_getnweight(int i,int k,struct tvector *tvectors,double t) {
	double firsttop,secondtop,firstbtm,secondbtm = 0;

	/* if its the first one its easy honest */
	if ( k == 1 )
	{
		if ( (t >= getnth_tvector_val(tvectors,i))
			 && ( t < getnth_tvector_val(tvectors,i+1) ) )
		{
			return 1.0;
		} else {
			return 0.0;
		}
	} else
	{
	/* calculate those values 
	** and past values
	*/
	firsttop = t - getnth_tvector_val(tvectors,i);

	secondtop = getnth_tvector_val(tvectors,i+k) - t; 

	firstbtm = getnth_tvector_val(tvectors,i+k-1) 
			- getnth_tvector_val(tvectors,i);

	secondbtm = getnth_tvector_val(tvectors,i+k) 
		- getnth_tvector_val(tvectors,i+1);

		
		/* make sure then arent some zero like value */
		if ( firstbtm != 0 )
		{
			firsttop = firsttop / firstbtm;
		}
		else
		{
			firsttop = 0;
		}

		if ( secondbtm != 0 )
		{
			secondtop = secondtop / secondbtm;
		}
		else
		{
			secondtop = 0;
		}
			
		/* and times by those other values further down
		** the tree ( RECURSE )
		*/
		firsttop *= bs_getnweight(i,k-1,tvectors,t);
		secondtop *= bs_getnweight(i+1,k-1,tvectors,t);
		/* and return that weight */
		return ( firsttop  + secondtop );
	}
}


