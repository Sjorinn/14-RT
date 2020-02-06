/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   noises.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pchambon <pchambon@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/01/29 15:50:11 by pchambon          #+#    #+#             */
/*   Updated: 2020/02/01 16:15:19 by pchambon         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/rtv1.h"

int		fastfloor(double x)
{
	if (x > 0)
		return ((int)x);
	return (((int)x) - 1);
}

double	noises(double noise, t_scene *s, int i)
{
	double amp;
	double step;
	double wood;
	double cloud;

	amp = 20;
	step = 0.2;
	wood = fmod(noise, step);
	if (i == 2)
		return (noise);
	if (i == 3)
		cloud = sqrt(fabs(sin(2 * M_PI * noise)));
	if (i == 4)
		cloud = (sin((s->hit.isc.x + noise * amp * 10) * 2
			* M_PI / 200) + 1) / 2;
	if (i == 5)
	{
		if (wood > step / 2)
			wood = step - wood;
		cloud = (1 - cos(M_PI * wood / (step / 2))) / 2;
	}
	return (cloud);
}

double	cloud(t_scene *s, double noise)
{
	int		i;
	double	amp;
	double	freq;
	double	maxamp;

	i = 0;
	amp = 1;
	noise = 0;
	freq = 0.1;
	maxamp = 0;
	while (i < 16)
	{
		noise += noise3d(s, (s->hit.isc.x + s->p.offset.i) *
		freq, (s->hit.isc.y + s->p.offset.j)
		* freq, (s->hit.isc.z + s->p.offset.k) * freq) * amp;
		maxamp += amp;
		amp *= 0.5;
		freq *= 2;
		i++;
	}
	noise /= maxamp;
	return (noise);
}
