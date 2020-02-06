/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   texel.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nkellum <nkellum@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/01/16 15:43:26 by nkellum           #+#    #+#             */
/*   Updated: 2020/02/05 11:35:34 by nkellum          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rtv1.h"

t_vec3	get_texel_plane(t_scene *s)
{
	t_vec3 w_to_obj;
	double uv[2];

	w_to_obj = world_to_obj(&s->hit);
	uv[0] = s->hit.obj->txt->x_offset +
	fmod(w_to_obj.x / s->hit.obj->txt->stretch, 1.0);
	uv[1] = s->hit.obj->txt->y_offset -
	fmod(w_to_obj.z / s->hit.obj->txt->stretch, 1.0);
	return (get_texel(uv[0], uv[1], s->hit.obj->txt->data));
}

t_vec3	get_texel_cylinder(t_scene *s)
{
	t_vec3 w_to_obj;
	double *uv;
	double uuv[2];

	w_to_obj = world_to_obj(&s->hit);
	uv = cylindre_map(w_to_obj, s->hit.obj->txt->stretch);
	uv[0] = s->hit.obj->txt->x_offset + uv[0];
	uv[1] = s->hit.obj->txt->y_offset - uv[1];
	uuv[0] = uv[0];
	uuv[1] = uv[1];
	ft_memdel((void **)&uv);
	return (get_texel(uuv[0], uuv[1], s->hit.obj->txt->data));
}

t_vec3	get_texel_cone(t_scene *s)
{
	t_vec3 w_to_obj;
	double *uv;
	double uuv[2];

	w_to_obj = world_to_obj(&s->hit);
	uv = cylindre_map(w_to_obj, s->hit.obj->txt->stretch);
	uv[0] += s->hit.obj->txt->x_offset;
	uv[1] += s->hit.obj->txt->y_offset;
	uuv[0] = uv[0];
	uuv[1] = uv[1];
	ft_memdel((void **)&uv);
	return (get_texel(uuv[0], uuv[1], s->hit.obj->txt->data));
}

t_vec3	get_texel_sphere(t_scene *s)
{
	t_vec3 w_to_obj;
	double *uv;
	double uuv[2];

	w_to_obj = world_to_obj(&s->hit);
	uv = spherical_map(w_to_obj, s->hit.obj->txt->stretch);
	uv[0] = s->hit.obj->txt->x_offset + uv[0];
	uv[1] = s->hit.obj->txt->y_offset - uv[1];
	uuv[0] = uv[0];
	uuv[1] = uv[1];
	ft_memdel((void **)&uv);
	return (get_texel(uuv[0], uuv[1], s->hit.obj->txt->data));
}
