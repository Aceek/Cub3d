/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_utils.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pbeheyt <pbeheyt@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/24 00:43:35 by ilinhard          #+#    #+#             */
/*   Updated: 2023/01/25 00:34:03 by pbeheyt          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub3d.h"

int	ft_strlen(char *str)
{
	int	i;

	i = 0;
	while (str && str[i])
		i++;
	return (i);
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
