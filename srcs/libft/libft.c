/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   libft.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pbeheyt <pbeheyt@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/25 03:14:58 by ilinhard          #+#    #+#             */
/*   Updated: 2023/02/25 01:25:36 by pbeheyt          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub3d.h"

void	ft_putstr_fd(char *s, int fd)
{
	int	i;

	if (fd < 0 || !s)
		return ;
	i = -1;
	while (s[++i])
		write(fd, &s[i], 1);
}

char	*ft_strdup(const char *s)
{
	int			i;
	char		*cpy;

	if (s == NULL)
		return (NULL);
	i = ft_strlen((char *)s);
	cpy = malloc(sizeof(char) * (i + 1));
	if (cpy == NULL)
		return (NULL);
	i = 0;
	while (s[i])
	{
		cpy[i] = s[i];
		i++;
	}
	cpy[i] = '\0';
	return (cpy);
}

int	ft_count_nbr(int nbr)
{
	int			i;
	long long	count;

	i = 0;
	count = nbr;
	if (nbr < 0)
	{
		count = -nbr;
		i++;
	}
	while (count)
	{
		count = count / 10;
		i++;
	}
	return (i);
}

char	*ft_itoa(long long nbr)
{
	char	*str;
	int		len;
	int		sign;

	len = ft_count_nbr(nbr);
	sign = 0;
	str = malloc(sizeof(char) * (len + 1));
	if (!str)
		return (NULL);
	if (nbr < 0)
	{
		str[0] = '-';
		nbr = -nbr;
		sign = 1;
	}
	str[len] = '\0';
	while (len)
	{
		len --;
		str[len] = nbr % 10 + '0';
		nbr /= 10;
	}
	if (sign)
		str[0] = '-';
	return (str);
}

int	ft_strlen(char *str)
{
	int	i;

	i = 0;
	while (str && str[i])
		i++;
	return (i);
}

void	ft_free_tab(char **tab)
{
	int	i;

	i = -1;
	while (tab && tab[++i])
	{
		if (tab[i])
			free(tab[i]);
	}
	free(tab);
}
