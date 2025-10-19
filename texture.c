/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   texture.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rammisse <rammisse@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/27 14:41:00 by azaimi            #+#    #+#             */
/*   Updated: 2025/10/19 20:56:07 by rammisse         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3D.h"

int	getcolor(t_texture *texture, int x, int y)
{
	char	*pixel;

	if (x < 0 || x >= texture->width || y < 0 || y >= texture->height)
		return (0);
	pixel = texture->addr + (y * texture->linelength + x * (texture->bpp / 8));
	return (*(unsigned int *)pixel);
}

int	load_texture(t_mlx *mlx, t_texture *texture, char *path)
{
	texture->img = mlx_xpm_file_to_image(mlx->mlx, path, &texture->width,
			&texture->height);
	if (!texture->img)
	{
		printf("Error: Failed to load texture%s\n", path);
		return (0);
	}
	texture->addr = mlx_get_data_addr(texture->img, &texture->bpp,
			&texture->linelength, &texture->endian);
	return (1);
}

void	load_all_textures(t_mlx *mlx)
{
	if (!load_texture(mlx, &mlx->north, mlx->data.textures[0])
		|| !load_texture(mlx, &mlx->south, mlx->data.textures[1])
		|| !load_texture(mlx, &mlx->west, mlx->data.textures[2])
		|| !load_texture(mlx, &mlx->east, mlx->data.textures[3]))
		cleanexit(mlx);
}

t_texture	*getwalltexture(t_mlx *mlx, int i)
{
	t_Ray	*ray;

	ray = &mlx->rays[i];
	if (ray->washitvertical)
	{
		if (ray->israyfacingright)
			return (&mlx->east);
		else
			return (&mlx->west);
	}
	else
	{
		if (ray->israyfacingdown)
			return (&mlx->south);
		else
			return (&mlx->north);
	}
}

void	texturehelp(t_vars *vars, t_render *re, t_mlx *mlx)
{
	while (re->z < re->stripwidth)
	{
		re->y = re->walltop;
		while (re->y < re->wallbottom)
		{
			vars->tex_y = (int)vars->tex_pos;
			if (vars->tex_y < 0)
				vars->tex_y = 0;
			if (vars->tex_y >= vars->text->height)
				vars->tex_y = vars->text->height - 1;
			put_pixel(mlx, re->x + re->z, re->y,
				getcolor(vars->text, vars->tex_x, vars->tex_y));
			vars->tex_pos += (double)vars->text->height / re->wallheight;
			re->y++;
		}
		re->z++;
	}
}
