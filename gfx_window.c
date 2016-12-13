/* $Id: gfx_window.c,v 1.4 1997/11/18 19:15:57 simon Exp simon $
** gfx_window.c
** Copyright Simon Loader 1997
** simon 04/11/1997
**  Program for all the functions
** for the gfx window :)
*/

#include <gdk/gdktypes.h>
#include <string.h>
#include <gdk/gdkkeysyms.h>
#include "gfx_window.h"


GtkWidget *drawing_area;



void gfx_destroy_window (GtkWidget  *widget, GtkWidget **window)
{
	  *window = NULL;
}

/* 
** display where point T is
*/
void gfx_draw_ton(GtkWidget *widget)
{

	int i = -1;

	if ( global_settings.valuet >= getnth_tvector_val(the_vectors,global_settings.kvalue-1) &&
	global_settings.valuet <= getnth_tvector_val(the_vectors,global_settings.no_o_vectors - global_settings.kvalue-1) )
	{
		the_vectors = tvector_start(the_vectors);
		while( the_vectors->tvalue <= global_settings.valuet )
		{
			i++;
			the_vectors = the_vectors->next;
		}
		if (  i == global_settings.no_o_vectors - global_settings.kvalue-1 )
		{
			i--;
		}
		bs_calculate_at(the_vectors,the_points,i,global_settings.kvalue,widget);
	}
}

/*
** display the stuff effected by P
*/
void gfx_draw_pon(GtkWidget *widget)
{
	int old_dot_no;
	int old_bspline_no;
	int old_convex_no;
	int numround;
	int i = 0;

	old_dot_no = global_settings.dot_no;
	old_bspline_no = global_settings.bspline_no;
	old_convex_no = global_settings.convex_no;

	the_points = mpoint_start(the_points);

	while ( the_points != which_point )
	{
		i++;
		the_points = the_points->next;
	}
	/* i now equal the point number 
	** the places effected by point p are the last k
	*/
	if ( i - global_settings.kvalue + 2  <=0 )
	{
		global_settings.dot_no = 1;
		global_settings.bspline_no = 1;
		global_settings.convex_no = 1;
	}
	else
	{
		global_settings.dot_no = i - global_settings.kvalue + 2;
		global_settings.bspline_no = i - global_settings.kvalue + 2;
		global_settings.convex_no = i - global_settings.kvalue + 2;
	}
	i += 2;
	if ( i + global_settings.kvalue > global_settings.no_o_points + 1 )
	{
		i = global_settings.no_o_points -  global_settings.kvalue +2;
	}


	if ( global_settings.p_dot_no < 0  || global_settings.p_dot_no > global_settings.kvalue)
		global_settings.p_dot_no = 0;
	if ( global_settings.p_bspline_no < 0 || global_settings.p_bspline_no > global_settings.kvalue)
		global_settings.p_bspline_no = 0;
	if ( global_settings.p_convex_no < 0 || global_settings.p_convex_no > global_settings.kvalue)
		global_settings.p_convex_no = 0;


	/* Do bspline for point */
	if ( global_settings.p_bspline_no == 0 )
	{
		while ( global_settings.bspline_no < i )
		{
			 if ( global_settings.bsplineon == 0 )
				gfx_draw_spline(widget);
			 global_settings.bspline_no++;
		}
	}
	else
	{
		global_settings.bspline_no += global_settings.p_bspline_no - 1;
		if ( global_settings.bsplineon == 0 )
			 gfx_draw_spline(widget);
	}

	/* For the dot to dot */
	if ( global_settings.p_dot_no == 0 )
	{
		while ( global_settings.dot_no < i )
		{
			if ( global_settings.doton == 0 )	
				gfx_dot_to_dot(widget);
			global_settings.dot_no++;
		}
	}
	else
	{
		global_settings.dot_no += global_settings.p_dot_no - 1;
		if ( global_settings.doton == 0 )
			gfx_dot_to_dot(widget);
	}

	/* do convex hull for point */
	if ( global_settings.p_convex_no == 0)
	{
		while ( global_settings.convex_no < i )
		{
			if ( global_settings.convexon == 0 )
				gfx_convex(widget);
			global_settings.convex_no++;
		}	
	}
	else
	{
		global_settings.convex_no += global_settings.p_convex_no - 1;
		if ( global_settings.convexon == 0 )
			gfx_convex(widget);
	}


	if ( global_settings.pointson == 0 )	
		draw_points(widget);
	if ( global_settings.dis_tvec == 0 )
		gfx_display_tvectors(widget);


	global_settings.dot_no = old_dot_no;
	global_settings.bspline_no = old_bspline_no;
	global_settings.convex_no = old_convex_no;
}

/* routine to draw Bsplines Yeah |)
*/
void gfx_draw_spline(GtkWidget *widget)
{
	int q;
	
	global_settings.bspline_no = check_global(global_settings.bspline_no);
	
	if ( global_settings.bspline_no == 0 ) 
	{
		for ( q = global_settings.kvalue-1 ; q < global_settings.no_o_points ; q++ )
		{
			bs_calculateq(the_vectors,the_points,q,global_settings.kvalue,widget);
		}
	}
	else
	{
		bs_calculateq(the_vectors,the_points
				,global_settings.bspline_no+global_settings.kvalue-2,
				global_settings.kvalue,widget);
	}

}

/*******************************************************************/
/*
** +++ THIS NEEDS TO BE MODULIZED
*/
void gfx_convex(GtkWidget *widget)
{
	struct mpoint *copylist = NULL;
	int i;

	the_points = mpoint_start(the_points);

	/* this is done here to allow the deletion of points easily */
	global_settings.convex_no = check_global(global_settings.convex_no);


	if ( global_settings.convex_no == 0 )
	{
		gfx_convex_for(widget,the_points);
	}
	else
	{
		for ( i = 1 ; i < global_settings.convex_no ; i++ )
		{
			the_points = the_points->next;
		}
		for ( i = 0 ; i < global_settings.kvalue-1 ; i++ )
		{
			copylist = newmpoint(the_points->x,the_points->y,copylist);
			the_points = the_points->next;
		}
		copylist = newmpoint(the_points->x,the_points->y,copylist);

		gfx_convex_for(widget,copylist);
		copylist = mpoint_destory(copylist);
	}
}

void gfx_convex_for(GtkWidget *widget,struct mpoint *some_points)
{
	struct mpoint *copylist_hix = NULL;
	struct mpoint *best = NULL;
	int		x1,y1,x2,y2;
	float	dx1,dy1,dx2,dy2,bestgrad;


	some_points = mpoint_start(some_points);
	while ( some_points->next != NULL )
	{
		copylist_hix = newmpoint(some_points->x,some_points->y,copylist_hix);
		some_points = some_points->next;
	}
	copylist_hix = newmpoint(some_points->x,some_points->y,copylist_hix);

	/* sort list to there highest value */
	copylist_hix = mpoint_start(copylist_hix);
	copylist_hix = sort_hix(copylist_hix);

	/* plot them ^:*? */

	/* Get to the starting positions */
	copylist_hix = mpoint_start(copylist_hix);

	/* draw the first side till hi x next = NULL */
	bestgrad = 99999999;

    while (  copylist_hix->next != NULL )
    {
   		x1 = copylist_hix->x;
   		y1 = copylist_hix->y;
   		copylist_hix = copylist_hix->next;
   		dx1 = x1 - copylist_hix->x;
   		dy1 = y1 - copylist_hix->y;
   		if ( dx1 == 0 )
   		{
   		     bestgrad = -999999999;
   		     best = copylist_hix;
   		}
   		bestgrad = dy1 / dx1;

   		best = copylist_hix;
        while ( copylist_hix != NULL )
        {
            dx1 = x1 - copylist_hix->x;
            dy1 = y1 - copylist_hix->y;
            if ( dx1 == 0 )
            {
                bestgrad = -999999999;
                best = copylist_hix;
            }
            if ( ( dy1 / dx1 ) < bestgrad )
            {
                bestgrad = dy1 / dx1;
                best = copylist_hix;
            }
            copylist_hix = copylist_hix->next;
        }
    copylist_hix = best;
    gdk_draw_line(widget->window,widget->style->black_gc,
        copylist_hix->x,copylist_hix->y,
        x1, y1);
    }
	/* right now the other side till = last y */
	copylist_hix = mpoint_end(copylist_hix);


	bestgrad = 999999999;

	while ( copylist_hix->last != NULL )
    {
        x1 = copylist_hix->x;
        y1 = copylist_hix->y;
        copylist_hix = copylist_hix->last;
        dx1 = x1 - copylist_hix->x;
        dy1 = y1 - copylist_hix->y;
        if ( dx1 == 0 )
        {
            bestgrad = -999999999;
            best = copylist_hix;
        }
        bestgrad = dy1 / dx1;

        best = copylist_hix;
        while ( copylist_hix != NULL )
        {
            dx1 = x1 - copylist_hix->x;
            dy1 = y1 - copylist_hix->y;
            if ( dx1 == 0 )
            {
                bestgrad = -999999999;
                best = copylist_hix;
            }
            if ( ( dy1 / dx1 ) < bestgrad )
            {
                bestgrad = dy1 / dx1;
                best = copylist_hix;
            }
            copylist_hix = copylist_hix->last;
        }
    copylist_hix = best;
    gdk_draw_line(widget->window,widget->style->black_gc,
        copylist_hix->x,copylist_hix->y,
        x1, y1);
    }







	/*
	gdk_draw_line(widget->window,widget->style->black_gc,
		copylist_hix->x,copylist_hix->y,
		copylist_hix->last->x, copylist_hix->last->y);
		*/

	copylist_hix = mpoint_destory(copylist_hix);

}
/****************************************************************/

int check_global(int value)
{

	if ( value < 0  )
	{
		value = global_settings.no_o_points - global_settings.kvalue + 1;
	} 
	if ( value >=
				( global_settings.no_o_points - global_settings.kvalue + 2 )
				|| value < 0 )
	{
		value = 0;
	}
	return(value);
		
}
	

/* routine to do joining the dots
*/
void gfx_dot_to_dot(GtkWidget *widget)
{
	GdkGC *gc_green;
    GdkColor *colgreen;
	int i;

	/* Done here to allow easy deletion */
	global_settings.dot_no = check_global(global_settings.dot_no);

    /* set up the cololur green 
    */
    colgreen = malloc(sizeof(GdkColor));
    gdk_color_parse("green",colgreen);
	gdk_color_alloc(global_cmap,colgreen);
    gc_green = gdk_gc_new(widget->window);
    gdk_gc_set_foreground(gc_green,colgreen);

	if ( the_points != NULL )
	{
		the_points = mpoint_start(the_points);
		if ( global_settings.dot_no == 0 )
		{
			while ( the_points->next != NULL )
			{
				gdk_draw_line(widget->window,gc_green,
					the_points->x,the_points->y,the_points->next->x,
					the_points->next->y);
				the_points = the_points->next;
			}
		}
		else
		{
			for ( i = 1 ; i < global_settings.dot_no ; i++ )
			{
				the_points = the_points->next;
			}
			for ( i = 0 ; i < global_settings.kvalue  - 1; i++ )
			{
				gdk_draw_line(widget->window,gc_green,
					the_points->x,the_points->y,the_points->next->x,
					the_points->next->y);
				the_points = the_points->next;
			}
		}
	}
	gdk_gc_destroy(gc_green);
	free(colgreen);
	
}

/* routine to display teh Tvector at the top
** of the window area
*/
void gfx_display_tvectors(GtkWidget *widget)
{
	char the_text[2024];
	char temp[100];
	GdkFont	*font;

	the_vectors = tvector_start(the_vectors);
	sprintf(the_text,"[ ");
	while( the_vectors->next != NULL)
		{
		sprintf(temp,"%.2f ",the_vectors->tvalue);
		strcat(the_text,temp);
		the_vectors = the_vectors->next;
		}
	sprintf(temp,"%.2f ]",the_vectors->tvalue);
	strcat(the_text,temp);
	font = gdk_font_load ("-adobe-helvetica-medium-r-normal--*-80-*-*-*-*-*-*");
	gdk_draw_string(widget->window, font,widget->style->black_gc,3,8,the_text);

	gdk_font_free(font);
	
}

/* routines To draw
** each point with the corresponding name 
*/
void draw_points(GtkWidget *widget)
{
	if ( the_points != NULL )
	{
		the_points = mpoint_start(the_points);
		while ( the_points->next != NULL )
		{
			gfx_draw_dot(widget,the_points->x,the_points->y);
			the_points = the_points->next;
		}
		gfx_draw_dot(widget,the_points->x,the_points->y);
	}

}

void gfx_draw_dot(GtkWidget *widget, int x,int y)
{
	char *str;
	GdkGC *gc_red;
	GdkColor *colred;
	GdkFont	*font;

	/* set up the cololur red 
	*/
	colred = malloc(sizeof(GdkColor));
	gdk_color_parse("red",colred);
	gdk_color_alloc(global_cmap,colred);
	gc_red = gdk_gc_new(widget->window);
	gdk_gc_set_foreground(gc_red,colred);
	
	/* setup a string for the text 
	** +++ Set length should be dynamic
	*/
	str = malloc(1024);
		
	gdk_draw_arc( widget->window, gc_red, TRUE, x-3, y-3, 5, 5, 0, 64*360);
	if ( the_points == which_point )
		gdk_draw_rectangle( widget->window, gc_red, FALSE, x-4, y-4, 7, 7);
	sprintf(str,"p");
	get_all_points(the_points,x,y,str);
	font = gdk_font_load ("-adobe-helvetica-medium-r-normal--*-80-*-*-*-*-*-*");
	if ( global_settings.disp == 0 )	
		gdk_draw_string(widget->window, font ,gc_red,x+4,y+6,str);
	gdk_font_free(font);
	gdk_gc_destroy(gc_red);
	free(colred);
	free(str);
}

/*****************************************************************/


/*** Code for events that may happen mouse /keyboard***/
gint
gfx_button_release_event (GtkWidget *widget, GdkEventButton *event)
{
	if ( event->button == 1 )
	{
		return(0);
	}
}

gint
gfx_motion_notify_event (GtkWidget *widget, GdkEventMotion *event)
{
	if (event->state & GDK_BUTTON1_MASK && which_point != NULL)
	{
		which_point->x = event->x;
		which_point->y = event->y;
		gfx_refresh();
	}
}

gint
gfx_key_press_event (GtkWidget *widget, GdkEventKey *event)
{
	if ( which_point != NULL )
	{
		switch (event->keyval)
		{
			case GDK_Up: which_point->y -=1; break;
			case GDK_Down: which_point->y += 1; break;
			case GDK_Left: which_point->x -=1; break;
			case GDK_Right: which_point->x +=1; break;
			default:
				break;
		}
	gfx_refresh();
	}
}

gint
gfx_button_press_event (GtkWidget *widget, GdkEventButton *event)
{
	struct mpoint *temp;
	if ( event->button == 1 && global_settings.placeing == 0) 
	{
	 temp = get_point(the_points,event->x,event->y);
		if ( temp != NULL )
		{
			temp->x = event->x;
			temp->y = event->y;
			which_point = temp;
			gfx_refresh();
		}
		else 
		{
	 		which_point = NULL;
		}
	}
	else if ( event->button == 1 && global_settings.placeing > 0)
	{
		/* are we placing a point 1 = next 2 = before 3 = after*/
		if ( global_settings.placeing == 2 && which_point != NULL)
		{
		the_points = which_point->last->last;
		}
		else if ( global_settings.placeing == 3 && which_point != NULL)
		{
			the_points = which_point;
		}
		else
		{
			the_points = mpoint_end(the_points);
		}
	
		the_points = newmpoint(event->x,event->y,the_points);
		the_vectors = tvector_end(the_vectors);
		the_vectors = newtvector(the_vectors->tvalue+global_settings.uni_skip
							,the_vectors);
		global_settings.no_o_points++;
		global_settings.no_o_vectors++;
		which_point = mpoint_end(the_points);
		gfx_refresh();
	}
	else if ( event->button == 2 )
	{
		printf("Middle Button pressed\n");
	} 
	else
	{
	temp = get_point(the_points,event->x,event->y);
		if ( temp != NULL )
		{
		if ( temp == which_point )
			which_point = NULL;
		the_points = delmpoint(temp);
		the_vectors = tvector_end(the_vectors);
		the_vectors = deltvector(the_vectors);
		global_settings.no_o_points--;
		global_settings.no_o_vectors--;
		gfx_refresh();
		}
	}

	
	return FALSE;
}


/* STUFF TO DO WITH EXPOSEING THE SCREEN
*/
void gfx_refresh()
{
	gtk_widget_hide(drawing_area);
	gtk_widget_show(drawing_area);
}
gint
configure_event (GtkWidget *widget, GdkEventConfigure *event)
{
/* set background color to white */

  return TRUE;
}


/*  Put in all those things */
gint
expose_event (GtkWidget *widget, GdkEventExpose *event)
{
	/* THIS WILL BE A FUNCTIONS TO GO THROUGH THE POINTS */
	if ( the_points != NULL )
	{
		if ( global_settings.p_on == 1 && which_point != NULL )
		{
			gfx_draw_pon(widget);
		}
		else
		{
			if ( global_settings.pointson == 0 )	
				draw_points(widget);
			if ( global_settings.doton == 0 )	
				gfx_dot_to_dot(widget);
			if ( global_settings.dis_tvec == 0 )
				gfx_display_tvectors(widget);
			if ( global_settings.bsplineon == 0 )
				gfx_draw_spline(widget);
			if ( global_settings.convexon == 0 )
				gfx_convex(widget);
			if ( global_settings.t_on == 1 )
				gfx_draw_ton(widget);
		}
	}

  return FALSE;
}

void gfx_window_destory()
{
}


void gfx_window()
{
    GtkWidget *window2 = NULL;
	GtkWidget *vbox;
	GdkCursor *cursor;
	int i;

	global_settings.kvalue = 4;
	global_settings.no_o_points = 5;
	global_settings.no_o_vectors = 10;
	global_settings.current_t = 0;
	global_settings.uniform = 1;
	global_settings.uni_start = 0;
	global_settings.uni_skip = 1;
	global_settings.gran = 100;
	global_settings.disq = 1;
	global_settings.dist = 1;
	global_cmap = gdk_colormap_get_system();

	the_points = newmpoint(10,45,the_points);
	the_points = newmpoint(20,150,the_points);
	the_points = newmpoint(90,50,the_points);
	the_points = newmpoint(129,52,the_points);
	the_points = newmpoint(100,130,the_points);
	for ( i = 0 ; i < 9 ; i++ )
	{
		the_vectors = newtvector(i,the_vectors);
	}

    if (!window2)
    {

        window2 = gtk_window_new (GTK_WINDOW_TOPLEVEL);


        gtk_widget_set_name (window2, "DISPLAY");
        gtk_signal_connect (GTK_OBJECT (window2), "destroy",
            (GtkSignalFunc) gfx_destroy_window,
            &window2);
        gtk_window_set_title (GTK_WINDOW (window2), "DISPLAY");
        gtk_container_border_width (GTK_CONTAINER (window2), 0);

		/* create a box for the drwaing area*/
		vbox = gtk_vbox_new (FALSE, 0);
		gtk_container_add (GTK_CONTAINER (window2), vbox);
		gtk_widget_show (vbox);


		/* create a drawing area */
		drawing_area = gtk_drawing_area_new ();

/*		gdk_window_set_background(drawing_area->window, whitepix);*/

		gtk_drawing_area_size (GTK_DRAWING_AREA (drawing_area), 200, 200);
		gtk_box_pack_start (GTK_BOX (vbox), drawing_area, TRUE, TRUE, 0);

		gtk_widget_show (drawing_area);

		/* Signals to display the area 
		** e.g. from behind a window to infront 
		** X-refresh command etc.
		*/
		gtk_signal_connect (GTK_OBJECT (drawing_area), "expose_event",
			(GtkSignalFunc) expose_event, NULL);
		gtk_signal_connect (GTK_OBJECT(drawing_area),"configure_event",
			(GtkSignalFunc) configure_event, NULL);

		/* Attch events to the drawing area and 
		** there related functios.
		*/
		gtk_signal_connect (GTK_OBJECT (drawing_area), "button_press_event",
			(GtkSignalFunc) gfx_button_press_event, NULL);
		gtk_signal_connect (GTK_OBJECT (drawing_area), "motion_notify_event",
		 	(GtkSignalFunc) gfx_motion_notify_event, NULL);
		gtk_signal_connect (GTK_OBJECT (drawing_area), "button_release_event",
			(GtkSignalFunc) gfx_button_release_event, NULL);
		gtk_signal_connect (GTK_OBJECT (drawing_area), "key_press_event",
			(GtkSignalFunc) gfx_key_press_event, NULL);


		/* set the event masks so that the we a notifed of
		** certain events :)
		*/
		gtk_widget_set_events (drawing_area, GDK_EXPOSURE_MASK
             | GDK_LEAVE_NOTIFY_MASK
             | GDK_BUTTON_PRESS_MASK
			 | GDK_KEY_PRESS_MASK
             | GDK_POINTER_MOTION_MASK
             | GDK_POINTER_MOTION_HINT_MASK
             | GDK_PROXIMITY_OUT_MASK);


		/* The following call enables tracking and processing of extension
		events for the drawing area */
		gtk_widget_set_extension_events (drawing_area, GDK_EXTENSION_EVENTS_ALL);


	}

	if (!GTK_WIDGET_VISIBLE (window2))
		gtk_widget_show (window2);
	else
		gtk_widget_destroy (window2);


	/*Set up a nice Cursor */
	cursor = gdk_cursor_new (GDK_CROSSHAIR);
	gdk_window_set_cursor (window2->window,cursor);
	gdk_cursor_destroy (cursor);

}

