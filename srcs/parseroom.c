/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parseroom.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ppatel <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/08/23 17:21:29 by ppatel            #+#    #+#             */
/*   Updated: 2017/08/23 17:21:31 by ppatel           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lemin.h"

t_room		*create_room(char **roominfo)
{
	t_room *new;

	if (!(new = (t_room *)malloc(sizeof(t_room))))
		map_error("Malloc Error; Exiting lemin");
	new->name = ft_strdup(roominfo[0]);
	new->x = ft_atoi(roominfo[1]);
	new->y = ft_atoi(roominfo[2]);
	new->filled = 0;
	new->next = NULL;
	new->link = NULL;
	return (new);
}

char		map_commands(char *line, t_parse *parse, t_map *map)
{
	if (!strcmp(line, "##start"))
	{
		if (parse->start || parse->end == 1)
			map_getout(NULL, "ERROR", map);
		parse->start = 1;
	}
	if (!strcmp(line, "##end"))
	{
		if (parse->end || parse->start == 1)
			map_getout(NULL, "ERROR", map);
		parse->end = 1;
	}
	return (1);
}

void		roomfill(char **roominfo, t_room *cur, t_parse *parse, t_map *map)
{
	if (map->room)
		cur->next = create_room(roominfo);
	else
		map->room = create_room(roominfo);
	if (parse->start == 1)
	{
		parse->start = 2;
		map->start = ft_strdup(roominfo[0]);
	}
	if (parse->end == 1)
	{
		parse->end = 2;
		map->end = ft_strdup(roominfo[0]);
	}
}

char		parseroom(t_map *map, t_parse *parse, char *line)
{
	int		i;
	t_room	*current;
	char	**roominfo;

	if (!line || (!strchr(line, ' ') && !(line[0] == '#')))
		return (0);
	if (map->room)
	{
		current = map->room;
		while (current->next)
			current = current->next;
	}
	if (line[0] == '#')
		return (map_commands(line, parse, map));
	roominfo = ft_strsplit(line, ' ');
	i = 0;
	while (roominfo[i])
		++i;
	if (i != 3 || !ft_strisdigit(roominfo[1]) || !ft_strisdigit(roominfo[2]))
		map_getout(roominfo, "ERROR", map);
	roomfill(roominfo, current, parse, map);
	ft_tabfree(roominfo);
	return (1);
}
