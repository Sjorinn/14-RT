/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_fmin.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gbianco <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/12/27 21:37:27 by gbianco           #+#    #+#             */
/*   Updated: 2019/12/27 21:40:52 by gbianco          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

void	ft_fmin(double *n, double min)
{
	*n = *n < min ? min : *n;
}
