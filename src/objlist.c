
#include "../incl/minirt.h"

t_objlist	*objlst_new(t_data *d, void *object, t_objtype objtype)
{
	t_objlist	*new;

	new = malloc(sizeof(t_objlist));
	if (!new)
		error_exit(d, E_MALLOC);
	new->object = object;
	new->objtype = objtype;
	if (objtype == sp)
	{
		new->get_intersection = intersect_sphere;
		new->get_normal = get_normal_sphere;
		print_3d(new->get_normal((t_3d){0,0,0}, new->object), "knang" );
	}
	else if (objtype == pl)
	{
		new->get_intersection = intersect_plane;
		new->get_normal = get_normal_plane;
	}
	else if (objtype == cy)
	{
		new->get_intersection = intersect_cylinder;
		new->get_normal = get_normal_cylinder;
	}
	else if (objtype == tr)
	{
		new->get_intersection = intersect_triangle;
		new->get_normal = get_normal_triangle;
	}
	new->next = NULL;
	return (new);
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
	t_objlist	*temp;

	if (!lst)
		return (NULL);
	temp = lst;
	while (temp->next)
		temp = temp->next;
	return (temp);
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
