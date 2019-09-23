/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   errors.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bsabre-c <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/09/18 12:09:16 by bsabre-c          #+#    #+#             */
/*   Updated: 2019/09/19 09:43:11 by bsabre-c         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lem_in.h"

void		kill_room(t_room **room)
{
	if (room && *room)
	{
		if ((*room)->name)
			free((*room)->name);
		if ((*room)->link)
			free((*room)->link);
		free(*room);
		*room = NULL;
	}
}

static void	kill_roomlist(t_room *room)
{
	t_room		*tmp_room;

	if (room)
	{
		while (room->prev)
			room = room->prev;
		while (room)
		{
			tmp_room = room;
			room = room->next;
			kill_room(&tmp_room);
		}
	}
}

void		free_exit(t_room *room, t_data *s, int need_to_read_all, \
		char *message)
{
	kill_roomlist(room);
	if (need_to_read_all)
	{
		if (s->line)
			ft_strdel(&(s->line));
		while (gnl(0, &(s->line)) > 0)
			ft_strdel(&(s->line));
	}
	if (s)
	{
		if (s->line)
			ft_strdel(&(s->line));
		free(s);
	}
	if (message)
		fprint("%s\n", message);
	exit(0);
}
