/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   afterparser_imp.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gbianco <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/12/23 20:45:35 by gbianco           #+#    #+#             */
/*   Updated: 2020/02/04 15:13:31 by gbianco          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rtv1.h"

static void	improve_lights(t_lht *l)
{
	if (l->pow < 0)
		error("Seriously? Black holes are not supported...");
	if (l->clr == 0)
		error("The color of the light cannot be 'black'");
	if (l->s && (l->s->ang > 360 || l->s->ang < 0))
		error("The angle of the some spot light is invalid [0 to 360]");
	l->pow *= 10.;
}

static void	improve_triangles(t_scene *s, int *i)
{
	t_vec3	center;

	if (s->obj[*i].id > 0)
	{
		obj_translation(&s->obj[*i]);
		center = v3_scd(v3_add(v3_add(s->obj[*i].tr->v0, s->obj[*i].tr->v1)
					, s->obj[*i].tr->v2), 3.);
		rotate_triangle(&s->obj[*i], &center);
	}
	else
		rotate_mesh(s, i);
}

static void	improve_primitives(t_obj *o)
{
	if (o->typ == 12 && GRADE < 4)
		error("Please change the GRADE to 4 to render a torus");
	if (o->typ == 13 && GRADE < 3)
		error("Please change the GRADE to 3 to render a mobius");
	if (v3_cmp(v3(0, 0, 0), o->dir) == 1)
		error("Invalid object direction detected");
	if (o->pr->dim < 0)
		error("The object dimension cannot be negative");
	o->dir = v3_nor(o->dir);
	obj_translation(o);
	add_transform_to_obj(o);
}

static void	improve_global(t_obj *o, int blur)
{
	if (v3_cmp(v3(0, 0, 0), o->blur) == 0 && blur != 0)
		error("Concurrently blur method in the scene");
	if (o->rfl < 0 || o->rfl > 1)
		error("Invalid reflection range. [0 to 1]");
	if (o->tcy < 0 || o->tcy > 1)
		error("Invalid trasparence range. [0 to 1]");
	if (o->tcy && (o->ior < 1 || o->ior > 2))
		error("Invalid refraction index. [1 to 2]{ex. 1.5 = glass}");
}

void		improve_data(t_scene *s)
{
	int i;
	int	blur_check;

	i = -1;
	while (++i < s->n_lht)
		improve_lights(&s->lht[i]);
	blur_check = (s->efc.blu[0] != 0) ? 1 : 0;
	i = -1;
	while (++i < s->n_obj)
	{
		improve_global(&s->obj[i], blur_check);
		if (s->obj[i].pr)
			improve_primitives(&s->obj[i]);
		else
			improve_triangles(s, &i);
	}
	determinate_max_time(s);
}
