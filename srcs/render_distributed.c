/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   render_distributed.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gbianco <gbianco@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/01/02 22:50:56 by gbianco           #+#    #+#             */
/*   Updated: 2020/02/05 21:53:32 by gbianco          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rtv1.h"

int		average_color(int *rgb, int n)
{
	int		i;
	t_rgb	s;

	s.r = 0;
	s.g = 0;
	s.b = 0;
	i = -1;
	while (++i < n)
	{
		s.r += (rgb[i] >> 16) & 0xff;
		s.g += (rgb[i] >> 8) & 0xff;
		s.b += rgb[i] & 0xff;
	}
	s.r /= n;
	s.g /= n;
	s.b /= n;
	return (((s.r & 0x0ff) << 16) | ((s.g & 0x0ff) << 8) | (s.b & 0x0ff));
}

int		bi_rate_color(int clr_a, int clr_b, double a, double b)
{
	t_vec3	rgb;
	t_vec3	rgb_a;
	t_vec3	rgb_b;

	if (a + b > 100)
		error("wtf?");
	rgb_a = v3((clr_a >> 16) & 0xFF, (clr_a >> 8) & 0xFF, (clr_a & 0xFF));
	rgb_b = v3((clr_b >> 16) & 0xFF, (clr_b >> 8) & 0xFF, (clr_b & 0xFF));
	rgb_a = v3_scp(v3_scd(rgb_a, 100.), a);
	rgb_b = v3_scp(v3_scd(rgb_b, 100.), b);
	rgb = v3_add(rgb_a, rgb_b);
	return (((int)rgb.x << 16) | ((int)rgb.y << 8) | (int)rgb.z);
}

int		clr_scp(int clr, double coef)
{
	t_vec3	rgb;

	rgb = v3((clr >> 16) & 0xFF, (clr >> 8) & 0xFF, (clr & 0xFF));
	rgb = v3_scp(rgb, coef);
	return (((int)rgb.x << 16) | ((int)rgb.y << 8) | (int)rgb.z);
}

int		clr_add(int clr_a, int clr_b)
{
	t_vec3	rgb_a;
	t_vec3	rgb_b;
	t_vec3	rgb_c;

	rgb_a = v3((clr_a >> 16) & 0xFF, (clr_a >> 8) & 0xFF, (clr_a & 0xFF));
	rgb_b = v3((clr_b >> 16) & 0xFF, (clr_b >> 8) & 0xFF, (clr_b & 0xFF));
	rgb_c = v3_add(rgb_a, rgb_b);
	ft_fmax(&rgb_c.x, 255);
	ft_fmax(&rgb_c.y, 255);
	ft_fmax(&rgb_c.z, 255);
	return (((int)rgb_c.x << 16) | ((int)rgb_c.y << 8) | (int)rgb_c.z);
}

int		distribuited_rays(t_scene *s, t_ray *r, double x, double y)
{
	if (s->efc.select == 2)
		return (timed_rays(s, r, x, y));
	else if (s->efc.blu[1] != 0)
		return (global_blur(s, r, x, y));
	else if (s->efc.toon != 0)
		return (cartoon_effect(s, r, x, y));
	else if (s->efc.aa != 0)
		return (antialiasing(s, r, x, y));
	else
		return (0);
}
