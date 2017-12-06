/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   findpath.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ppatel <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/08/23 17:46:39 by ppatel            #+#    #+#             */
/*   Updated: 2017/08/23 17:46:41 by ppatel           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lemin.h"

int			maxpath(t_map *map, t_room *end)
{
	int		maxpath;
	t_pipe	*tmp;

	maxpath = 0;
	tmp = end->link;
	while (tmp)
	{
		maxpath++;
		if (!ft_strcmp(tmp->room->name, map->start))
		{
			maxpath = 1;
			break ;
		}
		tmp = tmp->next;
	}
	return (maxpath);
}

t_paths		*nextpath(t_map *map, t_paths *paths)
{
	paths->size = map->count;
	if (!(paths->next = (t_paths *)malloc(sizeof(t_paths))))
		map_error("Malloc Error; Exiting lemin");
	clear_path(map);
	if (map->antn <= 100000)
		map->count = (map->paths->size + map->antn) - 1;
	else
		map->count = (map->paths->size + 100000) - 1;
	paths = paths->next;
	paths->size = 0;
	paths->next = NULL;
	return (paths);
}

t_path		*find_firstpath(t_map *map)
{
	t_path	*path;

	while (!(path = find_shortest(map, searchroom(map, map->start), 0)))
	{
		if (map->maxcount < map->count)
			map_getout(NULL, "ERROR", map);
		clear_path(map);
		map->count++;
	}
	return (path);
}

t_paths		*find_otherpaths(t_paths *paths, t_map *map)
{
	paths = nextpath(map, paths);
	while ((paths->path = find_shortest(map, searchroom(map, map->start), 0)))
	{
		map->pcur++;
		if (map->pcur >= map->pmax)
			break ;
		paths = nextpath(map, paths);
	}
	return (paths);
}

void		find_paths(t_map *map)
{
	t_paths *paths;

	if (!map->start || !map->end)
		map_getout(NULL, "ERROR", map);
	paths = map->paths;
	map->pmax = maxpath(map, searchroom(map, map->end));
	if (!map->pmax)
		map_getout(NULL, "ERROR", map);
	paths->path = find_firstpath(map);
	clear_path(map);
	map->pcur++;
	if (map->pcur >= map->pmax)
		return ;
	if (!map->opt->one)
		paths = find_otherpaths(paths, map);
	clear_paths(map);
	clear_path(map);
}
