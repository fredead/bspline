/* $Id: tvectors.h,v 1.2 1997/11/09 19:41:45 simon Exp simon $
** simon 30101997
** Copyright Simon Loader 1997
** simon@surf.org.uk http://www.surf.org.uk/
** tvectors.h
**  Header file for the tvector
** in a tree type sytem includeing function calls
*/
#ifndef __tvectors
#define __tvectors


struct tvector {
	double tvalue;
	struct tvector *last;
	struct tvector *next;
};


/* LIST O FUNCTIONS */
struct tvector *newtvector(int,struct tvector *);
struct tvector *deltvector(struct tvector *);
struct tvector *getnth_tvector(struct tvector *,int);
struct tvector *alloctvector();
struct tvector *tvector_start(struct tvector *);
struct tvector *tvector_end(struct tvector *t);
double getnth_tvector_val(struct tvector *,int);
struct tvector *maketvectors(struct tvector *,double ,double );
/* end list */

#endif
