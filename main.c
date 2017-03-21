/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nterol <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/03/07 21:58:30 by nterol            #+#    #+#             */
/*   Updated: 2017/03/16 17:52:46 by nterol           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

int			draw(int x, int y, t_fdf *env)
{
	if (x < env->len_x - 1)
	{
		color_change(x, y, env);
		env->x0 = f_x(x, y, env);
		env->y0 = f_y(x, y, env);
		env->x1 = f_x(x + 1, y, env);
		env->y1 = f_y(x + 1, y, env);
		line(env);
	}
	if (y < env->len_y - 1)
	{
		color_change(x, y, env);
		env->x0 = f_x(x, y, env);
		env->y0 = f_y(x, y, env);
		env->x1 = f_x(x, y + 1, env);
		env->y1 = f_y(x, y + 1, env);
		line(env);
	}
	return (0);
}

int			launcher(t_fdf *env)
{
	int		x;
	int		y;

	env->base_x = env->width / env->width_control;
	env->base_y = env->height / env->height_control;
	env->image = mlx_new_image(env->init, env->width, env->height);
	env->data = mlx_get_data_addr(env->image, &(env->bpp), &(env->size_line),\
			&(env->endian));
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

void		init(t_fdf *env)
{
	env->height = HEIGHT;
	env->width = WIDTH;
	env->width_control = 4;
	env->height_control = 4;
	env->windows = mlx_new_window(env->init, env->width, env->height, TITLE);
	env->zoom = 1;
	 while ((env->zoom * env->len_x * env->len_y) < (env->width * env->height)\
	 		/ env->zoom / 4)
	 	env->zoom++;
	ft_putnbr(env->zoom);
	ft_putnbr(env->zoom * env->len_x * env->len_y);
	ft_putnbr((env->width * env->height) / env->zoom / 4);
	env->alph = 15;
	env->z_height = 5;
}

int			main(int ac, char **av)
{
	char	buf[BUFF_SIZE + 1];
	t_fdf	*env;

	if (ac != 2)
		wrong();
	env = (t_fdf *)malloc(sizeof(t_fdf));
	env->init = mlx_init();
	env->len_y = count_size_map(av[1], buf);
	map_it(env, av[1]);
	ft_putnbr(env->len_x);
	ft_putendl(":");
	ft_putnbr(env->len_y);
	ft_putendl("");
	init(env);
	launcher(env);
	mlx_key_hook(env->windows, key_function, env);
	mlx_loop(env->init);
	return (0);
}
