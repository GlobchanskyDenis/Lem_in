/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   karpov-globchansky_2.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bsabre-c <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/09/26 18:08:19 by bsabre-c          #+#    #+#             */
/*   Updated: 2019/09/28 13:19:35 by bsabre-c         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lem_in.h"

static int		find_ways(t_list **way_arr, t_data *s)
{
	int		i;
	t_list	*way;

	if (!way_arr || !s)
		return (-1);
	i = 0;
	while (way_arr[i + 1])
		i++;
	way = way_arr[i];
	while (way && (((t_room *)(way->content))->way == 0 || \
				((t_room *)(way->content))->way == i + 1))
		way = way->next;
	if (!way)
		return (-1);
	//fprint_fd(s->fd, "check2\n");
	s->conflict_way1 = i + 1;
	s->conflict_way2 = ((t_room *)(way->content))->way;
	return (0);
}

static void		cut_middle(t_list *head, t_list *tail, t_data *s)
{
	t_list	*middle;
	//t_room	*hd;
	//t_room	*tl;
	//t_room	*nxt;

	if (!head || !(head->next) || !tail)
		return ;
	//hd = head->content;
	//tl = tail->content;
	//nxt = head->next->content;
	//fprint_fd(s->fd, "head %s next %s tail %s", hd->name, nxt->name, tl->name);//!!!!!!!!
	//if (head->next == tail)
	//{
	//	head->next = NULL;
	//	return ;
	//}
	middle = head;
	while (middle->next && middle->next != tail)
		middle = middle->next;
	middle->next = NULL;
	s->end_conf = ((t_room *)(head->content))->name;
	s->start_conf = ((t_room *)(middle->content))->name;
	kill_tlist(head->next);
	head->next = NULL;
}

/*
static int	cut_way1(t_list **way_arr, t_data *s)
{
	t_list	*tail;
	t_list	*head;

	if (!way_arr || !s)
		return (-1);
	head = way_arr[s->conflict_way1];
	while (head && ((t_room *)(head->content))->way != s->conflict_way2)
		head = head->next;
	tail = head;
	while (tail && tail->next && ((t_room *)(tail->next->content)) == \
			s->conflict_way2)
		tail = tail->next;
	if (!tail)
		return (-1);
	s->tail1 = tail;
	cut_middle(head, tail);
}
*/

static t_list	*cut_way1(t_list **way_arr, int way1, int way2, t_data *s)
{
	t_list	*tail;
	t_list	*head;

	if (!way_arr || !s)
		return (NULL);
	head = way_arr[way2 - 1];
	//fprint_fd(s->fd, "head way\n");
	//print_way(head, way2, s);
	while (head && ((t_room *)(head->content))->way != way1)
		head = head->next;
	//if (head)
	//	fprint_fd(s->fd, "head end %s\n", ((t_room *)(head->content))->name);
	//else
	//	fprint_fd(s->fd, "empty head!!!\n");
	tail = head;
	while (tail && tail->next && ((t_room *)(tail->content))->way == way1)
		tail = tail->next;
	if (!tail)
	{
		//fprint_fd(s->fd, "empty tail\n");
		return (NULL);
	}
	//fprint_fd(s->fd, "goto cut middle\n");
	cut_middle(head, tail, s);
	//fprint_fd(s->fd, "head is:\n");
	//print_way(way_arr[way2 - 1], 666, s);
	//fprint_fd(s->fd, "tail is:\n");
	//print_way(tail, 666, s);
	return (tail);
}

static void		change_way_number(t_list *way, int way1, int way2)
{
	if (!way)
		return ;
	while (way)
	{
		if (((t_room *)(way->content))->way == way1)
			((t_room *)(way->content))->way = way2;
		else if (((t_room *)(way->content))->way == way2)
			((t_room *)(way->content))->way = way1;
		way = way->next;
	}
}

static void		its_alive(t_list **way_arr, t_data *s)
{
	t_list	*head;

	if (!way_arr || !s)
		return ;
	head = way_arr[s->conflict_way1 - 1];
	while (head->next)
		head = head->next;
	head->next = s->tail2;
	change_way_number(head, s->conflict_way1, s->conflict_way2);
	//((t_room *)(head->content))->way = s->conflict_way1 + 1;//////
	//fprint_fd(s->fd, "check 2\n":q);
	head = way_arr[s->conflict_way2 - 1];
	while (head->next)
		head = head->next;
	head->next = s->tail1;
	change_way_number(head, s->conflict_way1, s->conflict_way2);
	//((t_room *)(head->content))->way = s->conflict_way2 + 1;//////
	// Заменить предыдущую строку на функцию меняющую номер пути хвоста
	//fprint_fd(s->fd, "check 3\n");
}

static t_list	*cut_way2(t_list **way_arr, int way_num, t_data *s)
{
	t_list	*way;
	t_list	*tmp;

	if (!way_arr || !s)
		return (NULL);
	way = way_arr[way_num - 1];
	while (way && ((t_room *)(way->content))->name != s->start_conf)
		way = way->next;
	if (!way)
		return (NULL);
	tmp = way;
	way = way->next;
	tmp->next = NULL;
	while (way && ((t_room *)(way->content))->name != s->end_conf)
	{
		tmp = way;
		way = way->next;
		free(tmp);
	}
	tmp = way;
	way = way->next;
	free(tmp);
	return (way);
}

int				conflict_solver(t_list **way_arr, t_data *s)
{
	if (!way_arr || !s)
		return (-1);
	if (find_ways(way_arr, s) < 0)
		return (-1);
	if (!(s->tail1 = cut_way1(way_arr, s->conflict_way2, s->conflict_way1, s)))
		return (-1);
	if (!(s->tail2 = cut_way2(way_arr, s->conflict_way2, s)))
		return (-1);
	fprint_fd(s->fd, "cut ways done\n");
	print_way(s->tail1, s->conflict_way1, s);
	print_way(s->tail2, s->conflict_way2, s);
	fprint_fd(s->fd, "cut ways print done\n");
	its_alive(way_arr, s);
	fprint_fd(s->fd, "GOTO next\n");
	return (0);
}
