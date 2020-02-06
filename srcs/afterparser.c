/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   afterparser.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gbianco <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/07/23 20:34:31 by gbianco           #+#    #+#             */
/*   Updated: 2020/02/06 05:52:14 by lucmarti         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rtv1.h"

static void	correct_cam_dir(t_scene *s)
{
	if (CAM_CORRECTION == 1)
	{
		if (s->cam.dir.x == 0 && s->cam.dir.y == 0)
			s->cam.dir.y = CAM_BIAS;
		if (s->cam.dir.y == 0 && s->cam.dir.z == 0)
			s->cam.dir.y = CAM_BIAS;
		if (s->cam.dir.x == 0 && s->cam.dir.z == 0)
			s->cam.dir.z = CAM_BIAS;
	}
}

static void	check_effects_data(t_scene *s)
{
	if (s->efc.gly[0] > 0)
	{
		if (s->efc.clrm != 0)
			error("Color cannot be changed in 3D mode");
		if (s->efc.maxtime != 0 || s->efc.blu[0] != 0)
			error("Blur not supported in 3D mode");
	}
	if (s->efc.blu[1] > 20 || s->efc.blu[1] < -20)
		error("The intensity of the cam blur is out of range [-20 to 20]");
	if (s->efc.aa != 0 || s->efc.toon != 0 || s->efc.blu[1] > 1
		|| s->efc.blu[1] < -1)
		s->efc.select = 1;
	if (s->efc.maxtime != 0)
		s->efc.select = 2;
}

static void	check_scene_data(t_scene *s)
{
	if (v3_cmp(s->cam.dir, v3(0, 0, 0)) == 1)
		error("The direction of the camera cannot be [0, 0, 0]");
	s->cam.dir = v3_nor(s->cam.dir);
	if (s->cam.fov <= 0 || s->cam.fov >= 180)
		error("The camera FOV is invalid [1 to 179]");
	if (s->mlx.title == '\0')
		s->mlx.title = "No title";
	if (s->mlx.wid > 2000 || s->mlx.wid < 100)
		error("Windows width out of range [100 to 2000]");
	if (s->mlx.hei > 2000 || s->mlx.hei < 100)
		error("Windows height out of range [100 to 2000]");
	if (s->pix.amb > 1 || s->pix.amb < 0)
		error("Ambient light out of range [0 to 1]");
	if (s->pix.amb == 0)
		s->pix.amb = AMBIENT_CORRECTION;
}

void		init_camlight_data(t_scene *s)
{
	int i;

	if (s->cam.glr.select == 1)
	{
		s->cam.glr.shadow = (int*)ft_secmemalloc(sizeof(int) * s->n_lht);
		s->cam.glr.fakeplane = (t_obj*)ft_secmemalloc(sizeof(t_obj) * s->n_lht);
		i = -1;
		while (++i < s->n_lht)
			s->cam.glr.fakeplane[i].pr = (t_prm*)ft_secmemalloc(sizeof(t_prm));
		s->cam.glr.select = 2;
	}
}

void		after_parser(t_scene *s)
{
	improve_data(s);
	check_scene_data(s);
	check_effects_data(s);
	init_camlight_data(s);
	correct_cam_dir(s);
	s->rstcam = s->cam;
}
