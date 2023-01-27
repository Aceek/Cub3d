/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   clear.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pbeheyt <pbeheyt@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/09 11:47:15 by pbeheyt           #+#    #+#             */
/*   Updated: 2023/01/27 05:46:24 by pbeheyt          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub3d.h"

void	free_txt(t_image *image, t_texture *txt)
{
	if (!txt)
		return ;
	if (txt && txt->content)
		mlx_destroy_image(image->mlx, txt->content);
	free(txt);
}

int	exit_clean(t_image *image)
{
	free_txt(image, image->north);
	free_txt(image, image->south);
	free_txt(image, image->west);
	free_txt(image, image->east);
	mlx_destroy_window(image->mlx, image->win);
	mlx_destroy_display(image->mlx);
	free(image->mlx);
	ft_free_tab(image->game->map);
	ft_free_data_game(image->game);
	exit(0);
	return (0);
}
