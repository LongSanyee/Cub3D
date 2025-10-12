/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3D.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rammisse <rammisse@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/23 08:40:09 by rammisse          #+#    #+#             */
/*   Updated: 2025/10/05 16:46:27 by rammisse         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CUB3D_H
#define CUB3D_H

# ifndef BUFFER_SIZE
#  define BUFFER_SIZE 42
# endif

# define TILE 5
# define RAY_WIDTH 1
# define RAYS WIDTH / RAY_WIDTH
#define WALL_STRIP_WIDTH 5

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
# include <limits.h>
# include <fcntl.h>
# include <stdlib.h>
# include <stdbool.h>
# include <math.h>

# define WIDTH 900
# define HEIGHT 900
# define PI 3.14159
# define FOV 66 * (PI / 180)


typedef struct s_texture
{
	void    *img;
    char    *addr;
    int     width;
    int     height;
    int     bpp;
    int     linelength;
    int     endian;
}	t_texture;


typedef struct s_Ray
{
	double	rayAngle;
	double	wallhitx;
	double	wallhity;
	double	wallhorhitx;
	double	wallverhitx;
	double	wallhorhity;
	double	wallverhity;
	double	distance;
	int		wasHitVertical;
	int		isRayFacingUp;
	int		isRayFacingDown;
	int		isRayFacingLeft;
	int		isRayFacingRight;
	int		wallHitContent;
}	t_Ray;

typedef struct	s_data
{
	char	**map;
	char	playerdir;
	size_t	len;
	size_t	k;
	char	**cubfile;
	char	**textures;
	char	**dir;
	char	**dir_2;
	char	**rgb;
	char	**rgb_2;
	size_t	longestline;
	int		ceiling[3];
	int		floor[3];
}	t_data;

typedef struct s_player
{
	double	x;
	double	y;
	double	angle;
	int		turndirection;
	int		walkdirection;
	double	rotationangle;
	double	rotationspeed;
	double	speed;
	int		rad;
}	t_player;

typedef struct	s_mlx
{
	void		*mlx;
	void		*mlxwin;
	void		*img;
	int			img_width;
	int			img_height;
	int 		bpp;
	int			linelength;
	int			endian;
	void		*addr;
	t_data		data;
	t_player	player;
	t_texture	south;
	t_texture	north;
	t_texture	west;
	t_texture	east;
	t_Ray		*rays;
} t_mlx;

typedef struct s_render
{
	int		i;
	int		x;
	int		y;
	int		z;
	int		stripWidth;
	double	WallHeight;
	double	GRayDistance;
	double	Distanceproj;
	double	wallTop;
	double	wallBottom;
} t_render;

typedef struct s_color
{
	int		x;
	int		y;
	int		color;
	int		color2;
} t_color;

typedef struct s_draw_R
{
	int x;
	int y;
	int px;
	int py;
	int screenX;
	int screenY;
} t_draw_R;

typedef struct s_Raycasting
{
	double	xstep;
	double	ystep;
	double	Ax;
	double	Ay;
	double	nextHorTouchX;
	double	nextHorTouchY;
	bool	foundHorWall;
	double	wallhorhitx;
	double	wallhorhity;
	double	hordistance;
	double	nextVerTouchX;
	double	nextVerTouchY;
	bool	foundVerWall;
	double	wallverhitx;
	double	wallverhity;
	double	Verdistance;
	int		direction;
} t_Raycasting;

typedef struct s_line
{
	int x0, y0;
	int x1, y1;
	int dx, dy;
	int sx, sy;
	int err;
}	t_line;

int	gettextures(t_data *data);
char	*get_next_line(int fd);
char	*ft_strjoin(char *s1, const char *s2);
char	*ft_strdup(const char *s);
char	*ft_calloc(size_t count, size_t size);
int getcolor(t_texture *texture, int x, int y);
size_t	ft_strlen(const char *str);
int     ft_atoi(char *str);
int		getmap(t_data *data);
void	doublearraylen(char **av, t_data *data);
size_t	ft_strlcpy(char *dst, char *src, size_t dstsize);
int		ft_strncmp(const char *s1, const char *s2, size_t n);
int		getceiling(t_data *data);
int		getfloor(t_data *data);
char	*ft_substr(char const *s, unsigned int start, size_t len);
char	*ft_strchr(const char *s, int c);
char    *ft_strtrim(char *s1, char *set);
void	get_dir(t_data *data);
int		parse_dir(t_data *data);
void	get_rgb(t_data *data);
int		ft_isdigit(int ch);
int		parse_rgb(t_data *data);
int		validatepadding(t_data *data);
int		validatemap(t_data *data);
void	ft_exit(t_data *data);
int		validateinside(t_data *data);
void	freedoublearr(char **arr);
int		check_num(t_data *data);
void	get_rgb_v2(t_data *data);
int		parse_rgb_v2(t_data *data);
int		parse_dir_v2(t_data *data);
void	get_dir_v2(t_data *data);
int		check_dir_v2(t_data *data);
int		check_all(t_data *data);
int		check_col_rgb_v2(t_data *data, int j);
int		longestline(t_data *data);
int		isplayer(char c);
int		createmap(t_mlx *mlx);
void	render(t_mlx *win);
void	freeeverything(t_data *data);
void	cast_all_rays(t_mlx *mlx, int i);
void    render_rays(t_mlx *mlx);
bool	haswallat(t_mlx *mlx, double x, double y);
void	render3dwalls(t_mlx *mlx);
double	update_angle(double angle);
int		update(t_mlx *mlx);
void	it(t_mlx *mlx);
void	draw_line(t_mlx *mlx, int x0, int y0, int x1, int y1, int color);
int		drawmap(t_mlx *mlx);
void	DWalls(t_mlx *mlx);
void	cast_hor(t_mlx *mlx, double ray_angle, int i, t_Raycasting *r);
void	cast_ver(t_mlx *mlx, double ray_angle, int i, t_Raycasting *r);
int		xbutton(t_mlx *mlx);
int		keypress(int key, t_mlx *mlx);
void	put_pixel(t_mlx *mlx, int x, int y, int color);
void	initstruct(t_player *player);
double	calc_distance(double x1, double y1, double x2, double y2);
void	cast_single_ray(t_mlx *mlx, double ray_angle, int i);
int		check_col_rgb(t_data *data, int j);
int		keyrelease(int key, t_mlx *mlx);
void	cleanexit(t_mlx *mlx);
int		parse(int ac, char **av);
int		extractcubfile(t_data *data, char **av);
void	parsedata(int ac, char **av, t_data *data);
void load_all_textures(t_mlx *mlx);

#endif