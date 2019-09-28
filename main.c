/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bsabre-c <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/09/15 12:49:39 by bsabre-c          #+#    #+#             */
/*   Updated: 2019/09/28 20:14:59 by bsabre-c         ###   ########.fr       */
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

static void	check_flags(int ac, char **av, t_data *s)
{
	int		i;

	if (!av || !s || ac < 2)
		return ;
	i = 1;
	while (i < ac)
	{
		if (!ft_strcmp(av[i], "-error"))
			s->err_flag_on = 1;
		if (!ft_strcmp(av[i], "-grafix"))
			s->grafix_on = 1;
		i++;
	}
}

int			main(int ac, char **av)
{
	t_room	*room;
	t_data	*s;
	t_list	**way_arr;

	if (!(s = (t_data *)malloc(sizeof(t_data))))
		return (-1);
	ft_bzero(s, sizeof(t_data));
	check_flags(ac, av, s);
	s->fd = open("log.txt", O_RDWR | O_CREAT);
	if (!read_ants(s))
		free_exit(NULL, s, 1, "read ants");
	ft_strdel(&(s->line));
	if (!(room = read_rooms(s)))
		free_exit(room, s, 1, "read rooms incorrect");
	make_linkage(room, s);
	if (!(way_arr = karpov_globchansky(room, s)))
		free_exit(room, s, 0, "no ways");
	temp_print_roomlist(room, s);
	print_all_ways(way_arr, s);
	s->exit_without_message = 1;
	kill_tlist_array(way_arr);
	free_exit(room, s, 0, NULL);
	return (0);
}
