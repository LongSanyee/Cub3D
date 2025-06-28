/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3D.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rammisse <rammisse@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/23 08:40:09 by rammisse          #+#    #+#             */
/*   Updated: 2025/06/28 20:23:22 by rammisse         ###   ########.fr       */
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

typedef struct	s_data
{
	char	**map;
	size_t	len;
	size_t	k;
	char	**cubfile;
	char	**textures;
	int		ceiling[3];
	int		floor[3];
}	t_data;

typedef struct s_grid
{
	int y;
	int x;
}	t_grid;

typedef struct	s_mlx
{
	void	*win;
	void	*mlxwin;
	t_data data;
	void	*img;
	
} t_mlx;


char	*get_next_line(int fd);
char	*ft_strjoin(char *s1, const char *s2);
char	*ft_strdup(const char *s);
char	*ft_calloc(size_t count, size_t size);
size_t	ft_strlen(const char *str);
int     ft_atoi(char *str);
int getmap(t_data *data);
void	doublearraylen(char **av, t_data *data);
size_t	ft_strlcpy(char *dst, char *src, size_t dstsize);
int	ft_strncmp(const char *s1, const char *s2, size_t n);
int getceiling(t_data *data);
int getfloor(t_data *data);
char	*ft_substr(char const *s, unsigned int start, size_t len);
char	*ft_strchr(const char *s, int c);
char    *ft_strtrim(char *s1, char *set);
int validatepadding(t_data *data);
int validatemap(t_data *data);
void ft_exit(t_data *data);
int validateinside(t_data *data);
void freedoublearr(char **arr);

#endif