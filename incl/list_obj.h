/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   list_obj.h                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wmardin <wmardin@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/25 18:01:48 by wmardin           #+#    #+#             */
/*   Updated: 2023/04/28 14:44:10 by wmardin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef LIST_OBJ_H
# define LIST_OBJ_H

# include <stdlib.h>

# include "structs.h"

typedef enum e_objtype
{
	sp = 1,
	pl = 2,
	tu = 3,
	di = 4,
	tr = 5,
	co = 6
}	t_objtype;

typedef struct s_phong
{
	double		amb;
	double		diff;
	double		spec;
}	t_phong;

// forward declaration
typedef struct s_objlst	t_objlst;

typedef struct s_objlst
{
	void		*object;
	t_objtype	objtype;
	t_phong		phong;
	int			spec_exp;
	t_intrsct	(*get_intersection)(t_ray ray, void *obj);
	t_3d		(*get_normal)(t_3d point, t_3d ray_origin, void *obj);
	t_objlst	*next;

}	t_objlst;

// list_obj1.c
t_objlst	*objlst_new(t_data *d, void *object, t_objtype objtype);
void		objlst_add_back(t_objlst **lst, t_objlst *new);
t_objlst	*objlst_last(t_objlst *lst);
void		objlst_free(t_objlst *lst);

// list_obj2.c
void		select_functions(t_objlst *new);
void		select_intersect(t_objlst *new);
void		select_normal(t_objlst *new);

#endif
