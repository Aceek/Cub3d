/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_parsing2.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ilinhard <ilinhard@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/25 00:37:38 by ilinhard          #+#    #+#             */
/*   Updated: 2023/03/12 03:11:20 by ilinhard         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub3d.h"

int	ft_check_carac(char *str, int *count, t_game *game)
{
	int	i;

	i = 0;
	while (str[i] && str[i] == ' ')
		i++;
	while (str[i])
	{
		if (str[i] == 'N' || str[i] == 'W' || str[i] == 'S' || str[i] == 'E')
		{
			*count += 1;
			game->player_x = i;
			game->dir_player = str[i];
		}
		if (str[i] == 'N' || str[i] == 'W' || str[i] == 'S' || str[i] == 'E'
			|| str[i] == '0' || str[i] == '1' || str[i] == ' ')
			i++;
		else
			return (1);
	}
	return (0);
}

char	**ft_final_map(char **map, int start_map, int len)
{
	char	**final_map;
	int		i;

	i = 0;
	final_map = NULL;
	if (len < 3)
		return (ft_free_tab(map), error_handler(NULL, ERR_MAP_FORMAT), NULL);
	final_map = malloc(sizeof(char *) * (len + 1));
	if (!final_map)
		return (ft_free_tab(map), NULL);
	while (map[start_map + i])
	{
		final_map[i] = ft_strdup(map[start_map + i]);
		i++;
	}
	final_map[i] = NULL;
	ft_free_tab(map);
	return (final_map);
}

void	ft_verify_map_exit(char **map, int i, int j, int *exit)
{
	if (j < 0 || i < 0 || !map[i] || j >= ft_strlen(map[i])
		|| !map[i][j] || (map[i][j] && map[i][j] == ' '))
	{
		*exit = 1;
		return ;
	}
	else if (map[i][j] != '0')
		return ;
	map[i][j] = 'X';
	ft_verify_map_exit(map, i - 1, j, exit);
	ft_verify_map_exit(map, i + 1, j, exit);
	ft_verify_map_exit(map, i, j - 1, exit);
	ft_verify_map_exit(map, i, j + 1, exit);
}

char	**ft_verify_map_error(char **map, t_game *game, int i, int start_map)
{
	int	exit;

	exit = 0;
	map = ft_final_map(map, start_map, (i - start_map));
	if (!map)
		return (NULL);
	exit = 0;
	map[game->player_y][game->player_x] = '0';
	ft_verify_map_exit(map, game->player_y, game->player_x, &exit);
	if (exit)
		return (ft_free_tab(map), error_handler(NULL, ERR_MAP_EXIT), NULL);
	return (map);
}

char	**ft_create_map(char **map, t_game *game)
{
	int	i;
	int	start_map;
	int	count;
	int	first;

	first = 0;
	i = 0;
	count = 0;
	ft_search_tab(map, "1", &i, 0);
	start_map = i;
	while (i >= 0 && map[i])
	{
		if (ft_check_carac(map[i], &count, game))
			return (ft_free_tab(map), error_handler(NULL, ERR_MAP_CARAC), NULL);
		if (count && !game->player_y && !first)
		{
			game->player_y = i - start_map;
			first = 1;
		}
		i++;
	}
	if (count != 1)
		return (ft_free_tab(map),
			error_handler(NULL, ERR_MAP_FORMAT), NULL);
	return (map = ft_verify_map_error(map, game, i, start_map), map);
}
