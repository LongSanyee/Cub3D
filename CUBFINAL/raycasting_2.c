/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   raycasting_2.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rammisse <rammisse@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/27 14:38:26 by azaimi            #+#    #+#             */
/*   Updated: 2025/09/27 21:55:59 by rammisse         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3D.h"

bool	haswallat(t_mlx *mlx, double x, double y)
{
	int	mapx;
	int	mapy;

	mapx = (int)(x / TILE);
	mapy = (int)(y / TILE);
	if (mapx < 0 || mapx >= (int)mlx->data.len
		|| mapy < 0 || mapy >= (int)mlx->data.k)
		return (true);
	if (!mlx->data.map[mapy] || mapx >= (int)ft_strlen(mlx->data.map[mapy]))
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
	{
		angle += 2 * PI;
	}
	return (angle);
}

void	cast_all_rays(t_mlx *mlx, int i)
{
	double	ray_angle;

	ray_angle = mlx->player.rotationangle - (FOV / 2);
	mlx->rays = malloc(sizeof(t_Ray) * RAYS);
	if (!mlx->rays)
		return ;
	while (i < RAYS - 1)
	{
		mlx->rays[i].rayAngle = update_angle(ray_angle);
		mlx->rays[i].wallhorhitx = 0;
		mlx->rays[i].wallverhitx = 0;
		mlx->rays[i].wallhorhity = 0;
		mlx->rays[i].wallverhity = 0;
		mlx->rays[i].distance = 0;
		mlx->rays[i].isRayFacingDown = mlx->rays[i].rayAngle > 0
			&& mlx->rays[i].rayAngle < PI;
		mlx->rays[i].isRayFacingUp = !mlx->rays[i].isRayFacingDown;
		mlx->rays[i].isRayFacingRight = mlx->rays[i].rayAngle < (0.5 * PI)
			|| mlx->rays[i].rayAngle > (1.5 * PI);
		mlx->rays[i].isRayFacingLeft = !mlx->rays[i].isRayFacingRight;
		cast_single_ray(mlx, ray_angle, i);
		ray_angle += FOV / RAYS;
		i++;
	}
}
