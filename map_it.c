/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map_it.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nterol <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/03/07 22:28:47 by nterol            #+#    #+#             */
/*   Updated: 2017/03/16 17:28:47 by nterol           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

void		wrong(void)
{
	ft_putendl("usage : ./fdf heregoesyourmap you fucking cunt");
	exit(0);
}

int			count_size_map(char *file, char *buf)
{
	int		a;
	int		ret;
	int		fd;

	a = 0;
	fd = open(file, O_RDONLY);
	while ((ret = read(fd, buf, BUFF_SIZE)) > 0)
	{
		if (ft_strchr(buf, '\n'))
			a++;
	}
	return (a);
}

int			*does_atoi(char **lel, t_fdf **env)
{
	ft_putendl("does atoi");
	int		*lol;
	int		i;

	i = 0;
	while (lel[i])
		i++;
	lol = (int *)malloc(sizeof(int) * i);
	i = 0;
	while (lel[i])
	{
		lol[i] = ft_atoi(lel[i]);
		lol[i] > (*env)->z_max ? (*env)->z_max = lol[i] : 0;
		lol[i] < (*env)->z_min ? (*env)->z_min = lol[i] : 0;
		i++;
	}
	(*env)->len_x = i;
	return (lol);
}

void		map_it(t_fdf *env, char *file)
{
	ft_putendl("start map_it");
	char	*line;
	int		i;
	int		fd;

	fd = open(file, O_RDONLY);
	env->map = (int **)malloc(sizeof(int *) * (env->len_y + 1));
	if (!env->map)
		return ;
	i = 0;
	env->len_x = 0;
	env->z_max = 0;
	env->z_min = 0;
	while (get_next_line(fd, &line))
	{
		//ft_putendl("iteration : ");
		//ft_putnbr(i);
		//ft_putendl("");
		env->map[i] = does_atoi(ft_strsplit(line, ' '), &env);
		i++;
		//free(line);
	}
	env->map[i] = NULL;
}
