
#include "../incl/minirt.h"

t_lightlist	*lightlist_new(t_data *d, t_light *light)
{
	t_objlist	*new;

	new = malloc(sizeof(t_light));
	if (!new)
		error_exit(d, E_MALLOC);
	new->light = light;
	new->next = NULL;
	return (new);
}

void	lightlst_add_back(t_objlist **lst, t_objlist *new)
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
