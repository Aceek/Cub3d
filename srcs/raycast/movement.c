/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   movement.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ilinhard <ilinhard@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/31 03:32:07 by ilinhard          #+#    #+#             */
/*   Updated: 2023/01/31 04:27:31 by ilinhard         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub3d.h"

int	press(int keycode, t_image *image)
{
	image->key = 0;
	image->key = keycode;
	return (0);
}

int	release(int keycode, t_image *image)
{
	(void)keycode;
	image->key = 0;
	return (0);
}

void	move(t_image *image, double next_x, double next_y)
{
	if (image->game->map[(int)next_y][(int)next_x] == 'X')
	{
		image->player_pos.x = next_x;
		image->player_pos.y = next_y;
	}
}

void	ft_camera_movement(int keycode, t_image *image)
{
	double	tmp;

	if (keycode == 65361 || keycode == 'o')
	{
		image->player_dir.x = \
			image->player_dir.x * cos(-0.02) - image->player_dir.y * sin(-0.02);
		image->player_dir.y = \
			image->player_dir.x * sin(-0.02) + image->player_dir.y * cos(-0.02);
		tmp = image->plane.x;
		image->plane.x = \
			image->plane.x * cos(-0.02) - image->plane.y * sin(-0.02);
		image->plane.y = \
			tmp * sin(-0.02) + image->plane.y * cos(-0.02);
	}
	else if (keycode == 65363 || keycode == 'p')
	{
		image->player_dir.x = \
			image->player_dir.x * cos(0.02) - image->player_dir.y * sin(0.02);
		image->player_dir.y = \
			image->player_dir.x * sin(0.02) + image->player_dir.y * cos(0.02);
		tmp = image->plane.x;
		image->plane.x = \
			image->plane.x * cos(0.02) - image->plane.y * sin(0.02);
		image->plane.y = tmp * sin(0.02) + image->plane.y * cos(0.02);
	}
}

int	keyboard_input(int keycode, t_image *image)
{
	if (keycode == 65307)
		exit_clean(image);
	if (keycode == 'W' || keycode == 'w')
		move(image, image->player_pos.x + image->player_dir.x * 0.05,
			image->player_pos.y + image->player_dir.y * 0.05);
	if (keycode == 'S' || keycode == 's')
		move(image, image->player_pos.x - image->player_dir.x * 0.05,
			image->player_pos.y - image->player_dir.y * 0.05);
	if (keycode == 'A' || keycode == 'a')
		move(image, image->player_pos.x - image->plane.x * 0.05,
			image->player_pos.y - image->plane.y * 0.05);
	if (keycode == 'D' || keycode == 'd')
		move(image, image->player_pos.x + image->plane.x * 0.05,
			image->player_pos.y + image->plane.y * 0.05);
	ft_camera_movement(keycode, image);
	return (0);
}
