/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free_all.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ppatel <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/08/23 19:11:08 by ppatel            #+#    #+#             */
/*   Updated: 2017/08/23 19:11:12 by ppatel           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lemin.h"

void		free_pipe(t_room *room)
{
	t_pipe	*fpipe;

	while (room->link && room->link->next)
	{
		fpipe = room->link;
		while (fpipe->next->next)
			fpipe = fpipe->next;
		free(fpipe->next);
		fpipe->next = NULL;
	}
	free(room->link);
}

void		free_room(t_map *map)
{
	t_room	*froom;

	while (map->room && map->room->next)
	{
		froom = map->room;
		while (froom->next->next)
			froom = froom->next;
		free_pipe(froom->next);
		free(froom->next->name);
		free(froom->next);
		froom->next = NULL;
	}
	free_pipe(map->room);
	free(map->room->name);
	free(map->room);
}

void		free_path(t_paths *paths)
{
	t_path	*fpath;

	while (paths->path && paths->path->next)
	{
		fpath = paths->path;
		while (fpath->next->next)
			fpath = fpath->next;
		free(fpath->next);
		fpath->next = NULL;
	}
	free(paths->path);
}

void		free_paths(t_map *map)
{
	t_paths *fpaths;

	while (map->paths && map->paths->next)
	{
		fpaths = map->paths;
		while (fpaths->next->next)
			fpaths = fpaths->next;
		free_path(fpaths->next);
		free(fpaths->next);
		fpaths->next = NULL;
	}
	free_path(map->paths);
}

void		free_all(t_map *map)
{
	free_paths(map);
	free_room(map);
	free(map->ants);
	free(map->start);
	free(map->end);
	free_basic(map);
}
