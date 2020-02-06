/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   xml_count.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gbianco <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/01 17:06:11 by gbianco           #+#    #+#             */
/*   Updated: 2020/02/01 17:06:13 by gbianco          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rtv1.h"

int		count_all_tags(char *st)
{
	int	i;
	int	count;

	i = 1;
	count = 0;
	while (st[i] != 0)
	{
		while (st[i] != '\0' && st[i] != '<')
			i++;
		count++;
		if (st[i] != '\0')
			i++;
	}
	return (count);
}

int		count_word(char *str, char *chk)
{
	int	i;
	int	j;
	int	cnt;

	i = 0;
	cnt = 0;
	while (str[i] != '\0')
	{
		if (str[i] == chk[0])
		{
			j = 0;
			while (str[i] != '\0' && chk[j] != '\0' && str[i] == chk[j])
			{
				i++;
				j++;
			}
			if (chk[j] == '\0')
				cnt++;
			else
				i -= j;
		}
		if (str[i] != '\0')
			i++;
	}
	return (cnt);
}

int		count_tag_size(char *st)
{
	int	i;

	i = 0;
	if (st[i] != '\0' && st[i] == '<')
		while (st[i] != '\0' && st[i] != '>')
			i++;
	if (st[i] == '\0')
		error("Problem with some xml tag");
	i++;
	return (i);
}
