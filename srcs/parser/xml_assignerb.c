/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   xml_assignerb.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gbianco <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/01 17:05:52 by gbianco           #+#    #+#             */
/*   Updated: 2020/02/05 16:55:53 by gbianco          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rtv1.h"

int		assign_hex(char *str)
{
	int	hex;

	if (str[0] == '0' && (!(str[1])))
		return (0);
	if (ft_ishex(str) == 0)
		error("Plese check the format of hex values [0x000000]");
	hex = ft_atoi_base(str + 2, 16);
	return (hex);
}

int		assign_int(char *str)
{
	int	i;

	if (str == NULL)
		return (0);
	i = 0;
	while (str[i])
	{
		if (ft_isdigit(str[i]) == 0 && str[i] != '-')
			error("Please check the format of entire numbers");
		i++;
	}
	i = ft_atoi(str);
	return (i);
}

int		assign_chartype(char *str)
{
	char	*type[OBJ];
	int		i;

	type[0] = "plane";
	type[1] = "sphere";
	type[2] = "cylinder";
	type[3] = "cone";
	type[4] = "disk";
	type[5] = "triangle";
	type[6] = "cube";
	type[7] = "hyperboloid1";
	type[8] = "hyperboloid2";
	type[9] = "paraboloid1";
	type[10] = "paraboloid2";
	type[11] = "ellipsoid";
	type[12] = "torus";
	type[13] = "mobius";
	i = -1;
	while (++i < OBJ)
		if (ft_strcmp(type[i], str) == 0)
			return (i);
	error("The object type doesn't exist");
	return (0);
}

int		assign_colortype(char *str)
{
	char	*type[4];
	int		i;

	if (str == NULL)
		return (0);
	type[0] = "classic";
	type[1] = "sepia";
	type[2] = "grayscale";
	type[3] = "negative";
	i = -1;
	while (++i < 4)
		if (ft_strcmp(type[i], str) == 0)
			return (i);
	error("The color mode doesn't exist");
	return (0);
}

char	*assign_char_double(char *str, double *d)
{
	int		i;
	int		j;
	char	*dest;

	i = -1;
	if (str == NULL)
		return (NULL);
	j = 0;
	while (str[++i] != '\0' && str[i] != ',')
		j++;
	if (str[i] == '\0')
		error("Please check the format of char-double tags");
	dest = ft_secmemalloc(sizeof(char) * (j + 1));
	i = -1;
	while (++i < j)
		dest[i] = str[i];
	dest[i] = '\0';
	j = i;
	while (str[++i] != '\0')
		if (ft_isnumber(str[i]) == 0 && str[i] != ',' && str[i] != ' ')
			error("Please check the format of char-double tags");
	*d = ft_atof(str + j + 1);
	return (dest);
}
