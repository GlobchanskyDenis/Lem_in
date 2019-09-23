/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   temp.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bsabre-c <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/09/18 12:12:21 by bsabre-c          #+#    #+#             */
/*   Updated: 2019/09/22 19:49:59 by bsabre-c         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lem_in.h"

void		temp_print_link_names(t_room *room, t_data *s)
{
	int		i;
	t_room	*tmp;

	if (!room || !s || !room->link)
	{
		if (s)
			fprint_fd(s->fd, "\n");
		return ;
	}
	i = 0;
	while ((room->link)[i])
	{
		tmp = (room->link)[i];
		fprint_fd(s->fd, "\t|%s", tmp->name);
		i++;
	}
	fprint_fd(s->fd, "\t|\n");
}

void		temp_print_roomlist(t_room *room, t_data *s)
{
	if (!room || !s)
		return ;
	while (room->prev)
		room = room->prev;
	fprint_fd(s->fd, "===== rooms =====\n");
	while (room)
	{
		fprint_fd(s->fd, "room '%s'\tx '%d' y '%d'\t way %d\t mark %d\t", room->name, \
				room->width, room->height, room->way, room->mark);
		if (room->room_flag == FLAG_ROOM)
			fprint_fd(s->fd, "ROOM\t");
		else if (room->room_flag == FLAG_END)
			fprint_fd(s->fd, "END\t");
		else if (room->room_flag == FLAG_START)
			fprint_fd(s->fd, "START\t");
		else
			fprint_fd(s->fd, "something else");
		temp_print_link_names(room, s);
		room = room->next;
	}
	fprint_fd(s->fd, "== end of list ==\n");
}

/*
void		print_way(int way, t_room *room, t_data *s)
{
	int		marker;
	int		i;

	if (!room || !s)
		free_exit(room, s, 0, "temp_func EMPTY_PTR");
	while (room->next)
		room = room->next;
	marker = room->marker;
	fprint_fd(s->fd, "==== way %d ====\n", way);
	while (room->room_flag != FLAG_START)
	{
		fprint_fd(s->fd, "%s - ", room->name);
		i = 0;
		while (room->link && room->link[i] && room->link[i]->way != way && \
				room->link[i]->marker != room->marker - 1)
			i++;
		room = room->link[i];
		if (!room)
			break ;
	}
	if (room)
		fprint_fd(s->fd, "%s\n==== end =====\n", room->name);
}
*/
void		print_way(t_list **list, int way, t_data *s)
{
	t_list	*tmp;
	t_list	*lst;

	if (!s || !list || !(*list))
		return ;
	lst = *list;
	fprint_fd(s->fd, "=== way %d ===\n", way);
	while (lst->next)
	{
		tmp = lst;
		lst = lst->next;
		fprint_fd(s->fd, "%s - ", ((t_room *)(tmp->content))->name);
		free(tmp);
	}
	fprint_fd(s->fd, "%s\n=== end ===\n", ((t_room *)(lst->content))->name);
	free(lst);
	*list = NULL;
}
