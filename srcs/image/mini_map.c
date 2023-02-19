/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   MMAP.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ilinhard <ilinhard@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/19 00:45:34 by ilinhard          #+#    #+#             */
/*   Updated: 2023/02/19 01:26:52 by ilinhard         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub3d.h"

void	print_mini_map(t_image *image)
{
	t_posi	len;
	t_posi	pos;
	t_posi	draw;

	ft_memset(&len, 0, sizeof(t_posi));
	print_map_back(image);
	print_tile(TILE * (MMAP / 2), TILE * (MMAP / 2), image, RED);
	draw_map(image, len, pos, draw);
}

void	print_tile(int x, int y, t_image *image, int color)
{
	int	x_max;
	int	y_max;
	int	y_init;

	x_max = x + TILE;
	y_max = y + TILE;
	y_init = y;
	while (x < x_max)
	{
		y = y_init;
		while (y < y_max)
		{
			image->global_image->buff[x + y * image->size.width] = color;
			y++;
		}
		x++;
	}
}

void	print_map_back(t_image *image)
{
	int	x;
	int	y;

	x = -1;
	while (++x < MMAP * TILE)
	{
		y = -1;
		while (++y < MMAP * TILE)
			image->global_image->buff[y + x * image->size.width] = DARK_GRAY;
	}
}

void	draw_map(t_image *image, t_posi len, t_posi pos, t_posi draw)
{
	while (image->game->map[len.y])
		len.y++;
	pos.y = (int)image->player_pos.y - ((MMAP / 2) - 1) - 1;
	draw.y = 1;
	while (++pos.y < len.y && pos.y
		< (int)image->player_pos.y + ((MMAP / 2) - 1))
	{
		pos.x = (int)image->player_pos.x - ((MMAP / 2) - 1) - 1;
		draw.x = 1;
		while (++pos.x < (int)image->player_pos.x + ((MMAP / 2) - 1))
		{
			if (pos.y >= 0)
				len.x = ft_strlen(image->game->map[pos.y]);
			if (pos.x < len.x && pos.x >= 0 && pos.y > 0 && pos.y < len.y
				&& image->game->map[pos.y][pos.x] == '1')
				print_tile(draw.x * TILE, draw.y * TILE, image, BLACK);
			draw.x++;
		}
		draw.y++;
	}
}
