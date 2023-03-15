
#include "../incl/minirt.h"

void	select_functions(t_objlst *new)
{
	select_intersect(new);
	select_normal(new);
}

void	select_intersect(t_objlst *new)
{
	if (new->objtype == pl)
		new->get_intersection = intersect_plane;
	else if (new->objtype == di)
		new->get_intersection = intersect_disc;
	else if (new->objtype == tr)
		new->get_intersection = intersect_triangle;
	else if (new->objtype == sp)
		new->get_intersection = intersect_sphere;
	else if (new->objtype == tu)
		new->get_intersection = intersect_tube;
	else if (new->objtype == co)
		new->get_intersection = intersect_cone;
}

void	select_normal(t_objlst *new)
{
	if (new->objtype == pl)
		new->get_normal = normal_plane;
	else if (new->objtype == di)
		new->get_normal = normal_disc;
	else if (new->objtype == tr)
		new->get_normal = normal_triangle;
	else if (new->objtype == sp)
		new->get_normal = normal_sphere;
	else if (new->objtype == tu)
		new->get_normal = normal_tube;
	else if (new->objtype == co)
		new->get_normal = normal_cone;
}
