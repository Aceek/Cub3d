/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_utils.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ilinhard <ilinhard@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/24 00:43:35 by ilinhard          #+#    #+#             */
/*   Updated: 2023/01/24 04:29:30 by ilinhard         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

int	ft_strlen(char *str)
{
	int	i;

	i = 0;
	while (str && str[i])
		i++;
	return (i);
}

int	ft_find(char *str, char *to_find)
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
	if (j == len)
	{
		while (str[i + j] && str[i + j] == ' ')	
			j++;
		if (str[i + j] == '.')
			return (1);
	}
	return (0);
}

int	ft_search_tab(char **tab, char *to_find, int *pos)
{
	int	i;

	i = 0;
	while (tab[i])
	{
		if (ft_find(tab[i], to_find))		
			return (*pos = i, i);
		i++;
	}
	return (*pos = -1, -1);
}

void	ft_free_tab(char **tab)
{
	int	i;

	i = -1;
	while (tab && tab[++i])
		free(tab[i]);
	free(tab);
}

char	*ft_cpy(char *str)
{
	int		i;
	int		j;
	int		len;
	char	*new;

	i = 0;
	while (str[i] && str[i] != '.')
		i++;
	len = ft_strlen(str) - i;
	if (!str[i] || str[i] != '.' || len <= 0)
		return (NULL);
	new = malloc(sizeof(char) * (len + 1));
	if (!new)
		return (NULL);
	j = 0;
	while (str[i + j])
	{
		new[j] = str[i + j];
		j++;
	}
	new[j] = '\0';
	return (new);
}

void	ft_free_data_game(t_game *game)
{
	free(game->north);
	free(game->east);
	free(game->west);
	free(game->south);

	free(game);
}