
#ifndef LIST_OBJ_H
# define LIST_OBJ_H

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
typedef struct s_objlst	t_objlst;

typedef struct s_objlst
{
	void		*object;
	t_objtype	objtype;
	t_intrsct	(*get_intersection)();
	t_3d		(*get_normal)();
	t_objlst	*next;

}	t_objlst;

// list_obj.c
t_objlst	*objlst_new(t_data *d, void *object, t_objtype objtype);
void		select_functions(t_objlst *new);
void		objlst_add_back(t_objlst **lst, t_objlst *new);
t_objlst	*objlst_last(t_objlst *lst);
void		objlst_free(t_objlst *lst);

#endif
