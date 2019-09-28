/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bsabre-c <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/09/15 12:49:39 by bsabre-c          #+#    #+#             */
/*   Updated: 2019/09/27 14:40:47 by bsabre-c         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lem_in.h"

static int	read_ants(t_data *s)
{
	char	*tmp;
	int		ret;

	if (!s)
		return (0);
	while (gnl(0, &(s->line)) && (s->line)[0] == '#')
		ft_strdel(&(s->line));
	if (!(s->line))
		return (0);
	s->ants = ft_atoi(s->line);
	tmp = ft_itoa(s->ants);
	ret = ft_strcmp(tmp, s->line);
	ft_strdel(&tmp);
	ft_strdel(&(s->line));
	fprint_fd(s->fd, "ants number = %d\n", s->ants);
	if (ret != 0 || s->ants < 1)
	{
		fprint_fd(s->fd, "invalid line with ants\n");
		return (0);
	}
	return (1);
}

int			main(void)
{
	t_room	*room;
	t_data	*s;
	t_list	**ways;
	short	i;

	room = NULL;
	if (!(s = (t_data *)malloc(sizeof(t_data))))
		return (-1);
	ft_bzero(s, sizeof(t_data));
	s->fd = open("log.txt", O_RDWR | O_CREAT);
	if (!read_ants(s))
		free_exit(room, s, 1, "ERROR: read ants");
	ft_strdel(&(s->line));
	if (!(room = read_rooms(s)))
		free_exit(room, s, 1, "ERROR: read rooms incorrect");
	make_linkage(room, s);
	if (!(ways = karpov_globchansky(room, s)))
	{
		fprint_fd(s->fd, "KARPOV_GLOBCHANSKY returned NULL\n");
		free_exit(room, s, 0, "FIN");
	}
	temp_print_roomlist(room, s);
	i = 0;
	while (ways[i])
	{
		print_way(ways[i], i + 1, s);
		i++;
	}
	kill_tlist_array(ways);
	free_exit(room, s, 0, NULL);
	return (0);
}
