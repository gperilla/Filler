/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fvisu_norm.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gperilla <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/02/08 02:31:43 by gperilla          #+#    #+#             */
/*   Updated: 2018/02/08 03:09:02 by gperilla         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "filler_visu.h"

int		verif_ending(t_visuenv *env, char *line)
{
	if (fork() == 0)
	{
		if (env->ac == 1)
			system("killall afplay; afplay ../sound/fanfare.mp3");
		else
			system("killall afplay; afplay ../sound/coromaster.mp3");
		exit(0);
	}
	ft_printf("\n\nscore %s = %d\n", env->p1, ft_atoi(line + 10));
	if (line)
		ft_memdel((void**)&line);
	if (!(get_next_line(0, &line) > 0))
		exit(0);
	ft_printf("score %s = %d\n\n\n", env->p2, ft_atoi(line + 10));
	if (line)
		ft_memdel((void**)&line);
	return (0);
}

void	get_taille_plateau(t_visuenv *env, char *line)
{
	int x;

	if (!env->penv.sizex || !env->penv.sizey)
	{
		x = -1;
		while (line[++x] != ' ')
			if (!line[x])
				exit(1);
		env->penv.sizey = ft_atoi(line + x);
		while (line[++x] != ' ')
			if (!line[x])
				exit(1);
		env->penv.sizex = ft_atoi(line + x);
	}
}

void	skip_piece(void)
{
	char *line;

	if (get_next_line(0, &line) <= 0)
		exit(1);
	free(line);
	if (get_next_line(0, &line) <= 0)
		exit(1);
	while (line[0] != '<' && line[0] != '=')
	{
		free(line);
		if (get_next_line(0, &line) <= 0)
			exit(1);
	}
	free(line);
}

void	get_turn(t_visuenv *env)
{
	char	*line;
	int		x;

	x = -1;
	if (env->actuel)
		ft_memdel((void**)&(env->actuel));
	env->actuel = ft_strdup("");
	while (++x < env->penv.sizey)
	{
		if (get_next_line(0, &line) <= 0)
			exit(1);
		env->actuel = ft_strjoin_free(env->actuel, line + 4, 1);
		env->actuel = ft_strjoin_free(env->actuel, "\n", 1);
		free(line);
	}
	++env->nbturn;
}

int		show_next_step(t_visuenv *env)
{
	char *line;

	if (get_next_line(0, &line) <= 0)
		return (0);
	if (line && line[0] == '=')
		return (verif_ending(env, line));
	while (ft_strncmp(line, "Plateau", 7) != 0)
	{
		free(line);
		if (get_next_line(0, &line) <= 0)
			return (0);
	}
	get_taille_plateau(env, line);
	if (line)
		ft_memdel((void**)&line);
	if (get_next_line(0, &line) <= 0)
		exit(1);
	free(line);
	get_turn(env);
	affiche(env);
	skip_piece();
	mlx_put_image_to_window(env->ptr, env->win, env->img, 50, 50);
	mlx_destroy_image(env->ptr, env->img);
	return (1);
}
