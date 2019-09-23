/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   make_linkage.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bsabre-c <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/09/18 12:44:51 by bsabre-c          #+#    #+#             */
/*   Updated: 2019/09/21 15:51:08 by bsabre-c         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lem_in.h"

static t_room	*find_room(t_room *lst, char *name, t_data *s)
{
	t_room		*room;

	if (!lst || !name || !s)
		return (NULL);
	room = lst;
	while (room->prev && ft_strcmp(name, room->name))
		room = room->prev;
	if (!ft_strcmp(room->name, name))
		return (room);
	room = lst;
	while (room->next && ft_strcmp(name, room->name))
		room = room->next;
	if (!ft_strcmp(room->name, name))
		return (room);
	return (NULL);
}

static int		link_isnt_exists(t_room *room1, t_room *room2, t_data *s)
{
	int			i;

	if (!room1 || !room2 || !s)
		return (-1);
	fprint_fd(s->fd, "check for existing link\n");
	i = 0;
	while (room1->link && room1->link[i])
	{
		if (!ft_strcmp(room1->link[i]->name, room2->name))
			return (0);
		i++;
	}
	i = 0;
	while (room2->link && room2->link[i])
	{
		if (!ft_strcmp(room2->link[i]->name, room1->name))
			return (0);
		i++;
	}
	return (1);
}

void			make_linkage(t_room *lst, t_data *s)
{
	char		**arr;
	t_room		*room1;
	t_room		*room2;

	if (!lst || !s)
		free_exit(lst, s, 1, "ERROR: make_linkage empty pointer");
	while (s->line && ft_strlen(s->line) > 2 && ft_strchr(s->line, (int)'-'))
	{
		if (!(arr = ft_strsplit(s->line, '-')) || count_words(arr) != 2)
			free_exit(lst, s, 1, "ERROR: make_linkage empty pointer");
		if (!(room1 = find_room(lst, arr[0], s)) || \
				!(room2 = find_room(lst, arr[1], s)))
			free_exit(lst, s, 1, "ERROR: make_linkage empty pointer");
		if (link_isnt_exists(room1, room2, s) > 0)
		{
			room1->link = make_bigger_array_and_fill(room1->link, room2);
			room2->link = make_bigger_array_and_fill(room2->link, room1);
		}
		ft_strdel(&(s->line));
		ft_strdel(&(arr[0]));
		ft_strdel(&(arr[1]));
		free(arr);
		gnl(0, &(s->line));
	}
}
