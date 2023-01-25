/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_parsing2.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ilinhard <ilinhard@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/25 00:37:38 by ilinhard          #+#    #+#             */
/*   Updated: 2023/01/25 03:26:21 by ilinhard         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub3d.h"

int	ft_check_carac(char *str, int *count, t_game *game)
{
	int	i;

	i = 0;
	while(str[i] && (str[i] == ' ' || str[i] == '\t'))
		i++;
	while (str[i])
	{
		if (str[i] == 'N' || str[i] == 'W' || str[i] == 'S' || str[i] == 'E')
		{
			*count += 1;
			game->player_x = i;
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
		return (ft_free_tab(map), NULL);
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
	return(final_map);
}

char	**ft_create_map(char **map, t_game *game)
{
	int	i;
	int	start_map;
	int	count;

	i = 0;
	count = 0;
	ft_search_tab(map, "1", &i);
	start_map = i;
	while(i >= 0 && map[i])
	{
		if (ft_check_carac(map[i], &count, game))
				return (write(1, "Errors map format / caract\n", 27), map);
		if (count && !game->player_y)
			game->player_y = i - start_map; // vrai pos !!!!
		i++;
	}
	if (count > 1)
		write(1, "Errors map format / caract\n", 27);
	count = i - start_map;
	map = ft_final_map(map, start_map, count);
	return (map);
}