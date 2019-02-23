/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   dessine.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gperilla <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/02/08 02:24:32 by gperilla          #+#    #+#             */
/*   Updated: 2018/02/08 02:25:13 by gperilla         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "filler_visu.h"

void	draw_grille(t_visuenv *env)
{
	int i;
	int j;

	if (!(env->img = mlx_new_image(env->ptr, 1820, 980)))
		exit(1);
	if (!(env->pix = mlx_get_data_addr(env->img, &(env->bpp), &(env->s_l),
					&(env->endian))))
		exit(0);
	i = -1;
	while (++i <= env->penv.sizey * (980 / env->penv.sizey))
	{
		j = -1;
		while (++j <= env->penv.sizex * (1820 / env->penv.sizex))
		{
			if (i == 0 || j == 0
					|| i == env->penv.sizey * (980 / env->penv.sizey)
					|| j == env->penv.sizex * (1820 / env->penv.sizex))
				my_putpixel(env, j, i, 0x00FFFFFF);
		}
	}
}

int		set_color(t_visuenv *env, int i, int x, int y)
{
	int color;

	color = 0x708090;
	if (env->actuel[i] == 'X')
		color = 0x8A2BE2;
	else if (env->actuel[i] == 'x')
		color = 0x9370DB;
	else if (env->actuel[i] == 'O')
		color = 0x0000FF00;
	else if (env->actuel[i] == 'o')
		color = 0x0098FB98;
	color = color - (x + y + 1)
		* (0xE2 / (env->penv.sizex + env->penv.sizey + 1));
	return (color);
}

void	draw_pieces(t_visuenv *env, int i, int x, int y)
{
	int k;
	int l;
	int color;

	color = set_color(env, i, x, y);
	if (env->actuel[i] != '.' && env->actuel[i] != '\n')
	{
		l = (y) * (980 / env->penv.sizey);
		while (++l < (y + 1) * (980 / env->penv.sizey) - 1)
		{
			k = x * (1820 / env->penv.sizex);
			while (++k < (x + 1) * (1820 / env->penv.sizex) - 1)
				my_putpixel(env, k, l, color);
		}
	}
}

void	affiche(t_visuenv *env)
{
	int i;
	int x;
	int y;

	draw_grille(env);
	i = -1;
	x = -1;
	y = 0;
	while (env->actuel[++i])
	{
		++x;
		draw_pieces(env, i, x, y);
		if (env->actuel[i] == '\n')
		{
			++y;
			x = -1;
		}
	}
}
