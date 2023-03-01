
#include "../incl/minirt.h"

t_objlist	*objlst_new(void *object, t_objtype objtype)
{
	t_objlist	*new;

	new = malloc(sizeof(t_objlist));
	if (!new)
		return (NULL);
	new->object = object;
	new->objtype = objtype;
	if (objtype == sp)
		new->get_intersection = intersect_sphere;
	else if (objtype == pl)
		new->get_intersection = intersect_plane;
	else if (objtype == cy)
		new->get_intersection = intersect_cylinder;
	else if (objtype == tr)
		new->get_intersection = intersect_triangle;
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
