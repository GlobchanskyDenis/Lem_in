/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   grafix_draw_line.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bsabre-c <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/03 18:09:07 by bsabre-c          #+#    #+#             */
/*   Updated: 2019/10/03 21:06:31 by bsabre-c         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lem_in.h"

https://github.com/VBrazhnik/FdF/blob/master/fdf/sources/draw.c

static void	put_pixel(t_fdf *fdf, int x, int y, int color)
{
	int		i;

	if (x >= MENU_WIDTH && x < WIDTH && y >= 0 && y < HEIGHT)
	{
		i = (x * fdf->bits_per_pixel / 8) + (y * fdf->size_line);
		fdf->data_addr[i] = color;
		fdf->data_addr[++i] = color >> 8;
		fdf->data_addr[++i] = color >> 16;
	}
}

static void	draw_line(t_pos a, t_pos b, t_fdf *fdf)
{
	t_pos	delta;
	t_pos	sign;
	t_pos	cur;
	int		error[2];

	delta.hor = (int)ft_absi(b.hor - a.hor);
	delta.vert = (int)ft_absi(b.vert - a.vert);
	sign.hor = a.hor < b.hor ? 1 : -1;
	sign.vert = a.vert < b.vert ? 1 : -1;
	error[0] = delta.hor - delta.vert;
	cur = f;
	while (cur.hor != b.hor || cur.vert != b.vert)
	{
		//put_pixel(fdf, cur.x, cur.y, get_color(cur, a, b, delta));
		if ((error[1] = error[0] * 2) > -delta.vert)
		{
			error[0] -= delta.vert;
			cur.hor += sign.hor;
		}
		if (error[1] < delta.hor)
		{
			error[0] += delta.hor;
			cur.vert += sign.vert;
		}
	}
}

/*
int		draw_line(t_pos begin, t_pos end, int color, t_data *s)
{
	t_pos	a;
	t_pos	b;
	t_pos	i;
	t_pos	size;
	t_pos	direction;
	int		count;

	if (!s)
		return (-1);
	fprint("begin hor %d vert %d\n", begin.hor, begin.vert);
	fprint("end hor %d vert %d\n", end.hor, end.vert);
	a.hor = OFFSET + begin.hor * (s->win_size.hor / s->size.hor);
	a.vert = OFFSET + begin.vert * (s->win_size.vert / s->size.vert);
	b.hor = OFFSET + end.hor * (s->win_size.hor / s->size.hor);
	b.vert = OFFSET + end.vert * (s->win_size.vert / s->size.vert);
	size.hor = (int)ft_absi(a.hor - b.hor);
	size.vert = (int)ft_absi(a.vert - b.vert);
	fprint("a hor %d vert %d\n", a.hor, a.vert);
	fprint("b hor %d vert %d\n", b.hor, b.vert);
	if (a.hor >= b.hor)
		direction.hor = 0;
	else
		direction.hor = 1;
	if (a.vert >= b.vert)
		direction.vert = 0;
	else
		direction.vert = 1;
	i = a;
	count = 0;
	while (i.hor != b.hor)
	{
		i.vert = a.vert;
		while (i.vert != b.vert)
		{
			if (size.vert - )
			//if ((i.vert * 1) / (int)ft_absi((b.vert - a.vert) * 1) == \
			//		(i.hor * 1) / (int)ft_absi((b.hor - a.hor) * 1))
			{
				mlx_pixel_put(s->mlx, s->win, i.hor, i.vert, color);
				count++;
			}
			if (direction.vert)
				i.vert++;
			else
				i.vert--;
		}
		if (direction.hor)
			i.hor++;
		else
			i.hor--;
	}
	fprint("count = %d\n", count);
	return (0);
}
*/
