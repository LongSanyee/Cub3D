/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3D.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rammisse <rammisse@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/23 08:40:09 by rammisse          #+#    #+#             */
/*   Updated: 2025/07/04 15:57:15 by rammisse         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CUB3D_H
#define CUB3D_H

# ifndef BUFFER_SIZE
#  define BUFFER_SIZE 42
# endif

# define TILE 20
# define PI 3.14159265359
# define FOVANGLE = 60 * (PI / 180)
# define RAYS 320

# define W 119
# define A 97
# define S 115
# define D 100
# define ESC 65307

# define UP 65362
# define RIGHT 65363
# define LEFT 65361
# define DOWN 65364

# include "minilibx/mlx.h"
# include <stdio.h>
# include <fcntl.h>
# include <unistd.h>
# include <math.h>
# include <limits.h>
# include <stdlib.h>

typedef struct	s_data
{
	char	**map;
	char	**cubfile;
	char	**textures;
	size_t	len;
	size_t	k;
	size_t	longestline;
	int		ceiling[3];
	int		floor[3];
}	t_data;

typedef struct s_player
{
	double	x;
	double	y;
	double angle;
	int		turndirection;
	int		walkdirection;
	double rotationangle;
	double rotationspeed;
	double speed;
	int rad;
}	t_player;

typedef struct	s_mlx
{
	void	*mlx;
	void	*mlxwin;
	void	*img;
	int		img_width;
	int		img_height;
	int 	bpp;
	int		linelength;
	int		endian;
	void	*addr;
	t_data data;
	t_player player;
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
void freeeverything(t_data *data);
int validatemap(t_data *data);
void render(t_mlx *win);
int createmap(t_mlx *mlx);
void ft_exit(t_data *data);
int validateinside(t_data *data);
void freedoublearr(char **arr);
int longestline(t_data *data);
int isplayer(char c);

#endif