/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   dijkstra.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bsabre-c <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/09/21 17:07:49 by bsabre-c          #+#    #+#             */
/*   Updated: 2019/09/23 12:59:52 by bsabre-c         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lem_in.h"

static t_list	*init_algorithm(t_room *room, t_data *s)
{
	t_list	*dst;

	if (!room || !s)
		free_exit(room, s, 0, "ERROR: init_algorithm empty ptr");
	while (room->next)
		room = room->next;
	while (room->prev)
	{
		room->mark = 0;
		room->flag = 0;
		room = room->prev;
	}
	room->mark = 1;
	room->flag = 1;
	dst = ft_lstnew_fag(room, 0);
	return (dst);
}

static int		mark_links_till_end(t_list *queue, t_room *room_lst, t_data *s)
{
	int		i;
	t_room	*room;

	if (!queue || !room_lst || !s)
	{
		ft_lstdel_fag(&queue);
		free_exit(room_lst, s, 0, "ERROR: mark_links.. empty ptr");
	}
	i = 0;
	room = queue->content;
	while (room->link && room->link[i])
	{
		if (room->link[i]->mark == 0 || room->link[i]->mark > room->mark)
		{
			queue_push_back(queue, room->link[i], s);
			room->link[i]->mark = room->mark + 1;
		}
		if (room->link[i]->room_flag == FLAG_END)
			return (1);
		i++;
	}
	room->flag = 1;
	return (0);
}

static t_list	*make_way_lst(int way, t_room *room, t_data *s)
{
	t_list	*lst;
	t_list	*tmp;
	int		i;

	if (!room || !s)
		free_exit(room, s, 0, "ERROR: make_way_lst empty ptr");
	while (room->next)
		room = room->next;
	if (!(lst = ft_lstnew_fag(room, 0)))
		free_exit(room, s, 0, "malloc error");
	while (room->room_flag != FLAG_START)
	{
		i = 0;
		while (room->link && room->link[i]->mark != room->mark - 1)
			i++;
		room = room->link[i];
		room->way = way;
		if (!(tmp = ft_lstnew_fag(room, lst->content_size + 1)))
		{
			ft_lstdel_fag(&lst);
			free_exit(room, s, 0, "malloc error");
		}
		tmp->next = lst;
		lst = tmp;
	}
	return (lst);
}

t_list			*dijkstra(int way, t_room *room, t_data *s)
{
	t_list	*queue;

	if (!room || !s)
		free_exit(room, s, 0, "ERROR: dijkstra empty ptr");
	queue = init_algorithm(room, s);
	while (queue)
	{
		if (mark_links_till_end(queue, room, s))
			break ;
		queue = queue_kill_go_next(queue, room, s);
	}
	if (!queue)
		return (NULL);
	ft_lstdel_fag(&queue);
	return (make_way_lst(way, room, s));
}
