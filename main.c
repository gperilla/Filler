/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gperilla <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/01/22 11:47:59 by gperilla          #+#    #+#             */
/*   Updated: 2018/02/08 04:10:08 by gperilla         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "filler.h"

void	dispatch_min_max(t_env *env, int x, int y)
{
	if (env->plateau[y][x] == env->self.symbol
			|| env->plateau[y][x] == env->self.symbol + ' ')
	{
		env->self.xmax = ft_max(env->self.xmax, x);
		env->self.xmin = ft_min(env->self.xmin, x);
		env->self.ymax = ft_max(env->self.ymax, y);
		env->self.ymin = ft_min(env->self.ymin, y);
	}
	if (env->plateau[y][x] == env->ennemy.symbol
			|| env->plateau[y][x] == env->ennemy.symbol + ' ')
	{
		env->ennemy.xmax = ft_max(env->ennemy.xmax, x);
		env->ennemy.xmin = ft_min(env->ennemy.xmin, x);
		env->ennemy.ymax = ft_max(env->ennemy.ymax, y);
		env->ennemy.ymin = ft_min(env->ennemy.ymin, y);
	}
}

void	insert_resolv_algorithm_here(t_env *env)
{
	int x;
	int y;
	int xans;
	int yans;
	int best;

	xans = 0;
	yans = 0;
	best = INT_MIN;
	get_min_max_pos(env);
	y = 0 - env->piece.piecey;
	while (++y < env->sizey)
	{
		x = 0 - env->piece.piecex;
		while (++x < env->sizex)
			if (check_pos(env, y, x) == 1)
				if (calc_score(env, x, y) > best)
				{
					best = calc_score(env, x, y);
					xans = x;
					yans = y;
				}
	}
	ft_printf("%d %d\n", yans, xans);
}

void	get_plateau(t_env *env, char *line)
{
	int x;

	if (!env->sizex || !env->sizey)
	{
		x = -1;
		while (line[++x] != ' ')
			if (!line[x])
				ca_fail();
		env->sizey = ft_atoi(line + x);
		while (line[++x] != ' ')
			if (!line[x])
				ca_fail();
		env->sizex = ft_atoi(line + x);
	}
	if (!(env->plateau))
		init_plateau(env);
}

void	status_plateau(t_env *env)
{
	int		y;
	int		x;
	char	*line;

	y = -1;
	while (++y < env->sizey)
	{
		if (!(get_next_line(0, &line) > 0))
			ca_fail();
		x = -1;
		while (++x < env->sizex)
		{
			if (!line[x + 4])
				ca_fail();
			env->plateau[y][x] = line[x + 4];
		}
		if (line)
			ft_memdel((void**)&line);
	}
}

int		main(void)
{
	char	*line;
	t_env	*env;

	if (!(env = malloc(sizeof(t_env))))
		ca_fail();
	init_all(env);
	get_symbol(env);
	while (get_next_line(0, &line) > 0)
	{
		get_plateau(env, line);
		if (line)
			ft_memdel((void**)&line);
		if (!(get_next_line(0, &line) > 0))
			ca_fail();
		if (line)
			ft_memdel((void**)&line);
		status_plateau(env);
		if (env->self.xstart < 0)
			get_start_pos(env);
		get_piece(env);
		insert_resolv_algorithm_here(env);
	}
	return (0);
}
