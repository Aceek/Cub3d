/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pbeheyt <pbeheyt@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/09 11:47:15 by pbeheyt           #+#    #+#             */
/*   Updated: 2023/01/25 02:58:41 by pbeheyt          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub3d.h"

int	init_mlx(t_image *image)
{
	ft_memset(image, 0, sizeof(t_image));
	image->height = 720;
	image->width = 1480;
	image->mlx = mlx_init();
	if (!image->mlx)
		return (0);
	image->win = mlx_new_window(image->mlx, image->width,
			image->height, "CUBE3D");
	// mlx_key_hook(image->win, keyboard_input, &data);
	// mlx_loop_hook(image->mlx, load_animated_walls, &data);
	mlx_hook(image->win, 17, 0, exit_clean, NULL);
	mlx_loop(image->mlx);
	printf("yo");
	return (0);
}
