/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   karpov_globchansky_3.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bsabre-c <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/09/28 16:47:16 by bsabre-c          #+#    #+#             */
/*   Updated: 2019/09/28 16:51:04 by bsabre-c         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lem_in.h"

static void	change_way_number(t_list *way, int way1, int way2)
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

void		its_alive(t_list **way_arr, t_data *s)
{
	t_list	*head;

	if (!way_arr || !s)
		return ;
	head = way_arr[s->conflict_way1 - 1];
	while (head->next)
		head = head->next;
	head->next = s->tail2;
	change_way_number(head, s->conflict_way1, s->conflict_way2);
	head = way_arr[s->conflict_way2 - 1];
	while (head->next)
		head = head->next;
	head->next = s->tail1;
	change_way_number(head->next, s->conflict_way1, s->conflict_way2);
}
