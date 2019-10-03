/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   grafix.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bsabre-c <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/03 12:07:40 by bsabre-c          #+#    #+#             */
/*   Updated: 2019/10/03 16:01:18 by bsabre-c         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lemin.h"

static int	read_min_max_coord(t_room *room, t_data *s)
{
	int		hor_min;
	int		hor_max;
	int		vert_min;
	int		vert_max;

	if (!room || !s)
		return (-1);
	while (room->prev)
		reoom = room->prev;
	hor_min = room->width;
	hor_max = room->width;
	vert_min = room->height;
	vert_max = room->height;
	while (room->next)
	{
		room = room->next;
		if (hor_min > room->width)
			hor_min = room->width;
		if (hor_max < room->width)
			hor_max = room->width;
		if (vert_min > room->height)
			vert_min = room->height;
		if (vert_max < room->height)
			vert_max = room->height;
	}
}

static int	start_calc(t_room *room, t_data *s)
{
	if (!room || !s)
		return (-1);
	read_min_max_coord();
	calc_window_size();
	calc_img_size();
	
}

int			grafix(t_list **way_arr, t_list **ant_queues, t_room *room, \
		t_data *s)
{
	if (!ant_queues || !room || !way_arr || !s)
		return (-1);
	if (start_calc(room, s) < 0 || create_images(s) < 0)
		return (-1);
	mlx_loop_hook(s->mlx, loop_hook, s);
	mlx_key_hook(s->win, key_escape, s);
	mlx_mouse_hook(s->win, mouse_puse, s);
	mlx_loop(s->mlx);
	return (0);
}
