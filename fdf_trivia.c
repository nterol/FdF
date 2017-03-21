/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fdf_trivia.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nterol <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/03/07 23:29:45 by nterol            #+#    #+#             */
/*   Updated: 2017/03/16 17:01:26 by nterol           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

void		mlx_pixel_image(t_fdf *env, int x, int y, int color)
{
	int		p;

	p = (x * (env->bpp / 8) + (y * env->size_line));
	env->data[p] = color;
	env->data[p + 1] = color >> 8;
	env->data[p + 2] = color >> 16;
}

void		line(t_fdf *env)
{
	env->dx = abs(env->x1 - env->x0);
	env->sx = (env->x0 < env->x1 ? 1 : -1);
	env->dy = abs(env->y1 - env->y0);
	env->sy = (env->y0 < env->y1 ? 1 : -1);
	env->err = (env->dx > env->dy ? env->dx : -env->dy) / 2;
	while (1)
	{
		if (env->x0 < env->width && env->y0 < env->height && env->x0 > 1\
				&& env->y0 > 1)
			mlx_pixel_image(env, env->x0, env->y0, env->color);
		if ((env->x0 == env->x1) && (env->y0 == env->y1))
			break ;
		env->e2 = env->err;
		if (env->e2 > -env->dx)
		{
			env->err -= env->dy;
			env->x0 += env->sx;
		}
		if (env->e2 < env->dy)
		{
			env->err += env->dx;
			env->y0 += env->sy;
		}
	}
}

int			f_x(int x, int y, t_fdf *env)
{
	int		i;

	i = (x * cos(ALPHA) * env->zoom) - (y * sin(ALPHA) * env->zoom) +\
		env->base_x;
	return (i);
}

int			f_y(int x, int y, t_fdf *env)
{
	int		j;

	j = ((x * sin(ALPHA) * env->zoom) / 2) + ((y * cos(ALPHA) * env->zoom) / 2)\
		- (env->map[y][x] * env->z_height) + env->base_y;
	return (j);
}

void		color_change(int x, int y, t_fdf *env)
{
	env->color = 0xC0FFF4;
	if (env->map[y][x] == env->z_min)
		env->color = 0xFFD5C0;
	if (env->map[y][x] == env->z_max)
		env->color = 0xFFC0CB;
}
