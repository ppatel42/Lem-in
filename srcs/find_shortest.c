/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   find_shortest.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ppatel <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/08/23 18:00:40 by ppatel            #+#    #+#             */
/*   Updated: 2017/08/23 18:00:42 by ppatel           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lemin.h"

t_path		*newpath(t_room *cur)
{
	t_path	*path;

	if (!(path = (t_path *)malloc(sizeof(t_path))))
		map_error("Malloc Error; Exiting lemin");
	path->cur = cur;
	return (path);
}

t_path		*returnpath(t_map *map, t_path *path, t_room *cur, int count)
{
	if (!map->count || count < map->count)
	{
		if (!(path = (t_path *)malloc(sizeof(t_path))))
			map_error("Malloc Error; Exiting lemin");
		path->cur = cur;
		path->next = NULL;
		map->count = count;
		return (path);
	}
	else
		return (NULL);
}

t_path		*find_shortest(t_map *map, t_room *cur, int count)
{
	t_path	*path;
	t_path	*new;
	t_pipe	*pipe;

	path = NULL;
	map->maxcount = (count > map->maxcount) ? count : map->maxcount;
	if (!cur->link || (map->count && count >= map->count) || !check(map, cur))
		return (NULL);
	if (!ft_strcmp(cur->name, map->end))
		return (returnpath(map, path, cur, count));
	pipe = cur->link;
	while (pipe)
	{
		clear_path_till_room(map->check, cur);
		if ((new = find_shortest(map, pipe->room, count + 1)) != NULL)
		{
			if (!path)
				path = newpath(cur);
			else
				clear_path_till_room(path, cur);
			path->next = new;
		}
		pipe = pipe->next;
	}
	return (path);
}
