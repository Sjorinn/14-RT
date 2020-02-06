/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   bexel.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nkellum <nkellum@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/03 20:02:19 by nkellum           #+#    #+#             */
/*   Updated: 2020/02/05 14:55:45 by nkellum          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rtv1.h"

void	add_bump(t_scene *s, t_vec3 *vectr_nrm)
{
	t_vec3	bump;

	bump = v3(0, 0, 0);
	if (s->hit.obj->txt != NULL && s->hit.obj->txt->bump != NULL)
	{
		if (s->hit.obj->typ == 0)
			bump = get_bump_plane(s);
		else if (s->hit.obj->typ == 1)
			bump = get_bump_sphere(s);
		else if (s->hit.obj->typ == 2)
			bump = get_bump_cylinder(s);
		else if (s->hit.obj->typ == 3)
			bump = get_bump_cone(s);
		vectr_nrm->x += bump.x / s->hit.obj->txt->bump_pow;
		vectr_nrm->y += bump.y / s->hit.obj->txt->bump_pow;
		vectr_nrm->z += bump.z / s->hit.obj->txt->bump_pow;
	}
}

t_vec3	get_bump_sphere(t_scene *s)
{
	t_vec3 w_to_obj;
	double *uv;
	double uuv[2];

	w_to_obj = world_to_obj(&s->hit);
	uv = spherical_map(w_to_obj, 1);
	uuv[0] = uv[0];
	uuv[1] = uv[1];
	ft_memdel((void **)&uv);
	return (get_texel(uuv[0], uuv[1], s->hit.obj->txt->bump));
}

t_vec3	get_bump_cylinder(t_scene *s)
{
	t_vec3 w_to_obj;
	double *uv;
	double uuv[2];

	w_to_obj = world_to_obj(&s->hit);
	uv = cylindre_map(w_to_obj, 1);
	uuv[0] = uv[0];
	uuv[1] = uv[1];
	ft_memdel((void **)&uv);
	return (get_texel(uuv[0], uuv[1], s->hit.obj->txt->bump));
}

t_vec3	get_bump_plane(t_scene *s)
{
	t_vec3 w_to_obj;
	double uv[2];

	w_to_obj = world_to_obj(&s->hit);
	uv[0] = fmod(w_to_obj.x, 1.0);
	uv[1] = fmod(w_to_obj.z, 1.0);
	return (get_texel(uv[0], uv[1], s->hit.obj->txt->bump));
}

t_vec3	get_bump_cone(t_scene *s)
{
	t_vec3 w_to_obj;
	double *uv;
	double uuv[2];

	w_to_obj = world_to_obj(&s->hit);
	uv = cylindre_map(w_to_obj, 1);
	uuv[0] = uv[0];
	uuv[1] = uv[1];
	ft_memdel((void **)&uv);
	return (get_texel(uuv[0], uuv[1], s->hit.obj->txt->bump));
}
