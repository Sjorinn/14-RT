/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cartoon.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gbianco <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/12/19 01:18:53 by gbianco           #+#    #+#             */
/*   Updated: 2020/02/04 15:19:54 by lucmarti         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rtv1.h"

static int		no_border(t_scene *s, t_ray *r)
{
	if (s->hit.t != INFINITY)
	{
		if (s->hit.obj->id >= ID_OFFSET)
			return (0xffffff);
		s->hit.nrm = get_norm(s, &s->hit, r);
		s->hit.maxrfl = 0;
		s->hit.maxrfr = 0;
		if (s->hit.obj->rfl > 0 || s->hit.obj->tcy > 0)
			return (recursive_ray(s, *r, &cartoon_shader));
		return (light(s, &cartoon_shader));
	}
	if (s->cam.glr.select < 1)
		return (0);
	return (camera_light(s, 0));
}

int				cartoon(t_scene *s, t_ray *r, double x, double y)
{
	t_vec3	dir[3];
	int		id[3];
	int		i;

	dir[0] = orientate_axes(s, x, y);
	dir[1] = orientate_axes(s, x + 1, y);
	dir[2] = orientate_axes(s, x, y + 1);
	ft_bzero((void*)&id, sizeof(int) * 3);
	i = 3;
	while (--i > -1)
	{
		s->hit.ray = r;
		s->hit.ray->dir = dir[i];
		collect_object_isc(s, r);
		get_object_hit(s);
		if (s->hit.t != INFINITY)
			id[i] = s->hit.obj->id;
	}
	if ((id[0] == 0 && id[1] == 0 && id[2] == 0)\
		|| (id[0] == id[1] && id[0] == id[2]))
		return (no_border(s, r));
	return (0);
}

int				cartoon_effect(t_scene *s, t_ray *r, double x, double y)
{
	t_crd2	c;

	c.x = x;
	c.y = y;
	if (s->efc.aa == 0)
		return (cartoon(s, r, x, y));
	else if (s->efc.aa == 2)
		return (aa_x2(s, r, c, &cartoon));
	else if (s->efc.aa == 4)
		return (aa_x4(s, r, c, &cartoon));
	else
		return (0);
}
