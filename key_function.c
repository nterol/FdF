/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   key_function.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nterol <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/03/07 22:45:11 by nterol            #+#    #+#             */
/*   Updated: 2017/03/16 19:20:22 by nterol           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

void move_around(int keycode, t_fdf *env)
{
	if (keycode == HEIGHT_PLUS)
	{
		env->height_control += 1;
		if (env->height_control == 0)
			env->height_control = 1;
	}
	if (keycode == HEIGHT_MINUS)
	{
		env->height_control -= 1;
		if (env->height_control == 0)
			env->height_control = -1;
	}
	if (keycode == WIDTH_MINUS)
	{
		env->width_control += 1;
		if (env->width_control == 0)
			env->width_control = 1;
	}
	if (keycode == WIDTH_PLUS)
	{
		env->width_control -= 1;
		if (env->width_control == 0)
			env->width_control = -1;
	}
	launcher(env);
}

void set_zoom(int keycode, t_fdf *env)
{
	mlx_destroy_image(env->init, env->image);
	if (keycode == PAD_PLUS)
		env->zoom += 1;
	else if (keycode == PAD_SUB)
		env->zoom -= 1;
	launcher(env);
}

void 		turn_around(int keycode, t_fdf *env)
{
	mlx_destroy_image(env->init, env->image);
	if (keycode == LEFT)
		env->alph -= 2;
	else if (keycode == RIGHT)
		env->alph += 2;
	launcher(env);
}

void		z_up_n_down(int keycode, t_fdf *env)
{
	mlx_destroy_image(env->init, env->image);
	if (keycode == UP)
		env->z_height += 1;
	else if (keycode == DOWN)
		env->z_height -= 1;
	launcher(env);
}

int		key_function(int keycode, t_fdf *env)
{
	if (keycode == PAD_PLUS || keycode == PAD_SUB)
		set_zoom(keycode, env);
	if (keycode == LEFT || keycode == RIGHT)
		turn_around(keycode, env);
	if (keycode == UP || keycode == DOWN)
		z_up_n_down(keycode, env);
	if (keycode == HEIGHT_PLUS || keycode == HEIGHT_MINUS || keycode == \
		WIDTH_PLUS || keycode  == WIDTH_MINUS)
		{
			mlx_destroy_image(env->init, env->image);
			move_around(keycode, env);
		}
	if (keycode == ESC)
		exit(0);
	return (0);
}
