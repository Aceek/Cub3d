/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ilinhard <ilinhard@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/09 11:47:15 by pbeheyt           #+#    #+#             */
/*   Updated: 2023/02/20 02:40:31 by ilinhard         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub3d.h"

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
	{
		write(2, "Errors loading texture\n", 23);
		return (free(txt), exit_clean(image), NULL);
	}
	txt->buff = \
		(int *)mlx_get_data_addr(txt->content, &bpp, &size_line, &endian);
	return (txt);
}

void	ft_init_default_player(t_image *image)
{
	image->player_pos.x = image->game->player_x + 0.5;
	image->player_pos.y = image->game->player_y + 0.5;
	image->player_dir.x = 0;
	image->player_dir.y = -1;
	image->plane.x = FOV;
	image->plane.y = 0;
}

void	init_image(t_image *image, t_game *game)
{
	t_text_list	*tmp;

	ft_memset(image, 0, sizeof(t_image));
	image->mlx = mlx_init();
	if (!image->mlx)
		exit_clean(image);
	image->game = game;
	image->size.height = SCRHGHT;
	image->size.width = SCRWDTH;
	image->head = game->head;
	tmp = image->head;
	while (tmp)
	{
		tmp->north = file_to_image(image, tmp->path);
		image->txt_nb += 1;
		tmp = tmp->next;
	}
	image->north = image->head->north;
	image->south = file_to_image(image, game->south);
	image->west = file_to_image(image, game->west);
	image->east = file_to_image(image, game->east);
}

void	ft_init_diplay_struct(t_image *image, t_game *game)
{
	ft_init_default_player(image);
	if (game->dir_player == 'E')
	{
		image->player_dir.x = 1;
		image->player_dir.y = 0;
		image->plane.x = 0;
		image->plane.y = FOV;
	}
	else if (game->dir_player == 'W')
	{
		image->player_dir.x = -1;
		image->player_dir.y = 0;
		image->plane.x = 0;
		image->plane.y = -FOV;
	}
	else if (game->dir_player == 'S')
	{
		image->player_dir.x = 0;
		image->player_dir.y = 1;
		image->plane.x = -FOV;
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
	mlx_mouse_get_pos(image->mlx, image->win, &image->mouse.x, &image->mouse.y);
	mlx_loop_hook(image->mlx, &display, image);
	mlx_loop(image->mlx);
	return (0);
}
