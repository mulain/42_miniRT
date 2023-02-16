
#include "../incl/minirt.h"

/*
Sphere:
sp 0.0,0.0,20.6 12.6 10,0,255
∗ identifier: sp (-> elements[0])
∗ x,y,z coordinates of the sphere center: 0.0,0.0,20.6 (-> elements[1])
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
	parse_tpoint(d, &sphere->center, 1, E_SPHERE1);
	d->parse.min = 0;
	d->parse.max = 0;
	parse_double(d, &sphere->diameter, 2, E_SPHERE2);
	parse_tcolor(d, &sphere->color, 3, E_SPHERE3);
}

/*
Plane:
pl 0.0,0.0,-10.0 0.0,1.0,0.0 0,0,225
∗ identifier: pl (-> elements[0])
∗ x,y,z coordinates: 0.0,0.0,-10.0 (-> elements[1])
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
	parse_tpoint(d, &plane->anchor, 1, E_PLANE1);
	parse_tnormvector(d, &plane->normvector, 2, E_PLANE2);
	parse_tcolor(d, &plane->color, 3, E_PLANE3);
}

/*
Cylinder:
cy 50.0,0.0,20.6 0.0,0.0,1.0 14.2 21.42 10,0,255
∗ identifier: cy (-> elements[0])
∗ x,y,z coordinates: 50.0,0.0,20.6 (-> elements[1])
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
	parse_tpoint(d, &cylinder->anchor, 1, E_CYLINDER1);
	parse_tnormvector(d, &cylinder->normvector, 2, E_CYLINDER2);
	d->parse.min = 0.0;
	d->parse.max = 0.0;
	parse_double(d, &cylinder->diameter, 3, E_CYLINDER3);
	parse_double(d, &cylinder->height, 4, E_CYLINDER4);
	parse_tcolor(d, &cylinder->color, 5, E_CYLINDER5);
}
