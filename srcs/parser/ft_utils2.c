/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_utils2.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ilinhard <ilinhard@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/24 05:55:57 by ilinhard          #+#    #+#             */
/*   Updated: 2023/02/25 03:04:10 by ilinhard         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub3d.h"

int	ft_make_color(char *str)
{
	int	red;
	int	blue;
	int	green;
	int	i;

	i = 0;
	red = -1;
	blue = -1;
	green = -1;
	red = ft_atoi(str, &i, 1);
	green = ft_atoi(str, &i, 0);
	blue = ft_atoi(str, &i, 0);
	while (str[i] && str[i] == ' ')
		i++;
	if (str[i] != '\0')
		return (-1);
	if (green < 0 || red < 0 || blue < 0)
		return (-1);
	return (ft_encode_rgb(red, green, blue));
}

int	ft_atoi(char *str, int *pos, int first)
{
	int	nbr;
	int	len;

	nbr = 0;
	len = 0;
	if (first && (str[*pos] == 'F' || str[*pos] == 'C'))
		*pos += 1;
	while (first && str[*pos] == ' ')
		*pos += 1;
	if (!first && str[*pos] == ',')
		*pos += 1;
	while (str && (str[*pos] >= '0' && str[*pos] <= '9'))
	{
		nbr = (nbr * 10) + str[*pos] - '0';
		*pos += 1;
		len++;
	}
	if (!len || len >= 4 || nbr > 255)
		return (-1);
	return (nbr);
}

int	ft_encode_rgb(int red, int green, int blue)
{
	return (red << 16 | green << 8 | blue);
}

char	*ft_strjoin(char *s1, char *s2)
{
	char	*new;
	int		i;
	int		j;

	if (!s1)
	{
		s1 = malloc(sizeof(char) * 1);
		s1[0] = '\0';
	}
	if (!s1 || !s2)
		return (NULL);
	new = malloc(sizeof(char) * (ft_strlen(s1) + ft_strlen(s2) + 1));
	if (!new)
		return (NULL);
	i = -1;
	while (s1[++i])
		new[i] = s1[i];
	j = -1;
	while (s2[++j])
		new[i + j] = s2[j];
	new[i + j] = '\0';
	free(s1);
	return (new);
}

int	ft_find(char *str, char *to_find, int mod)
{
	int	i;
	int	j;
	int	len;

	i = 0;
	len = ft_strlen(to_find);
	while (str && str[i] == ' ')
		i++;
	j = 0;
	while (str[i + j] && to_find[j] && str[i + j] == to_find[j])
			j++;
	if (!mod && j == len)
		return (1);
	else if (mod && j == len && str[i + j] == ' ')
		return (1);
	return (0);
}
