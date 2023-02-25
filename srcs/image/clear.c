/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   clear.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ilinhard <ilinhard@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/09 11:47:15 by pbeheyt           #+#    #+#             */
/*   Updated: 2023/02/25 04:02:03 by ilinhard         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub3d.h"

char	*error_message(int error)
{
	char	*tab[14];

	tab[ERR_MALLOC] = "Error\nMemory alloction\n";
	tab[ERR_ARGS_NB] = "Error\nInvalid number of arguments\n";
	tab[ERR_MLX] = "Error\nMlx failed to init or create content\n";
	tab[ERR_FILE_PATH] = "Error\nInvalid texture path name\n";
	tab[ERR_FILE_COLOR] = "Error\nInvalid color format\n";
	tab[ERR_FILE_EMPTY] = "Error\nFile is empty\n";
	tab[ERR_FILE_SPACE] = "Error\nUnexpected space in file\n";
	tab[ERR_FILE_TXT_NAME] = "Error\nInvalid texture file name\n";
	tab[ERR_FILE_NAME] = "Error\nInvald file name\n";
	tab[ERR_FILE_FORMAT] = "Error\nInvald file format\n";
	tab[ERR_FILE_OPEN] = "Error\nCan't open file\n";
	tab[ERR_MAP_CARAC] = "Error\nInvalid character on map\n";
	tab[ERR_MAP_FORMAT] = "Error\nInvalid map format\n";
	tab[ERR_MAP_EXIT] = "Error\nMap have exit\n";
	return (tab[error]);
}

int	error_handler(t_image *image, int error)
{
	if (error >= 0)
		ft_putstr_fd(error_message(error), 2);
	if (image)
	{
		image->error = error;
		exit_clean(image);
	}
	return (error);
}

void	free_txt(t_image *image, t_texture *txt)
{
	if (!txt)
		return ;
	if (txt && txt->content)
		mlx_destroy_image(image->mlx, txt->content);
	free(txt);
}

void	ft_clear_list(t_image *image)
{
	t_text_list	*tmp;
	t_text_list	*next;

	tmp = image->head;
	next = NULL;
	while (tmp)
	{
		next = tmp->next;
		if (tmp->north && tmp->north->content)
			mlx_destroy_image(image->mlx, tmp->north->content);
		free(tmp->path);
		free(tmp->north);
		free(tmp);
		tmp = next;
	}
}

int	exit_clean(t_image *image)
{
	free_txt(image, image->south);
	free_txt(image, image->west);
	free_txt(image, image->east);
	ft_clear_list(image);
	free(image->global_image);
	if (image->win)
		mlx_destroy_window(image->mlx, image->win);
	if (image->mlx)
	{
		mlx_destroy_display(image->mlx);
		free(image->mlx);
	}
	ft_free_tab(image->game->map);
	ft_free_data_game(image->game);
	exit(image->error);
}
