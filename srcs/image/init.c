/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pbeheyt <pbeheyt@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/09 11:47:15 by pbeheyt           #+#    #+#             */
/*   Updated: 2023/01/25 03:38:10 by pbeheyt          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub3d.h"

int	keyboard_input(int keycode, t_image *image)
{
	if (keycode == 65307)
		exit_clean(image);
	// if (keycode == 'W' || keycode == 'w')
	// if (keycode == 'S' || keycode == 's')
	// if (keycode == 'A' || keycode == 'a')
	// if (keycode == 'D' || keycode == 'd')
	return (0);
}

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
	mlx_key_hook(image->win, keyboard_input, &image);
	mlx_hook(image->win, 17, 0, exit_clean, &image);
	mlx_loop(image->mlx);
	return (0);
}
