/* $Id: main.c,v 1.5 1997/11/09 00:32:39 simon Exp simon $
** main.c
** simon 02/11/1997
** Copyright Simon Loader 1997
** simon@surf.org.uk http://www.surf.org.uk/
**  Program to create menus / buttons / input boxes etc.
** for GFX bspline project :)
*/


#include <gtk/gtk.h>

#include "main.h"
#include "menus.h"
#include "gfx_window.h"
#include "gfx_label.h"
#include "gfx_io.h"

/* destory a window */

void destroy_window (GtkWidget  *widget,
        GtkWidget **window)
{
  *window = NULL;
}



main(int argc, char *argv[])
  {
      GtkWidget *window;
      GtkWidget *main_vbox;
      GtkWidget *menubar;
	GtkWidget *table;
	  GtkWidget *button;
	  GtkWidget *box1;

      GtkAcceleratorTable *accel;

      gtk_init(&argc, &argv);


	  /* set up a window */
      window = gtk_window_new(GTK_WINDOW_TOPLEVEL);
      gtk_signal_connect(GTK_OBJECT(window), "destroy",
                         GTK_SIGNAL_FUNC(file_quit_cmd_callback),
                         "WM destroy");
      gtk_window_set_title(GTK_WINDOW(window), "Bspilines Project");
      gtk_widget_set_usize(GTK_WIDGET(window), 350, 250);

/* HERE TO HERE END SHOULD BE IN A FUNCTION WHICH TAKES WINDOW */
	/* ste up box for menu system*/
      main_vbox = gtk_vbox_new(FALSE, 1);
      gtk_container_border_width(GTK_CONTAINER(main_vbox), 1);
     gtk_container_add(GTK_CONTAINER(window), main_vbox);
      gtk_widget_show(main_vbox);

	/* create a menu bar using factory method easy*/
      get_main_menu(&menubar, &accel);
      gtk_window_add_accelerator_table(GTK_WINDOW(window), accel);
      gtk_box_pack_start(GTK_BOX(main_vbox), menubar, FALSE, TRUE, 0);
      gtk_widget_show(menubar);

/* HERE END */

/* create some click on off buttons */
	/* first creat a box for them */
	box1 = gtk_vbox_new (FALSE, 0);
	gtk_box_pack_start(GTK_BOX(main_vbox), box1, FALSE, TRUE, 0);
	gtk_widget_show (box1);


	/* create a table for them to lie in */
	table = gtk_table_new (8, 4, FALSE);
	gtk_container_border_width (GTK_CONTAINER (table), 10);
	gtk_box_pack_start (GTK_BOX (box1), table, TRUE, TRUE, 0);
	gtk_widget_show (table);


	/* convex Hull buttton*/
	button = gtk_toggle_button_new_with_label ("Convex Hull");
	gtk_signal_connect (GTK_OBJECT (button), "clicked",
		 GTK_SIGNAL_FUNC (switch_convex),NULL);
	gtk_table_attach_defaults (GTK_TABLE (table), button,0,1,0,1);
	gtk_widget_show (button);

	/* convex hull backward and forward button */
	button = gtk_button_new_with_label ("<");
	gtk_signal_connect (GTK_OBJECT (button), "clicked",
		GTK_SIGNAL_FUNC (button_convex_dec),NULL);
	gtk_table_attach_defaults (GTK_TABLE (table), button,1,2,0,1);
	gtk_widget_show (button);
	button = gtk_button_new_with_label (">");
	gtk_signal_connect (GTK_OBJECT (button), "clicked",
		GTK_SIGNAL_FUNC (button_convex_inc),NULL);
	gtk_table_attach_defaults (GTK_TABLE (table), button,2,3,0,1);
	gtk_widget_show (button);

	/* bspline operartions */
	button = gtk_toggle_button_new_with_label ("Bspline Curve");
	gtk_table_attach_defaults (GTK_TABLE (table), button,0,1,1,2);
	gtk_signal_connect (GTK_OBJECT (button), "clicked",
		GTK_SIGNAL_FUNC (switch_bspline),NULL);
	gtk_widget_show (button);
	button = gtk_button_new_with_label ("<");
	gtk_table_attach_defaults (GTK_TABLE (table), button,1,2,1,2);
	gtk_signal_connect (GTK_OBJECT (button), "clicked",
		GTK_SIGNAL_FUNC (button_bspline_dec),NULL);
	gtk_widget_show (button);
	button = gtk_button_new_with_label (">");
	gtk_table_attach_defaults (GTK_TABLE (table), button,2,3,1,2);
	gtk_signal_connect (GTK_OBJECT (button), "clicked",
		GTK_SIGNAL_FUNC (button_bspline_inc),NULL);
	gtk_widget_show (button);

	/* dot to dot operations */
	button = gtk_toggle_button_new_with_label ("Dot-to-Dot");
	gtk_table_attach_defaults (GTK_TABLE (table), button,0,1,2,3);
	gtk_signal_connect (GTK_OBJECT (button), "clicked",
		 GTK_SIGNAL_FUNC (switch_dtd),NULL);
	gtk_widget_show (button);
	button = gtk_button_new_with_label ("<");
	gtk_table_attach_defaults (GTK_TABLE (table), button,1,2,2,3);
	gtk_signal_connect (GTK_OBJECT (button), "clicked",
		 GTK_SIGNAL_FUNC (button_dtd_dec),NULL);
	gtk_widget_show (button);
	button = gtk_button_new_with_label (">");
	gtk_table_attach_defaults (GTK_TABLE (table), button,2,3,2,3);
	gtk_signal_connect (GTK_OBJECT (button), "clicked",
		 GTK_SIGNAL_FUNC (button_dtd_inc),NULL);
	gtk_widget_show (button);

	/* clear button */
	button = gtk_button_new_with_label ("clear");
	gtk_table_attach_defaults (GTK_TABLE (table), button,3,4,0,1);
	gtk_signal_connect (GTK_OBJECT (button), "clicked",
		 GTK_SIGNAL_FUNC (button_clear),NULL);
	gtk_widget_show (button);

	/* exit button */
	button = gtk_button_new_with_label ("EXIT");
	gtk_table_attach_defaults (GTK_TABLE (table), button,3,4,1,2);
	gtk_signal_connect (GTK_OBJECT (button), "clicked",
	        GTK_SIGNAL_FUNC (file_quit_cmd_callback),"\n");
	gtk_widget_show (button);

	/* place a new dot on the screen */
	button = gtk_toggle_button_new_with_label ("New dot");
	gtk_table_attach_defaults (GTK_TABLE (table), button,3,4,2,3);
	gtk_signal_connect (GTK_OBJECT (button), "clicked",
			GTK_SIGNAL_FUNC (button_new_dot), NULL);
	gtk_widget_show (button);

	/* matrix toggle button */
	button = gtk_toggle_button_new_with_label ("Matrix");
	gtk_table_attach_defaults (GTK_TABLE (table), button,0,1,3,4);
	gtk_signal_connect (GTK_OBJECT (button), "clicked",
		GTK_SIGNAL_FUNC (switch_matrix),NULL);
	gtk_widget_show (button);

	/* Text for spline on/off */
	button = gtk_toggle_button_new_with_label ("Q`s");
	gtk_table_attach_defaults (GTK_TABLE (table), button,1,2,3,4);
	gtk_signal_connect (GTK_OBJECT (button), "clicked",
		GTK_SIGNAL_FUNC (button_disq),NULL);
	gtk_widget_show (button);

	/* Text for nodes on/off which controlled by bspline */
	button = gtk_toggle_button_new_with_label ("T`s");
	gtk_table_attach_defaults (GTK_TABLE (table), button,2,3,3,4);
	gtk_signal_connect (GTK_OBJECT (button), "clicked",
		GTK_SIGNAL_FUNC (button_dist),NULL);
	gtk_widget_show (button);
	
	/* Toggle lableing of points */
	button = gtk_toggle_button_new_with_label ("P`s");
	gtk_table_attach_defaults (GTK_TABLE (table), button,3,4,3,4);
	gtk_signal_connect (GTK_OBJECT (button), "clicked",
		GTK_SIGNAL_FUNC (button_disp),NULL);
	gtk_widget_show (button);

	/* display vector toggle */
	button = gtk_toggle_button_new_with_label ("Vectors");
	gtk_table_attach_defaults (GTK_TABLE (table), button,0,1,4,5);
	gtk_signal_connect (GTK_OBJECT (button), "clicked",
			GTK_SIGNAL_FUNC (switch_tvector),NULL);
	gtk_widget_show (button);

	/* Edit uniform Tvectors button */
	button = gtk_toggle_button_new_with_label ("Edit uni T`s");
	gtk_table_attach_defaults (GTK_TABLE (table), button,1,2,4,5);
	gtk_signal_connect (GTK_OBJECT (button), "clicked",
						GTK_SIGNAL_FUNC (button_edit_uni_tvec) , NULL);
	gtk_widget_show (button);

	/* Edit non-uniform Tvectors button */
	button = gtk_toggle_button_new_with_label ("Edit non-uni T`s");
	gtk_table_attach_defaults (GTK_TABLE (table), button,2,3,4,5);
	gtk_signal_connect (GTK_OBJECT (button), "clicked",
						GTK_SIGNAL_FUNC (button_edit_nonuni_tvec) , NULL);
	gtk_widget_show (button);

	/* Set value of K */
	button = gtk_button_new_with_label ("Edit K");
	gtk_table_attach_defaults (GTK_TABLE (table), button,3,4,4,5);
	gtk_signal_connect (GTK_OBJECT (button), "clicked",
			GTK_SIGNAL_FUNC (button_set_k), NULL);
	gtk_widget_show (button);

	/* show vlaue T  toggle */
	button = gtk_toggle_button_new_with_label ("Point T");
	gtk_table_attach_defaults (GTK_TABLE (table), button,0,1,5,6);
	gtk_signal_connect (GTK_OBJECT (button), "clicked",
		 GTK_SIGNAL_FUNC (switch_t_on),NULL);
	gtk_widget_show (button);
	
	/* Set value T */
	button = gtk_button_new_with_label ("Set T");
	gtk_table_attach_defaults (GTK_TABLE (table), button,1,2,5,6);
	gtk_signal_connect (GTK_OBJECT (button), "clicked",
		 GTK_SIGNAL_FUNC (button_set_tpoint),NULL);
	gtk_widget_show (button);


	/* show lines effected by point P toggle */
	button = gtk_toggle_button_new_with_label ("-P-");
	gtk_table_attach_defaults (GTK_TABLE (table), button,3,4,5,6);
	gtk_signal_connect (GTK_OBJECT (button), "clicked",
		 GTK_SIGNAL_FUNC (switch_p_on),NULL);
	gtk_widget_show (button);

	/* The points display of the dots and text*/
	button = gtk_toggle_button_new_with_label ("Points");
	gtk_table_attach_defaults (GTK_TABLE (table), button,0,1,6,7);
	gtk_signal_connect (GTK_OBJECT (button), "clicked",
					GTK_SIGNAL_FUNC (switch_points), NULL);
	gtk_widget_show (button);

	/* edit granultarty */
	button = gtk_button_new_with_label ("Edit Gran");
	gtk_table_attach_defaults (GTK_TABLE (table), button,1,2,6,7);
	gtk_signal_connect (GTK_OBJECT (button), "clicked",
					GTK_SIGNAL_FUNC (button_set_gran), NULL);
	gtk_widget_show (button);

	/* Uniform on off IS THIS TEH RIGHT PLACE TO PUT IT */
	button = gtk_button_new_with_label ("Uniform");
	gtk_table_attach_defaults (GTK_TABLE (table), button,2,4,6,7);
	gtk_signal_connect (GTK_OBJECT (button), "clicked",
		GTK_SIGNAL_FUNC (switch_uniform),NULL);
	gtk_widget_show (button);


	/* INsert the new button after chosen */
	button = gtk_toggle_button_new_with_label ("Insert After");
	gtk_table_attach_defaults (GTK_TABLE (table), button,0,1,7,8);
	gtk_signal_connect (GTK_OBJECT (button), "clicked",
		GTK_SIGNAL_FUNC (switch_after),NULL);
	gtk_widget_show (button);

	/* INsert the new button before chosen */
	button = gtk_toggle_button_new_with_label ("Insert Before");
	gtk_table_attach_defaults (GTK_TABLE (table), button,1,2,7,8);
	gtk_signal_connect (GTK_OBJECT (button), "clicked",
		GTK_SIGNAL_FUNC (switch_before),NULL);
	gtk_widget_show (button);
/* end button making */

	/* display and be happy */
      gtk_widget_show(window);

	  /* gfx window */
	  gfx_window();

      gtk_main();

      return(0);
  }

 /*
 ** exit routine
 */

  void file_quit_cmd_callback (GtkWidget *widget, gpointer data)
  {
  	gfx_window_destory();
      g_print ("%s\n", (char *) data);
      gtk_exit(0);
  }


void switch_uniform(GtkWidget *widget,gpointer data)
{
		the_vectors = maketvectors(the_vectors,global_settings.uni_start,global_settings.uni_skip);
	gfx_refresh();
}
void switch_matrix(GtkWidget *widget,gpointer data)
{
	if ( global_settings.matrix == 1 )
		global_settings.matrix = 0;
	else
		global_settings.matrix = 1;
	gfx_refresh();
}


void switch_p_on(GtkWidget *widget,gpointer data)
{
	/* make it start showing all*/
	global_settings.p_convex_no = 0;
	global_settings.p_bspline_no = 0;
	global_settings.p_dot_no = 0;
	
	if ( global_settings.p_on == 1 )
		global_settings.p_on = 0;
	else
		global_settings.p_on = 1;
	gfx_refresh();
}
void switch_t_on(GtkWidget *widget,gpointer data)
{
	if ( global_settings.t_on == 1 )
		global_settings.t_on = 0;
	else
		global_settings.t_on = 1;
	gfx_refresh();
}


void switch_convex(GtkWidget *widget,gpointer data)
{
	if ( global_settings.convexon == 1 )
		global_settings.convexon = 0;
	else
		global_settings.convexon = 1;
	gfx_refresh();
}
void button_convex_dec(GtkWidget *widget,gpointer data)
{
	global_settings.convex_no--;
	global_settings.p_convex_no--;
	gfx_refresh();
}

void button_convex_inc(GtkWidget *widget,gpointer data)
{
	global_settings.convex_no++;
	global_settings.p_convex_no++;
	gfx_refresh();
}

void switch_bspline(GtkWidget *widget,gpointer data)
{
	if ( global_settings.bsplineon == 1 )
		global_settings.bsplineon = 0;
	else
		global_settings.bsplineon = 1;
	gfx_refresh();
}

void button_bspline_inc(GtkWidget *widget,gpointer data)
{
	global_settings.bspline_no++;
	global_settings.p_bspline_no++;
	gfx_refresh();
}


void button_bspline_dec(GtkWidget *widget,gpointer data)
{
	global_settings.bspline_no--;
	global_settings.p_bspline_no--;
	gfx_refresh();
}


void switch_dtd(GtkWidget *widget,gpointer data)
{
	if ( global_settings.doton == 1 )
		global_settings.doton = 0;
	else
		global_settings.doton = 1;
	gfx_refresh();
}
void button_dtd_inc(GtkWidget *widget,gpointer data)
{
	global_settings.p_dot_no++;
	global_settings.dot_no++;
	gfx_refresh();
}
void button_dtd_dec(GtkWidget *widget,gpointer data)
{
	global_settings.p_dot_no--;
	global_settings.dot_no--;
	gfx_refresh();
}

void switch_tvector(GtkWidget *widget,gpointer data)
{
	if ( global_settings.dis_tvec == 1 )
		global_settings.dis_tvec = 0;
	else
		global_settings.dis_tvec = 1;
	gfx_refresh();
}

void button_new_dot(GtkWidget *widget,gpointer data)
{
	if ( global_settings.placeing == 1 )
		global_settings.placeing = 0;
	else if ( global_settings.placeing == 0 )
		global_settings.placeing = 1;
	else
		gtk_toggle_button_set_state(widget,FALSE);
}
void switch_after(GtkWidget *widget,gpointer data)
{
	if ( global_settings.placeing == 3 )
		global_settings.placeing = 0;
	else if ( global_settings.placeing == 0 )
		global_settings.placeing = 3;
	else
		gtk_toggle_button_set_state(widget,FALSE);
}

void switch_before(GtkWidget *widget,gpointer data)
{
	if ( global_settings.placeing == 2 )
		global_settings.placeing = 0;
	else if ( global_settings.placeing == 0 )
		global_settings.placeing = 2;
	else
		gtk_toggle_button_set_state(widget,FALSE);
}


void button_set_k(GtkWidget *widget,gpointer data)
{
	char stri[10];
	sprintf(stri,"%d",global_settings.kvalue);
	gfx_getinput(stri,widget,(GtkSignalFunc) k_return);
}
void k_return(GtkWidget *widget,GtkWidget **window)
{
 /* get the text , check and set */
 char *value, *end = NULL;
 int j,k,addts = 0;
 int i = 0;

 value = gtk_entry_get_text (GTK_ENTRY (gfx_entry));
	i = (int) strtod(value,&end);

 if ( i > 0 && i < 50 )
 {
 	addts = i - global_settings.kvalue;
	global_settings.kvalue = i;
	the_vectors = tvector_end(the_vectors);
	if ( addts < 0 )
	{
		for ( i = 0 ; i < addts * -1 ; i++ )
		{
			the_vectors = deltvector(the_vectors);
			global_settings.no_o_vectors--;
		}
	}
	if ( addts > 0 )
	{
		for ( i = 0 ; i < addts ; i++ )
		{
			the_vectors = newtvector(
					the_vectors->tvalue+global_settings.uni_skip,the_vectors);
			global_settings.no_o_vectors++;
		}
	}
 }


	gtk_widget_destroy(widget);
	gfx_refresh();
}

void button_set_gran(GtkWidget *widget,gpointer data)
{
	char stri[10];
	sprintf(stri,"%d",global_settings.gran);
	gfx_getinput(stri,widget,(GtkSignalFunc) gran_return);
}
void gran_return(GtkWidget *widget,GtkWidget **window)
{
	char *value, *end;
	int i;

	value = gtk_entry_get_text (GTK_ENTRY (gfx_entry));
	i = (int) strtod(value,&end);  /* end is just a null pointer */
	global_settings.gran = i;
	gtk_widget_destroy(widget);
	gfx_refresh();
}

void button_set_tpoint(GtkWidget *widget,gpointer data)
{
	char stri[10];
	sprintf(stri,"%f",global_settings.valuet);
	gfx_getinput(stri,widget,(GtkSignalFunc) tvalue_return);
}
void tvalue_return(GtkWidget *widget,GtkWidget **window)
{
	char *value, *end;
	double i;

	value = gtk_entry_get_text (GTK_ENTRY (gfx_entry));
	i = (double) strtod(value,&end);  /* end is just a null pointer */
	if ( i >= getnth_tvector_val(the_vectors,global_settings.kvalue-1) &&
			i <= getnth_tvector_val(the_vectors,global_settings.no_o_vectors - global_settings.kvalue-1) )
	{
		global_settings.valuet = i;
	}
	else
	{
		gfx_message("NOT IN RANGE");
	}
	gtk_widget_destroy(widget);
	gfx_refresh();
}

void button_disq(GtkWidget *widget,gpointer data)
{
    if ( global_settings.disq == 1 )
        global_settings.disq = 0;
    else
        global_settings.disq = 1;
	gfx_refresh();
}

void button_dist(GtkWidget *widget,gpointer data)
{
    if ( global_settings.dist == 1 )
        global_settings.dist = 0;
    else
        global_settings.dist = 1;
	gfx_refresh();
}
void button_disp(GtkWidget *widget,gpointer data)
{
	if ( global_settings.disp == 1 )
		global_settings.disp = 0;
	else
		global_settings.disp = 1;
	gfx_refresh();
}
void switch_points(GtkWidget *widget,gpointer data)
{
	if ( global_settings.pointson == 1 )
		global_settings.pointson = 0;
	else
		global_settings.pointson = 1;
	gfx_refresh();
}

void button_clear(GtkWidget *widget,gpointer data)
{
 	int i;

	the_points = mpoint_destory(the_points);
	which_point = NULL;
	global_settings.no_o_points = 0;
	the_vectors = tvector_end(the_vectors);
	for ( i = global_settings.no_o_vectors ; i >  global_settings.kvalue+1 ; i-- )
	{
		the_vectors = deltvector(the_vectors);
		global_settings.no_o_vectors--;
	}
	gfx_refresh();

}



void help_info (GtkWidget *widget,gpointer data)
{
	static GtkWidget *window = NULL;
	GtkWidget *box1;
	GtkWidget *box2;
	GtkWidget *button;
	GtkWidget *text;

	if (!window)
	{
		window = gtk_window_new (GTK_WINDOW_TOPLEVEL);
		gtk_widget_set_name (window, "INFO");
		gtk_signal_connect (GTK_OBJECT (window), "destroy",
			(GtkSignalFunc) destroy_window,
			&window);
		gtk_window_set_title (GTK_WINDOW (window), "INFO");
		gtk_container_border_width (GTK_CONTAINER (window), 0);
		

		/* creat a box for text */
		box1 = gtk_vbox_new (FALSE, 0);
		gtk_container_add (GTK_CONTAINER (window), box1);
		gtk_widget_show (box1);
		

		/*Cenrate some text*/
		text = gtk_text_new (NULL, NULL);
		gtk_box_pack_start (GTK_BOX (box1), text,TRUE,TRUE,0);
		gtk_widget_show (text);
		gtk_text_freeze (GTK_TEXT (text));
		gtk_widget_realize (text);
		gtk_text_insert (GTK_TEXT (text), NULL, &text->style->black, NULL, "Bspline Project\n",-1);
		gtk_text_insert (GTK_TEXT (text), NULL, &text->style->black, NULL, "By simon Loader\n",-1);
		gtk_text_insert (GTK_TEXT (text), NULL, &text->style->black, NULL, "   (c) 1997 \n",-1);
		gtk_text_thaw (GTK_TEXT (text));

		/* create a box for close widget */
		box2 = gtk_vbox_new (FALSE, 10);
		gtk_container_border_width (GTK_CONTAINER (box2), 10);
		gtk_box_pack_start (GTK_BOX (box1), box2, TRUE, TRUE, 0);
		gtk_widget_show (box2);

		/* create a close button */
		button = gtk_button_new_with_label ("close");
		gtk_signal_connect_object (GTK_OBJECT (button), "clicked",
			(GtkSignalFunc) gtk_widget_destroy,
			GTK_OBJECT (window));

		gtk_box_pack_start (GTK_BOX (box2), button, TRUE, TRUE, 0);
		GTK_WIDGET_SET_FLAGS (button, GTK_CAN_DEFAULT);
		gtk_widget_grab_default (button);
		gtk_widget_show (button);
	}


	if (!GTK_WIDGET_VISIBLE (window))
		gtk_widget_show (window);
	else
		gtk_widget_destroy (window);
}

