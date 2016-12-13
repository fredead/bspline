/* $Id: mpoints.h,v 1.3 1997/11/06 15:28:18 simon Exp simon $
** simon 30101997
** Copyright Simon Loader 1997
** simon@surf.org.uk http://www.surf.org.uk/
** mpoints.h
**  List of functions + defination of points on the
** screen in a tree format 
*/

#ifndef __mpoints
#define __mpoints

struct mpoint {
	int x,y;
	struct mpoint *next;
	struct mpoint *last;
};


/* THE FUNCTIONS */
struct mpoint *getnth_mpoint(struct mpoint *,int);
struct mpoint *mpoint_start(struct mpoint *);
struct mpoint *mpoint_end(struct mpoint *);
struct mpoint *allocmpoint();
struct mpoint *newmpoint(int,int,struct mpoint *);
struct mpoint *delmpoint(struct mpoint *);
void get_all_points(struct mpoint *,int,int,char *);
struct mpoint *get_point(struct mpoint *,int,int);
struct mpoint *sort_hix(struct mpoint *);
struct mpoint *sort_hiy(struct mpoint *);
void print_mpoint(struct mpoint *);
struct mpoint *mpoint_destory(struct mpoint *);
/* FUNCTIONS END */
	
#endif
