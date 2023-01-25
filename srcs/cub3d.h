/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ilinhard <ilinhard@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/23 23:17:42 by ilinhard          #+#    #+#             */
/*   Updated: 2023/01/25 05:51:33 by ilinhard         ###   ########.fr       */
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
# include "../mlx_linux/mlx.h"

# define BUFFER_SIZE 50

typedef struct s_game
{
	char	*north;
	char	*south;
	char	*east;
	char	*west;
	int		color_f;
	int		color_c;
	int		player_x;
	int		player_y;
	char	**map;
}			t_game;

typedef struct s_image
{
	void	*mlx;
	void	*win;
	int		height;
	int		width;
	char	*north;
	char	*south;
	char	*east;
	char	*west;
	int		color_f;
	int		color_c;
	t_game	*game;
}			t_image;

/*image/clear*/
int		exit_clean(t_image *image);

/*image/init*/
int		keyboard_input(int keycode, t_image *image);
int		init_mlx(t_image *image, t_game *game);

/*libft*/
char	**ft_split(char const *s, char c);
void	*ft_memset(void *s, int c, size_t n);

/*parsing*/
char	**ft_init_parsing(char *file, t_game *game);
int		ft_strlen(char *str);
void	ft_free_tab(char **tab);
int		ft_search_tab(char **tab, char *to_find, int *pos);
char	*ft_cpy(char *str);
void	ft_free_data_game(t_game *game);
int		ft_make_color(char *str);
int		ft_atoi(char *str, int *pos);
int		ft_encode_rgb(int red, int green, int blue);
char	*ft_strjoin(char *s1, char *s2);
int		ft_find(char *str, char *to_find);
char	**ft_create_map(char **map, t_game *game);
char	*ft_strdup(const char *s);

#endif