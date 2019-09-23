/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   read_rooms.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bsabre-c <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/09/17 14:26:38 by bsabre-c          #+#    #+#             */
/*   Updated: 2019/09/21 15:59:50 by bsabre-c         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lem_in.h"

static int		is_need_to_add_room(t_room *room, t_data *s, short *room_flag)
{
	if (!s || !(s->line) || !room_flag)
		return (-1);
	if ((s->line)[0] == '#')
	{
		if (*room_flag != FLAG_ROOM && (!ft_strncmp(s->line, "##start", 7) || \
				!ft_strncmp(s->line, "##end", 5)))
			free_exit(room, s, 1, "ERROR: double start / end commit!");
		if (!ft_strncmp(s->line, "##start", 7))
			*room_flag = FLAG_START;
		else if (!ft_strncmp(s->line, "##end", 5))
			*room_flag = FLAG_END;
		ft_strdel(&(s->line));
		return (0);
	}
	return (1);
}

static t_room	*add_room(t_room *room, t_data *s, short *room_flag)
{
	t_room		*tmp;

	if (!s)
		free_exit(room, s, 1, "ERROR: add_room empty pointer");
	if (!(tmp = new_room(&(s->line), *room_flag)))
		free_exit(room, s, 1, "ERROR: add_room empty pointer");
	*room_flag = FLAG_ROOM;
	fprint_fd(s->fd, "room was created. Name '%s' x '%d' y '%d'\n", \
			tmp->name, tmp->width, tmp->height);
	if (!room)
		return (tmp);
	while (room->next)
		room = room->next;
	room->next = tmp;
	tmp->prev = room;
	return (tmp);
}

static void		check_names(t_room *room, t_data *s)
{
	t_room		*prev;

	if (!room || !s)
		free_exit(room, s, 1, "ERROR: check_names empty pointer");
	while (room->next)
		room = room->next;
	while (room->prev)
	{
		prev = room->prev;
		while (prev)
		{
			if (!ft_strcmp(room->name, prev->name))
				free_exit(room, s, 1, "ERROR: check_names invalid name");
			prev = prev->prev;
		}
		room = room->prev;
	}
}

t_room			*read_rooms(t_data *s)
{
	t_room		*room;
	short		is_room_flag;
	short		room_flag;

	if (!s)
		free_exit(NULL, s, 1, "ERROR: read_rooms empty pointer");
	is_room_flag = 1;
	room_flag = FLAG_ROOM;
	room = NULL;
	while (is_room_flag)
	{
		if (gnl(0, &(s->line)) < 3 || \
				ft_strchr(s->line, (int)'-') || (s->line)[0] == 'L')
			is_room_flag = 0;
		else
		{
			if (is_need_to_add_room(room, s, &room_flag) == 1)
			{
				if (!(room = add_room(room, s, &room_flag)))
					free_exit(room, s, 1, "ERROR: read_rooms empty pointer");
			}
		}
	}
	check_names(room, s);
	return (get_first_last_room(room, s));
}
