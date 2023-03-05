#ifndef OBJLIST_H
# define OBJLIST_H

# include <stdlib.h>

typedef enum e_objtype
{
	sp = 1,
	pl = 2,
	cy = 3,

}	t_objtype;

typedef struct s_objlist t_objlist;
typedef struct s_vector t_vector;
typedef struct s_data t_data;


typedef double	(*t_ft)(void *shape, t_vector d, t_data *data);


typedef struct s_objlist
{
	void		*content;
	t_objtype	objtype;
	t_ft		formula;
	t_objlist	*next;

}	t_objlist;

// objlist.c
t_objlist	*objlst_new(void *content, t_objtype objtype, t_ft formula);
void		objlst_add_back(t_objlist **lst, t_objlist *new);
t_objlist	*objlst_last(t_objlist *lst);
void		objlist_free(t_objlist *lst);

#endif
