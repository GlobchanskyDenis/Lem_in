/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   grafix.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bsabre-c <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/03 12:07:40 by bsabre-c          #+#    #+#             */
/*   Updated: 2019/10/03 20:37:35 by bsabre-c         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lem_in.h"

static int	find_min_max_position(t_room *room, t_data *s)
{
	if (!room || !s)
		return (-1);
	while (room->prev)
		room = room->prev;
	s->min_pos.hor = room->pos.hor;
	s->max_pos.hor = room->pos.hor;
	s->min_pos.vert = room->pos.vert;
	s->max_pos.vert = room->pos.vert;
	while (room->next)
	{
		room = room->next;
		if (s->min_pos.hor > room->pos.hor)
			s->min_pos.hor = room->pos.hor;
		if (s->max_pos.hor < room->pos.hor)
			s->max_pos.hor = room->pos.hor;
		if (s->min_pos.vert > room->pos.vert)
			s->min_pos.vert = room->pos.vert;
		if (s->max_pos.vert < room->pos.vert)
			s->max_pos.vert = room->pos.vert;
	}
	return (0);
}

static int	start_calc(t_room *room, t_data *s)
{
	if (!room || !s)
		return (-1);
	if (find_min_max_position(room, s) < 0)
		return (-1);
	//calc_window_size
	s->size.hor = (int)ft_absi(s->max_pos.hor - s->min_pos.hor);
	s->size.vert = (int)ft_absi(s->max_pos.vert - s->min_pos.vert);
	s->win_size.hor = WIN_SIZE_HOR - 2 * OFFSET;
	s->win_size.vert = WIN_SIZE_VERT - 2 * OFFSET;
	if (!(s->mlx = mlx_init()) || !(s->win = mlx_new_window(s->mlx, \
					WIN_SIZE_HOR, WIN_SIZE_VERT, "lem-in by bsabre-c")))
		return (-1);
	return (0);
}

int			create_images(t_data *s)
{
	if (!s)
		return (-1);
	return (0);
}

int			grafix(t_list **way_arr, t_list **ant_queues, t_room *room, \
		t_data *s)
{
	t_room	*r1;
	t_room	*r2;

	if (!ant_queues || !room || !way_arr || !s)
		return (-1);
	fprint_fd(s->fd, "\n\n===== GRAFIX START =====\n");
	if (start_calc(room, s) < 0 || create_images(s) < 0)
		return (-1);
	s->is_pause = 1;
	r1 = way_arr[0]->content;
	r2 = way_arr[0]->next->content;
	draw_line(r1->pos, r2->pos, 0x808080, s);
	mlx_loop_hook(s->mlx, loop_hook, s);
	mlx_key_hook(s->win, key_escape, s);
	mlx_mouse_hook(s->win, mouse_pause, s);
	mlx_loop(s->mlx);
	return (0);
}
