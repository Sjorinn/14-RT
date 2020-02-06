/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gbianco <gbianco@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/06/24 15:52:33 by gbianco           #+#    #+#             */
/*   Updated: 2020/02/05 16:46:29 by gbianco          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rtv1.h"

void	clean_scene(t_scene *s)
{
	ft_bzero(s->mlx.pst, s->mlx.wid * s->mlx.hei * 4);
	if (s->cam.glr.select > 0)
	{
		ft_bzero(s->cam.glr.shadow, sizeof(int) * s->n_lht);
		s->cam.glr.select = 2;
	}
	if (s->efc.gly[0] != 0)
	{
		ft_bzero(s->mlx.sst, s->mlx.wid * s->mlx.hei * 4);
		s->efc.clrm = 10;
	}
	select_image_mode(s);
}

void	*select_image_mode(void *sv)
{
	static int	i;
	t_scene		*s;

	s = (t_scene *)sv;
	if (s->efc.gly[0] == 0)
	{
		multithr_single_image(s);
	}
	else
	{
		if (i == 0)
		{
			s->mlx.sim = mlx_new_image(s->mlx.ptr, s->mlx.wid, s->mlx.hei);
			s->mlx.sst = mlx_get_data_addr(s->mlx.sim, &s->mlx.b, &s->mlx.s,\
					&s->mlx.e);
			i = 1;
		}
		anaglyph_multi_image(s);
	}
	if (s->mlx.event_enable == 1)
		mlx_put_image_to_window(s->mlx.ptr, s->mlx.win, s->mlx.pim, 0, 0);
	return (NULL);
}

void	duplicate_scene_thread(t_scene *s)
{
	int i;
	int	add;

	i = 0;
	srand(time(NULL));
	s->p.offset.i = rand() % 2048;
	s->p.offset.j = rand() % 2048;
	s->p.offset.k = rand() % 2048;
	add = s->mlx.hei / THREAD;
	s[i].strt = add * i;
	s[i].hit.clt = (t_clt*)ft_secmemalloc(sizeof(t_clt) * (s[i].n_obj * GRADE));
	while (++i < THREAD)
	{
		s[i] = s[0];
		s[i].id = i;
		s[i].done = 0;
		s[i].strt = add * i;
		s[i].hit.clt = (t_clt*)ft_secmemalloc(sizeof(t_clt)\
				* (s[i].n_obj * GRADE));
		s[i].obj = (t_obj*)ft_secmemalloc(sizeof(t_obj) * s->n_obj);
		ft_memcpy(s[i].obj, s[0].obj, sizeof(t_obj) * s->n_obj);
	}
}

int		main(int ac, char **av)
{
	t_scene	s[THREAD];

	ft_bzero((void *)&s, sizeof(t_scene) * THREAD);
	parse(&s[0], av, ac);
	after_parser(&s[0]);
	s->p.perl = 0;
	s->mlx.ptr = mlx_init();
	s->mlx.win = mlx_new_window(s->mlx.ptr, s->mlx.wid, s->mlx.hei,\
			s->mlx.title);
	s->mlx.pim = mlx_new_image(s->mlx.ptr, s->mlx.wid, s->mlx.hei);
	s->mlx.pst = mlx_get_data_addr(s->mlx.pim, &s->mlx.b, &s->mlx.s, &s->mlx.e);
	init_textures(s);
	duplicate_scene_thread(s);
	start_program(s, 0, -1, 100 / THREAD);
	mlx_hook(s->mlx.win, 2, 0, key_press_loop, &s[0]);
	mlx_hook(s->mlx.win, 3, 0, key_release_loop, &s[0]);
	mlx_hook(s->mlx.win, 4, 0, mouse_loop, &s[0]);
	mlx_hook(s->mlx.win, 17, 0, finish, NULL);
	mlx_loop(s->mlx.ptr);
	return (0);
}
