/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lem_in.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bsabre-c <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/09/15 13:39:21 by bsabre-c          #+#    #+#             */
/*   Updated: 2019/09/28 16:52:17 by bsabre-c         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef LEM_IN_H
# define LEM_IN_H

# include "libft/libft.h"

# define FLAG_ROOM	0
# define FLAG_START	1
# define FLAG_END	2

typedef struct	s_room
{
	short			room_flag;
	int				width;
	int				height;
	char			*name;
	int				way;
	int				mark;
	int				flag;
	struct s_room	*next;
	struct s_room	*prev;
	struct s_room	*prev_room;
	struct s_room	**link;
	short			*not_allowed;
}				t_room;

typedef struct	s_data
{
	char			*line;
	int				ants;
	int				fd;
	t_list			*tail1;
	t_list			*tail2;
	int				conflict_way1;
	int				conflict_way2;
	char			*start_conf;
	char			*end_conf;
}				t_data;

void			temp_print_roomlist(t_room *room, t_data *s);
void			free_exit(t_room *room, t_data *s, int need_to_read_all, \
		char *message);
void			kill_room(t_room **room);
t_room			*new_room(char **src_string, short room_flag);
t_room			*read_rooms(t_data *s);
int				gnl(int fd, char **line);
t_room			*get_first_last_room(t_room *room, t_data *s);
t_room			**new_room_array(int size);
t_room			**make_bigger_array_and_fill(t_room **arr, t_room *link);
void			make_linkage(t_room *room, t_data *s);
t_list			*dijkstra(int way, t_room *room, t_data *s);
void			print_way(t_list *lst, int way, t_data *s);
void			print_all_ways(t_list **way_arr, t_data *s);
void			queue_push_back(t_list *queue, void *void_ptr, t_data *s);
t_list			*queue_kill_go_next(t_list *queue, t_room *room, t_data *s);
int				mark_links_till_end(t_list *queue, t_room *room_lst, t_data *s);
void			kill_tlist(t_list *lst);
void			kill_tlist_array(t_list **arr);
t_list			**karpov_globchansky(t_room *room, t_data *s);
int				conflict_solver(t_list **way_arr, t_data *s);
void			its_alive(t_list **way_arr, t_data *s);

#endif
