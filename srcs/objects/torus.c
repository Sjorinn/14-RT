/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   torus.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gbianco <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/01/21 00:22:23 by gbianco           #+#    #+#             */
/*   Updated: 2020/01/21 00:31:42 by gbianco          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rtv1.h"

void		normal_torus(double pnt[4][1], double dst[4][1])
{
	double x;
	double y;

	x = pnt[0][0];
	y = pnt[2][0];
	dst[0][0] = 2. * x - (4. * x / sqrt(x * x + y * y));
	dst[2][0] = 2. * y - (4. * y / sqrt(x * x + y * y));
	dst[1][0] = 2. * pnt[1][0];
}

void		intersect_ray_torus(t_ray *r, t_obj *o, double *t)
{
	t_ray	tr;
	t_vec3	dots;
	double	c[5];
	int		solutions;

	tr = transform_ray(r, o);
	dots.x = v3_dot(tr.dir, tr.dir);
	dots.y = v3_dot(tr.ori, tr.ori);
	dots.z = v3_dot(tr.ori, tr.dir);
	c[4] = dots.x * dots.x;
	c[3] = 4. * dots.x * dots.z;
	c[2] = 2. * dots.x * (dots.y - 5.);
	c[2] += (4. * (dots.z * dots.z) + (4. * 4. * tr.dir.y * tr.dir.y));
	c[1] = 4. * (dots.y - 5.) * dots.z;
	c[1] += (8. * 4. * tr.ori.y * tr.dir.y);
	c[0] = (dots.y - 5.);
	c[0] *= c[0];
	c[0] -= (4. * 4. * (1. - tr.ori.y * tr.ori.y));
	solutions = quartic_solver(c, t);
	t[solutions] = 0;
}
