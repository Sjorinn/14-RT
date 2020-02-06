/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   random_textures.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pchambon <pchambon@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/01/26 11:38:26 by pchambon          #+#    #+#             */
/*   Updated: 2020/02/01 15:45:04 by pchambon         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/rtv1.h"

void	init_perm(t_scene *sc)
{
	int i;

	i = 0;
	while (i < 256)
	{
		sc->p.perm[i] = i;
		i++;
	}
	while (i < 512)
	{
		sc->p.perm[i] = i - 256;
		i++;
	}
}

void	deal_order1(t_scene *sc)
{
	sc->p.offijk[0].j = 0;
	if (sc->p.pos0.y >= sc->p.pos0.z)
	{
		sc->p.offijk[0].i = 1;
		sc->p.offijk[0].k = 0;
		sc->p.offijk[1].i = 1;
		sc->p.offijk[1].j = 1;
		sc->p.offijk[1].k = 0;
	}
	else if (sc->p.pos0.x >= sc->p.pos0.z)
	{
		sc->p.offijk[0].i = 1;
		sc->p.offijk[0].k = 0;
		sc->p.offijk[1].i = 1;
		sc->p.offijk[1].j = 0;
		sc->p.offijk[1].k = 1;
	}
	else
	{
		sc->p.offijk[0].i = 0;
		sc->p.offijk[0].k = 1;
		sc->p.offijk[1].i = 1;
		sc->p.offijk[1].j = 0;
		sc->p.offijk[1].k = 1;
	}
}

void	deal_order2(t_scene *sc)
{
	sc->p.offijk[0].i = 0;
	if (sc->p.pos0.y < sc->p.pos0.z)
	{
		sc->p.offijk[0].j = 0;
		sc->p.offijk[0].k = 1;
		sc->p.offijk[1].i = 0;
		sc->p.offijk[1].j = 1;
		sc->p.offijk[1].k = 1;
	}
	else if (sc->p.pos0.x < sc->p.pos0.z)
	{
		sc->p.offijk[0].j = 1;
		sc->p.offijk[0].k = 0;
		sc->p.offijk[1].i = 0;
		sc->p.offijk[1].j = 1;
		sc->p.offijk[1].k = 1;
	}
	else
	{
		sc->p.offijk[0].j = 1;
		sc->p.offijk[0].k = 0;
		sc->p.offijk[1].i = 1;
		sc->p.offijk[1].j = 1;
		sc->p.offijk[1].k = 0;
	}
}

void	init_noise(t_scene *sc, double x, double y, double z)
{
	int		i;
	int		j;
	int		k;
	double	s;
	double	t;

	s = (x + y + z) * F3;
	i = fastfloor((x + s));
	j = fastfloor((y + s));
	k = fastfloor((z + s));
	t = (double)(i + j + k) * G3;
	sc->p.pos0 = fix_vec(x - (i - t), y - (j - t), z - (k - t));
	sc->p.posijk.i = i & 0xff;
	sc->p.posijk.j = j & 0xff;
	sc->p.posijk.k = k & 0xff;
}

double	noise3d(t_scene *sc, double x, double y, double z)
{
	double noise;
	t_vec3 g[4];

	init_noise(sc, x, y, z);
	if (sc->p.pos0.x >= sc->p.pos0.y)
		deal_order1(sc);
	else
		deal_order2(sc);
	fix_corner_other(sc);
	perm_corn1(sc, g);
	perm_corn2(sc, g);
	perm_corn3(sc, g);
	perm_corn4(sc, g);
	noise = 28.0f * (sc->p.noise_corners.x +
		sc->p.noise_corners.y + sc->p.noise_corners.z +
			sc->p.noise_corners.w);
	return (noise);
}
