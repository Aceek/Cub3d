/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   display_utils.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pbeheyt <pbeheyt@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/31 02:32:33 by ilinhard          #+#    #+#             */
/*   Updated: 2023/02/25 00:22:26 by pbeheyt          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub3d.h"

void	animated_wall(t_image *image)
{
	t_text_list	*tmp;

	if (image->txt_nb >= 1)
	{
		image->count += 1;
		if (image->count == TIMER)
		{
			image->count = 0;
			tmp = image->head;
			while (tmp && tmp->i != image->txt_i)
				tmp = tmp->next;
			image->north = tmp->north;
			if (image->txt_i < image->txt_nb - 1)
				image->txt_i += 1;
			else
				image->txt_i = 0;
		}
	}
}

int	get_pxl_color(t_image *image, t_texture *txt, int y)
{
	double	wallx;
	int		tex_x;
	int		tex_y;
	int		color;

	if (!image->side)
		wallx = image->player_pos.y + (image->wall_dist * image->raydir.y);
	else
		wallx = image->player_pos.x + (image->wall_dist * image->raydir.x);
	wallx -= floor(wallx);
	tex_x = (int)(wallx * (double)txt->size.width);
	if (!image->side && image->raydir.x > 0)
		tex_x = txt->size.width - tex_x - 1;
	if (image->side == 1 && image->raydir.y < 0)
		tex_x = txt->size.width - tex_x - 1;
	tex_y = (((y * 2 - image->size.height + image->line_height)
				* txt->size.height) / image->line_height) / 2;
	if (tex_y < 0)
		tex_y = 0;
	color = txt->buff[(int)(tex_y * txt->size.width + tex_x)];
	return (color);
}

void	ft_floor_and_celling(t_image *image)
{
	int	i;

	i = -1;
	while (++i < ((image->size.width * image->size.height) / 2))
		image->global_image->buff[i] = image->game->color_c;
	while (++i < (image->size.width * image->size.height))
		image->global_image->buff[i] = image->game->color_f;
}

t_texture	*ft_init_display(t_image *image)
{
	int			bpp;
	int			endian;
	int			size_line;
	t_texture	*global_img;

	bpp = 32;
	endian = 1;
	size_line = 0;
	global_img = malloc(sizeof(t_texture));
	if (!global_img)
		return (error_handler(image, ERR_MALLOC), NULL);
	global_img->content = mlx_new_image(image->mlx, image->size.width,
			image->size.height);
	if (!global_img->content)
		return (error_handler(image, ERR_MLX), NULL);
	global_img->buff = (int *)mlx_get_data_addr(global_img->content,
			&bpp, &size_line, &endian);
	return (global_img);
}

void	ft_calculate_side_dist(t_image *image)
{
	if (image->raydir.x < 0)
	{
		image->step.x = -1;
		image->side_dist.x = \
			(image->player_pos.x - image->map.x) * image->delta_dist.x;
	}
	else
	{
		image->step.x = 1;
		image->side_dist.x = \
			(image->map.x + 1.0 - image->player_pos.x) * image->delta_dist.x;
	}
	if (image->raydir.y < 0)
	{
		image->step.y = -1;
		image->side_dist.y = \
			(image->player_pos.y - image->map.y) * image->delta_dist.y;
	}
	else
	{
		image->step.y = 1;
		image->side_dist.y = \
			(image->map.y + 1.0 - image->player_pos.y) * image->delta_dist.y;
	}
}
