/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   render_3.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rammisse <rammisse@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/27 14:40:13 by azaimi            #+#    #+#             */
/*   Updated: 2025/10/20 23:51:04 by rammisse         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3D.h"

void	initstruct(t_player *player)
{
	player->turndirection = 0;
	player->walkdirection = 0;
	player->strafedirection = 0;
	player->rotationspeed = 4 * (PI / 180);
	player->speed = 0.06;
}

int	keypress(int key, t_mlx *mlx)
{
	if (key == ESC)
		cleanexit(mlx);
	if (key == W)
		mlx->player.walkdirection = 1;
	if (key == S)
		mlx->player.walkdirection = -1;
	if (key == A)
		mlx->player.strafedirection = -1;
	if (key == D)
		mlx->player.strafedirection = 1;
	if (key == LEFT)
		mlx->player.turndirection = -1;
	if (key == RIGHT)
		mlx->player.turndirection = 1;
	return (0);
}

int	keyrelease(int key, t_mlx *mlx)
{
	if (key == W)
		mlx->player.walkdirection = 0;
	if (key == S)
		mlx->player.walkdirection = 0;
	if (key == A)
		mlx->player.strafedirection = 0;
	if (key == D)
		mlx->player.strafedirection = 0;
	if (key == LEFT || key == RIGHT)
		mlx->player.turndirection = 0;
	return (0);
}

static int	can_move(t_mlx *mlx, double x_px, double y_px, double radius_px)
{
	if (haswallat(mlx, x_px - radius_px, y_px))
		return (0);
	if (haswallat(mlx, x_px + radius_px, y_px))
		return (0);
	if (haswallat(mlx, x_px, y_px - radius_px))
		return (0);
	if (haswallat(mlx, x_px, y_px + radius_px))
		return (0);
	if (haswallat(mlx, x_px - radius_px, y_px - radius_px))
		return (0);
	if (haswallat(mlx, x_px + radius_px, y_px - radius_px))
		return (0);
	if (haswallat(mlx, x_px - radius_px, y_px + radius_px))
		return (0);
	if (haswallat(mlx, x_px + radius_px, y_px + radius_px))
		return (0);
	return (1);
}

int	update(t_mlx *mlx)
{
	double	new_x;
	double	new_y;
	double	movestep;
	double	strafe_angle;

	mlx->player.rotationangle += mlx->player.turndirection
		* mlx->player.rotationspeed;
	mlx->player.rotationangle = update_angle(mlx->player.rotationangle);
	movestep = mlx->player.walkdirection * mlx->player.speed;
	new_x = mlx->player.x + cos(mlx->player.rotationangle) * movestep;
	new_y = mlx->player.y + sin(mlx->player.rotationangle) * movestep;
	strafe_angle = mlx->player.rotationangle + (PI / 2);
	movestep = mlx->player.strafedirection * mlx->player.speed;
	new_x += cos(strafe_angle) * movestep;
	new_y += sin(strafe_angle) * movestep;
	if (can_move(mlx, new_x * TILE, new_y * TILE, 4.0))
	{
		mlx->player.x = new_x;
		mlx->player.y = new_y;
	}
	cast_all_rays(mlx);
	render3dwalls(mlx);
	mlx_put_image_to_window(mlx->mlx, mlx->mlxwin, mlx->img, 0, 0);
	return (0);
}
