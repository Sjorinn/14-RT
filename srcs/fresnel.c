/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fresnel.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gbianco <gbianco@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/01/28 20:52:10 by gbianco           #+#    #+#             */
/*   Updated: 2020/02/04 20:22:32 by nkellum          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rtv1.h"

double	compute_fresnel(t_scene *s, t_ray r)
{
	double	ior[2];
	double	wave[2];
	double	angle[3];

	angle[0] = v3_dot(r.dir, s->hit.nrm);
	ft_frange(&angle[0], -1., 1.);
	ior[0] = s->hit.i_ior;
	ior[1] = s->hit.obj->ior;
	if (angle[0] > 0)
		ft_fswap(&ior[0], &ior[1]);
	angle[1] = 1. - angle[0] * angle[0];
	angle[1] = (angle[1] < 0) ? 0 : angle[1];
	angle[1] = ior[0] / ior[1] * sqrt(angle[1]);
	if (angle[1] >= 1.)
		return (1.);
	angle[2] = 1. - angle[1] * angle[1];
	angle[2] = (angle[2] > 0) ? sqrt(angle[2]) : 0;
	angle[0] = fabs(angle[0]);
	wave[0] = ((ior[1] * angle[0]) - (ior[0] * angle[2]))
		/ ((ior[1] * angle[0]) + (ior[0] * angle[2]));
	wave[1] = ((ior[0] * angle[0]) - (ior[1] * angle[2]))
		/ ((ior[0] * angle[0]) + (ior[1] * angle[2]));
	return ((wave[0] * wave[0] + wave[1] * wave[1]) / 2.);
}

void	correct_rates(t_scene *s, double *rfl, double *rfr, double *phg)
{
	if (s->hit.maxrfl < MAXRFL)
		*rfl = s->hit.obj->rfl + *rfl;
	else
		*rfl = 0;
	*rfr = s->hit.obj->tcy - *rfl;
	ft_frange(rfl, 0, 1.);
	ft_frange(rfr, 0, 1.);
	*phg = 1. - (*rfl + *rfr);
	ft_frange(phg, 0, 1.);
	if (*rfr + *rfl + *phg > 1)
		error("Impossible to compute right color rates for fresnel");
}

int		fresnel_ray(t_scene *s, t_ray *ray, double *rate, t_shader f)
{
	s->hit.ray = ray;
	collect_object_isc(s, ray);
	get_object_hit(s);
	s->hit.nrm = get_norm(s, &s->hit, ray);
	return (clr_scp(recursive_ray(s, *ray, f), rate[0]));
}

int		mix_fresnel_case(t_scene *s, t_ray *r, t_shader f)
{
	t_ray	refracted;
	t_ray	reflected;
	double	rate[3];
	int		clr[3];

	s->hit.i_ior = (s->hit.maxrfr == 0) ? AIR_IOR : s->hit.i_ior;
	rate[0] = compute_fresnel(s, *r);
	correct_rates(s, &rate[0], &rate[1], &rate[2]);
	clr[0] = 0;
	clr[1] = 0;
	clr[2] = clr_scp(light(s, *f), rate[2]);
	if (s->hit.maxrfl < MAXRFL)
		reflected = compute_reflected(s, *r);
	if (s->hit.maxrfr < MAXRFR)
		refracted = compute_refracted(s, *r);
	s->hit.i_ior = (s->hit.obj->ior > 1) ? s->hit.obj->ior : 1;
	if (s->hit.maxrfl < MAXRFL)
		clr[0] = fresnel_ray(s, &reflected, &rate[0], *f);
	if (s->hit.maxrfr < MAXRFR)
		clr[1] = fresnel_ray(s, &refracted, &rate[1], *f);
	return (clr_add(clr_add(clr[0], clr[1]), clr_scp(clr[2], rate[2])));
}
