/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   plane.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gbianco <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/01/21 00:21:56 by gbianco           #+#    #+#             */
/*   Updated: 2020/02/04 15:14:38 by lucmarti         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rtv1.h"

void		intersect_ray_plane(t_ray *r, t_obj *o, double *t)
{
	t_ray	tr;

	tr = transform_ray(r, o);
	if (fabs(tr.dir.y) < EPSILON)
	{
		t[0] = 0;
		return ;
	}
	t[0] = -tr.ori.y / tr.dir.y;
	t[1] = 0;
}

t_vec3		normal_plane(t_scene *s, t_hit *hit)
{
	t_vec3	vectr_nrm;

	vectr_nrm = hit->obj->dir;
	add_bump(s, &vectr_nrm);
	add_pert(s, &vectr_nrm);
	return (v3_nor(vectr_nrm));
}
