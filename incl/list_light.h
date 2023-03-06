#ifndef LIGHTLIST_H
# define LIGHTLIST_H

# include <stdlib.h>

# include "structs.h"

// forward declaration
typedef struct s_lightlist t_lightlist;

typedef struct s_lightlist
{
	t_light		*light;
	t_objlist	*next;

}	t_lightlist;

// list_light.c
t_objlist	*objlst_new(t_data *d, void *object, t_objtype objtype);
void		select_functions(t_objlist *new);
void		objlst_add_back(t_objlist **lst, t_objlist *new);
t_objlist	*objlst_last(t_objlist *lst);
void		objlist_free(t_objlist *lst);

#endif
