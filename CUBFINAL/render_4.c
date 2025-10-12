/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   render_4.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rammisse <rammisse@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/27 14:41:00 by azaimi            #+#    #+#             */
/*   Updated: 2025/10/10 18:00:43 by rammisse         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3D.h"

void	do_c_f(t_mlx *mlx)
{
	t_color	color;

	color.y = 0;
	color.color = (mlx->data.floor[0] << 16) | (mlx->data.floor[1] << 8)
		| mlx->data.floor[2];
	while (color.y < HEIGHT / 2)
	{
		color.x = 0;
		while (color.x < WIDTH)
			put_pixel(mlx, color.x++, color.y, color.color);
		color.y++;
	}
	color.y = HEIGHT / 2;
	color.color2 = (mlx->data.ceiling[0] << 16) | (mlx->data.ceiling[1] << 8)
		| mlx->data.ceiling[2];
	while (color.y < HEIGHT)
	{
		color.x = 0;
		while (color.x < WIDTH)
		{
			put_pixel(mlx, color.x, color.y, color.color2);
			color.x++;
		}
		color.y++;
	}
}

int getcolor(t_texture *texture, int x, int y)
{
    char *pixel;
    
    if (x < 0 || x >= texture->width || y < 0 || y >= texture->height)
        return (0);
    pixel = texture->addr + (y * texture->linelength + x * (texture->bpp / 8));
    return (*(unsigned int *)pixel);
}

int load_texture(t_mlx *mlx, t_texture *texture, char *path)
{
    texture->img = mlx_xpm_file_to_image(mlx->mlx, path, &texture->width, &texture->height);
    if (!texture->img)
    {
        printf("Error: Failed to load texture%s\n", path);
        return (0);
    }
    texture->addr = mlx_get_data_addr(texture->img, &texture->bpp, &texture->linelength, &texture->endian);
    return (1);
}

void load_all_textures(t_mlx *mlx)
{
    if (!load_texture(mlx, &mlx->north, mlx->data.textures[0])
		|| !load_texture(mlx, &mlx->south, mlx->data.textures[1])
		|| !load_texture(mlx, &mlx->west, mlx->data.textures[2])
		|| !load_texture(mlx, &mlx->east, mlx->data.textures[3]))
		cleanexit(mlx);
}

t_texture *getwalltexture(t_mlx *mlx, int i)
{
	t_Ray *ray = &mlx->rays[i];
	
	if (ray->wasHitVertical)
	{
		if (ray->isRayFacingRight)
			return (&mlx->east);
		else
			return (&mlx->west);
	}
	else
	{
		if (ray->isRayFacingDown)
			return (&mlx->south);
		else
			return (&mlx->north);
	}
}

void drawtexture(t_mlx *mlx, t_render *re)
{
	t_texture *text;
	int		tex_y;
	int		tex_x;
	double	wallhitx;
	double	tex_step;
	double	tex_pos;
	
	text = getwalltexture(mlx, re->i);
	if (mlx->rays[re->i].wasHitVertical)
        wallhitx = fmod(mlx->rays[re->i].wallhity, TILE);
    else
        wallhitx = fmod(mlx->rays[re->i].wallhitx, TILE);
    tex_x = (int)(wallhitx * text->width / TILE);
    if (tex_x < 0)
        tex_x = 0;
    if (tex_x >= text->width)
        tex_x = text->width - 1;
    tex_step = (double)text->height / re->WallHeight;
    tex_pos = 0;
	if (re->wallTop < 0)
		tex_pos = -re->wallTop * tex_step;
    re->x = re->i * re->stripWidth;
    re->z = 0;
    while (re->z < re->stripWidth)
    {
		double column_tex_pos = tex_pos;
        re->y = re->wallTop;
        while (re->y < re->wallBottom)
        {
            tex_y = (int)column_tex_pos;
            if (tex_y < 0)
                tex_y = 0;
            if (tex_y >= text->height)
                tex_y = text->height - 1;
            put_pixel(mlx, re->x + re->z, re->y, getcolor(text, tex_x, tex_y));
            column_tex_pos += tex_step;
            re->y++;
        }
        re->z++;
    }
}

void	render3dwalls(t_mlx *mlx)
{
	t_render	re;

	re.i = 0;
	do_c_f(mlx);
	while (re.i < RAYS)
	{
		re.GRayDistance = mlx->rays[re.i].distance
			* cos(mlx->rays[re.i].rayAngle - mlx->player.rotationangle);
		re.Distanceproj = (WIDTH / 2) / tan(FOV / 2);
		re.WallHeight = (int)((TILE / re.GRayDistance) * re.Distanceproj);
		if (re.WallHeight > HEIGHT)
			re.WallHeight = HEIGHT;
		re.wallTop = (HEIGHT / 2) - (re.WallHeight / 2);
		if (re.wallTop < 0)
			re.wallTop = 0;
		re.wallBottom = (HEIGHT / 2) + (re.WallHeight / 2);
		if (re.wallBottom >= HEIGHT)
			re.wallBottom = HEIGHT - 1;
		re.stripWidth = WIDTH / RAYS;
		if (re.stripWidth < 1)
			re.stripWidth = 1;
		drawtexture(mlx, &re);
		re.i++;
	}
}

void	initstruct(t_player *player)
{
	player->turndirection = 0;
	player->walkdirection = 0;
	player->rotationspeed = 4 *(PI / 180);
	player->rad = 3;
	player->speed = 0.06;
}

int	keypress(int key, t_mlx *mlx)
{
	if (key == ESC)
		cleanexit(mlx);
	if (key == W || key == UP)
		mlx->player.walkdirection = 1;
	if (key == S || key == DOWN)
		mlx->player.walkdirection = -1;
	if (key == A || key == LEFT)
		mlx->player.turndirection = -1;
	if (key == D || key == RIGHT)
		mlx->player.turndirection = 1;
	return (0);
}
