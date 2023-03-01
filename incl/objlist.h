#ifndef OBJLIST_H
# define OBJLIST_H

# include <stdlib.h>

# include "structs.h"

typedef enum e_objtype
{
	sp = 1,
	pl = 2,
	cy = 3,
	tr = 4,
	co = 5
}	t_objtype;

// forward declaration
typedef struct s_objlist t_objlist;

typedef struct s_objlist
{
	void		*object;
	t_objtype	objtype;
	t_intrsct	(*get_intersection)();
	t_objlist	*next;

}	t_objlist;

// objlist.c
t_objlist	*objlst_new(void *object, t_objtype objtype);
void		objlst_add_back(t_objlist **lst, t_objlist *new);
t_objlist	*objlst_last(t_objlist *lst);
void		objlist_free(t_objlist *lst);

#endif
