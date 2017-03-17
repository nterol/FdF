/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   key_function.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nterol <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/03/07 22:45:11 by nterol            #+#    #+#             */
/*   Updated: 2017/03/16 17:02:30 by nterol           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

int		key_function(int keycode, t_fdf *env)
{
	if (keycode == PAD_PLUS || keycode == PAD_SUB)
	{
		mlx_destroy_image(env->init, env->image);
		env->zoom += (keycode = PAD_PLUS ? 1 : -1);
		launcher(env);
	}
	if (keycode == LEFT || keycode == RIGHT)
	{
		mlx_destroy_image(env->init, env->image);
		env->alph += (keycode = LEFT ? -2 : 2);
		launcher(env);
	}
	if (keycode == UP || keycode == DOWN)
	{
		mlx_destroy_image(env->init, env->image);
		env->z_height += (keycode = UP ? 2 : -2);
		launcher(env);
	}
	if (keycode == ESC)
		exit(0);
	return (0);
}
