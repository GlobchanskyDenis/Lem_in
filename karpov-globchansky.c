/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   karpov-globchansky.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bsabre-c <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/09/26 13:19:03 by bsabre-c          #+#    #+#             */
/*   Updated: 2019/09/28 12:32:16 by bsabre-c         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lem_in.h"

static t_list	**make_bigger_tlist_array(t_list **src)
{
	short	size;
	short	i;
	t_list	**dst;

	if (!src)
		return (NULL);
	size = 0;
	while (src[size])
		size++;
	if (!(dst = (t_list **)malloc(sizeof(t_list *) * (size + 2))))
	{
		kill_tlist_array(src);
		return (NULL);
	}
	i = 0;
	while (i < size)
	{
		dst[i] = src[i];
		i++;
	}
	dst[i] = NULL;
	dst[i + 1] = NULL;
	free(src);
	return (dst);
}

static short	find_conflicts(t_list **way_arr, t_data *s)
{
	short	i;
	t_list	*lst;
	t_room	*room;

	if (!way_arr || !s)
		return (-1);
	/*
	i = -1;
	while (way_arr[i + 1])
		i++;
	if (i < 0 || !(lst = way_arr[i]))
		return (-1);
	while (lst)
	{
		room = lst->content;
		if (room->room_flag == FLAG_ROOM && room->way != i + 1)
			return (1);
		lst = lst->next;
	}
	*/
	i = 0;
	while (way_arr[i])
	{
		lst = way_arr[i];
		while (lst)
		{
			room = lst->content;
			if (room->room_flag == FLAG_ROOM && room->way != i + 1)
				return (1);
			lst = lst->next;
		}
		i++;
	}
	return (0);
}

t_list			**karpov_globchansky(t_room *room, t_data *s)
{
	t_list	**way_arr;
	short	i;
	t_list	*way;

	if (!room || !s)
		return (NULL);
	if (!(way_arr = (t_list **)malloc(sizeof(t_list *) * 1)))
		return (NULL);
	way_arr[0] = NULL;
	i = 0;
	while ((way = dijkstra(i + 1, room, s)))
	{
		if (!(way_arr = make_bigger_tlist_array(way_arr)))
		{
			kill_tlist(way);
			return (NULL);
		}
		way_arr[i++] = way;
		while (find_conflicts(way_arr, s) > 0)
		{
			fprint_fd(s->fd, "conflict was found!\n");
			temp_print_roomlist(room, s);
			print_all_ways(way_arr, s);
			if (conflict_solver(way_arr, s) < 0)
				fprint_fd(s->fd, "conflict was not solved\n");
		}
	}
	return (way_arr);
}
