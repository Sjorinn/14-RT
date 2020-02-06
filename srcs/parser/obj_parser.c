/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   obj_parser.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gbianco <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/01/10 14:28:07 by gbianco           #+#    #+#             */
/*   Updated: 2020/02/05 16:36:52 by gbianco          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rtv1.h"

static void	show_info(int v, int n, int t)
{
	ft_putstr("File information\n");
	ft_putstr("N.Vertex: ");
	ft_putnbr(v);
	ft_putchar('\n');
	ft_putstr("N.Normals: ");
	ft_putnbr(n);
	ft_putchar('\n');
	ft_putstr("N.Triangles: ");
	ft_putnbr(t);
	ft_putchar('\n');
}

static void	obj_collect_data(char **av, t_objw *objw)
{
	int		fd;
	int		check;
	char	*line;

	if ((fd = open(av[1], O_RDONLY)) < 0)
		error("Error reading the file, sure that it exists?");
	check = 1;
	ft_bzero((void*)objw, sizeof(t_objw));
	while ((check = get_next_line(fd, &line)) > 0)
		count_elements(objw, line);
	close(fd);
	if (objw->n_vertex < 1 || objw->n_triangle < 1)
		error("Invalid obj file");
	alloc_elements(objw);
	fd = open(av[1], O_RDONLY);
	while ((check = get_next_line(fd, &line)) > 0)
		split_elements(objw, line);
	show_info(objw->n_vertex, objw->n_normal, objw->n_triangle);
}

static void	obj_data_cleaner(t_objw *objw)
{
	free(objw->v_vertex);
	free(objw->v_normal);
	free(objw->v_texture);
	free(objw->d_trn);
}

void		parser_obj(t_scene *s, char **av)
{
	t_objw	objw;

	if (ft_strcmp(av[2], "render") == 0)
	{
		obj_collect_data(av, &objw);
		obj_data_associer(s, &objw);
		obj_data_cleaner(&objw);
	}
	else if (ft_strcmp(av[2], "converter") == 0)
	{
		obj_collect_data(av, &objw);
		obj_data_converter(av[1], &objw);
		obj_data_cleaner(&objw);
	}
	else
		error("Aviable mode for obj files: [render], [converter]");
}
