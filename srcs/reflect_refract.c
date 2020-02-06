/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   reflect_refract.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gbianco <gbianco@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/01/23 19:39:54 by gbianco           #+#    #+#             */
/*   Updated: 2020/02/04 20:27:39 by nkellum          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rtv1.h"

t_ray	compute_reflected(t_scene *s, t_ray r)
{
	t_ray		reflected;

	s->hit.maxrfl++;
	reflected.time = r.time;
	reflected.ori = v3_add(s->hit.isc, v3_scp(s->hit.nrm, REC_BIAS));
	reflected.dir = v3_scp(s->hit.nrm, (2. * v3_dot(r.dir, s->hit.nrm)));
	reflected.dir = v3_nor(v3_dif(r.dir, reflected.dir));
	return (reflected);
}

t_ray	compute_refracted(t_scene *s, t_ray r)
{
	t_ray	refracted;
	t_vec3	normal;
	double	c[2];
	double	ior[3];

	s->hit.maxrfr++;
	refracted.time = r.time;
	normal = s->hit.nrm;
	c[0] = v3_dot(r.dir, s->hit.nrm);
	ior[0] = s->hit.i_ior;
	ior[1] = s->hit.obj->ior;
	if (c[0] < 0)
		c[0] *= -1.;
	else
	{
		ft_fswap(&ior[0], &ior[1]);
		normal = v3_neg(normal);
	}
	ior[2] = ior[0] / ior[1];
	c[1] = 1. - ior[2] * ior[2] * (1. - c[0] * c[0]);
	refracted.ori = v3_add(s->hit.isc, v3_scp(v3_neg(normal), REC_BIAS));
	refracted.dir = (c[1] < 0) ? v3(0, 0, 0) : v3_add(v3_scp(r.dir, ior[2]),
		v3_scp(normal, ior[2] * c[0] - sqrt(c[1])));
	return (refracted);
}

int		only_reflection_case(t_scene *s, t_ray *r, t_shader *f)
{
	t_ray	reflected;
	double	refle_rate;
	double	phong_rate;
	int		clr;

	clr = 0x000000;
	refle_rate = s->hit.obj->rfl;
	phong_rate = 1 - refle_rate;
	clr = clr_scp(light(s, *f), phong_rate);
	reflected = compute_reflected(s, *r);
	s->hit.ray = &reflected;
	collect_object_isc(s, &reflected);
	get_object_hit(s);
	s->hit.nrm = get_norm(s, &s->hit, &reflected);
	clr = clr_add(clr, clr_scp(recursive_ray(s, reflected, *f), refle_rate));
	return (clr);
}

int		only_refraction_case(t_scene *s, t_ray *r, t_shader *f)
{
	t_ray	refracted;
	double	trasp_rate;
	double	phong_rate;
	int		clr;

	clr = 0x000000;
	s->hit.i_ior = (s->hit.maxrfr == 0) ? AIR_IOR : s->hit.i_ior;
	trasp_rate = s->hit.obj->tcy;
	phong_rate = 1 - trasp_rate;
	clr = clr_scp(light(s, *f), phong_rate);
	refracted = compute_refracted(s, *r);
	if (v3_cmp(refracted.dir, v3(0, 0, 0)) == 1)
		refracted = compute_reflected(s, *r);
	s->hit.i_ior = (s->hit.obj->ior > 1) ? s->hit.obj->ior : 1;
	s->hit.ray = &refracted;
	collect_object_isc(s, &refracted);
	get_object_hit(s);
	s->hit.nrm = get_norm(s, &s->hit, &refracted);
	clr = clr_add(clr, clr_scp(recursive_ray(s, refracted, *f), trasp_rate));
	return (clr);
}

int		recursive_ray(t_scene *s, t_ray r, t_shader f)
{
	int		clr;
	double	reflectance;
	double	trasparence;

	clr = 0x000000;
	reflectance = s->hit.obj->rfl;
	trasparence = s->hit.obj->tcy;
	if (s->hit.obj->id >= ID_OFFSET)
		return (0xffffff);
	if (s->hit.t != INFINITY)
	{
		if (trasparence == 0 && reflectance > 0 && s->hit.maxrfl < MAXRFL)
			clr = only_reflection_case(s, &r, &f);
		else if (reflectance == 0 && trasparence > 0 && s->hit.maxrfr < MAXRFR)
			clr = only_refraction_case(s, &r, &f);
		else if (reflectance > 0 && trasparence > 0 && s->hit.maxrfr < MAXRFR)
			clr = mix_fresnel_case(s, &r, f);
		else
			clr = light(s, f);
	}
	return (clr);
}
