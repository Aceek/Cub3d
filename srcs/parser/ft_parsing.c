/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_parsing.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pbeheyt <pbeheyt@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/24 00:33:26 by ilinhard          #+#    #+#             */
<<<<<<< HEAD:srcs/ft_parsing.c
/*   Updated: 2023/01/25 00:37:53 by ilinhard         ###   ########.fr       */
=======
/*   Updated: 2023/01/25 00:33:35 by pbeheyt          ###   ########.fr       */
>>>>>>> main:srcs/parser/ft_parsing.c
/*                                                                            */
/* ************************************************************************** */

#include "../cub3d.h"

char	*ft_init_map(int file_fd)
{
	char	*str_map;
	char	*buff;
	int		read_len;

	str_map = NULL;
	buff = malloc(sizeof(char) * (BUFFER_SIZE + 1));
	if (!buff)
		return (write(1, "Error init map\n", 15), NULL);
	read_len = 1;
	while (read_len)
	{
		read_len = read(file_fd, buff, BUFFER_SIZE);
		if (read_len < 0)
			return (free(buff), NULL);
		buff[read_len] = '\0';
		str_map = ft_strjoin(str_map, buff);
	}
	free(buff);
	close(file_fd);
	return (str_map);
}

int	ft_check_text_name(t_game *game)
{
	int	len;

	len = ft_strlen(game->north);
	if (len <= 4 || game->north[len - 1] != 'm' || game->north[len - 2] != 'p'
		|| game->north[len - 3] != 'x' || game->north[len - 4] != '.')
		return (1);
	len = ft_strlen(game->south);
	if (len <= 4 || game->south[len - 1] != 'm' || game->south[len - 2] != 'p'
		|| game->south[len - 3] != 'x' || game->south[len - 4] != '.')
		return (1);
	len = ft_strlen(game->west);
	if (len <= 4 || game->west[len - 1] != 'm' || game->west[len - 2] != 'p'
		|| game->west[len - 3] != 'x' || game->west[len - 4] != '.')
		return (1);
	len = ft_strlen(game->east);
	if (len <= 4 || game->east[len - 1] != 'm' || game->east[len - 2] != 'p'
		|| game->east[len - 3] != 'x' || game->east[len - 4] != '.')
		return (1);
	return (0);
}

int	ft_check_texture(char **map_file, t_game *game)
{
	int	i;

	i = 0;
	if (!map_file)
		return (1);
	if (ft_search_tab(map_file, "NO", &i) >= 0)
		game->north = ft_cpy(map_file[i]);
	if (ft_search_tab(map_file, "SO", &i) >= 0)
		game->south = ft_cpy(map_file[i]);
	if (ft_search_tab(map_file, "WE", &i) >= 0)
		game->west = ft_cpy(map_file[i]);
	if (ft_search_tab(map_file, "EA", &i) >= 0)
		game->east = ft_cpy(map_file[i]);
	if (ft_check_text_name(game))
	{
		write(1, "Errors texture path\n", 20);
		ft_free_data_game(game);
		return (1);
	}
	return (0);
}

int	ft_check_color(char **map_file, t_game *game)
{
	int	i;

	i = 0;
	if (!map_file)
		return (1);
	if (ft_search_tab(map_file, "F", &i) >= 0)
		game->color_f = ft_make_color(map_file[i]);
	if (ft_search_tab(map_file, "C", &i) >= 0)
		game->color_c = ft_make_color(map_file[i]);
	if (game->color_c < 0 || game->color_f < 0)
		return (1);
	return (0);
}

char	**ft_init_parsing(char *file, t_game *game)
{
	int		len;
	int		file_fd;
	char	*str_map;
	char	**map_file;

	len = ft_strlen(file);
	if (len < 4 || file[len - 1] != 'b' || file[len - 2] != 'u'
		|| file[len - 3] != 'c' || file[len - 4] != '.')
		return (write(1, "Error name file\n", 16), NULL);
	file_fd = open(file, O_RDONLY);
	if (file_fd < 0)
		return (write(1, "Error can't open file\n", 22), NULL);
	str_map = ft_init_map(file_fd);
	map_file = ft_split(str_map, '\n');
	free(str_map);
	if (ft_check_texture(map_file, game))
		return (ft_free_tab(map_file), NULL);
	if (ft_check_color(map_file, game))
		return (ft_free_tab(map_file), NULL);
	return (map_file);
}
