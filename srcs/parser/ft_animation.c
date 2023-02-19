/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_animation.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ilinhard <ilinhard@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/20 00:29:24 by ilinhard          #+#    #+#             */
/*   Updated: 2023/02/20 00:38:09 by ilinhard         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub3d.h"

char	*ft_strjoin2(const char *s1, char *s2)
{
	char	*new;
	int		i;
	int		j;

	if (!s2)
		return (NULL);
	new = malloc(sizeof(char) * (2 + ft_strlen(s2) + 1));
	if (!new)
		return (NULL);
	i = -1;
	while (s1[++i])
		new[i] = s1[i];
	j = -1;
	while (s2[++j])
		new[i + j] = s2[j];
	new[i + j] = '\0';
	return (new);
}

void	ft_list_add_back(t_text_list **head, char *path, int pos, t_game *game)
{
	t_text_list	*tmp;

	tmp = (*head);
	if (!tmp)
	{
		tmp = malloc(sizeof(t_text_list));
		if (!tmp)
			return ;
		tmp->path = path;
		tmp->i = pos;
		tmp->next = NULL;
		game->head = tmp;
		return ;
	}
	while (tmp->next)
		tmp = tmp->next;
	tmp->next = malloc(sizeof(t_text_list));
	if (!tmp)
		return ;
	tmp->next->path = path;
	tmp->next->i = pos;
	tmp->next->next = NULL;
}

int	ft_animation(char **map_file, t_game *game)
{
	int		i;
	int		pos;
	char	*path;
	char	*tmp;
	char	*tmp2;

	game->head = NULL;
	game->animation = 0;
	i = 1;
	pos = 0;
	tmp2 = ft_itoa(i);
	tmp = ft_strjoin2("NO", tmp2);
	while (ft_search_tab(map_file, tmp, &pos) >= 0)
	{
		game->animation = 1;
		path = ft_cpy(map_file[pos]);
		ft_list_add_back(&game->head, path, i, game);
		i++;
		free(tmp2);
		free(tmp);
		tmp2 = ft_itoa(i);
		tmp = ft_strjoin2("NO", tmp2);
	}
	return (free(tmp), free(tmp2), i);
}
