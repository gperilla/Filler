/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   filler_inits.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gperilla <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/02/07 21:24:59 by gperilla          #+#    #+#             */
/*   Updated: 2018/02/07 21:47:16 by gperilla         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "filler.h"

void	ca_fail(void)
{
	ft_printf("-1 -1\n");
	exit(0);
}

void	init_all(t_env *env)
{
	if (!(env))
		exit(0);
	env->sizex = 0;
	env->sizey = 0;
	env->plateau = NULL;
	env->piece.coord = NULL;
	env->piece.piecex = 0;
	env->piece.piecey = 0;
	env->self.xmin = INT_MAX;
	env->self.xmax = 0;
	env->self.ymin = INT_MAX;
	env->self.ymax = 0;
	env->self.xstart = -1;
	env->self.ystart = -1;
	env->self.symbol = '\0';
	env->ennemy.xmin = INT_MAX;
	env->ennemy.xmax = 0;
	env->ennemy.ymin = INT_MAX;
	env->ennemy.ymax = 0;
	env->ennemy.xstart = -1;
	env->ennemy.ystart = -1;
	env->ennemy.symbol = '\0';
}

void	init_plateau(t_env *env)
{
	int i;
	int j;

	if (!(env))
		exit(0);
	if (!(env->plateau = malloc(sizeof(char*) * env->sizey + 1)))
		ca_fail();
	i = -1;
	while (++i < env->sizey)
		if (!(env->plateau[i] = malloc(sizeof(char) * env->sizex + 1)))
			ca_fail();
	j = -1;
	while (++j < env->sizey)
	{
		i = -1;
		while (++i <= env->sizex)
		{
			if (i != env->sizex)
				env->plateau[j][i] = '.';
			else
				env->plateau[j][i] = '\0';
		}
	}
	env->plateau[j] = 0;
}

void	init_piece(t_env *env)
{
	int y;

	if (env->piece.coord)
	{
		y = -1;
		while (++y < env->piece.piecey)
		{
			if (env->piece.coord[y])
				ft_memdel((void**)&env->piece.coord[y]);
		}
		if (env->piece.coord)
			ft_memdel((void**)&env->piece.coord);
	}
	env->piece.coord = NULL;
	env->piece.piecey = 0;
	env->piece.piecey = 0;
}

void	get_symbol(t_env *env)
{
	char *line;

	if (!(get_next_line(0, &line) > 0))
		ca_fail();
	env->self.symbol = 'O';
	env->ennemy.symbol = 'X';
	if (line[10] && line[10] == '2')
	{
		env->self.symbol = 'X';
		env->ennemy.symbol = 'O';
	}
	if (line)
		ft_memdel((void**)&line);
}
