/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ilinhard <ilinhard@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/23 23:16:50 by ilinhard          #+#    #+#             */
/*   Updated: 2023/01/31 03:49:51 by ilinhard         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */


#include "cub3d.h"

void	ft_init_struct(t_game *game)
{
	game->east = NULL;
	game->north = NULL;
	game->south = NULL;
	game->west = NULL;
	game->color_c = 0;
	game->color_f = 0;
	game->player_x = 0;
	game->player_y = 0;
}

int	main(int ac, char **av)
{
	t_game	*game;
	t_image	image;
	char	**map;

	if (ac < 2 || !av || !av[1])
		return (write(1, "Error nb args\n", 14), 1);
	game = malloc(sizeof(t_game));
	if (!game)
		return (0);
	ft_init_struct(game);
	map = ft_init_parsing(av[1], game);
	if (!map)
		return (ft_free_data_game(game), 1);
	game->map = map;
	image.game = game;
	
	init_mlx(&image, game);
	ft_free_tab(map);
	ft_free_data_game(game);
	return (0);
}
