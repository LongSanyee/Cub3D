/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   texture_2.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rammisse <rammisse@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/19 20:56:59 by rammisse          #+#    #+#             */
/*   Updated: 2025/10/20 22:28:38 by rammisse         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3D.h"

void	drawtexture(t_mlx *mlx, t_render *re)
{
	t_vars	vars;

	vars.text = getwalltexture(mlx, re->i);
	if (mlx->rays[re->i].washitvertical)
		vars.wallhitx = fmod(mlx->rays[re->i].wallhity, TILE);
	else
		vars.wallhitx = fmod(mlx->rays[re->i].wallhitx, TILE);
	vars.tex_x = (int)(vars.wallhitx * vars.text->width / TILE);
	if (vars.tex_x < 0)
		vars.tex_x = 0;
	if (vars.tex_x >= vars.text->width)
		vars.tex_x = vars.text->width - 1;
	vars.tex_pos = 0;
	if (re->wallheight > HEIGHT)
		vars.tex_pos = (re->wallheight - HEIGHT) / 2;
	vars.tex_pos *= (double)vars.text->height / re->wallheight;
	re->z = 0;
	texturehelp(&vars, re, mlx);
}

void	render3dwalls(t_mlx *mlx)
{
	t_render	re;
	double		fov;

	re.i = 0;
	do_c_f(mlx);
	fov = 60 * (PI / 180);
	while (re.i < RAYS)
	{
		re.correctdistance = mlx->rays[re.i].distance
			* cos(mlx->rays[re.i].rayangle - mlx->player.rotationangle);
		re.distanceproj = (WIDTH / 2) / tan(fov / 2);
		re.wallheight = (int)((TILE / re.correctdistance) * re.distanceproj);
		re.walltop = (HEIGHT / 2) - (re.wallheight / 2);
		if (re.walltop < 0)
			re.walltop = 0;
		re.wallbottom = (HEIGHT / 2) + (re.wallheight / 2);
		if (re.wallbottom >= HEIGHT)
			re.wallbottom = HEIGHT - 1;
		re.stripwidth = 1;
		if (re.stripwidth < 1)
			re.stripwidth = 1;
		drawtexture(mlx, &re);
		re.i++;
	}
}
