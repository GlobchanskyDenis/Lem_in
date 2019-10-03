/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lem_in.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bsabre-c <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/09/15 13:39:21 by bsabre-c          #+#    #+#             */
/*   Updated: 2019/10/03 18:48:47 by bsabre-c         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef LEM_IN_H
# define LEM_IN_H

# include "libft/libft.h"
# include "mlx/mlx.h"

# define FLAG_ROOM		0
# define FLAG_START		1
# define FLAG_END		2
# define INTMAX			2147483646
# define BUFF_SIZE		10
# define FD_LIMIT		100
# define OFFSET			30
# define LINE_OFFSET	15
# define WIN_SIZE_HOR	1500
# define WIN_SIZE_VERT	1200
# define ESCAPE			53

typedef struct	s_pos
{
	int				hor;
	int				vert;
}				t_pos;

typedef struct	s_room
{
	short			room_flag;
	t_pos			pos;
	char			*name;
	int				way;
	int				mark;
	int				flag;
	size_t			ant;
	struct s_room	*next;
	struct s_room	*prev;
	struct s_room	*prev_room;
	struct s_room	**link;
	short			*not_allowed;
}				t_room;

typedef struct	s_data
{
	char			*line;
	int				steps;
	int				ants;
	int				fd;
	t_list			*tail1;
	t_list			*tail2;
	int				conflict_way1;
	int				conflict_way2;
	char			*start_conf;
	char			*end_conf;
	int				err_flag_on;
	int				grafix_on;
	int				full_logs_on;
	t_pos			max_pos;
	t_pos			min_pos;
	t_pos			size;
	t_pos			win_size;
	void			*mlx;
	void			*win;
	void			*bg_img;
	short			is_pause;
	short			is_end;
}				t_data;

void			temp_print_roomlist(t_room *room, t_data *s);
void			free_exit(t_room *room, t_data *s, int need_to_read_all, \
		char *message);
void			kill_room(t_room **room);
void			kill_roomlist(t_room *room);
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
void			kill_tlist(t_list *lst, short free_content);
void			kill_tlist_array(t_list **arr, short free_content);
t_list			**karpov_globchansky(t_room *room, t_data *s);
int				conflict_solver(t_list **way_arr, t_data *s);
void			its_alive(t_list **way_arr, t_data *s);
void			renumber_way_array_len(t_list **way_arr, t_data *s);
t_list			**cpy_way_arr(t_list **src, t_list **to_delete, t_data *s);
int				can_continue(t_list **way_arr, t_list ***old, t_data *s);
t_list			**prepare_ant_queues(t_list **way_arr, t_data *s);
void			print_ant_queues(t_list **way_arr, t_list **ant_queues, \
		t_data *s);
int				check_line(t_room *room, t_data *s);

int				loop_hook(t_data *s);
int				mouse_pause(int param, int x, int y, t_data *s);
int				key_escape(int key, t_data *s);
int				grafix(t_list **way_arr, t_list **ant_queues, t_room *room, \
		t_data *s);
int				draw_line(t_pos begin, t_pos end, int color, t_data *s);

#endif
