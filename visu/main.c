/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gperilla <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/01/27 17:14:05 by gperilla          #+#    #+#             */
/*   Updated: 2018/02/08 03:08:44 by gperilla         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "filler_visu.h"

int		key_events(int key)
{
	if (key == 53)
	{
		system("killall afplay");
		exit(0);
	}
	return (1);
}

void	play_music(int argc)
{
	if (argc == 1)
		system("afplay ../sound/music.mp3");
	else
		system("afplay ../sound/coro.mp3");
	exit(0);
}

void	first_steps(t_visuenv *env)
{
	int		i;
	char	*line;

	i = -1;
	while (++i < 5)
	{
		get_next_line(0, &line);
		free(line);
	}
	if ((env->ptr = mlx_init()) == NULL)
		exit(1);
	if ((env->win = mlx_new_window(env->ptr, 1920, 1080, "Test"))
			== NULL)
		exit(1);
}

void	get_names(t_visuenv *env)
{
	char *line;

	if (get_next_line(0, &line) <= 0)
		exit(1);
	env->p1 = ft_strdup(line + 9);
	free(line);
	if (get_next_line(0, &line) <= 0)
		exit(1);
	free(line);
	if (get_next_line(0, &line) <= 0)
		exit(1);
	env->p2 = ft_strdup(line + 9);
	free(line);
	if (get_next_line(0, &line) <= 0)
		exit(1);
	free(line);
}

int		main(int argc, char **argv)
{
	t_visuenv	env;

	(void)argv;
	env.ac = argc;
	if (fork() == 0)
		play_music(argc);
	first_steps(&env);
	get_names(&env);
	env.penv.sizex = 0;
	env.penv.sizey = 0;
	env.nbturn = 0;
	mlx_loop_hook(env.ptr, show_next_step, &env);
	mlx_key_hook(env.win, key_events, &env);
	mlx_loop(env.ptr);
	return (0);
}
