/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   solver_quartic.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gbianco <gbianco@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/01/21 00:06:10 by gbianco           #+#    #+#             */
/*   Updated: 2020/02/04 20:34:44 by nkellum          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rtv1.h"
#include "solver.h"

static int	power2_factorization(double *c, double *t)
{
	t_vec3	coef;
	double	v_sqrt;

	coef.x = c[1] / (2. * c[2]);
	coef.y = c[0] / c[2];
	coef.z = coef.x * coef.x - coef.y;
	if (iszero(coef.z))
	{
		t[0] = -coef.x;
		return (1);
	}
	else if (coef.z < 0)
		return (0);
	else
	{
		v_sqrt = sqrt(coef.z);
		t[0] = v_sqrt - coef.x;
		t[1] = -v_sqrt - coef.x;
		return (2);
	}
}

static int	quartic_conditions_c(t_quartic *qr)
{
	if (iszero(qr->u))
		qr->u = 0;
	else if (qr->u > 0)
		qr->u = sqrt(qr->u);
	else
		return (-1);
	if (iszero(qr->v))
		qr->v = 0;
	else if (qr->v > 0)
		qr->v = sqrt(qr->v);
	else
		return (-1);
	return (0);
}

static int	quartic_conditions_b(double *t, t_quartic *qr)
{
	qr->coef[0] = 1. / 2. * qr->r * qr->p - 1. / 8. * qr->q * qr->q;
	qr->coef[1] = -qr->r;
	qr->coef[2] = -1. / 2. * qr->p;
	qr->coef[3] = 1.;
	cubic_solver(qr->coef, t);
	qr->z = t[0];
	qr->u = qr->z * qr->z - qr->r;
	qr->v = 2. * qr->z - qr->p;
	if (quartic_conditions_c(qr) == -1)
		return (-1);
	qr->coef[0] = qr->z - qr->u;
	qr->coef[1] = qr->q < 0 ? -qr->v : qr->v;
	qr->coef[2] = 1.;
	qr->num = power2_factorization(qr->coef, t);
	qr->coef[0] = qr->z + qr->u;
	qr->coef[1] = qr->q < 0 ? qr->v : -qr->v;
	qr->coef[2] = 1.;
	qr->num += power2_factorization(qr->coef, &t[qr->num]);
	return (0);
}

static void	quartic_conditions_a(double *t, t_quartic *qr)
{
	qr->coef[0] = qr->q;
	qr->coef[1] = qr->p;
	qr->coef[2] = 0;
	qr->coef[3] = 1.;
	qr->num = cubic_solver(qr->coef, t);
	t[qr->num++] = 0;
}

int			quartic_solver(double c[5], double *t)
{
	t_quartic	qr;

	qr.a = c[3] / c[4];
	qr.b = c[2] / c[4];
	qr.c = c[1] / c[4];
	qr.d = c[0] / c[4];
	qr.sq_a = qr.a * qr.a;
	qr.p = -3. / 8. * qr.sq_a + qr.b;
	qr.q = 1. / 8. * qr.sq_a * qr.a - 1. / 2. * qr.a * qr.b + qr.c;
	qr.r = -3. / 256. * qr.sq_a * qr.sq_a + 1. / 16. * qr.sq_a * qr.b - 1. / 4.
		* qr.a * qr.c + qr.d;
	if (iszero(qr.r))
		quartic_conditions_a(t, &qr);
	else if (quartic_conditions_b(t, &qr) == -1)
		return (0);
	qr.sub = 1. / 4. * qr.a;
	qr.i = -1;
	while (++qr.i < qr.num)
		t[qr.i] -= qr.sub;
	return (qr.num);
}
