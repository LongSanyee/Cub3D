/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   texture_2.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rammisse <rammisse@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/19 20:56:59 by rammisse          #+#    #+#             */
/*   Updated: 2025/10/20 04:07:44 by rammisse         ###   ########.fr       */
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
