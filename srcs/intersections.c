/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   intersections.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gbianco <gbianco@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/18 15:39:58 by gbianco           #+#    #+#             */
/*   Updated: 2020/02/04 20:25:57 by nkellum          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rtv1.h"

t_vec3		find_intersection_point(t_ray *r, double *t)
{
	t_vec3 intsc;

	intsc = v3_scp(r->dir, *t);
	intsc = v3_add(intsc, r->ori);
	return (intsc);
}

static void	cam_inside_or_not(t_obj *o, double *t)
{
	o->inv_nrm = 1;
	if (t[1] && (o->typ < 4 || o->typ == 6 || o->typ == 11))
	{
		if ((t[0] < 0 && t[1] > 0) || (t[0] > 0 && t[1] < 0))
			o->inv_nrm = -1.;
	}
}

static void	share_intersection_method(t_obj *o, t_ray *r, double *t)
{
	if (o->typ == 6)
		intersect_ray_cube(r, o, t);
	else if (o->typ == 7)
		intersect_ray_hyperboloid_1s(r, o, t);
	else if (o->typ == 8)
		intersect_ray_hyperboloid_2s(r, o, t);
	else if (o->typ == 9)
		intersect_ray_paraboloid_el(r, o, t);
	else if (o->typ == 10)
		intersect_ray_paraboloid_hy(r, o, t);
	else if (o->typ == 12)
		intersect_ray_torus(r, o, t);
	else if (o->typ == 13)
		intersect_ray_mobius(r, o, t);
}

void		shadow_intersection(t_obj *o, t_ray *r, double *t)
{
	if (o->typ == 0)
		intersect_ray_plane(r, o, t);
	else if (o->typ == 1 || o->typ == 11)
		intersect_ray_sphere(r, o, t);
	else if (o->typ == 2)
		intersect_ray_cylinder(r, o, t);
	else if (o->typ == 3)
		intersect_ray_cone(r, o, t);
	else if (o->typ == 4)
		intersect_ray_disk(r, o, t);
	else if (o->typ == 5)
	{
		if (o->id < ID_OFFSET)
			intersect_ray_triangle(r, o, t);
	}
	else
		share_intersection_method(o, r, t);
}

void		object_intersection(t_obj *o, t_ray *r, double *t)
{
	if (o->typ == 0)
		intersect_ray_plane(r, o, t);
	else if (o->typ == 1 || o->typ == 11)
		intersect_ray_sphere(r, o, t);
	else if (o->typ == 2)
		intersect_ray_cylinder(r, o, t);
	else if (o->typ == 3)
		intersect_ray_cone(r, o, t);
	else if (o->typ == 4)
		intersect_ray_disk(r, o, t);
	else if (o->typ == 5)
		intersect_ray_triangle(r, o, t);
	else
		share_intersection_method(o, r, t);
	cam_inside_or_not(o, t);
}
