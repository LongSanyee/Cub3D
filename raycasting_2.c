/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   raycasting_2.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rammisse <rammisse@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/27 14:38:26 by azaimi            #+#    #+#             */
/*   Updated: 2025/10/20 23:37:37 by rammisse         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3D.h"

bool	haswallat(t_mlx *mlx, double x, double y)
{
	int		mapx;
	int		mapy;
	size_t	rowlen;

	mapx = (int)(x / TILE);
	mapy = (int)(y / TILE);
	if (mapx < 0 || mapy < 0 || mapy >= (int)mlx->data.k)
		return (true);
	if (!mlx->data.map[mapy])
		return (true);
	rowlen = ft_strlen(mlx->data.map[mapy]);
	if (mapx >= (int)rowlen)
		return (true);
	return (mlx->data.map[mapy][mapx] == '1');
}

double	calc_distance(double x1, double y1, double x2, double y2)
{
	return (sqrt(pow(x2 - x1, 2) + pow(y2 - y1, 2)));
}

double	update_angle(double angle)
{
	angle = fmod(angle, 2 * PI);
	if (angle < 0)
		angle += 2 * PI;
	return (angle);
}

static void	init_ray_struct(t_mlx *mlx, double ray_angle, int i)
{
	mlx->rays[i].rayangle = update_angle(ray_angle);
	mlx->rays[i].wallhorhitx = 0;
	mlx->rays[i].wallverhitx = 0;
	mlx->rays[i].wallhorhity = 0;
	mlx->rays[i].wallverhity = 0;
	mlx->rays[i].distance = 0;
	mlx->rays[i].israyfacingdown = (mlx->rays[i].rayangle > 0
			&& mlx->rays[i].rayangle < PI);
	mlx->rays[i].israyfacingup = !mlx->rays[i].israyfacingdown;
	mlx->rays[i].israyfacingright = (mlx->rays[i].rayangle < (0.5 * PI)
			|| mlx->rays[i].rayangle > (1.5 * PI));
	mlx->rays[i].israyfacingleft = !mlx->rays[i].israyfacingright;
}

void	cast_all_rays(t_mlx *mlx)
{
	int			i;
	double		fov;
	static int	leak = 0;
	double		ray_angle;

	fov = 60 * (PI / 180);
	ray_angle = mlx->player.rotationangle - (fov / 2);
	i = 0;
	if (mlx->rays && leak != 0)
		free(mlx->rays);
	mlx->rays = malloc(sizeof(t_Ray) * RAYS);
	if (!mlx->rays)
		return ;
	leak = 1;
	while (i < RAYS)
	{
		init_ray_struct(mlx, ray_angle, i);
		cast_single_ray(mlx, mlx->rays[i].rayangle, i);
		ray_angle += fov / RAYS;
		i++;
	}
}
