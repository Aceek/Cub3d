/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_utils.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ilinhard <ilinhard@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/24 00:43:35 by ilinhard          #+#    #+#             */
/*   Updated: 2023/02/28 04:15:21 by ilinhard         ###   ########.fr       */
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
		return (error_handler(NULL, ERR_FILE_FORMAT));
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

int	ft_check_map_start(char *str_map)
{
	int	i;
	int	j;

	i = 0;
	while (str_map[i])
	{
		if (str_map[i] == '\n')
		{
			j = 1;
			while (str_map[i + j] && str_map[i + j] == ' ')
				j++;
			if (str_map[i + j] == '1' || str_map[i + j] == '0')
				return (i + j);
		}
		i++;
	}
	return (0);
}

int	ft_check_map_separation(char *str_map)
{
	int	i;

	i = ft_check_map_start(str_map);
	if (!i)
		return (error_handler(NULL, ERR_MAP_START), 1);
	while (str_map[i])
	{
		if (str_map[i] == '\n' && str_map[i + 1] == '\n'
			&& (str_map[i + 2] == '1' || str_map[i + 2] == '0'))
			return (error_handler(NULL, ERR_MAP_NEWLINE), 1);
		i++;
	}
	return (0);
}
