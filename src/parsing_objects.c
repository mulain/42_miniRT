
#include "minirt.h"

/*
Sphere:
sp 0.0,0.0,20.6 12.6 10,0,255
∗ identifier: sp (-> elements[0])
∗ x,y,z point of the sphere point: 0.0,0.0,20.6 (-> elements[1])
∗ the sphere diameter: 12.6 (-> elements[2])
∗ R,G,B colors in range [0-255]: 10, 0, 255 (-> elements[3])
*/
void	parse_sphere(t_data *d)
{
	t_sphere	*sphere;

	sphere = malloc(sizeof(t_sphere));
	if (!sphere)
		error_exit(d, E_MALLOC);
	objlst_add_back(&d->objectlist, objlst_new(sphere, sp));
	sphere->point = parse_tpoint(d, d->parse.elmnts[1], E_SPHERE1);
	d->parse.min = 0;
	d->parse.max = 0;
	sphere->radius = 0.5 * parse_double(d, d->parse.elmnts[2], E_SPHERE2);
	sphere->color = parse_tcolor(d, d->parse.elmnts[3], E_SPHERE3);
}

/*
Plane:
pl 0.0,0.0,-10.0 0.0,1.0,0.0 0,0,225
∗ identifier: pl (-> elements[0])
∗ x,y,z point: 0.0,0.0,-10.0 (-> elements[1])
∗ 3d normalized orientation vector. In range [-1,1] for each x,y,z axis:
0.0,0.0,1.0 (-> elements[2])
∗ R,G,B colors in range [0-255]: 0, 0, 255 (-> elements[3])
*/
void	parse_plane(t_data *d)
{
	t_plane		*plane;

	plane = malloc(sizeof(t_plane));
	if (!plane)
		error_exit(d, E_MALLOC);
	objlst_add_back(&d->objectlist, objlst_new(plane, pl));
	plane->point = parse_tpoint(d, d->parse.elmnts[1], E_PLANE1);
	plane->vector = parse_tvector(d, d->parse.elmnts[2], E_PLANE2);
	plane->color = parse_tcolor(d, d->parse.elmnts[3], E_PLANE3);
}

/*
Cylinder:
cy 50.0,0.0,20.6 0.0,0.0,1.0 14.2 21.42 10,0,255
∗ identifier: cy (-> elements[0])
∗ x,y,z point: 50.0,0.0,20.6 (-> elements[1])
∗ 3d normalized orientation vector. In range [-1,1] for each x,y,z axis:
0.0,0.0,1.0 (-> elements[2])
∗ the cylinder diameter: 14.2 (-> elements[3])
∗ the cylinder height: 21.42 (-> elements[4])
∗ R,G,B colors in range [0,255]: 10, 0, 255 (-> elements[5])
*/
void	parse_cylinder(t_data *d)
{
	t_cylinder	*cylinder;

	cylinder = malloc(sizeof(t_cylinder));
	if (!cylinder)
		error_exit(d, E_MALLOC);
	objlst_add_back(&d->objectlist, objlst_new(cylinder, cy));
	cylinder->point = parse_tpoint(d, d->parse.elmnts[1], E_CYLINDER1);
	cylinder->vector = parse_tvector(d, d->parse.elmnts[2], E_CYLINDER2);
	d->parse.min = 0.0;
	d->parse.max = 0.0;
	cylinder->diameter = parse_double(d, d->parse.elmnts[3], E_CYLINDER3);
	cylinder->height = parse_double(d, d->parse.elmnts[4], E_CYLINDER4);
	cylinder->color = parse_tcolor(d, d->parse.elmnts[5], E_CYLINDER5);
}
