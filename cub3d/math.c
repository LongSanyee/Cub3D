/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   math.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rammisse <rammisse@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/02 13:23:33 by rammisse          #+#    #+#             */
/*   Updated: 2025/07/02 14:04:47 by rammisse         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3D.h"

double degtorad(double degree)
{
	return (degree * (PI * 180.0));
}

double radtodegree(double rad)
{
	return (rad * (180.0 / PI));
}
