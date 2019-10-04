/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   grafix_draw_room_web.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bsabre-c <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/04 20:39:50 by bsabre-c          #+#    #+#             */
/*   Updated: 2019/10/04 21:02:16 by bsabre-c         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lem_in.h"

static void bzero_all_not_allowed(t_room *room)
{
	short	i;

	if (!room)
		return ;
	while (room)
	{
		i = 0;
		while (room->link[i])
			room->not_allowed[i++] = 0;
		room = room->next;
	}
}

static void	set_not_allowed(t_room *room, t_room *ptr)
{
	short	i;

	if (!room || !ptr)
		return ;
	i = 0;
	while (room->link[i] && room->link[i] != ptr)
		i++;
	if (room->link[i] == ptr)
		room->not_allowed[i] = 1;
}

void	draw_room_web(t_room *room, t_data *s)
{
	t_room	*tmp;
	short	i;

	if (!room || !s)
		return ;
	while (room->prev)
		room = room->prev;
	bzero_all_not_allowed(room);
	while (room->next)
	{
		i = 0;
		while ((tmp = room->link[i]))
		{
			if (!room->not_allowed[i])
			{
				room->not_allowed[i] = 1;
				set_not_allowed(tmp, room);
				draw_line(room->pos, tmp->pos, 0x3030AF, s);
			}
			i++;
		}
		room = room->next;
	}
}
