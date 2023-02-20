/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   clear.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ilinhard <ilinhard@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/09 11:47:15 by pbeheyt           #+#    #+#             */
/*   Updated: 2023/02/20 03:19:52 by ilinhard         ###   ########.fr       */
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
	exit(1);
}
