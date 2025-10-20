/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   raycasting.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rammisse <rammisse@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/22 23:57:26 by azaimi            #+#    #+#             */
/*   Updated: 2025/10/20 05:56:19 by rammisse         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3D.h"

void	init_hor(t_mlx *mlx, double ray_angle, int i, t_Raycasting *r)
{
	r->wallhorhitx = 0;
	r->wallhorhity = 0;
	r->hordistance = 1e30;
	r->foundhorwall = false;
	r->ay = floor(mlx->player.y) * TILE;
	if (mlx->rays[i].israyfacingdown)
		r->ay += TILE;
	r->ax = mlx->player.x * TILE
		+ ((r->ay - mlx->player.y * TILE) / tan(ray_angle));
	r->ystep = TILE;
	if (mlx->rays[i].israyfacingup)
		r->ystep *= -1;
	r->xstep = TILE / tan(ray_angle);
	if (mlx->rays[i].israyfacingleft && r->xstep > 0)
		r->xstep *= -1;
	if (mlx->rays[i].israyfacingright && r->xstep < 0)
		r->xstep *= -1;
	r->nexthortouchx = r->ax;
	r->nexthortouchy = r->ay;
	if (mlx->rays[i].israyfacingup)
		r->nexthortouchy -= 0.01;
}

void	cast_hor(t_mlx *mlx, double ray_angle, int i, t_Raycasting *r)
{
	int	max_steps;
	int	steps;

	max_steps = (int)(mlx->data.len + mlx->data.k) * 2;
	steps = 0;
	init_hor(mlx, ray_angle, i, r);
	while (steps < max_steps && r->nexthortouchx >= 0 && r->nexthortouchy >= 0
		&& r->nexthortouchx <= ((int)mlx->data.len * TILE)
		&& r->nexthortouchy <= ((int)mlx->data.k * TILE))
	{
		if (haswallat(mlx, r->nexthortouchx, r->nexthortouchy))
		{
			r->foundhorwall = true;
			r->wallhorhitx = r->nexthortouchx;
			r->wallhorhity = r->nexthortouchy;
			r->hordistance = calc_distance(mlx->player.x * TILE,
					mlx->player.y * TILE,
					r->nexthortouchx, r->nexthortouchy);
			break ;
		}
		r->nexthortouchx += r->xstep;
		r->nexthortouchy += r->ystep;
		steps++;
	}
}

void	init_ver(t_mlx *mlx, double ray_angle, int i, t_Raycasting *r)
{
	r->wallverhitx = 0;
	r->wallverhity = 0;
	r->verdistance = 1e30;
	r->foundverwall = false;
	r->ax = floor(mlx->player.x) * TILE;
	if (mlx->rays[i].israyfacingright)
		r->ax += TILE;
	r->ay = mlx->player.y * TILE
		+ ((r->ax - mlx->player.x * TILE) * tan(ray_angle));
	r->xstep = TILE;
	if (mlx->rays[i].israyfacingleft)
		r->xstep *= -1;
	r->ystep = TILE * tan(ray_angle);
	if (mlx->rays[i].israyfacingup && r->ystep > 0)
		r->ystep *= -1;
	if (mlx->rays[i].israyfacingdown && r->ystep < 0)
		r->ystep *= -1;
	r->nextvertouchx = r->ax;
	r->nextvertouchy = r->ay;
	if (mlx->rays[i].israyfacingleft)
		r->nextvertouchx -= 0.01;
	if (mlx->rays[i].israyfacingup)
		r->nextvertouchy -= 0.01;
	else if (mlx->rays[i].israyfacingdown)
		r->nextvertouchy += 0.01;
}

void	cast_ver(t_mlx *mlx, double ray_angle, int i, t_Raycasting *r)
{
	int	max_steps;
	int	steps;

	max_steps = (int)(mlx->data.len + mlx->data.k) * 2;
	steps = 0;
	init_ver(mlx, ray_angle, i, r);
	while (steps < max_steps && r->nextvertouchx >= 0 && r->nextvertouchy >= 0
		&& r->nextvertouchx <= ((int)mlx->data.len * TILE)
		&& r->nextvertouchy <= ((int)mlx->data.k * TILE))
	{
		if (haswallat(mlx, r->nextvertouchx, r->nextvertouchy))
		{
			r->foundverwall = true;
			r->wallverhitx = r->nextvertouchx;
			r->wallverhity = r->nextvertouchy;
			r->verdistance = calc_distance(mlx->player.x * TILE,
					mlx->player.y * TILE,
					r->nextvertouchx, r->nextvertouchy);
			break ;
		}
		r->nextvertouchx += r->xstep;
		r->nextvertouchy += r->ystep;
		steps++;
	}
}

void	cast_single_ray(t_mlx *mlx, double ray_angle, int i)
{
	t_Raycasting	r;

	ray_angle = update_angle(ray_angle);
	r.foundhorwall = false;
	r.foundverwall = false;
	cast_hor(mlx, ray_angle, i, &r);
	cast_ver(mlx, ray_angle, i, &r);
	if (r.hordistance < r.verdistance)
	{
		mlx->rays[i].wallhitx = r.wallhorhitx;
		mlx->rays[i].wallhity = r.wallhorhity;
		mlx->rays[i].distance = r.hordistance;
		mlx->rays[i].washitvertical = false;
	}
	else
	{
		mlx->rays[i].wallhitx = r.wallverhitx;
		mlx->rays[i].wallhity = r.wallverhity;
		mlx->rays[i].distance = r.verdistance;
		mlx->rays[i].washitvertical = true;
	}
}
