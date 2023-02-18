/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ilinhard <ilinhard@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/23 23:17:42 by ilinhard          #+#    #+#             */
/*   Updated: 2023/02/18 22:04:44 by ilinhard         ###   ########.fr       */
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
# include "math.h"

# define BUFFER_SIZE 50

# define MINI_MAP 18
# define TILE_SIZE 10

typedef struct s_size
{
	int		height;
	int		width;
}			t_size;

typedef struct s_texture
{
	t_size	size;
	char	*path;
	void	*content;
	void	*txt;
	int		*buff;
}			t_texture;

typedef struct s_game
{
	char	dir_player;
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

typedef struct s_pos
{
	double	x;
	double	y;
}			t_pos;

typedef struct s_posi
{
	int	x;
	int	y;
}			t_posi;

typedef struct s_image
{
	t_pos		player_pos;
	t_pos		player_dir;
	t_pos		plane;	
	t_pos		raydir;
	t_posi		map;
	t_pos		side_dist;
	t_pos		delta_dist;
	t_posi		step;
	int			key;
	int			draw_start;
	int			line_height;
	int			draw_end;
	int			hit;
	int			side;
	double		wall_dist;
	double		camera_x;
	void		*mlx;
	void		*win;
	t_texture	*north;
	t_texture	*south;
	t_texture	*east;
	t_texture	*west;
	t_texture	*global_image;
	int			color_f;
	int			color_c;
	t_size		size;
	t_game		*game;
}				t_image;

/*display*/
void		ft_init_ray(t_image *image, int x);
void		ft_dda(t_image *image);
void		ft_fill_img_buffer(int x, t_image *image);
void		ft_wall_dist_calculate(t_image *image);
int			display(void *param);
/*display_utils*/
void		ft_calculate_side_dist(t_image *image);
void		ft_floor_and_celling(t_image *image);
int			get_pxl_color(t_image *image, t_texture *txt, int start);
t_texture	*ft_init_display(t_image *image);

/*movement.c*/
int			press(int keycode, t_image *image);
int			release(int keycode, t_image *image);
void		move(t_image *image, double next_x, double next_y);
int			keyboard_input(int keycode, t_image *image);

/*image/clear*/
void		free_txt(t_image *image, t_texture *txt);
int			exit_clean(t_image *image);

/*image/init*/
int			keyboard_input(int keycode, t_image *image);
t_texture	*file_to_image(t_image *image, char *path);
void		init_txt(t_image *image, t_game *game);
int			init_mlx(t_image *image, t_game *game);

/*libft*/
char		**ft_split(char const *s, char c);
void		*ft_memset(void *s, int c, size_t n);

/*parsing*/
char		**ft_init_parsing(char *file, t_game *game);
int			ft_strlen(char *str);
void		ft_free_tab(char **tab);
int			ft_search_tab(char **tab, char *to_find, int *pos);
char		*ft_cpy(char *str);
void		ft_free_data_game(t_game *game);
int			ft_make_color(char *str);
int			ft_atoi(char *str, int *pos);
int			ft_encode_rgb(int red, int green, int blue);
char		*ft_strjoin(char *s1, char *s2);
int			ft_find(char *str, char *to_find);
char		**ft_create_map(char **map, t_game *game);
char		*ft_strdup(const char *s);

#endif