/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   filler_gets.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gperilla <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/02/07 21:25:19 by gperilla          #+#    #+#             */
/*   Updated: 2018/02/08 04:13:09 by gperilla         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "filler.h"

void	get_start_pos(t_env *env)
{
	int x;
	int y;

	if (!(env))
		exit(0);
	y = -1;
	while (++y < env->sizey)
	{
		x = -1;
		while (++x < env->sizex)
		{
			if (env->plateau[y][x] == env->self.symbol)
			{
				env->self.xstart = x;
				env->self.ystart = y;
			}
			else if (env->plateau[y][x] != '.')
			{
				env->ennemy.xstart = x;
				env->ennemy.ystart = y;
			}
		}
	}
}

void	get_size_piece(t_env *env)
{
	int		x;
	int		y;
	char	*line;

	if (!(get_next_line(0, &line) > 0))
		ca_fail();
	x = -1;
	while (line[++x] != ' ')
		if (!line[x])
			ca_fail();
	env->piece.piecey = ft_atoi(line + x);
	while (line[++x] != ' ')
		if (!line[x])
			ca_fail();
	env->piece.piecex = ft_atoi(line + x);
	if (!(env->piece.coord = malloc(sizeof(char*) * env->piece.piecey)))
		ca_fail();
	y = -1;
	while (++y < env->piece.piecey)
		if (!(env->piece.coord[y] = malloc(sizeof(char) * env->piece.piecex)))
			ca_fail();
	if (line)
		ft_memdel((void**)&line);
}

void	get_piece(t_env *env)
{
	int		x;
	int		y;
	char	*line;

	init_piece(env);
	get_size_piece(env);
	y = -1;
	while (++y < env->piece.piecey)
	{
		x = -1;
		if (!(get_next_line(0, &line) > 0))
			ca_fail();
		while (++x < env->piece.piecex && line[x])
			env->piece.coord[y][x] = line[x];
		if (x != env->piece.piecex)
			ca_fail();
		if (line)
			ft_memdel((void**)&line);
	}
}

void	get_min_max_pos(t_env *env)
{
	int x;
	int y;

	env->self.xmin = INT_MAX;
	env->self.xmax = 0;
	env->self.ymin = INT_MAX;
	env->self.xmax = 0;
	env->ennemy.xmin = INT_MAX;
	env->ennemy.xmax = 0;
	env->ennemy.ymin = INT_MAX;
	env->ennemy.ymax = 0;
	y = -1;
	while (++y < env->sizey)
	{
		x = -1;
		while (++x < env->sizex)
		{
			dispatch_min_max(env, x, y);
		}
	}
}

int		get_distance(t_env *env, int x, int y)
{
	int score;
	int far;

	score = 0;
	far = 0;
	while (!score && far < ft_max(env->sizex, env->sizey))
	{
		far++;
		score = i_can_go_the_distance(env, x, y, far);
	}
	return (score);
}
