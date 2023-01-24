/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_parsing.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ilinhard <ilinhard@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/24 00:33:26 by ilinhard          #+#    #+#             */
/*   Updated: 2023/01/24 02:14:15 by ilinhard         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

char	*ft_strjoin(char *s1, char *s2)
{
	char	*new;
	int		i;
	int		j;

	if (!s1)
	{
		s1 = malloc(sizeof(char) * 1);
		s1[0] = '\0';
	}
	if (!s1 || !s2)
		return (NULL);
	new = malloc(sizeof(char) * (ft_strlen(s1) + ft_strlen(s2) + 1));
	if (!new)
		return (NULL);
	i = -1;
	while (s1[++i])
		new[i] = s1[i];
	j = -1;
	while (s2[++j])
		new[i + j] = s2[j];
	new[i + j] = '\0';
	free(s1);
	return (new);
}

char	*ft_init_map(int file_fd)
{
	char	*str_map;
	char	*buff;
	int		read_len;

	str_map = NULL;
	buff = malloc(sizeof(char) * (BUFFER_SIZE + 1));
	if (!buff)
		return (write(1, "Error init map\n", 15), NULL);
	read_len = 1;
	while (read_len)
	{
		read_len = read(file_fd, buff, BUFFER_SIZE);
		if (read_len < 0)
			return (free(buff), NULL); // add error code etc
		buff[read_len] = '\0';
		str_map = ft_strjoin(str_map, buff);
	}
	free(buff);
	close(file_fd);
	return (str_map);
	
}

// int	ft_check_texture(char **map_file)
// {
// 	if (!map_file)
// 		return (NULL);
	
// }

char	**ft_init_parsing(char *file)
{
	int		len;
	int		file_fd;
	char	*str_map;
	char	**map_file;

	len = ft_strlen(file);
	if (len < 4 || file[len - 1] != 'b' || file[len - 2] != 'u' || file[len - 3] != 'c' || file[len - 4] != '.')
		return (write(1, "Error name file\n", 16), NULL);
	file_fd = open(file, O_RDONLY);
	if (file_fd < 0)
		return (write(1, "Error can't open file\n", 22), NULL);
	str_map = ft_init_map(file_fd);
	map_file = ft_split(str_map, '\n');	
	free(str_map);
	// if (ft_check_texture(map_file))
	// 	return (NULL);
	//parsing > CHECK image N / S / E / W valide 
	// parsing > Map 
	ft_free_tab(map_file);
	return (NULL);
}