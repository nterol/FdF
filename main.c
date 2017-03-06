/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nterol <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/02/18 14:29:00 by nterol            #+#    #+#             */
/*   Updated: 2017/02/28 11:46:28 by nterol           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

void   mlx_pixel_image(t_fdf *env, int x, int y, int color)
{
	int p;

	p = (x *(env->bpp / 8) + (y * env->size_line));
	if (p >= 0)
	{

		env->data[p] = color;
		env->data[p + 1] = color >> 8;
		env->data[p + 2] = color >> 16;
	}
}

void  line(t_fdf *env)
{
	env->dx = abs(env->x1 - env->x0);
	env->sx = (env->x0 < env->x1 ? 1 : -1);
	env->dy = abs(env->y1 - env->y0);
	env->sy = (env->y0 < env->y1 ? 1 : -1);
	env->err = (env->dx > env->dy ? env->dx : -env->dy)/2;
	while (1)
	{
		if (env->len_x < env->width && env->len_y < env->height - 1 && env->x0 && env->y0)
			mlx_pixel_image(env, env->x0, env->y0, env->color);
		if ((env->x0 == env->x1) && (env->y0 == env->y1))
			break;
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

int  f_x(int x, int y, t_fdf *env) // x = f(f_x_Z  * f_x_X * f_x_Y) // y = f(f_x_Z  * f_y_X  * f_x_Y)
{
	int i;
	int rZx;
	int rYx;
	
	rZx = (x * cos(ALPHA) * env->zoom) - (y * sin(ALPHA) * env->zoom);
	rYx = (x * cos(BETA) * env->zoom) + (env->map[y][x] * env->zoom * sin(BETA));
	i = (rZx * rYx)+ env->base_x;
	// i = ((x * env->zoom) * ((x * cos(BETA)) + (env->map[y][x] * sin(BETA))) * ((x  * cos(GAMMA)) - (y * sin(GAMMA)))) + env->base_x;

	return (i);
}

int  f_y(int x, int y, t_fdf *env)
{
	int j;
	int rZy;
	int rYy;

	rZy = ((y * cos(ALPHA) * env->zoom) / 2) + ((x * sin(ALPHA) * env->zoom) / 2) -\
	(env->map[y][x] * env->zoom / 2);
	rYy = y * env->zoom;
	j = (rZy * rYy) + env->base_y;

}


int   draw(int x, int y, t_fdf *env)
{
	if (x < env->len_x - 1)
	{
		env->x0 = f_x(x, y, env);//(x * env->zoom) - (y * env->zoom) + env->base_x;
		env->y0 = f_y(x, y, env);//(x * env->zoom / 2) + (y * env->zoom / 2) + (-env->map[y][x] * env->zoom / 2) + env->base_y;
		env->x1 = f_x(x + 1, y, env);// )((x + 1) * env->zoom) - (y * env->zoom) + env->base_x;
		env->y1 = f_y(x + 1 , y, env);//env->y0;
		line(env);
	}
	//env->x0 = f_x(x, y, env);//(x * env->zoom) - (y * env->zoom) + env->base_x;
	//env->y0 = f_y(x, y, env);//(x * env->zoom / 2) + (y * env->zoom / 2) + (-env->map[y][x] * env->zoom / 2) + env->base_y;
	if (y < env->len_y - 1)
	{
		env->x0 = f_x(x, y, env);//(x * env->zoom) - (y * env->zoom) + env->base_x;
		env->y0 = f_y(x, y, env);
		env->x1 = f_x(x, y + 1, env);// )((x + 1) * env->zoom) - (y * env->zoom) + env->base_x;
		env->y1 = f_y(x, y + 1, env);
		line(env);
	}
	return (0);
}


int   launcher(t_fdf *env)
{
	int x;
	int y;

	env->image = mlx_new_image(env->init, env->height, env->width);
	env->data = mlx_get_data_addr(env->image, &(env->bpp), &(env->size_line), &(env->endian));
	y = 0;
	while (y < env->len_y)
	{
		x = 0;
		while (x < env->len_x)
		{
			draw(x, y, env);
			x++;
		}
		y++;
	}
	mlx_put_image_to_window(env->init, env->windows, env->image, 0, 0);
	return (0);
}

int   key_function(int keycode, t_fdf *env)
{
	if (keycode == 69)
	{
		mlx_destroy_image(env->init, env->image);
		env->zoom += 1;
		launcher(env);
	}
	if (keycode == 78)
	{
		mlx_destroy_image(env->init, env->image);
		env->zoom -= 1;
		launcher(env);
	}
	if (keycode == 91)
	{
		mlx_destroy_image(env->init, env->image);
		env->alph += 5;
		launcher(env);
	}
	if (keycode == 84)
	{
		mlx_destroy_image(env->init, env->image);
		env->alph -= 5;
		launcher(env);
	}
	if (keycode == 89)
	{
		mlx_destroy_image(env->init, env->image);
		env->bet += 5;
		launcher(env);
	}
	if (keycode == 85)
	{
		mlx_destroy_image(env->init, env->image);
		env->bet -= 5;
		launcher(env);
	}
	if (keycode == 86)
	{
		mlx_destroy_image(env->init, env->image);
		env->gmm += 5;
		launcher(env);
	}
	if (keycode == 88)
	{
		mlx_destroy_image(env->init, env->image);
		env->gmm -= 5;
		launcher(env);
	}
	if (keycode == 53)
		exit(42);
	return (0);
}

void  init(t_fdf *env)
{
	env->color = 0xFF69B4;
	env->height = 2300;
	env->width = 1300;
	env->windows = mlx_new_window(env->init, env->height, env->width, "Mona Lisa");
	env->zoom = 10;
	env->base_x = (env->width - (env->len_x * env->zoom));
	env->base_y = (env->height - (env->len_y * env->zoom)) / 4;
	env->alph = 0;
	env->bet = 0;
	env->gmm = 0;
}


int   main(int ac, char **av)
{
	char  buf[BUFF_SIZE + 1];
	t_fdf *env;
	int i;
	int j;

	i = 0;
	j = 0;
	if (ac != 2)
	{
		ft_putendl("nique ta mere");
		exit(0);
	}

	env = (t_fdf *)malloc(sizeof(t_fdf));
	env->init = mlx_init();
	env->len_y = count_size_map(av[1], buf);
	map_it(env, av[1]);
	init(env);
	launcher(env);
	mlx_key_hook(env->windows, key_function, env);
	mlx_loop(env->init);
	return (0);
}
