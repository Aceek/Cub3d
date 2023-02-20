/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   movement2.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ilinhard <ilinhard@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/20 02:16:14 by ilinhard          #+#    #+#             */
/*   Updated: 2023/02/20 02:18:18 by ilinhard         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub3d.h"

void	mouse_motion(t_image *image)
{
	int	compare;

	mlx_mouse_get_pos(image->mlx, image->win, &compare, &image->mouse.y);
	if (compare > image->mouse.x || compare >= image->size.width)
		ft_camera_movement('p', image);
	else if (compare < image->mouse.x || compare <= 0)
		ft_camera_movement('o', image);
	image->mouse.x = compare;
}

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
