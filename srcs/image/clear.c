/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   clear.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pbeheyt <pbeheyt@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/09 11:47:15 by pbeheyt           #+#    #+#             */
/*   Updated: 2023/02/25 00:58:14 by pbeheyt          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub3d.h"

int	error_handler(t_image *image, int error)
{
	if (error)
	{
		if (error == ERR_MALLOC)
			ft_putstr_fd("Error\nMemory alloction error\n", 2);
		else if (error == ERR_NB_ARGS)
			ft_putstr_fd("Error\nInvalid number of arguments\n", 2);
		else if (error == ERR_MLX)
			ft_putstr_fd("Error\nMlx failed to init or create content\n", 2);
		else if (error == ERR_PATH)
			ft_putstr_fd("Error\nInvalid texture path name\n", 2);
	}
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
