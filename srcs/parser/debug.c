/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   debug.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lucmarti <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/01/13 11:19:48 by lucmarti          #+#    #+#             */
/*   Updated: 2020/02/05 23:30:50 by lucmarti         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rtv1.h"

void	print_vector(t_vec3 v, char *name)
{
	ft_printf("%s\nx:[%.75f]\ny:[%.75f]\nz:[%.75f]\n\n", name, v.x, v.y, v.z);
}

void	print_void(t_scene *s)
{
	t_nhit *cur;

	cur = s->void_regions;
	if (!cur)
	{
		ft_printf("No void region\n");
		return ;
	}
	while (cur)
	{
		ft_printf("Forbidden zone : %f - %f\n", cur->dist_st, cur->dist_lt);
		cur = cur->next;
	}
}
