/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map_it.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nterol <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/02/20 21:02:50 by nterol            #+#    #+#             */
/*   Updated: 2017/02/20 21:02:55 by nterol           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

void   wrong()
{
  ft_putendl("wrong map motherfucker");
  exit(0);
}

int   count_size_map(char *file, char *buf)
{
  int a;
  int ret;
  int fd;
  a = 0;

  fd = open(file, O_RDONLY);
  while ((ret = read(fd, buf, 1)) > 0)
  {
    if (ft_strchr(buf, '\n'))
      a++;
  }
  return (a);
}

int   *do_atoi(char **lel, t_fdf **env)
{
  int *lol;
  int i;

  i = 0;
  while (lel[i])
    i++;
  lol = (int *)malloc(sizeof(int) * i);
  i = 0;
  while (lel[i])
  {
    lol[i] = ft_atoi(lel[i]);
    i++;
  }
  (*env)->len_x = i;
  return (lol);
}

void map_it(t_fdf *env, char *file)
{
  char  *line;
  int   i;
  int   fd;

  fd = open(file, O_RDONLY);
  env->map = (int **)malloc(sizeof(int *) * (env->len_y + 1));
  if (!env->map)
    return;
  i = 0;
  env->len_x = 0;
  while (get_next_line(fd, &line))
  {
    env->map[i] = do_atoi(ft_strsplit(line, ' '), &env);
    free(line);
    i++;
  }
  env->map[i] = NULL;
}
