/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nterol <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/03/07 21:58:30 by nterol            #+#    #+#             */
/*   Updated: 2017/03/16 17:07:10 by nterol           ###   ########.fr       */
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
	env->windows = mlx_new_window(env->init, env->width, env->height, TITLE);
	env->zoom = 1;
	while ((env->zoom * env->len_x * env->len_y) < (env->width * env->height)\
			/ env->zoom / 4)
		env->zoom++;
	env->base_x = (env->width - (env->len_x * env->len_y)) / 2.5;
	env->base_y = (env->height / 2) - (env->len_x * env->len_y);
	env->alph = 15;
	env->z_height = 5;
}

int			main(int ac, char **av)
{
	ft_putendl("start");
	int		i;
	int		j;
	char	buf[BUFF_SIZE + 1];
	t_fdf	*env;

	i = 0;
	j = 0;
	if (ac != 2)
		wrong();
	env = (t_fdf *)malloc(sizeof(t_fdf));
	env->init = mlx_init();
	env->len_y = count_size_map(av[1], buf);
	ft_putendl("1");
	map_it(env, av[1]);
	ft_putendl("2");
	init(env);
	ft_putendl("3");
	launcher(env);
	ft_putendl("4");
	mlx_key_hook(env->windows, key_function, env);
	mlx_loop(env->init);
	return (0);
}
