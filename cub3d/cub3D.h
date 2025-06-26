/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3D.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rammisse <rammisse@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/23 08:40:09 by rammisse          #+#    #+#             */
/*   Updated: 2025/06/26 08:29:51 by rammisse         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CUB3D_H
#define CUB3D_H

# ifndef BUFFER_SIZE
#  define BUFFER_SIZE 42
# endif

#include <stdio.h>
#include <fcntl.h>
#include <unistd.h>
#include "minilibx/mlx.h"
# include <limits.h>
# include <fcntl.h>
# include <stdlib.h>

#define WIDTH 800
#define LENGTH 600


typedef struct	s_mlx
{
	void	*win;
	void 	*mlxwin;
	void	*img;
	
} t_mlx;

char	*get_next_line(int fd);
char	*ft_strjoin(char *s1, const char *s2);
char	*ft_strdup(const char *s);
char	*ft_calloc(size_t count, size_t size);
size_t	ft_strlen(const char *str);

#endif