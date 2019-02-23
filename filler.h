/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   filler.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gperilla <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/01/22 11:38:27 by gperilla          #+#    #+#             */
/*   Updated: 2018/02/08 02:42:51 by gperilla         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FILLER_H
# define FILLER_H

# include "libft/libft.h"

typedef struct	s_player
{
	char		symbol;
	int			xmin;
	int			xmax;
	int			ymin;
	int			ymax;
	int			xstart;
	int			ystart;
}				t_player;

typedef struct	s_piece
{
	char		**coord;
	int			piecex;
	int			piecey;
}				t_piece;

typedef struct	s_env
{
	int			sizex;
	int			sizey;
	char		**plateau;
	t_piece		piece;
	t_player	self;
	t_player	ennemy;
}				t_env;

void			ca_fail(void);

void			init_all(t_env *env);

void			init_plateau(t_env *env);

void			init_plateau(t_env *env);

void			init_piece(t_env *env);

void			get_symbol(t_env *env);

void			dispatch_min_max(t_env *env, int x, int y);

int				i_can_go_the_distance(t_env *env, int x, int y, int far);

void			get_start_pos(t_env *env);

void			get_size_piece(t_env *env);

void			get_piece(t_env *env);

void			get_min_max_pos(t_env *env);

int				get_distance(t_env *env, int x, int y);

int				ccheck_pos(t_env *env, int yf, int xf, int y);

int				check_pos(t_env *env, int yf, int xf);

int				i_can_go_the_distance(t_env *env, int x, int y, int far);

int				defense_algo(t_env *env, int x, int y);

int				calc_score(t_env *env, int x, int y);

#endif
