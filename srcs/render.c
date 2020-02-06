/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   render.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gbianco <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/12/11 00:57:47 by gbianco           #+#    #+#             */
/*   Updated: 2020/02/05 19:24:22 by gbianco          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rtv1.h"

static void	color_pixel(t_scene *s, int x, int y)
{
	int pix;

	if (x >= 0 && y >= 0 && x <= s->mlx.wid && y <= s->mlx.hei)
	{
		pix = (x + (s->mlx.hei - 1 - y) * s->mlx.wid) << 2;
		*((int *)(s->mlx.pst + pix)) = s->pix.clr;
		s->mlx.pst[pix + 3] = 0;
	}
}

static void	select_color_mode(t_scene *s, int x, int y)
{
	if (s->efc.clrm != 0)
	{
		if (s->efc.clrm == 1)
			s->pix.clr = color_sepia(s->pix.clr);
		else if (s->efc.clrm == 2)
			s->pix.clr = color_grayscale(s->pix.clr);
		else if (s->efc.clrm == 3)
			s->pix.clr = color_negative(s->pix.clr);
		else if (s->efc.clrm == 10)
			s->pix.clr = color_nored(s->pix.clr);
		else if (s->efc.clrm == 11)
		{
			s->pix.clr = color_nocyan(s->pix.clr);
			color_secondary_pix(s, x, y);
			return ;
		}
	}
	color_pixel(s, x, y);
}

static void	select_ray_origin_mode(t_ray *r, t_scene *s)
{
	if (s->efc.clrm < 10)
		r->ori = s->cam.pos;
	else if (s->efc.clrm == 10)
		r->ori = v3_add(s->cam.pos, v3_scp(s->cam.v, s->efc.gly[0]));
	else if (s->efc.clrm == 11)
		r->ori = v3_dif(s->cam.pos, v3_scp(s->cam.v, s->efc.gly[0]));
}

static void	*rendering(void *sv)
{
	t_scene	*s;
	t_crd2	c;
	t_ray	r;
	int		max;

	s = (t_scene*)sv;
	select_ray_origin_mode(&r, s);
	max = s->strt + (s->mlx.hei / THREAD) + (s->mlx.hei % THREAD);
	c.y = s->strt - 1;
	while (++c.y < max)
	{
		c.x = -1;
		while (++c.x < s->mlx.wid)
		{
			if (s->efc.select == 0)
				s->pix.clr = single_ray(s, &r, c.x, c.y);
			else
				s->pix.clr = distribuited_rays(s, &r, c.x, c.y);
			select_color_mode(s, c.x, c.y);
		}
	}
	s->done = (s->efc.clrm == 10) ? 0 : 1;
	pthread_exit(NULL);
}

void		multithr_single_image(t_scene *s)
{
	pthread_t	thread[THREAD];
	int			i;

	precalc_camera(s);
	i = 0;
	while (++i < THREAD)
	{
		s[i].cam = s[0].cam;
		s[i].mlx = s[0].mlx;
		s[i].efc = s[0].efc;
	}
	i = -1;
	while (++i < THREAD)
		pthread_create(&thread[i], NULL, rendering, &s[i]);
	i++;
	while (--i > 0)
		pthread_join(thread[i - 1], NULL);
}
