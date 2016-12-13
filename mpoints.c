/* $Id: mpoints.c,v 1.4 1997/11/09 00:28:25 simon Exp simon $
** simon 30101997
** Copyright Simon Loader 1997
** simon@surf.org.uk http://www.surf.org.uk/
** mpoints.c
**  List of functions + defination of points on the
** screen in a tree format 
*/

#include <stdio.h>
#include <string.h>
#include "mpoints.h"

	
/* get the nth point in the tree
** IT MAKE SURE ITS AT THE TOP
*/
struct mpoint *getnth_mpoint(struct mpoint *thang,int n) {
	int i;
	thang = mpoint_start(thang);
	for ( i = 0 ; i < n ; i++ )
		thang = thang->next;
	return thang;
}

/* go to the beginning of the tree */
struct mpoint *mpoint_start(struct mpoint *m) {
	if ( m != NULL ) {
	while ( m->last != NULL )
		m = m->last;
	}
	return m;
}

/* go to the end of the tree */
struct mpoint *mpoint_end(struct mpoint *m) {
	if ( m != NULL ) {
	while ( m->next != NULL )
		m = m->next;
	}
	return m;
}

/* allocate the memory for a point */
struct mpoint *allocmpoint() {
	struct mpoint *newpoint;
	newpoint = (struct mpoint *)malloc(sizeof(struct mpoint) );
 	return newpoint;
}


/*insert a new point after the curent one
** this will insert between two points
** if at end make sure point is at end 
** will create new point if none in
** tree already
*/

struct mpoint *newmpoint(int x,int y,struct mpoint *ompoint) {
	struct mpoint *new;
	new = allocmpoint();
	if ( ompoint != NULL ) {
		new->next = ompoint->next;		
		ompoint->next = new;
		new->last = ompoint;
    } else {
		new->last = NULL;
		new->next = NULL;
	}
	new->y = y;
	new->x = x;
	return(new);
}

/* deletes the current point */
struct mpoint *delmpoint(struct mpoint *thepoint) {
	struct mpoint *ans;
	if ( thepoint->last != NULL )
		thepoint->last->next = thepoint->next;
	if ( thepoint->next != NULL )
		thepoint->next->last = thepoint->last;
	if ( thepoint->last != NULL )
	{
		ans = thepoint->last;
	} else 
	{
		ans = thepoint->next;
	}

	free(thepoint);
	return ans;
}

/* function to return as a string
** all the points (number) that are at a ceratin point
*/

void get_all_points(struct mpoint *points,int x,int y,char *str)
{
	char *strtemp;
	struct mpoint *p;
	int i = 0;
	
	p = points;
	strtemp = (char *)malloc(1024);   /* ok this should really test for
							** boundries but it takes a little more
							** thought Ill come back to it
							** if I have time +++
							*/

	p = mpoint_start(p);
	while ( p->next != NULL )
	{
		if (p->x == x && p->y == y )
		{
			sprintf(strtemp,"=%d",i);
			strcat(str,strtemp);
		}
		i++;
		p = p->next;
	}
	if (p->x == x && p->y == y )
	{
		sprintf(strtemp,"=%d",i);
		strcat(str,strtemp);
	}
	free(strtemp);
}

/* function to return the point closets to x,y
** 1 and 3 should be global variables
*/
struct mpoint *get_point(struct mpoint *p,int x,int y)
{
	p = mpoint_start(p);
	if ( p != NULL )
	{
		while ( p->next != NULL )
		{
			if ( (x + 2) > p->x && (x - 2) < p->x
				&& (y + 2) > p->y && (y - 2) < p->y )
				{
					return(p);
				}
			p = p->next;

		}
		if ( (x + 2) > p->x && (x - 2) < p->x
			&& (y + 2) > p->y && (y - 2) < p->y )
			{
				return(p);
			}
	}
	return(NULL);
}




/* sorting some sort of sort bubble ???
** probably should be quick 
** second sort by Hi y 
*/
struct mpoint *sort_hix(struct mpoint *sorted)
{
	struct mpoint *temp;
	if ( sorted->next == NULL )
	{
		return(sorted);
	}
	if ( (sorted->x < sorted->next->x) ||
			( sorted->x == sorted->next->x && sorted->y > sorted->next->y ) )
	{
		temp = sorted->next;

		if ( temp->next != NULL )
			temp->next->last = sorted;
		sorted->next = temp->next;
		temp->next = sorted;
		temp->last = sorted->last;
		sorted->last = temp;
		if ( temp->last != NULL )
		{
			temp->last->next = temp;
			temp = sort_hix(temp->last);
		} 
		sorted = temp;
	}
	if ( sorted->next != NULL )
	{
		sorted = sort_hix(sorted->next);
	}
	return(sorted);

}
struct mpoint *sort_hiy(struct mpoint *sorted)
{
    struct mpoint *temp;
    if ( sorted->next == NULL )
    {
        return(sorted);
    }
    if ( sorted->y < sorted->next->y )
    {
        temp = sorted->next;

		if ( temp->next != NULL )
		{
			temp->next->last = sorted;
		}
        sorted->next = temp->next;
        temp->next = sorted;
        temp->last = sorted->last;
        sorted->last = temp;
        if ( temp->last != NULL )
        {
            temp->last->next = temp;
            temp = sort_hiy(temp->last);
        }
        sorted = temp;

    }
    if ( sorted->next != NULL )
    {
        sorted = sort_hiy(sorted->next);
    }
    return(sorted);

}

/* destory an mpoint */
struct mpoint *mpoint_destory(struct mpoint *list)
{
	list = mpoint_end(list);
	while ( list != NULL )
		list = delmpoint(list);
	return(list);
}

/* debug util to print all mpoints */
void print_mpoint(struct mpoint *pp)
{
	struct mpoint *temp;

	temp = mpoint_start(pp);
	while ( temp != NULL )
	{
	  	printf("x %d y %d\n",temp->x,temp->y);
		temp = temp->next;
	}
}

