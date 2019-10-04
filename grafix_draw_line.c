/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   grafix_draw_line.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bsabre-c <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/03 18:09:07 by bsabre-c          #+#    #+#             */
/*   Updated: 2019/10/04 15:53:41 by bsabre-c         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lem_in.h"

void	init_delta(t_pos *a, t_pos *b, t_pos *delta, t_data *s)
{
	if (!a || !b || !delta || !s)
		return ;
	a->hor = OFFSET + a->hor * s->win_size.hor / s->size.hor;
	a->vert = OFFSET + a->vert * s->win_size.vert / s->size.vert;
	b->hor = OFFSET + b->hor * s->win_size.hor / s->size.hor;
	b->vert = OFFSET + b->vert * s->win_size.vert / s->size.vert;
	delta->hor = (int)ft_absi(b->hor - a->hor);
	delta->vert = (int)ft_absi(b->vert - a->vert);
}

void	logic(t_pos *a, t_pos *delta, t_pos *sign, int *error)
{
	if (!a || !delta || !sign || !error)
		return ;
	if (error[1] > -delta->vert)
	{
		error[0] -= delta->vert;
		a->hor += sign->hor;
	}
	if (error[1] < delta->hor)
	{
		error[0] += delta->hor;
		a->vert += sign->vert;
	}
}

void	draw_line(t_pos a, t_pos b, int color, t_data *s)
{
	t_pos	delta;
	t_pos	sign;
	int			error[2];

	if (!s)
		return ;
	fprint("a %d %d b %d %d\n", a.hor, a.vert, b.hor, b.vert);
	init_delta(&a, &b, &delta, s);
	//fprint("a %d %d b %d %d\n", a.hor, a.vert, b.hor, b.vert);
	sign.hor = a.hor < b.hor ? 1 : -1;
	sign.vert = a.vert < b.vert ? 1 : -1;
	error[0] = delta.hor - delta.vert;
	mlx_pixel_put(s->mlx, s->win, b.hor, b.vert, color);
	while (a.hor != b.hor || a.vert != b.vert)
	{
		mlx_pixel_put(s->mlx, s->win, a.hor, a.vert, color);
		error[1] = error[0] * 2;
		logic(&a, &delta, &sign, error);
	}
}


