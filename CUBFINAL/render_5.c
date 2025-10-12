/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   render_5.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: azaimi <azaimi@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/27 16:39:00 by azaimi            #+#    #+#             */
/*   Updated: 2025/09/27 17:25:55 by azaimi           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3D.h"

void	render(t_mlx *win)
{
	initstruct(&win->player);
	mlx_hook(win->mlxwin, 17, 0, xbutton, win);
	mlx_hook(win->mlxwin, 2, 1L << 0, keypress, win);
	mlx_hook(win->mlxwin, 3, 1L << 1, keyrelease, win);
	mlx_loop_hook(win->mlx, update, win);
	mlx_loop(win->mlx);
}
