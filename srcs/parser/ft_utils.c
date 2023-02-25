/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_utils.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ilinhard <ilinhard@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/24 00:43:35 by ilinhard          #+#    #+#             */
/*   Updated: 2023/02/25 02:55:06 by ilinhard         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub3d.h"

int	ft_search_tab(char **tab, char *to_find, int *pos, int mod)
{
	int	i;

	i = 0;
	while (tab[i])
	{
		if (ft_find(tab[i], to_find, mod))
			return (*pos = i, i);
		i++;
	}
	return (*pos = -1, -1);
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
	t_text_list	*tmp;
	t_text_list	*next;

	tmp = game->head;
	if (game && game->north)
		free(game->north);
	if (game && game->east)
		free(game->east);
	if (game && game->west)
		free(game->west);
	if (game && game->south)
		free(game->south);
	if (game->init)
	{
		free(game);
		return ;
	}
	while (tmp)
	{
		next = tmp->next;
		free(tmp->path);
		free(tmp);
		tmp = next;
	}
	free(game);
}

int	ft_check_size_map(char **map_file, t_game *game)
{
	int				size_list;
	int				max;
	t_text_list		*tmp;

	size_list = 0;
	max = 0;
	tmp = game->head;
	while (tmp)
	{
		size_list++;
		tmp = tmp->next;
	}
	ft_search_tab(map_file, "1", &max, 0);
	if ((max - 5 - size_list) != 0)
	{
		printf("Error\nconfig file format line\n"); // no
		return (1);
	}
	return (0);
}

int	ft_check_space_in_tab(char **map)
{
	int	i;
	int	j;

	i = 0;
	while (map[i])
	{
		j = 0;
		while (map[i][j] == ' ')
			j++;
		if (map[i][j] == '\0')
			return (1);
		i++;
	}
	return (0);
}
