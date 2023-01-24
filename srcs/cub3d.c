/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ilinhard <ilinhard@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/23 23:16:50 by ilinhard          #+#    #+#             */
/*   Updated: 2023/01/24 03:57:29 by ilinhard         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	ft_init_struct(t_game *game)
{
	game->east = NULL;
	game->north = NULL;
	game->south = NULL;
	game->west = NULL;
}

int	main(int ac, char **av)
{
	t_game	*game;

	if (ac < 2 || !av || !av[1])
		return (write(1, "Error nb args\n", 14), 1);
	game = malloc(sizeof(t_game)); // calloc plutot ?
	if (!game)
		return (0);
	ft_init_struct(game);
	ft_init_parsing(av[1], game);

	return (0);
}