/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   texture.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rammisse <rammisse@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/27 14:41:00 by azaimi            #+#    #+#             */
/*   Updated: 2025/10/20 23:53:01 by rammisse         ###   ########.fr       */
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
