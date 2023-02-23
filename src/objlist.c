
#include "../incl/objlist.h"

t_objlist	*objlst_new(void *content, t_objtype objtype)
{
	t_objlist	*new;

	new = malloc(sizeof(t_objlist));
	if (!new)
		return (NULL);
	new->content = content;
	new->objtype = objtype;
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
		free(lst->content);
		temp = lst;
		lst = lst->next;
		free(temp);
	}
}
