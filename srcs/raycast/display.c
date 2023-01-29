/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   display.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pbeheyt <pbeheyt@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/09 11:47:15 by pbeheyt           #+#    #+#             */
/*   Updated: 2023/01/29 05:30:39 by pbeheyt          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub3d.h"

void    ft_init_diplay_struct(t_image *image)
{
    image->player_pos.x = image->game->player_x;
    image->player_pos.y = image->game->player_y;
    image->player_dir.x = -1;
    image->player_dir.y = 0;
    image->plane.x = 0;
    image->plane.y = 0.66;
    // init time
}

void    ft_init_ray(t_image *image, int x)
{
    image->hit = 0;
    // calculate ray position and direction
    image->camera_x = (2 * x / (double)image->size.width) - 1;
    image->raydir.x = image->player_dir.x + (image->plane.x * image->camera_x);
    image->raydir.y = image->player_dir.y + (image->plane.y * image->camera_x);

    //which box of the map we're in
    image->map.x = image->plane.x;
    image->map.y = image->plane.y;
    
    //length of ray from one x or y-side to next x or y-side
    image->delta_dist.x = fabs(1 / image->raydir.x);
    image->delta_dist.y = fabs(1 / image->raydir.y);
}

void    ft_calculate_side_dist(t_image *image)
{
    if (image->raydir.x < 0)
    {
        image->step.x = -1;
        image->side_dist.x = (image->player_pos.x - image->map.x) * image->delta_dist.x;
    }
    else
    {
        image->step.x = 1;
        image->side_dist.x = (image->map.x + 1.0 - image->player_pos.x) * image->delta_dist.x;   
    }
    if (image->raydir.y < 0)
    {
        image->step.y = -1;
        image->side_dist.y = (image->player_pos.y - image->map.y) * image->delta_dist.y;
    }
    else
    {
        image->step.y = 1;
        image->side_dist.y = (image->map.y + 1.0 - image->player_pos.y) * image->delta_dist.y;   
    }
}

void    ft_wall_dist_calculate(t_image *image)
{
    //Calculate distance of perpendicular ray (Euclidean distance would give fisheye effect!)
    if (!image->side)
        image->wall_dist = (image->side_dist.x - image->delta_dist.x);
    else
        image->wall_dist = (image->side_dist.y - image->delta_dist.y);
    //Calculate height of line to draw on screen
    image->line_height = (image->size.height / image->wall_dist);
    //calculate lowest and highest pixel to fill in current stripe
    image->draw_start = -(image->line_height / 2) + (image->size.height / 2);
    if (image->draw_start < 0)
        image->draw_start = 0;
    image->draw_end = (image->line_height / 2) + (image->size.height / 2); 
    if (image->draw_end >= image->size.height)
        image->draw_end = image->size.height - 1;   
}

void    ft_dda(t_image *image)
{
    while (!image->hit)
    {
        //jump to next map square, either in x-direction, or in y-direction
        if (image->side_dist.x < image->side_dist.y)
        {
            image->side_dist.x += image->delta_dist.x;
            image->map.x += image->step.x;
            image->side = 0;
        }
        else
        {
            image->side_dist.y += image->delta_dist.y;
            image->map.y += image->step.y;
            image->side = 1;
        }
        if (image->map.x < 0)
            image->map.x = 0;
        if (image->map.y < 0)
            image->map.y = 0;
        //Check if ray has hit a wall
        if (image->game->map[(int)image->map.x][(int)image->map.y] == '1')
            image->hit = 1;
        ft_wall_dist_calculate(image);
    }
}


t_texture *ft_init_display(t_image *image)
{
    int         bpp;
    int         endian;
    int         size_line;
    t_texture   *global_img;

    bpp = 32;
    endian = 1;
    size_line = 0;
    global_img = malloc(sizeof(t_texture));
    if (!global_img)
        return (exit_clean(image), NULL);
    global_img->content = mlx_new_image(image->mlx, image->size.width, image->size.height);
    global_img->buff = (int *)mlx_get_data_addr(global_img->content, &bpp, &size_line, &endian);
    return (global_img);
    
}

void    ft_floor_and_celling(t_image *image)
{
    int i;

    i = -1;
    while (++i < ((image->size.width * image->size.height) / 2))
        image->global_image->buff[i] = image->game->color_c;
    while (++i < (image->size.width * image->size.height))
        image->global_image->buff[i] = image->game->color_f;
}

int get_pxl_color(t_image *image, t_texture *txt, int start)
{
    double      wallx;
    int         tex_x;    
    int         tex_y;
    // double     tex_pos;
    int         color;
    // double     step;
    
    if (!image->side)
        wallx = image->player_pos.y + (image->wall_dist * image->raydir.y);
    else
        wallx = image->player_pos.x + (image->wall_dist * image->raydir.x);
    wallx -= floor(wallx);
    tex_x = (int)(wallx * (double)txt->size.width);
    if (!image->side && image->raydir.x > 0)
        tex_x = txt->size.width - tex_x - 1;
    if (image->side == 1 && image->raydir.y < 0)
        tex_x = txt->size.width - tex_x - 1;
    // step = 1 * txt->size.height / image->line_height;
    // tex_pos = (start - image->size.height + image->line_height / 2) * step;    
    // tex_y = ((tex_pos * txt->size.height) / image->line_height);
    color = start * 256 - image->size.height * 128 + image->line_height * 128;
    tex_y = ((color * txt->size.height) / image->line_height) / 256;
    // printf("image->size.height : %d\n", image->size.height);
    // printf("color : %d\n", color);
    // printf("txt->size.height %d\n", txt->size.height);
    // printf("tex_y %d\n", tex_y);
    // printf("tex_x %d\n", tex_x);
    color = txt->buff[(int)(tex_y * txt->size.width + tex_x)];
    return (color);
}

void    ft_fill_img_buffer(int x, t_image *image)
{
    int start;
    int end;
    int color_txt;

    start = image->draw_start;
    end = image->draw_end;

    while (start < end)
    {
        color_txt = get_pxl_color(image, image->north, start);
        image->global_image->buff[(image->size.width * start) + x] = color_txt;
        start += 1;
    }
}

int display(void *param)
{
    t_image *image;
    int         x;

    image = (t_image *)param;
    ft_init_diplay_struct(image);
    image->global_image = ft_init_display(image);
    ft_floor_and_celling(image);
    x = 0;
    while (x < image->size.width)
    {
        ft_init_ray(image, x);
        // calculate step and initial sideDist
        ft_calculate_side_dist(image);
        //perform DDA
        ft_dda(image);
        // affichage ...
        ft_fill_img_buffer(x, image);
        x++;
        if (x == (image->size.width / 2) + 1 || x == 1 || x == (image->size.width / 2))
        {
            printf("x == %d\n", x);
            printf("camera_x : %f\n", image->camera_x);
            printf("side : %d\n", image->side);
            printf("wall dist : %f\n", image->wall_dist);
            printf("side_dist.x : %f\n", image->side_dist.x);
            printf("side_dist.y : %f\n", image->side_dist.y);
            printf("delta_dist_x : %f\n", image->delta_dist.x);
            printf("delta_dist_y : %f\n", image->delta_dist.y);
            printf("image->line_h : %d\n", image->line_height);
            printf(" size.height : %d\n", image->size.height);
            printf("start : %d\n", image->draw_start);
            printf("end : %d\n", image->draw_end);
            printf("raydir_x : %f\n", image->raydir.x);
            printf("raydir_y : %f\n", image->raydir.y);
            printf("delta_dist_y : %f\n\n\n\n", image->delta_dist.y);
        }
    }
    mlx_put_image_to_window(image->mlx, image->win, image->global_image->content, 0, 0);
    mlx_destroy_image(image->mlx, image->global_image->content);
    free(image->global_image);
    return (0);
}