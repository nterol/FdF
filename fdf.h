/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fdf.h                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nterol <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/02/18 15:28:47 by nterol            #+#    #+#             */
/*   Updated: 2017/02/20 19:32:09 by nterol           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */


#ifndef FDF_H
# define FDF_H

# include "libft/libft.h"
# include "minilibx_macos/mlx.h"
# include <stdio.h>
# include <math.h>

# define ALPHA M_PI * env->alph / 180
# define BETA  M_PI * env->bet / 180
# define GAMMA M_PI * env->gmm / 180


typedef struct s_fdf{
  void *init;
  void *windows;
  void *image;
  int  color;

  char *data; //mlx_get_data_addr
  int bpp;
  int size_line;
  int endian;

  int **map;
  int len_x;
  int len_y;
  int height;
  int width;
  int zoom;
  int base_x;
  int base_y;
  int x0;
  int y0;
  int x1;
  int y1;
  int dx;
  int dy;
  int sx;
  int sy;
  int err;
  int e2;
  double alph;
  double bet;
  double gmm;
  struct s_fdf *next;

}              t_fdf;

int     count_size_map(char *file, char *buf);
void    map_it(t_fdf *ntl, char *file);
int     main(int ac, char **av);

#endif
