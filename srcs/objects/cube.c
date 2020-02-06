/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cube.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gbianco <gbianco@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/01/21 00:18:51 by gbianco           #+#    #+#             */
/*   Updated: 2020/02/04 20:38:46 by nkellum          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rtv1.h"

static double	min_max(double a, double b, double c, int mode)
{
	double value;

	value = a;
	if (mode == 0)
	{
		if (b > value)
			value = b;
		if (c > value)
			value = c;
	}
	else if (mode == 1)
	{
		if (b < value)
			value = b;
		if (c < value)
			value = c;
	}
	return (value);
}

void			normal_cube(double pnt[4][1], double dst[4][1])
{
	double value;

	m41(dst);
	value = min_max(fabs(pnt[0][0]), fabs(pnt[1][0]), fabs(pnt[2][0]), 0);
	if (value == fabs(pnt[0][0]))
		dst[0][0] = pnt[0][0];
	else if (value == fabs(pnt[1][0]))
		dst[1][0] = pnt[1][0];
	else
		dst[2][0] = pnt[2][0];
}

static void		check_axis(double *r_o, double *r_d, double *min, double *max)
{
	double n_min;
	double n_max;
	double temp;

	n_min = -1. - *r_o;
	n_max = 1. - *r_o;
	if (fabs(*r_d) >= EPSILON)
	{
		*min = n_min / *r_d;
		*max = n_max / *r_d;
	}
	else
	{
		*min = n_min * INFINITY;
		*max = n_max * INFINITY;
	}
	if (*min > *max)
	{
		temp = *min;
		*min = *max;
		*max = temp;
	}
}

void			intersect_ray_cube(t_ray *r, t_obj *o, double *t)
{
	t_ray	tr;
	t_vec3	min;
	t_vec3	max;

	tr = transform_ray(r, o);
	check_axis(&tr.ori.x, &tr.dir.x, &min.x, &max.x);
	check_axis(&tr.ori.y, &tr.dir.y, &min.y, &max.y);
	check_axis(&tr.ori.z, &tr.dir.z, &min.z, &max.z);
	t[0] = min_max(min.x, min.y, min.z, 0);
	t[1] = min_max(max.x, max.y, max.z, 1);
	if (t[0] > t[1])
		t[0] = 0;
	t[2] = 0;
}
