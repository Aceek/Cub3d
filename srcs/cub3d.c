/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ilinhard <ilinhard@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/23 23:16:50 by ilinhard          #+#    #+#             */
/*   Updated: 2023/02/25 04:00:10 by ilinhard         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

int	main(int ac, char **av)
{
	t_game	*game;
	t_image	image;
	char	**map;

	if (ac != 2 || !av || !av[1])
		return (error_handler(NULL, ERR_ARGS_NB));
	game = malloc(sizeof(t_game));
	if (!game)
		return (error_handler(NULL, ERR_MALLOC));
	ft_memset(game, 0, sizeof(t_game));
	map = ft_init_parsing(av[1], game);
	if (!map)
		return (ft_free_data_game(game), 1);
	game->init = 1;
	game->map = map;
	image.game = game;
	init_mlx(&image, game);
	ft_free_tab(map);
	ft_free_data_game(game);
	return (0);
}
