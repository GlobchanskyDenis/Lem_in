/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   new_room.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bsabre-c <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/09/15 13:51:25 by bsabre-c          #+#    #+#             */
/*   Updated: 2019/09/19 10:14:28 by bsabre-c         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lem_in.h"

static char		*find_room_name(char *src, short *name_len)
{
	char	*name;
	short	len;
	short	i;

	if (!src)
		return (NULL);
	len = 0;
	while (src[len] && src[len] != ' ' && len < 50)
		len++;
	if (len >= 50)
		return (NULL);
	if (!(name = (char *)malloc(sizeof(char) * (len + 1))))
		return (NULL);
	i = -1;
	while (++i < len)
		name[i] = src[i];
	name[i] = '\0';
	*name_len = len;
	return (name);
}

static int		find_room_position(t_room *room, char *src, short name_len)
{
	short	i;

	if (!room || !src || name_len < 1)
		return (0);
	i = name_len;
	while (src[i] && i < 100 && (src[i] < '0' || src[i] > '9'))
		i++;
	if (src[i] == '\0' || i >= 100)
		return (0);
	room->width = ft_atoi(&(src[i]));
	while (src[i] && i < 100 && src[i] != ' ')
		i++;
	while (src[i] && i < 100 && (src[i] < '0' || src[i] > '9'))
		i++;
	if (src[i] == '\0' || i >= 100)
		return (0);
	room->height = ft_atoi(&(src[i]));
	return (1);
}

t_room			*new_room(char **src_string, short room_flag)
{
	t_room	*dst;
	short	name_len;

	if (!src_string || !(src_string))
		return (NULL);
	if (!(dst = (t_room *)malloc(sizeof(t_room))))
		return (NULL);
	ft_bzero(dst, sizeof(t_room));
	dst->room_flag = room_flag;
	if (!(dst->name = find_room_name(*src_string, &name_len)))
	{
		kill_room(&dst);
		ft_strdel(src_string);
		return (NULL);
	}
	if (!(find_room_position(dst, *src_string, name_len)))
	{
		kill_room(&dst);
		ft_strdel(src_string);
		return (NULL);
	}
	ft_strdel(src_string);
	return (dst);
}
