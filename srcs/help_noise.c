/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   help_noise.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pchambon <pchambon@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/01/29 13:29:05 by pchambon          #+#    #+#             */
/*   Updated: 2020/01/30 12:24:28 by pchambon         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/rtv1.h"

void	init_grad(t_scene *s)
{
	s->p.grad[0] = fix_vec(1, 0, 1);
	s->p.grad[1] = fix_vec(0, 1, 1);
	s->p.grad[2] = fix_vec(-1, 0, 1);
	s->p.grad[3] = fix_vec(0, -1, 1);
	s->p.grad[4] = fix_vec(1, 0, -1);
	s->p.grad[5] = fix_vec(0, 1, -1);
	s->p.grad[6] = fix_vec(-1, 0, -1);
	s->p.grad[7] = fix_vec(0, -1, -1);
	s->p.grad[8] = fix_vec(1, -1, 0);
	s->p.grad[9] = fix_vec(1, 1, 0);
	s->p.grad[10] = fix_vec(-1, 1, 0);
	s->p.grad[11] = fix_vec(-1, -1, 0);
	s->p.grad[12] = fix_vec(1, 0, 1);
	s->p.grad[13] = fix_vec(0, 1, 1);
	s->p.grad[14] = fix_vec(-1, 0, 1);
	s->p.grad[15] = fix_vec(0, -1, 1);
}

void	grad3(t_scene *s, int hash, t_vec3 *g)
{
	int h;

	h = hash & 15;
	g->x = s->p.grad[h].x;
	g->y = s->p.grad[h].y;
	g->z = s->p.grad[h].z;
	return ;
}

t_vec3	fix_vec(double x, double y, double z)
{
	t_vec3 tmp;

	tmp.x = x;
	tmp.y = y;
	tmp.z = z;
	return (tmp);
}
