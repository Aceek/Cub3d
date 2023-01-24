/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ilinhard <ilinhard@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/23 23:17:42 by ilinhard          #+#    #+#             */
/*   Updated: 2023/01/24 05:51:44 by ilinhard         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CUB3D_H
# define CUB3D_H

# include <stdio.h>
# include <stdlib.h>
# include <unistd.h>
# include <sys/types.h>
# include <sys/stat.h>
# include <fcntl.h>

# define BUFFER_SIZE 50

typedef struct s_game
{
	char	*north;
	char	*south;
	char	*east;
	char	*west;
	int		color_f;
	int		color_c;
}			t_game;

char	**ft_init_parsing(char *file, t_game *game);
int		ft_strlen(char *str);
char	**ft_split(char const *s, char c);
void	ft_free_tab(char **tab);
int		ft_search_tab(char **tab, char *to_find, int *pos);
char	*ft_cpy(char *str);
void	ft_free_data_game(t_game *game);
int		ft_make_color(char *str);
int		ft_atoi(char *str, int *pos);
int		ft_encode_rgb(int red, int green, int blue);
char	*ft_strjoin(char *s1, char *s2);

#endif