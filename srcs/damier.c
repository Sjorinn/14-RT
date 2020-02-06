/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   damier.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pchambon <pchambon@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/01/23 12:21:55 by pchambon          #+#    #+#             */
/*   Updated: 2020/02/05 13:45:30 by lucmarti         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/rtv1.h"

int		damier_2(t_scene *s, int x, int y)
{
	int color;

	if (!s->hit.obj)
		return (0);
	color = ((int)(x / s->hit.obj->damier[0])
	+ (int)(y / s->hit.obj->damier[0])) % 2;
	if (color == 0)
		return (s->hit.obj->damier[1]);
	else
		return (s->hit.obj->damier[2]);
}

int		damier(t_scene *s, int x, int y, int z)
{
	int color;

	if (!s->hit.obj)
		return (0);
	color = ((int)(x / s->hit.obj->damier[0])
	+ (int)(y / s->hit.obj->damier[0])
	+ (int)(z / s->hit.obj->damier[0])) % 2;
	if (color == 0)
		return (s->hit.obj->damier[1]);
	else
		return (s->hit.obj->damier[2]);
}

int		scale(t_scene *s, double value)
{
	value = fabs((value + 1) / 2);
	value > 1 ? value = 1 : 0;
	value = 255 * value;
	if (s->hit.obj->p_clr == 1)
		s->hit.obj->clr = ((((int)0 & 0x0ff) << 16)
		| ((((int)value) & 0x0ff) << 8)
		| (((int)255 & 0x0ff)));
	else if (s->hit.obj->p_clr == 2)
		s->hit.obj->clr = ((((int)0 & 0x0ff) << 16)
		| ((((int)255) & 0x0ff) << 8)
		| (((int)value & 0x0ff)));
	else if (s->hit.obj->p_clr == 3)
		s->hit.obj->clr = ((((int)255 & 0x0ff) << 16)
		| ((((int)0) & 0x0ff) << 8)
		| (((int)value & 0x0ff)));
	else
		s->hit.obj->clr = ((((int)value & 0x0ff) << 16)
		| ((((int)value) & 0x0ff) << 8)
		| (((int)value & 0x0ff)));
	return (value);
}

void	deal_pert2(t_scene *s)
{
	if (!s->hit.obj)
		return ;
	s->hit.obj->damier[0] = 5;
	s->hit.obj->damier[1] = 0x000000;
	s->hit.obj->damier[2] = 0xFFFFFF;
	if (s->hit.obj->typ == 0 || s->hit.obj->typ == 4)
		s->hit.obj->clr = damier(s, fabs(s->hit.isc.x
		- 10000), fabs(s->hit.isc.y - 10000), fabs(s->hit.isc.z - 10000));
	else if (s->hit.obj->typ == 1)
		s->hit.obj->clr = damier_2(s, s->hit.isc.x
		- 10000, s->hit.isc.y - 10000);
	else if (s->hit.obj->typ == 2)
		s->hit.obj->clr = damier_2(s, fabs(s->hit.isc.x - 10000),
		fabs(s->hit.isc.y - 10000));
	else if (s->hit.obj->typ == 3)
		s->hit.obj->clr = damier_2(s, s->hit.isc.x
		- 10000, s->hit.isc.z - 10000);
	else if (s->hit.obj->typ == 4)
		s->hit.obj->clr = damier_2(s, s->hit.isc.x
		- 10000, s->hit.isc.y - 10000);
}

void	deal_pert(t_scene *s)
{
	if (!s->hit.obj || s->hit.obj->pert == 1)
		deal_pert2(s);
	else if (s->hit.obj->pert >= 2 && s->hit.obj->pert <= 5)
	{
		if (s->p.perl != 1)
		{
			init_grad(s);
			init_perm(s);
			s->p.perl = 1;
		}
		scale(s, noises(noise3d(s, s->hit.isc.x + s->p.offset.i,
		s->hit.isc.y + s->p.offset.j, s->hit.isc.z + s->p.offset.k),
		s, s->hit.obj->pert));
	}
	else if (s->hit.obj->pert == 6)
	{
		if (s->p.perl != 1)
		{
			init_grad(s);
			init_perm(s);
			s->p.perl = 1;
		}
		scale(s, cloud(s, 0));
	}
}
