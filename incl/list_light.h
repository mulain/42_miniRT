/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   list_light.h                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wmardin <wmardin@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/25 18:01:40 by wmardin           #+#    #+#             */
/*   Updated: 2023/03/25 18:01:42 by wmardin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef LIST_LIGHT_H
# define LIST_LIGHT_H

# include <stdlib.h>

# include "structs.h"

// forward declaration
typedef struct s_lightlst	t_lightlst;

typedef struct s_lightlst
{
	t_3d		origin;
	double		brightness;
	t_color		color;
	t_lightlst	*next;

}	t_lightlst;

// list_light.c
t_lightlst		*lightlst_new(t_data *d, t_light light);
void			lightlst_add_back(t_lightlst **lst, t_lightlst *new);
t_lightlst		*lightlst_last(t_lightlst *lst);
void			lightlst_free(t_lightlst *lst);

#endif
