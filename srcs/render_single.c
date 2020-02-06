/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   render_single.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gbianco <gbianco@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/29 18:22:19 by gbianco           #+#    #+#             */
/*   Updated: 2020/02/05 15:40:26 by lucmarti         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rtv1.h"

void	add_pert(t_scene *s, t_vec3 *vectr_nrm)
{
	vectr_nrm->x += sin(s->hit.isc.x * s->hit.obj->bump[1].x)
	/ (1 + s->hit.obj->bump[0].x);
	vectr_nrm->y += sin(s->hit.isc.y * s->hit.obj->bump[1].y)
	/ (1 + s->hit.obj->bump[0].y);
	vectr_nrm->z += sin(s->hit.isc.z * s->hit.obj->bump[1].z)
	/ (1 + s->hit.obj->bump[0].z);
}

t_vec3	normal_at(t_scene *s, t_hit *hit, t_normal f)
{
	double	world_isc[4][1];
	double	objec_isc[4][1];
	double	objec_nrm[4][1];
	double	world_nrm[4][1];
	t_vec3	vectr_nrm;

	ft_ptom(hit->isc, world_isc);
	m44d41(hit->obj->mtx, world_isc, objec_isc);
	(f)(objec_isc, objec_nrm);
	m44d41(hit->obj->trx, objec_nrm, world_nrm);
	vectr_nrm.x = world_nrm[0][0];
	vectr_nrm.y = world_nrm[1][0];
	vectr_nrm.z = world_nrm[2][0];
	vectr_nrm = v3_scp(vectr_nrm, hit->obj->inv_nrm);
	add_bump(s, &vectr_nrm);
	add_pert(s, &vectr_nrm);
	return (v3_nor(vectr_nrm));
}

t_vec3	get_norm(t_scene *s, t_hit *hit, t_ray *r)
{
	if (hit->obj->typ == 0 || hit->obj->typ == 4)
		return (normal_plane(s, hit));
	else if (hit->obj->typ == 1 || hit->obj->typ == 11)
		return (normal_at(s, hit, &normal_sphere));
	else if (hit->obj->typ == 2)
		return (normal_at(s, hit, &normal_cylinder));
	else if (hit->obj->typ == 3)
		return (normal_at(s, hit, &normal_cone));
	else if (hit->obj->typ == 5)
		return (normal_triangle(hit, r));
	else if (hit->obj->typ == 6)
		return (normal_at(s, hit, &normal_cube));
	else if (hit->obj->typ == 7 || hit->obj->typ == 8)
		return (normal_at(s, hit, &normal_hyperboloid));
	else if (hit->obj->typ == 9)
		return (normal_at(s, hit, &normal_paraboloid1));
	else if (hit->obj->typ == 10)
		return (normal_at(s, hit, &normal_paraboloid2));
	else if (hit->obj->typ == 9 || hit->obj->typ == 12)
		return (normal_at(s, hit, &normal_torus));
	else if (hit->obj->typ == 13)
		return (normal_at(s, hit, &normal_mobius));
	return (v3(0, 0, 0));
}

t_vec3	orientate_axes(t_scene *s, double x, double y)
{
	t_vec3	ret;

	ret = v3_add(s->cam.bottleft, v3_scp(s->cam.vi_x, x));
	ret = v3_add(ret, v3_scp(s->cam.vi_y, y));
	ret = v3_nor(ret);
	return (ret);
}

int		single_ray(t_scene *s, t_ray *r, double x, double y)
{
	r->dir = orientate_axes(s, x, y);
	s->hit.ray = r;
	collect_object_isc(s, r);
	get_object_hit(s);
	if (s->hit.t != INFINITY)
	{
		s->hit.nrm = get_norm(s, &s->hit, r);
		s->hit.maxrfl = 0;
		s->hit.maxrfr = 0;
		if (s->hit.obj->id >= ID_OFFSET)
			return (0xffffff);
		if (s->hit.obj->rfl > 0 || s->hit.obj->tcy > 0)
			return (recursive_ray(s, *r, &classic_shader));
		return (light(s, &classic_shader));
	}
	if (s->cam.glr.select < 1)
		return (0);
	return (camera_light(s, 0));
}
