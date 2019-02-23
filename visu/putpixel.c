/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   putpixel.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gperilla <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/12/05 17:21:01 by gperilla          #+#    #+#             */
/*   Updated: 2018/01/29 13:14:34 by gperilla         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "filler_visu.h"

void	my_putpixel(t_visuenv *env, int x, int y, int color)
{
	int		pos;
	int8_t	mask;

	if ((x >= 0 && x <= 1919) && (y >= 0 && y <= 1079))
	{
		pos = (y * env->s_l + x * 4);
		mask = color;
		env->pix[pos] = mask;
		color = color >> 8;
		mask = color;
		env->pix[pos + 1] = mask;
		color = color >> 8;
		mask = color;
		env->pix[pos + 2] = mask;
		env->pix[pos + 3] = 0x00;
	}
}
