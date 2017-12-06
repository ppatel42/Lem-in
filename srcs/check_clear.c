/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_clear.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ppatel <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/08/23 18:50:22 by ppatel            #+#    #+#             */
/*   Updated: 2017/08/23 18:50:24 by ppatel           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lemin.h"

void		clear_path_till_room(t_path *path, t_room *this)
{
	t_path	*current;

	while (path->next)
	{
		current = path;
		while (current->next->next)
			current = current->next;
		if (current->next->cur == this)
			return ;
		free(current->next);
		current->next = NULL;
	}
	if (path->cur == this)
		return ;
	free(path);
	path = NULL;
}

void		clear_path(t_map *map)
{
	t_path	*current;

	while (map->check && map->check->next)
	{
		current = map->check;
		while (current->next->next)
			current = current->next;
		free(current->next);
		current->next = NULL;
	}
	free(map->check);
	map->check = NULL;
}

void		clear_paths(t_map *map)
{
	t_paths *paths;

	paths = map->paths;
	while (paths->next && paths->next->path)
		paths = paths->next;
	free(paths->next);
	paths->next = NULL;
}

char		inprevious(t_map *map, t_room *this)
{
	t_path	*cur;
	t_paths *curpaths;

	if (map->paths->path)
	{
		if (!ft_strcmp(map->start, this->name) ||
				!ft_strcmp(map->end, this->name))
			return (1);
		curpaths = map->paths;
		while (curpaths->next)
		{
			cur = curpaths->path;
			while (cur)
			{
				if (cur->cur == this)
					return (0);
				cur = cur->next;
			}
			curpaths = curpaths->next;
		}
	}
	return (1);
}

char		check(t_map *map, t_room *this)
{
	t_path	*cur;

	if (!inprevious(map, this))
		return (0);
	if (!map->check)
	{
		if (!(map->check = (t_path *)malloc(sizeof(t_path))))
			map_error("Malloc Error; Exiting lemin");
		map->check->cur = this;
		map->check->next = NULL;
		return (1);
	}
	cur = map->check;
	while (cur->next)
	{
		if (cur->next->cur == this)
			return (0);
		cur = cur->next;
	}
	if (!(cur->next = (t_path *)malloc(sizeof(t_path))))
		map_error("Malloc Error; Exiting lemin");
	cur->next->cur = this;
	cur->next->next = NULL;
	return (1);
}
