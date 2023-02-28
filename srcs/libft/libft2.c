/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   libft2.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ilinhard <ilinhard@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/09 11:47:15 by pbeheyt           #+#    #+#             */
/*   Updated: 2023/02/28 04:13:59 by ilinhard         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub3d.h"

void	*ft_memset(void *s, int c, size_t n)
{
	size_t			i;
	unsigned char	*ptr;

	ptr = (unsigned char *)s;
	i = 0;
	while (i < n)
		ptr[i++] = c;
	return (s);
}

void	ft_free_tab(char **tab)
{
	int	i;

	i = -1;
	while (tab && tab[++i])
	{
		if (tab[i])
			free(tab[i]);
	}
	free(tab);
}

char	*ft_cpy(char *str)
{
	int		i;
	int		j;
	int		len;
	char	*new;

	i = 0;
	while (str[i] && str[i] != '.')
		i++;
	len = ft_strlen(str) - i;
	if (!str[i] || str[i] != '.' || len <= 0)
		return (NULL);
	new = malloc(sizeof(char) * (len + 1));
	if (!new)
		return (NULL);
	j = 0;
	while (str[i + j])
	{
		new[j] = str[i + j];
		j++;
	}
	new[j] = '\0';
	return (new);
}

void	ft_free_data_game(t_game *game)
{
	t_text_list	*tmp;
	t_text_list	*next;

	tmp = game->head;
	if (game && game->north)
		free(game->north);
	if (game && game->east)
		free(game->east);
	if (game && game->west)
		free(game->west);
	if (game && game->south)
		free(game->south);
	if (game->init)
	{
		free(game);
		return ;
	}
	while (tmp)
	{
		next = tmp->next;
		free(tmp->path);
		free(tmp);
		tmp = next;
	}
	free(game);
}
