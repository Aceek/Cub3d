/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   display.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ilinhard <ilinhard@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/09 11:47:15 by pbeheyt           #+#    #+#             */
/*   Updated: 2023/01/31 04:03:49 by ilinhard         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub3d.h"

void	ft_init_ray(t_image *image, int x)
{
	image->hit = 0;
	image->camera_x = (2 * x / (double)image->size.width) - 1;
	image->raydir.x = image->player_dir.x + (image->plane.x * image->camera_x);
	image->raydir.y = image->player_dir.y + (image->plane.y * image->camera_x);
	image->delta_dist.x = fabs(1 / image->raydir.x);
	image->delta_dist.y = fabs(1 / image->raydir.y);
}

void	ft_dda(t_image *image)
{
	while (!image->hit)
	{
		if (image->side_dist.x < image->side_dist.y)
		{
			image->side_dist.x += image->delta_dist.x;
			image->map.x += image->step.x;
			image->side = 0;
		}
		else
		{
			image->side_dist.y += image->delta_dist.y;
			image->map.y += image->step.y;
			image->side = 1;
		}
		if (image->map.x < 0)
			image->map.x = 0;
		if (image->map.y < 0)
			image->map.y = 0;
		if (image->game->map[(int)image->map.y][(int)image->map.x] == '1')
			image->hit = 1;
	}
}

void	ft_wall_dist_calculate(t_image *image)
{
	if (!image->side)
		image->wall_dist = (image->side_dist.x - image->delta_dist.x);
	else
		image->wall_dist = (image->side_dist.y - image->delta_dist.y);
	image->line_height = (image->size.height / image->wall_dist);
	image->draw_start = -(image->line_height / 2) + (image->size.height / 2);
	if (image->draw_start < 0)
		image->draw_start = 0;
	image->draw_end = (image->line_height / 2) + (image->size.height / 2);
	if (image->draw_end >= image->size.height)
		image->draw_end = image->size.height - 1;
}

void	ft_fill_img_buffer(int x, t_image *image)
{
	int			start;
	int			end;
	int			color_txt;
	t_texture	*wall;

	start = image->draw_start;
	end = image->draw_end;
	if (image->raydir.x > 0 && !image->side)
		wall = image->east;
	else if (image->raydir.x < 0 && !image->side)
		wall = image->west;
	else if (image->raydir.y < 0 && !image->side)
		wall = image->north;
	else
		wall = image->south;
	while (start < end)
	{
		color_txt = get_pxl_color(image, wall, start);
		image->global_image->buff[(image->size.width * start) + x] = color_txt;
		start += 1;
	}
}

int	display(void *param)
{
	t_image	*image;
	int		x;

	image = (t_image *)param;
	image->global_image = ft_init_display(image);
	ft_floor_and_celling(image);
	x = -1;
	while (++x < image->size.width)
	{
		image->map.x = image->player_pos.x;
		image->map.y = image->player_pos.y;
		ft_init_ray(image, x);
		ft_calculate_side_dist(image);
		ft_dda(image);
		ft_wall_dist_calculate(image);
		ft_fill_img_buffer(x, image);
	}
	mlx_put_image_to_window(image->mlx, image->win,
		image->global_image->content, 0, 0);
	mlx_destroy_image(image->mlx, image->global_image->content);
	free(image->global_image);
	if (image->key != 0)
		keyboard_input(image->key, image);
	return (0);
}
