/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   libft.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ilinhard <ilinhard@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/25 03:14:58 by ilinhard          #+#    #+#             */
/*   Updated: 2023/01/31 03:56:40 by ilinhard         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub3d.h"

char	*ft_strdup(const char *s)
{
	int			i;
	char		*cpy;

	if (s == NULL)
		return (NULL);
	i = ft_strlen((char *)s);
	cpy = malloc(sizeof(char) * (i + 1));
	if (cpy == NULL)
		return (NULL);
	i = 0;
	while (s[i])
	{
		cpy[i] = s[i];
		i++;
	}
	cpy[i] = '\0';
	return (cpy);
}
