#ifndef OBJLIST_H
# define OBJLIST_H

# include <stdlib.h>

# include "structs.h"

typedef enum e_objtype
{
	sp = 1,
	pl = 2,
	tu = 3,
	di = 4,
	tr = 5,
	co = 6
}	t_objtype;

// forward declaration
typedef struct s_objlist t_objlist;

typedef struct s_objlist
{
	void		*object;
	t_objtype	objtype;
	t_intrsct	(*get_intersection)();
	t_3d		(*get_normal)();
	t_objlist	*next;

}	t_objlist;

// list_obj.c
t_lightlist	*objlst_new(t_data *d, void *object, t_objtype objtype);
void		objlst_add_back(t_objlist **lst, t_objlist *new);
t_lightlist	*objlst_last(t_objlist *lst);
void		objlist_free(t_objlist *lst);

#endif
