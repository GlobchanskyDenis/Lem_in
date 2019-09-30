/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   karpov_globchansky_1.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bsabre-c <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/09/26 13:19:03 by bsabre-c          #+#    #+#             */
/*   Updated: 2019/09/30 18:18:57 by bsabre-c         ###   ########.fr       */
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

static void		find_and_solve_conflicts(t_room *room, t_data *s, \
		t_list **way_arr)
{
	if (!room || !s || !way_arr)
		return ;
	while (find_conflicts(way_arr, s) > 0)
	{
		if (s->full_logs_on)
		{
			fprint_fd(s->fd, "conflict was found!!\n");
			temp_print_roomlist(room, s);
			print_all_ways(way_arr, s);
		}
		if (conflict_solver(way_arr, s) < 0)
		{
			fprint_fd(s->fd, "conflict was not solved\n");
			return ;
		}
	}
}

static void		print_new_way_status(t_list *way, t_room *room, t_data *s, \
		int way_num)
{
	if (!way || !room || !s)
		return ;
	fprint_fd(s->fd, "\n\nnew way!\n");
	temp_print_roomlist(room, s);
	print_way(way, way_num, s);
}

static t_list	*cpy_node(t_room *src, size_t cont_size)
{
	t_list	*dst;
	t_room	*room;

	if (!src)
		return (NULL);
	if (!(dst = (t_list *)malloc(sizeof(t_list))))
		return (NULL);
	if (!(room = (t_room *)malloc(sizeof(t_room))))
	{
		free(dst);
		return (NULL);
	}
	if (!(room->name = ft_strdup(src->name)))
	{
		free(dst);
		return (NULL);
	}
	dst->content_size = cont_size;
	dst->content = room;
	return (dst);
}

static t_list	*cpy_way(t_list *src)
{
	t_list	*dst;
	t_list	*lst;

	if (!src)
		return (NULL);
	if (!(dst = cpy_node(src->content, src->content_size)))
		return (NULL);
	lst = dst;
	src = src->next;
	while (src)
	{
		if (!(lst->next = cpy_node(src->content, src->content_size)))
		{
			kill_tlist(dst, 1);
			return (NULL);
		}
		lst = lst->next;
		src = src->next;
	}
	lst->next = NULL;
	return (dst);
}

static t_list	**cpy_way_arr(t_list **src, t_list **to_delete)
{
	t_list	**dst;
	short	size;
	short	i;

	kill_tlist_array(to_delete, 1);
	if (!src)
		return (NULL);
	size = 0;
	while (src[size])
		size++;
	if (!(dst = (t_list **)malloc(sizeof(t_list *) * (size + 1))))
		return (NULL);
	dst[size] = NULL;
	i = 0
	while (i < size)
	{
		if (!(dst[size] = copy_way(src[size])))
		{
			kill_tlist_arr(dst, 1);
			return (NULL);
		}
		i++;
	}
	return (dst);
}

static size_t	*create_way_size_arr(t_list **way_arr, short size)
{
	size_t	*dst;
	size_t	temp;
	short	i;

	if (!way_arr)
		return (NULL);
	if (!(dst = (size_t *)malloc(sizeof(size_t) * size)))
		return (NULL);
	i = -1;
	while (++i < size)
		dst[i] = way_arr[i]->content_size;
	i = -1;
	while (++i + 1 < size)
	{
		if (dst[i] > dst[i + 1])
		{
			temp = dst[i];
			dst[i] = dst[i + 1];
			dst[i + 1] = temp;
			i = -1;
		}
	}
	return (dst);
}

static size_t	find_max_and_size(t_list **way_arr, t_data *s, size_t *size)
{
	size_t	i;
	size_t	max;

	if (!way_arr || !s || !size)
		return (0);
	i = 0;
	max = 0;
	while (way_arr[i])
	{
		if (way_arr[i]->content_size > max)
			max = way_arr[i]->content_size;
		i++;
	}
	*size = i;
	return (max);
}

static size_t	count_size(size_t *arr, short size, size_t max, int ants)
{
	size_t	dst;
	short	i;

	if (!arr)
		return (0);
	dst = 0;
	i = 0;
	while (ants > 0)
	{
		if (i + 1 < size)
		{
			dst = dst + 
		}
	}
}

static size_t	size_of_ant_queue(t_list **way_arr, t_data *s)
{
	short	size;
	size_t	*waiting;
	size_t	max;

	if (!way_arr || !s)
		return (0);
	size = 0;
	max = find_max_and_size(way_arr, s, &size);
	if (!(arr = create_way_size_arr(way_arr, size)))
		return (0);
	return (count_size(waiting, size, max, s->ants));
}

static int		can_continue(t_list **way_arr, t_list ***cpy, t_data *s)
{
	if (!way_arr || !cpy || !(*cpy) || !s)
		return (-1);
	if (size_of_ant_queue(way_arr, s) > size_of_ant_queue(*cpy, s))
	{
		kill_tlist_arr(way_arr, 0);
		return (0);
	}
	if (!(*cpy = cpy_way_arr(way_arr, *cpy)))
		return (-1);
	return (1);
}

t_list			**karpov_globchansky(t_room *room, t_data *s)
{
	t_list	**way_arr;
	t_list	**cpy_way_arr;
	short	i;

	if (!room || !s || !(way_arr = (t_list **)malloc(sizeof(t_list *) * 2)))
		return (NULL);
	if (!(cpy = cpy_way_array(way_arr, cpy)))
		return (NULL);
	ft_bzero(way_arr, sizeof(t_list *) * 2);
	i = 0;
	while (can_continue(way_arr, &cpy, s) > 0 && \
			(way_arr[i] = dijkstra(i + 1, room, s)))
	{
		if (s->full_logs_on)
			print_new_way_status(way_arr[i], room, s, i + 1);
		if (!(way_arr = make_bigger_tlist_array(way_arr)))
			return (NULL);
		i++;
		find_and_solve_conflicts(room, s, way_arr);
	}
	return (way_arr);
}
