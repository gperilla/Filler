/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   filler_visu.h                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gperilla <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/01/27 17:46:06 by gperilla          #+#    #+#             */
/*   Updated: 2018/02/08 02:41:57 by gperilla         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FILLER_VISU_H
# define FILLER_VISU_H

# include "../filler.h"
# include "minilibx_macos/mlx.h"

typedef struct	s_visuenv
{
	void	*ptr;
	void	*win;
	void	*img;
	char	*pix;
	int		bpp;
	int		s_l;
	int		endian;
	int		nbturn;
	t_env	penv;
	char	*p1;
	char	*p2;
	int		ac;
	char	*actuel;
}				t_visuenv;

void			my_putpixel(t_visuenv *env, int x, int y, int color);

void			affiche(t_visuenv *env);

int				show_next_step(t_visuenv *env);

#endif
