/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fdf.h                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nterol <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/02/18 15:28:47 by nterol            #+#    #+#             */
/*   Updated: 2017/03/16 19:20:25 by nterol           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FDF_H
# define FDF_H

# include "libft/libft.h"
# include "minilibx_macos/mlx.h"
# include <stdio.h>
# include <math.h>

# define WIDTH 2300
# define HEIGHT 1300
# define TITLE "Hello this is window"
# define LEFT 123
# define UP 126
# define DOWN 125
# define RIGHT 124
# define PAD_PLUS 69
# define PAD_SUB 78
# define WIDTH_PLUS 88
# define WIDTH_MINUS 86
# define HEIGHT_PLUS 91
# define HEIGHT_MINUS 84
# define ESC 53
# define ALPHA M_PI * env->alph / 180

typedef struct		s_fdf {
	void			*init;
	void			*windows;
	void			*image;
	int				color;

	char			*data;
	int				bpp;
	int				size_line;
	int				endian;

	int				**map;
	int				len_x;
	int				len_y;
	int				z_height;
	int				height;
	int				width;
	double		zoom;
	double		base_x;
	double		base_y;
	int				z_min;
	int				z_max;
	int				x0;
	int				y0;
	int				x1;
	int				y1;
	int				dx;
	int				dy;
	int				sx;
	int				sy;
	int				err;
	int				e2;
	int				alph;
	int				width_control;
	int				height_control;
	struct s_fdf	*next;

}					t_fdf;

int					main(int ac, char **av);
int					launcher(t_fdf *env);
int					count_size_map(char *file, char *buf);
void				map_it(t_fdf *env, char *file);
void				wrong(void);
int					key_function(int keycode, t_fdf *env);
void				line(t_fdf *env);
int					f_x(int x, int y, t_fdf *env);
int					f_y(int x, int y, t_fdf *env);
void				color_change(int x, int y, t_fdf *env);

#endif
