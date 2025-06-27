/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3D.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rammisse <rammisse@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/23 08:40:09 by rammisse          #+#    #+#             */
/*   Updated: 2025/06/27 18:24:48 by rammisse         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CUB3D_H
#define CUB3D_H

# ifndef BUFFER_SIZE
#  define BUFFER_SIZE 42
# endif

# include "minilibx/mlx.h"
# include <stdio.h>
# include <fcntl.h>
# include <unistd.h>
# include <limits.h>
# include <fcntl.h>
# include <stdlib.h>

#define WIDTH 800
#define LENGTH 600


typedef struct	s_mlx
{
	void	*win;
	void	*mlxwin;
	void	*img;
	
} t_mlx;

typedef struct	s_data
{
	char	**map;
	char	**textures;
	int		ceiling[3];
	int		floor[3];
}	t_data;

char	*get_next_line(int fd);
char	*ft_strjoin(char *s1, const char *s2);
char	*ft_strdup(const char *s);
char	*ft_calloc(size_t count, size_t size);
size_t	ft_strlen(const char *str);
int     ft_atoi(char *str);
int		doublearraylen(char **av);
int		linelen(char **av);
size_t	ft_strlcpy(char *dst, char *src, size_t dstsize);
int		map(t_data *data, char **av);
int getceiling(t_data *data, char **av);
int getfloor(t_data *data, char **av);
char	*ft_substr(char const *s, unsigned int start, size_t len);

#endif