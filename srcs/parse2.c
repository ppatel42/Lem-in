/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse2.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ppatel <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/08/23 17:14:21 by ppatel            #+#    #+#             */
/*   Updated: 2017/08/23 17:14:23 by ppatel           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lemin.h"

t_pipe		*newpipe(t_room *room)
{
	t_pipe	*new;

	if (!(new = (t_pipe *)malloc(sizeof(t_pipe))))
		map_error("Malloc Error; Exiting lemin");
	new->to = room->name;
	new->room = room;
	new->next = NULL;
	return (new);
}

void		addpipe(t_room *room, t_pipe *npipe)
{
	t_pipe	*cpipe;

	if (!room->link)
		room->link = npipe;
	else
	{
		cpipe = room->link;
		while (cpipe->next)
			cpipe = cpipe->next;
		cpipe->next = npipe;
	}
}

void		createpipe(t_map *map, char **pinfo)
{
	t_room	*r1;
	t_room	*r2;
	t_pipe	*npipe1;
	t_pipe	*npipe2;

	r1 = map->room;
	while (strcmp(r1->name, pinfo[0]) && r1->next)
		r1 = r1->next;
	r2 = map->room;
	while (strcmp(r2->name, pinfo[1]) && r2->next)
		r2 = r2->next;
	npipe1 = newpipe(r2);
	addpipe(r1, npipe1);
	npipe2 = newpipe(r1);
	addpipe(r2, npipe2);
}

char		makepipes(t_map *map, char *line)
{
	int		i;
	char	**pipeinfo;

	if (!line)
		return (0);
	if (line[0] == '#')
		return (1);
	pipeinfo = ft_strsplit(line, '-');
	i = 0;
	while (pipeinfo[i])
		++i;
	if (i != 2 || !searchroom(map, pipeinfo[0]) ||
			!searchroom(map, pipeinfo[1]))
	{
		ft_tabfree(pipeinfo);
		return (2);
	}
	createpipe(map, pipeinfo);
	ft_tabfree(pipeinfo);
	return (1);
}

void		get_antnb(char *str, t_map *map)
{
	int	i;

	i = 0;
	if (!ft_strisdigit(str))
		map_getout(NULL, "ERROR", map);
	map->antn = ft_atoi(str);
	if (map->antn <= 0)
		map_getout(NULL, "ERROR", map);
}
