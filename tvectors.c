/* $Id: tvectors.c,v 1.2 1997/11/09 19:38:34 simon Exp simon $
** simon 30101997
** Copyright Simon Loader 1997
** simon@surf.org.uk http://www.surf.org.uk/
** tvectors.c
**  Header file for the tvector
** in a tree type sytem includeing function calls
*/

#include <stdio.h>
#include "tvectors.h"

/* deletes the current tvector */
struct tvector *deltvector(struct tvector *t)
{
	struct tvector *ans;
	if ( t->last != NULL )
        t->last->next = t->next;
    if ( t->next != NULL )
        t->next->last = t->last;
    if ( t->last != NULL )
    {
        ans = t->last;
    } else
    {
        ans = t->next;
    }

    free(t);
    return ans;
}

	
/* returns Nth t vector in tree from teh beginning */
struct tvector *getnth_tvector(struct tvector *thang,int n) {
	int i;
	thang = tvector_start(thang);
	for ( i = 0 ; i < n ; i++ )
		thang = thang->next;
	return thang;
}

/* retunrs the value of the nth t vector */
double getnth_tvector_val(struct tvector *start,int n)
{
	struct tvector *temp;
	temp = getnth_tvector(start,n);
	return (temp->tvalue);
}


/* goes to the begnning of the tvector tree */
struct tvector *tvector_start(struct tvector *t) {
        if ( t != NULL ) {
        while ( t->last != NULL )
                t = t->last;
        }
        return t;
}

/* goes to the end of the tvector tree */
struct tvector *tvector_end(struct tvector *t) {
        if ( t != NULL ) {
        while ( t->next != NULL )
                t = t->next;
        }
        return t;
}

/* allocate memory for new vector */
struct tvector *alloctvector() {
	return((struct tvector *)malloc(sizeof(struct tvector)) );
}

/* insert nec value inbetween two 
** vector in the tree
*/
struct tvector *newtvector(int new_tvalue,struct tvector *otvector) {
        struct tvector *new;
        new = alloctvector();
        if ( otvector != NULL ) {
			new->next = otvector->next;
            otvector->next = new;
            new->last = otvector;
        } else {
			new->last = NULL;
			new->next = NULL;
		}
        new->tvalue = new_tvalue;
        return(new);
}


/* using the global setting makes sure there is the correct
** number of tvectors
*/
struct tvector *maketvectors(struct tvector *t_vec,double start,double skip)
{
    t_vec = tvector_start(t_vec);
    t_vec->tvalue = start;

    while ( t_vec->next != NULL )
    {
        t_vec->next->tvalue = t_vec->tvalue + skip;
        t_vec = t_vec->next;
    }
    return(t_vec);
}

