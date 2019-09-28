/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   errors.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bsabre-c <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/09/18 12:09:16 by bsabre-c          #+#    #+#             */
/*   Updated: 2019/09/26 14:50:43 by bsabre-c         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lem_in.h"

void		kill_tlist(t_list *lst)
{
	t_list		*tmp;

	if (!lst)
		return ;
	while (lst)
	{
		tmp = lst;
		lst = lst->next;
		free(tmp);
	}
}

void		kill_tlist_array(t_list **arr)
{
	short		i;

	if (!arr)
		return ;
	i = 0;
	while (arr[i])
	{
		kill_tlist(arr[i]);
		i++;
	}
	free(arr);
}

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
			if (tmp_room->not_allowed)
				free(tmp_room->not_allowed);
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
