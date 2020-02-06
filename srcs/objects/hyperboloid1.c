/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   hyperboloid1.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gbianco <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/01/21 00:20:39 by gbianco           #+#    #+#             */
/*   Updated: 2020/01/21 00:20:42 by gbianco          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rtv1.h"

void			normal_hyperboloid(double pnt[4][1], double dst[4][1])
{
	dst[0][0] = 2. * pnt[0][0];
	dst[1][0] = -2. * pnt[1][0];
	dst[2][0] = 2. * pnt[2][0];
}

static void		equation(t_vec3 *coef, double *disc, double *t)
{
	t[0] = (sqrt(*disc) - coef->y) / (2. * coef->x);
	t[1] = (-sqrt(*disc) - coef->y) / (2. * coef->x);
	t[2] = 0;
}

void			intersect_ray_hyperboloid_1s(t_ray *r, t_obj *o, double *t)
{
	double	disc;
	t_vec3	coef;
	t_ray	tr;

	tr = transform_ray(r, o);
	coef.x = tr.dir.x * tr.dir.x - tr.dir.y * tr.dir.y + tr.dir.z * tr.dir.z;
	coef.y = tr.ori.x * tr.dir.x - tr.ori.y * tr.dir.y + tr.ori.z * tr.dir.z;
	coef.y *= 2.;
	coef.z = tr.ori.x * tr.ori.x - tr.ori.y * tr.ori.y + tr.ori.z * tr.ori.z;
	coef.z -= 1;
	disc = coef.y * coef.y - 4. * coef.x * coef.z;
	if (disc < 0)
		return ;
	equation(&coef, &disc, t);
}
