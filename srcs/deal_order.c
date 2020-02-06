/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   deal_order.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pchambon <pchambon@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/01/29 14:24:48 by pchambon          #+#    #+#             */
/*   Updated: 2020/01/29 15:25:45 by pchambon         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/rtv1.h"

void	fix_corner_other(t_scene *sc)
{
	sc->p.offxyz[0].x = sc->p.pos0.x - sc->p.offijk[0].i + G3;
	sc->p.offxyz[0].y = sc->p.pos0.y - sc->p.offijk[0].j + G3;
	sc->p.offxyz[0].z = sc->p.pos0.z - sc->p.offijk[0].k + G3;
	sc->p.offxyz[1].x = sc->p.pos0.x - sc->p.offijk[1].i
		+ 2.0f * G3;
	sc->p.offxyz[1].y = sc->p.pos0.y - sc->p.offijk[1].j
		+ 2.0f * G3;
	sc->p.offxyz[1].z = sc->p.pos0.z - sc->p.offijk[1].k
		+ 2.0f * G3;
	sc->p.offxyz[2].x = sc->p.pos0.x - 1.0f + 3.0f * G3;
	sc->p.offxyz[2].y = sc->p.pos0.y - 1.0f + 3.0f * G3;
	sc->p.offxyz[2].z = sc->p.pos0.z - 1.0f + 3.0f * G3;
}

void	perm_corn1(t_scene *sc, t_vec3 *g)
{
	double t0;
	double t20;
	double t40;

	t0 = 0.6f - sc->p.pos0.x * sc->p.pos0.x - sc->p.pos0.y
		* sc->p.pos0.y - sc->p.pos0.z * sc->p.pos0.z;
	if (t0 < 0.0f)
	{
		sc->p.noise_corners.x = 0;
		t0 = 0;
		t20 = 0;
		t40 = 0;
		g[0] = fix_vec(0, 0, 0);
	}
	else
	{
		grad3(sc, sc->p.perm[sc->p.posijk.i + sc->p.perm[sc->p.posijk.j
			+ sc->p.perm[sc->p.posijk.k]]], &g[0]);
		t20 = t0 * t0;
		t40 = t20 * t20;
		sc->p.noise_corners.x = t40 * (g[0].x * sc->p.pos0.x
			+ g[0].y * sc->p.pos0.y + g[0].z * sc->p.pos0.z);
	}
}

void	perm_corn2(t_scene *sc, t_vec3 *g)
{
	double t1;
	double t21;
	double t41;

	t1 = 0.6f - sc->p.offxyz[0].x * sc->p.offxyz[0].x - sc->p.offxyz[0].y
		* sc->p.offxyz[0].y - sc->p.offxyz[0].z * sc->p.offxyz[0].z;
	if (t1 < 0.0f)
	{
		sc->p.noise_corners.y = 0;
		t1 = 0;
		t21 = 0;
		t41 = 0;
		g[1] = fix_vec(0, 0, 0);
	}
	else
	{
		grad3(sc, sc->p.perm[sc->p.posijk.i + sc->p.offijk[0].i +
		sc->p.perm[sc->p.posijk.j + sc->p.offijk[0].j +
		sc->p.perm[sc->p.posijk.k + sc->p.offijk[0].k]]],
		&g[1]);
		t21 = t1 * t1;
		t41 = t21 * t21;
		sc->p.noise_corners.y = t41 * (g[1].x * sc->p.offxyz[0].x
			+ g[1].y * sc->p.offxyz[0].y + g[1].z * sc->p.offxyz[0].z);
	}
}

void	perm_corn3(t_scene *sc, t_vec3 *g)
{
	double t2;
	double t22;
	double t42;

	t2 = 0.6f - sc->p.offxyz[1].x * sc->p.offxyz[1].x - sc->p.offxyz[1].y
	* sc->p.offxyz[1].y - sc->p.offxyz[1].z * sc->p.offxyz[1].z;
	if (t2 < 0.0f)
	{
		sc->p.noise_corners.z = 0;
		t2 = 0;
		t22 = 0;
		t42 = 0;
		g[2] = fix_vec(0, 0, 0);
	}
	else
	{
		grad3(sc, sc->p.perm[sc->p.posijk.i + sc->p.offijk[1].i +
		sc->p.perm[sc->p.posijk.j + sc->p.offijk[1].j +
		sc->p.perm[sc->p.posijk.k + sc->p.offijk[1].k]]],
		&g[2]);
		t22 = t2 * t2;
		t42 = t22 * t22;
		sc->p.noise_corners.z = t42 * (g[2].x * sc->p.offxyz[1].x
			+ g[2].y * sc->p.offxyz[1].y + g[2].z * sc->p.offxyz[1].z);
	}
}

void	perm_corn4(t_scene *sc, t_vec3 *g)
{
	double t3;
	double t23;
	double t43;

	t3 = 0.6f - sc->p.offxyz[2].x * sc->p.offxyz[2].x
	- sc->p.offxyz[2].y * sc->p.offxyz[2].y -
		sc->p.offxyz[2].z * sc->p.offxyz[2].z;
	if (t3 < 0.0f)
	{
		sc->p.noise_corners.w = 0;
		t3 = 0;
		t23 = 0;
		t43 = 0;
		g[3] = fix_vec(0, 0, 0);
	}
	else
	{
		grad3(sc, sc->p.perm[sc->p.posijk.i + 1 + sc->p.perm[sc->p.posijk.j
			+ 1 + sc->p.perm[sc->p.posijk.k + 1]]], &g[3]);
		t23 = t3 * t3;
		t43 = t23 * t23;
		sc->p.noise_corners.w = t43 * (g[3].x * sc->p.offxyz[2].x +
			g[3].y * sc->p.offxyz[2].y + g[3].z * sc->p.offxyz[2].z);
	}
}
