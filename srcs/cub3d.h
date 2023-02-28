/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ilinhard <ilinhard@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/23 23:17:42 by ilinhard          #+#    #+#             */
/*   Updated: 2023/02/28 04:13:50 by ilinhard         ###   ########.fr       */
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

# define MMAP 25
# define TILE 7
# define BLACK 0x000000
# define RED 0xFF0000
# define DARK_GRAY 0x555555
# define SPEED 0.09
# define ROTATION 0.03
# define FOV 0.66
# define TIMER 5
# define SCRHGHT 720
# define SCRWDTH 1480

enum e_error
{
	ERR_MALLOC,
	ERR_ARGS_NB,
	ERR_MLX,
	ERR_FILE_PATH,
	ERR_FILE_COLOR,
	ERR_FILE_EMPTY,
	ERR_FILE_SPACE,
	ERR_FILE_TXT_NAME,
	ERR_FILE_NAME,
	ERR_FILE_FORMAT,
	ERR_FILE_OPEN,
	ERR_MAP_CARAC,
	ERR_MAP_FORMAT,
	ERR_MAP_EXIT,
	ERR_MAP_EMPTY,
	ERR_MAP_NEWLINE,
	ERR_MAP_START,
};

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

typedef struct s_text_list
{
	t_texture				*north;
	char					*path;
	int						i;
	struct s_text_list		*next;
}							t_text_list;

typedef struct s_game
{
	char		dir_player;
	char		*north;
	char		*south;
	char		*east;
	char		*west;
	int			animation;
	int			color_f;
	int			color_c;
	int			player_x;
	int			player_y;
	int			init;
	char		**map;
	t_text_list	*head;

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
	t_posi		mouse;
	int			error;
	int			key;
	int			draw_start;
	int			line_height;
	int			draw_end;
	int			hit;
	int			side;
	int			count;
	int			txt_nb;
	int			txt_i;
	double		wall_dist;
	double		camera_x;
	void		*mlx;
	void		*win;
	t_texture	*north;
	t_texture	*south;
	t_texture	*east;
	t_texture	*west;
	t_texture	*global_image;
	t_text_list	*head;
	int			color_f;
	int			color_c;
	t_size		size;
	t_game		*game;
}				t_image;

/*display*/
void		ft_init_ray(t_image *image, int x);
void		ft_dda(t_image *image);
void		ft_fill_img_buffer(int x, t_image *image);
int			display(void *param);
void		ft_wall_dist_calculate(t_image *image);

/*display_utils*/
void		ft_calculate_side_dist(t_image *image);
void		ft_floor_and_celling(t_image *image);
int			get_pxl_color(t_image *image, t_texture *txt, int start);
void		animated_wall(t_image *image);
t_texture	*ft_init_display(t_image *image);

/*movement.c*/
void		move(t_image *image, double next_x, double next_y);
int			keyboard_input(int keycode, t_image *image);
void		ft_camera_movement(int keycode, t_image *image);

/*movement2.c*/
int			press(int keycode, t_image *image);
int			release(int keycode, t_image *image);
void		mouse_motion(t_image *image);

/*image/clear*/
int			error_handler(t_image *image, int error);
void		free_txt(t_image *image, t_texture *txt);
int			exit_clean(t_image *image);

/*image/init*/
int			keyboard_input(int keycode, t_image *image);
t_texture	*file_to_image(t_image *image, char *path);
void		init_txt(t_image *image, t_game *game);
int			init_mlx(t_image *image, t_game *game);

/*image/mini_map*/
void		print_tile(int x, int y, t_image *image, int color);
void		print_map_back(t_image *image);
void		print_mini_map(t_image *image);
void		draw_map(t_image *image, t_posi len, t_posi pos, t_posi draw);

/*libft*/
void		*ft_memset(void *s, int c, size_t n);
char		*ft_itoa(long long nbr);
char		*ft_strjoin2(const char *s1, char *s2);
void		ft_putstr_fd(char *s, int fd);
int			ft_strlen(char *str);
void		ft_free_tab(char **tab);
char		**ft_split(char const *s, char c);
char		*ft_cpy(char *str);
void		ft_free_data_game(t_game *game);

/*parsing*/
int			ft_check_map_start(char *str_map);
int			ft_check_map_separation(char *str_map);
int			ft_check_space_in_tab(char **map);
int			ft_check_size_map(char **map_file, t_game *game);
char		**ft_init_parsing(char *file, t_game *game);
int			ft_search_tab(char **tab, char *to_find, int *pos, int mod);
char		*ft_cpy(char *str);
int			ft_make_color(char *str);
int			ft_atoi(char *str, int *pos, int first);
int			ft_encode_rgb(int red, int green, int blue);
char		*ft_strjoin(char *s1, char *s2);
int			ft_find(char *str, char *to_find, int mod);
char		**ft_create_map(char **map, t_game *game);
char		*ft_strdup(const char *s);
int			ft_animation(char **map_file, t_game *game);
void		ft_list_add_back(t_text_list **head, char *path,
				int pos, t_game *game);

#endif