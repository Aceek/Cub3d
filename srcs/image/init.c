/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ilinhard <ilinhard@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/09 11:47:15 by pbeheyt           #+#    #+#             */
/*   Updated: 2023/01/31 02:49:33 by ilinhard         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub3d.h"

int	press(int keycode, t_image *image)
{
	image->key = 0;
	image->key = keycode;
	return (0);
}

int release(int keycode, t_image *image)
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

int	keyboard_input(int keycode, t_image *image)
{
	double	tmp;
	
	if (keycode == 65307)
		exit_clean(image);
	if (keycode == 'W' || keycode == 'w')
		move(image, image->player_pos.x + image->player_dir.x * 0.05, image->player_pos.y + image->player_dir.y * 0.05);
	if (keycode == 'S' || keycode == 's')
		move(image, image->player_pos.x - image->player_dir.x * 0.05, image->player_pos.y - image->player_dir.y * 0.05);
	if (keycode == 'A' || keycode == 'a')
		move(image, image->player_pos.x - image->plane.x * 0.05, image->player_pos.y - image->plane.y * 0.05);
	if (keycode == 'D' || keycode == 'd')
		move(image, image->player_pos.x + image->plane.x * 0.05, image->player_pos.y + image->plane.y * 0.05);
	if (keycode == 65361 || keycode == 'o')
	{
		image->player_dir.x = image->player_dir.x * cos(-0.02) - image->player_dir.y * sin(-0.02);
		image->player_dir.y = image->player_dir.x * sin(-0.02) + image->player_dir.y * cos(-0.02);
		tmp = image->plane.x;
		image->plane.x = image->plane.x * cos(-0.02) - image->plane.y * sin(-0.02);
		image->plane.y = tmp * sin(-0.02) + image->plane.y * cos(-0.02);
	}
	else if (keycode == 65363 || keycode == 'p')
	{
		image->player_dir.x = image->player_dir.x * cos(0.02) - image->player_dir.y * sin(0.02);
		image->player_dir.y = image->player_dir.x * sin(0.02) + image->player_dir.y * cos(0.02);
		tmp = image->plane.x;
		image->plane.x = image->plane.x * cos(0.02) - image->plane.y * sin(0.02);
		image->plane.y = tmp * sin(0.02) + image->plane.y * cos(0.02);
	}
	return (0);
}

t_texture	*file_to_image(t_image *image, char *path)
{
	t_texture	*txt;
	int			bpp;
	int			endian;
	int			size_line;
	
	bpp = 32;
	endian = 1;
	size_line = 0;
	if (!path)
		return (exit_clean(image), NULL);
	txt = malloc(sizeof(t_texture));
	if (!txt)
		return (exit_clean(image), NULL);
	ft_memset(txt, 0, sizeof(t_texture));
	txt->path = path;
	txt->content = mlx_xpm_file_to_image(image->mlx, txt->path,
				&txt->size.width, &txt->size.height);
	if (!txt->content)
			return (free(txt), exit_clean(image), NULL);
	txt->buff = (int *)mlx_get_data_addr(txt->content, &bpp, &size_line, &endian);
	return (txt);
}

void	init_image(t_image *image, t_game *game)
{
	ft_memset(image, 0, sizeof(t_image));
	image->mlx = mlx_init();
	if (!image->mlx)
		exit_clean(image);
	image->game = game;
	image->size.height = 720;
	image->size.width = 1480;
	image->north = file_to_image(image, game->north);
	image->south = file_to_image(image, game->south);
	image->west = file_to_image(image, game->west);
	image->east = file_to_image(image, game->east);
}

void    ft_init_diplay_struct(t_image *image, t_game *game)
{
    image->player_pos.x = image->game->player_x + 0.5;
    image->player_pos.y = image->game->player_y + 0.5;
    image->player_dir.x = 0;
    image->player_dir.y = -1;
    image->plane.x = 0.66;
    image->plane.y = 0;
	if (game->dir_player == 'E')
	{
		image->player_dir.x = 1;
  		image->player_dir.y = 0;
   		image->plane.x = 0;
   		image->plane.y = 0.66;
	}
	else if (game->dir_player == 'W')
	{
		image->player_dir.x = -1;
  		image->player_dir.y = 0;
   		image->plane.x = 0;
   		image->plane.y = -0.66;
	}
	else if (game->dir_player == 'S')
	{
		image->player_dir.x = 0;
  		image->player_dir.y = 1;
   		image->plane.x = -0.66;
   		image->plane.y = 0;
	}
}

int	init_mlx(t_image *image, t_game *game)
{
	init_image(image, game);
	ft_init_diplay_struct(image, game);
	image->win = mlx_new_window(image->mlx, image->size.width,
			image->size.height, "CUBE3D");
	mlx_hook(image->win, 2, 1L << 0, &press, image);
	mlx_hook(image->win, 3, 1L << 1, &release, image);
	mlx_hook(image->win, 17, 0, exit_clean, image);
	mlx_loop_hook(image->mlx, &display, image);
	mlx_loop(image->mlx);
	return (0);
}
