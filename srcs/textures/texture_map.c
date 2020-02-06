/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   texture_map.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nkellum <nkellum@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/01/16 15:42:19 by nkellum           #+#    #+#             */
/*   Updated: 2020/02/05 14:53:01 by nkellum          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rtv1.h"

double	*cylindre_map(t_vec3 p, double stretch)
{
	double *uv;
	double theta;
	double raw;

	uv = (double*)malloc(sizeof(double) * 2);
	theta = atan2(p.x, p.z);
	raw = theta / (2. * M_PI);
	uv[0] = 1.0 - (raw + 0.5);
	uv[1] = fmod(p.y / stretch, 1.0);
	return (uv);
}

double	*spherical_map(t_vec3 p, double stretch)
{
	double *uv;
	double theta;
	double phi;
	double raw;

	uv = (double*)malloc(sizeof(double) * 2);
	theta = atan2(p.x, p.z);
	phi = acos(p.y / 1);
	raw = theta / (2.0 * M_PI);
	uv[0] = (1 - (raw + 0.5)) / stretch;
	uv[1] = (1 - phi / M_PI) / stretch;
	return (uv);
}

t_vec3	world_to_obj(t_hit *hit)
{
	double world_isc[4][1];
	double objec_isc[4][1];
	t_vec3 obj_pnt;

	ft_ptom(hit->isc, world_isc);
	m44d41(hit->obj->mtx, world_isc, objec_isc);
	obj_pnt.x = objec_isc[0][0];
	obj_pnt.y = objec_isc[1][0];
	obj_pnt.z = objec_isc[2][0];
	return (obj_pnt);
}
