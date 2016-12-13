/* $Id: gfx_label.c,v 1.1 1997/11/09 00:31:25 simon Exp simon $
** simon Sat Nov  8 15:15:38 GMT 1997
** Copyright Simon Loader 1997
** simon@surf.org.uk http://www.surf.org.uk/
** gfx_io.c
** Program to do all the input windows for the gfx program
** mainly implementing vector editing functions
*/

#include "gfx_io.h"


/* Open a simple window for any text input , put it
**  in a global variable Yuk and call the specifed function
** when done 
*/
void gfx_getinput(char *str,GtkWidget *widget,GtkSignalFunc func)
{

	static GtkWidget *window = NULL;
	GtkWidget *box1;
	GtkWidget *button;


	/* create a window */
	window = gtk_window_new (GTK_WINDOW_TOPLEVEL);
	gtk_signal_connect (GTK_OBJECT (window), "destroy",
	        (GtkSignalFunc) destroy_window,
			&window);
	gtk_window_set_title (GTK_WINDOW (window), " Enter");
	gtk_container_border_width (GTK_CONTAINER (window), 0);


	/* a box for things to go in */
	box1 = gtk_vbox_new (FALSE, 0); 
	gtk_container_add (GTK_CONTAINER (window), box1);
	gtk_widget_show (box1);
	

	/* A text box to edit and set the current value */
	gfx_entry = gtk_entry_new ();
	gtk_entry_set_text (GTK_ENTRY (gfx_entry),str);
	gtk_box_pack_start (GTK_BOX (box1), gfx_entry, TRUE, TRUE, 0);
	gtk_widget_show (gfx_entry);


	/* an ok button for when finished 
	** actully runs defines function which 
	** must kill the window
	*/
	button = gtk_button_new_with_label ("Ok");
	gtk_signal_connect_object (GTK_OBJECT (button), "clicked",
			func, GTK_OBJECT (window));
	gtk_box_pack_start (GTK_BOX (box1), button, TRUE, TRUE, 0);
	gtk_widget_show(button);

	/* show it all */
	gtk_widget_show (window);
	

}

/* Display a simple message as a button and close
** the window when the button is pressed 
*/
void gfx_message(char *message)
{
    static GtkWidget *window = NULL;
    GtkWidget *box1;
    GtkWidget *box2;
    GtkWidget *button;


	if (window)
	{
        gtk_widget_destroy (window);
		window = NULL;
	}

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


        /* create a box for close widget */
        box2 = gtk_vbox_new (FALSE, 10);

        gtk_container_border_width (GTK_CONTAINER (box2), 10);
        gtk_box_pack_start (GTK_BOX (box1), box2, TRUE, TRUE, 0);
        gtk_widget_show (box2);

        /* create a close button */
        button = gtk_button_new_with_label (message);
        gtk_signal_connect_object (GTK_OBJECT (button), "clicked",
            (GtkSignalFunc) gtk_widget_destroy,
            GTK_OBJECT (window));

        gtk_box_pack_start (GTK_BOX (box2), button, TRUE, TRUE, 0);
        GTK_WIDGET_SET_FLAGS (button, GTK_CAN_DEFAULT);
        gtk_widget_grab_default (button);
        gtk_widget_show (button);
    }

    gtk_widget_show (window);

}


/*************************************************************************/
/* code for editing the tvectors II 
** first lost lost in a mem crash 
** UNIFORM version
*/
/* expose routine for uniform vector so it is kept up to date
** of the changes ( called on a timer )
*/
void edit_uni_tvec_expose(GtkWidget *widget, GdkEventExpose *event)
{
	static GtkWidget *label;
	char info_vector[128];

	/* if there is already a label destroy it */
	if ( label != NULL && GTK_WIDGET_VISIBLE(label))
	{
		gtk_widget_destroy(label);
		label = NULL;
	}

	/* set up new label and display */
		sprintf(info_vector,"Start is %.2f and jump = %.2f",global_settings.uni_start,global_settings.uni_skip);

	label = gtk_label_new (info_vector);
	gtk_misc_set_padding (GTK_MISC (label), 10, 10);
	gtk_box_pack_start(GTK_BOX (GTK_DIALOG (widget)->vbox),label, TRUE, TRUE,0);
	gtk_widget_show (label);

}

/**********************************************************/
/* return for setting the start of a uniform vectors */
void edit_vect_uni_start_rts(GtkWidget *widget,GtkWidget **window)
{
 /* get the text , check and set */
  char *value, *end;
  double i;

	/* get value convert and make the new vectors */
  value = gtk_entry_get_text (GTK_ENTRY (gfx_entry));
  i = (double) strtod(value,&end);
  global_settings.uni_start = i;
  the_vectors = maketvectors(the_vectors,global_settings.uni_start,global_settings.uni_skip);
  gfx_refresh();
  gtk_widget_destroy(widget);

}
/* set up an input window for getting the start of a uniform vector */
void edit_tvec_uni_start(GtkWidget *widget,gpointer data)
{
	char stri[10];
    sprintf(stri,"%f",global_settings.uni_start);
	gfx_getinput(stri,widget,(GtkSignalFunc) edit_vect_uni_start_rts);
}
/***************************************************************/

/***************************************************************/
/* return for setting the skip value */
void edit_vect_uni_skip_rts(GtkWidget *widget,GtkWidget **window)
{
 /* get the text , check and set */
  char *value, *end;
  double i;

	/* get the value and convert to a double */
  value = gtk_entry_get_text (GTK_ENTRY (gfx_entry));
  i = (double) strtod(value,&end);
  global_settings.uni_skip = i;
  /* make the new vectors */
  the_vectors = maketvectors(the_vectors,global_settings.uni_start,global_settings.uni_skip);
  /* refresh the screen though it should not have chanaged */
  gfx_refresh();
  /* destory te input window*/
  gtk_widget_destroy(widget);

}

/* Create an input window for changeing the skip value */
void edit_tvec_uni_skip(GtkWidget *widget,gpointer data)
{
    char stri[10];
    sprintf(stri,"%f",global_settings.uni_skip);
    gfx_getinput(stri,widget,(GtkSignalFunc) edit_vect_uni_skip_rts);
}
/***********************************************************************/


/* 
** Set up a window for editing a uniform tvector
*/
void button_edit_uni_tvec(GtkWidget *widget,gpointer data)
{
	GtkWidget *button = NULL;	
	GtkWidget *button2 = NULL;
	static int timer = 0;
	static GtkWidget *window = NULL;

	if (!window)
	{
		/* setup a window */
		window = gtk_dialog_new ();
		gtk_signal_connect (GTK_OBJECT (window), "destroy",
					(GtkSignalFunc) destroy_window,
					&window);
		gtk_window_set_title (GTK_WINDOW (window), "Edit Tvector");
		gtk_container_border_width (GTK_CONTAINER (window), 0);
	
		/* Set an expose event to update values (labale) */
		 gtk_signal_connect (GTK_OBJECT (window), "expose_event",
		 			(GtkSignalFunc) edit_uni_tvec_expose, NULL);
  		 	timer = gtk_timeout_add ( 500 ,(GtkFunction) edit_uni_tvec_expose ,window);
	
		/* set up some buttons one for start one for jump*/
			button = gtk_button_new_with_label ("Edit Start");
			gtk_box_pack_start (GTK_BOX (GTK_DIALOG (window)->action_area)
						, button, TRUE, TRUE,0 );
			gtk_signal_connect (GTK_OBJECT (button), "clicked",
						(GtkSignalFunc) edit_tvec_uni_start, NULL);
			gtk_widget_show (button);
	
			button2 = gtk_button_new_with_label ("Edit Jump");
			gtk_box_pack_start (GTK_BOX (GTK_DIALOG (window)->action_area)
							, button2, TRUE, TRUE,0 );
			gtk_signal_connect (GTK_OBJECT (button2), "clicked",
						(GtkSignalFunc) edit_tvec_uni_skip, NULL);
			gtk_widget_show (button2);
	}
	/* if its there already get rid of it */
	if (GTK_WIDGET_VISIBLE (window) )
	{
		gtk_timeout_remove(timer);
		gtk_widget_destroy (window);
	}
	else
	{
		gtk_widget_show (window);
	}

}
/************************************************************************/

/*
** for non uniform vector 
** Did try and elmagmelt together didnt seem to work ??
*/
/* Expose routine for non unifom editing */
void edit_nonuni_tvec_expose(GtkWidget *widget, GdkEventExpose *event)
{
    static GtkWidget *label;
    char info_vector[128];

	/* destroy the label */
    if ( label != NULL && GTK_WIDGET_VISIBLE(label))
    {
        gtk_widget_destroy(label);
        label = NULL;
    }

	/* setup new label and display */
        sprintf(info_vector,"Vector %d is set at %.2f",global_settings.current_t
                    ,getnth_tvector_val(the_vectors,global_settings.current_t));

    label = gtk_label_new (info_vector);
    gtk_misc_set_padding (GTK_MISC (label), 10, 10);
    gtk_box_pack_start(GTK_BOX (GTK_DIALOG (widget)->vbox),label, TRUE, TRUE,0);
    gtk_widget_show (label);

}

/* return setup for no unifrom editing */
void edit_vect_notuni_value_rts(GtkWidget *widget,GtkWidget **window)
{
 /* get the text , check and set */
  char *value, *end;
  double i;

  value = gtk_entry_get_text (GTK_ENTRY (gfx_entry));
  i = (double) strtod(value,&end);
  if ( global_settings.current_t != 0 && global_settings.current_t != global_settings.no_o_vectors-2 )
  {
  	/* is this value really possible THERE must be a simpler way
	** and put a message up
	*/
    if ( i >= getnth_tvector_val(the_vectors,global_settings.current_t-1)
        && i <= getnth_tvector_val(the_vectors,global_settings.current_t+1) )
    {
        the_vectors = getnth_tvector(the_vectors,global_settings.current_t);
        the_vectors->tvalue = i;
    }
    else
    {
        gfx_message("Value not valid");
    }
  }
  else if ( global_settings.current_t == 0 )
  {
  	if ( i <= getnth_tvector_val(the_vectors,global_settings.current_t+1) )
	{
		the_vectors = getnth_tvector(the_vectors,global_settings.current_t);
		the_vectors->tvalue = i;
	}
	else
	{
		gfx_message("Value not valid");
	}
  }
  else
  {
  	if ( i >= getnth_tvector_val(the_vectors,global_settings.current_t-1) )
	{
		the_vectors = getnth_tvector(the_vectors,global_settings.current_t);
		the_vectors->tvalue = i;
	}
	else
	{
		gfx_message("Value not valid");
	}
  }

  gfx_refresh();
  gtk_widget_destroy(widget);

}
/* set up a input window for editing a Ts value */
void edit_tvec_notuni_value(GtkWidget *widget,gpointer data)
{
    char stri[10];
    sprintf(stri,"%f",getnth_tvector_val(the_vectors,global_settings.current_t));
    gfx_getinput(stri,widget,(GtkSignalFunc) edit_vect_notuni_value_rts);
}
/*********************************************************************/

/* return for setting current editing T */
void edit_vect_notuni_number_rts(GtkWidget *widget,GtkWidget **window)
{
 /* get the text , check and set */
  char *value, *end;
  double i;

  value = gtk_entry_get_text (GTK_ENTRY (gfx_entry));
  i = (int) strtod(value,&end);
  	/* check the value is valid and is in our T range
	** Prehaps I should use K 
	*/
    if ( i >= 0 && i <= global_settings.no_o_vectors-2)
    {
		global_settings.current_t = i;
    }
    else
    {
        gfx_message("Tvector not valid");
    }

  gfx_refresh();
  gtk_widget_destroy(widget);

}
/* set up a input window for changing the current T been added */
void edit_tvec_notuni_number(GtkWidget *widget,gpointer data)
{
    char stri[10];
    sprintf(stri,"%d",global_settings.current_t);
    gfx_getinput(stri,widget,(GtkSignalFunc) edit_vect_notuni_number_rts);
}



/* setup the non uniform window for inpout */
void button_edit_nonuni_tvec(GtkWidget *widget,gpointer data)
{
    GtkWidget *button = NULL;
    GtkWidget *button2 = NULL;
	static int timer = 0;
    static GtkWidget *window = NULL;

    if (!window)
    {
        window = gtk_dialog_new ();
        gtk_signal_connect (GTK_OBJECT (window), "destroy",
                    (GtkSignalFunc) destroy_window,
                    &window);
        gtk_window_set_title (GTK_WINDOW (window), "Edit Tvector");
        gtk_container_border_width (GTK_CONTAINER (window), 0);

        /* Set an expose event to update values (labale) */
         gtk_signal_connect (GTK_OBJECT (window), "expose_event",
                    (GtkSignalFunc) edit_nonuni_tvec_expose, NULL);
   		timer = gtk_timeout_add ( 500 ,(GtkFunction) edit_nonuni_tvec_expose ,window);

        /* set up some buttons one for non uni editing*/

            button = gtk_button_new_with_label ("Edit Number");
            gtk_box_pack_start (GTK_BOX (GTK_DIALOG (window)->action_area)
                    , button, TRUE, TRUE,0 );
            gtk_signal_connect (GTK_OBJECT (button), "clicked",
                        (GtkSignalFunc) edit_tvec_notuni_number, NULL);
            gtk_widget_show (button);

            button2 = gtk_button_new_with_label ("Edit value");
            gtk_box_pack_start (GTK_BOX (GTK_DIALOG (window)->action_area)
                    , button2, TRUE, TRUE,0 );
            gtk_signal_connect (GTK_OBJECT (button2), "clicked",
                        (GtkSignalFunc) edit_tvec_notuni_value, NULL);
            gtk_widget_show (button2);
    }

	/* If its there already destroy that window */
    if (GTK_WIDGET_VISIBLE (window) )
    {
		gtk_timeout_remove(timer);
        gtk_widget_destroy (window);
    }
    else
    {
        gtk_widget_show (window);
    }

}

