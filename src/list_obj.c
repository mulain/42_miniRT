
#include "../incl/minirt.h"

t_objlist	*objlst_new(t_data *d, void *object, t_objtype objtype)
{
	t_objlist	*new;

	new = malloc(sizeof(t_objlist));
	if (!new)
		error_exit(d, E_MALLOC);
	new->object = object;
	new->objtype = objtype;
	new->next = NULL;
	select_functions(new);
	return (new);
}

void	select_functions(t_objlist *new)
{
	if (new->objtype == pl)
	{
		new->get_intersection = intersect_plane;
		new->get_normal = get_normal_plane;
	}
	else if (new->objtype == di)
	{
		new->get_intersection = intersect_disc;
		new->get_normal = get_normal_disc;
	}
	else if (new->objtype == tr)
	{
		new->get_intersection = intersect_triangle;
		new->get_normal = get_normal_triangle;
	}
	else if (new->objtype == sp)
	{
		new->get_intersection = intersect_sphere;
		new->get_normal = get_normal_sphere;
	}
	else if (new->objtype == tu)
	{
		new->get_intersection = intersect_tube;
		new->get_normal = get_normal_tube;
	}
}

void	objlst_add_back(t_objlist **lst, t_objlist *new)
{
	if (!new || !lst)
		return ;
	if (!*lst)
		*lst = new;
	else
		(objlst_last(*lst))->next = new;
}

t_objlist	*objlst_last(t_objlist *lst)
{
	if (!lst)
		return (NULL);
	while (lst->next)
		lst = lst->next;
	return (lst);
}

void	objlist_free(t_objlist *lst)
{
	t_objlist	*temp;

	while (lst)
	{
		free(lst->object);
		temp = lst;
		lst = lst->next;
		free(temp);
	}
}