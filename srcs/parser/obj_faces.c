/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   obj_faces.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gbianco <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/01/10 14:34:02 by gbianco           #+#    #+#             */
/*   Updated: 2020/02/05 16:29:27 by gbianco          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rtv1.h"

static int	concat_elm(char *line, char *elm)
{
	int i;
	int j;

	line[0] = ' ';
	i = 1;
	j = 0;
	while (elm[j])
	{
		line[i] = elm[j];
		i++;
		j++;
	}
	line[i] = '\0';
	return (i);
}

static void	faces_to_triangles(t_objw *objw, char **elm, int triangles)
{
	char	*line[triangles];
	char	*temp;
	int		n;
	int		i;

	i = 0;
	while (i < triangles)
	{
		n = ft_strlen(elm[0]) + ft_strlen(elm[i + 1]) + ft_strlen(elm[i + 2]);
		line[i] = (char*)ft_secmemalloc(n + 5);
		temp = line[i];
		line[i][0] = 'f';
		line[i] += 1;
		line[i] += concat_elm(line[i], elm[0]);
		line[i] += concat_elm(line[i], elm[i + 1]);
		line[i] += concat_elm(line[i], elm[i + 2]);
		obj_assign_triangle(objw, temp);
		ft_strdel(&temp);
		i++;
	}
	ft_strarraydel(elm);
}

void		obj_assign_faces(t_objw *objw, char *line, int triangles)
{
	int		i;
	char	**elm;

	i = 0;
	while (line[i] && line[i] != 'f')
		i++;
	while (line[i] && ft_isnumber(line[i]) == 0)
		i++;
	elm = ft_strsplit(&line[i], ' ');
	triangles -= 2;
	faces_to_triangles(objw, elm, triangles);
}
