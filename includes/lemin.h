/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lemin.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ppatel <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/08/23 15:45:52 by ppatel            #+#    #+#             */
/*   Updated: 2017/08/23 15:46:23 by ppatel           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef LEMIN_H
# define LEMIN_H
# include "../libft/libft.h"
# include <limits.h>
# include <stdio.h>
# include <errno.h>

typedef struct s_pipe	t_pipe;
typedef struct s_room	t_room;
typedef struct s_path	t_path;
typedef struct s_paths	t_paths;

typedef	struct			s_parse
{
	char				start;
	char				end;
}						t_parse;

typedef struct			s_ants
{
	int					nb;
	char				color;
	t_room				*curoom;
	t_path				*path;
}						t_ants;

struct					s_pipe
{
	char				*to;
	t_room				*room;
	t_pipe				*next;
};

struct					s_room
{
	char				*name;
	int					x;
	int					y;
	char				filled;
	t_room				*next;
	t_pipe				*link;
};

struct					s_path
{
	t_room				*cur;
	t_path				*next;
};

struct					s_paths
{
	t_path				*path;
	int					size;
	t_paths				*next;
};

typedef struct			s_options
{
	char				details;
	char				paths;
	char				color;
	char				min;
	char				one;
}						t_options;

typedef struct			s_map
{
	int					antn;
	t_ants				*ants;
	char				*start;
	char				*end;
	int					maxcount;
	int					count;
	int					pmax;
	int					pcur;
	int					turns;
	t_options			*opt;
	t_room				*room;
	t_paths				*paths;
	t_path				*check;
}						t_map;

void					options(int argc, char **argv, t_map *map);
void					optinit(t_map *map);
void					find_paths(t_map *map);
t_path					*find_shortest(t_map *map, t_room *cur, int count);
char					check(t_map *map, t_room *this);
t_room					*searchroom(t_map *map, char *str);
void					move_print(t_map *map);
void					free_all(t_map *map);
void					free_basic(t_map *map);
void					clear_path(t_map *map);
void					clear_paths(t_map *map);
void					clear_path_till_room(t_path *path, t_room *from);
char					ft_strisascii(char *str);
char					*ft_strcatnfree(char *str, char *from);
void					parse(char *input, t_map *map);
char					parseroom(t_map *map, t_parse *parse, char *line);
void					map_getout(char **tab, char *str, t_map *map);
void					map_error(char *str);
void					map_exit(char *str);
void					ft_tabfree(char **tab);
char					makepipes(t_map *map, char *line);
void					makeants(t_map *map);
void					get_antnb(char *str, t_map *map);
char					ft_strisdigit(char *str);
void					print_details(t_map *map);
void					print_paths(t_map *map);

#endif
