/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   filler_msc.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gperilla <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/02/07 21:25:09 by gperilla          #+#    #+#             */
/*   Updated: 2018/02/08 04:11:45 by gperilla         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "filler.h"

int		ccheck_pos(t_env *env, int yf, int xf, int y)
{
	int x;
	int cpt;

	cpt = 0;
	x = -1;
	while (++x < env->piece.piecex)
	{
		if (env->piece.coord[y][x] == '*'
				&& (x + xf >= env->sizex || y + yf >= env->sizey
					|| x + xf < 0 || y + yf < 0))
			return (-1);
		if (env->piece.coord[y][x] == '*'
				&& env->plateau[yf + y][xf + x] != '.')
		{
			if (env->plateau[yf + y][xf + x] == env->self.symbol
					|| env->plateau[yf + y][xf + x] == env->self.symbol + ' ')
				++cpt;
			else
				return (-1);
		}
	}
	return (cpt);
}

int		check_pos(t_env *env, int yf, int xf)
{
	int y;
	int com;

	com = 0;
	y = -1;
	while (++y < env->piece.piecey)
	{
		if (ccheck_pos(env, yf, xf, y) < 0)
			return (0);
		com += ccheck_pos(env, yf, xf, y);
	}
	if (com == 1)
		return (1);
	return (0);
}

int		i_can_go_the_distance(t_env *env, int x, int y, int far)
{
	int i;
	int j;

	i = far;
	j = 0;
	while (i >= 0)
	{
		if (y + i < env->sizey && x + j < env->sizex
				&& env->plateau[y + i][x + j] == env->ennemy.symbol)
			return (far);
		else if (y - i >= 0 && x + j < env->sizex
				&& env->plateau[y - i][x + j] == env->ennemy.symbol)
			return (far);
		else if (y - i >= 0 && x - j >= 0
				&& env->plateau[y - i][x - j] == env->ennemy.symbol)
			return (far);
		else if (y + i < env->sizey && x - j >= 0
				&& env->plateau[y + i][x - j] == env->ennemy.symbol)
			return (far);
		i--;
		j++;
	}
	return (0);
}

int		defense_algo(t_env *env, int x, int y)
{
	int score;
	int up;
	int left;

	score = 0;
	if (ft_min(env->sizey - 1, env->ennemy.ymax + 5) > env->self.ymax)
		up = env->self.ymax - ft_min(env->sizey - 1, env->ennemy.ymax + 5);
	if (ft_max(0, env->ennemy.ymin - 5) < env->self.ymin)
		up = env->self.ymin - ft_max(0, env->ennemy.ymin - 5);
	if (ft_max(0, env->ennemy.xmin - 5) < env->self.xmin)
		left = env->self.xmin - ft_max(0, env->ennemy.xmin - 5);
	if (ft_min(env->sizex - 1, env->ennemy.xmax + 5) > env->self.xmax)
		left = env->self.xmax - ft_min(env->sizex - 1, env->ennemy.xmax + 5);
	if (up > 0)
		score += (env->sizey - y) * up;
	else if (up < 0)
		score += y * ft_abs(up);
	if (left > 0)
		score += (env->sizex - x) * ft_abs(left);
	else if (left < 0)
		score += x * ft_abs(left);
	return (score);
}

int		calc_score(t_env *env, int x, int y)
{
	int yp;
	int xp;
	int score;

	if ((ft_max(0, env->ennemy.ymin - 5) < env->self.ymin
		|| ft_min(env->sizey - 1, env->ennemy.ymax + 5) > env->self.ymax)
		|| (ft_max(0, env->ennemy.xmin - 5) < env->self.xmin
		|| ft_min(env->sizex - 1, env->ennemy.xmax + 5) > env->self.xmax))
		return (defense_algo(env, x, y));
	score = 0;
	yp = -1;
	while (++yp < env->piece.piecey)
	{
		xp = -1;
		while (++xp < env->piece.piecex)
		{
			if (env->piece.coord[yp][xp] == '*')
			{
				score -= get_distance(env, x + xp, y + yp);
			}
		}
	}
	return (score);
}
