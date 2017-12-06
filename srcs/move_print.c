/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   move_print.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ppatel <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/08/23 18:33:57 by ppatel            #+#    #+#             */
/*   Updated: 2017/08/23 18:34:00 by ppatel           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lemin.h"

void		assign_path(t_map *map)
{
	int		i;
	int		max;
	t_paths	*tmp;

	i = 0;
	max = (map->paths->size + map->antn) - 1;
	tmp = map->paths;
	while (i < map->antn)
	{
		if (tmp->size < max)
			map->ants[i].path = tmp->path;
		else
		{
			tmp = map->paths;
			map->ants[i].path = tmp->path;
		}
		max--;
		if (tmp->next)
			tmp = tmp->next;
		else
			tmp = map->paths;
		++i;
	}
}

void		move_ant(t_map *map, t_path *tmp, int i)
{
	map->ants[i].curoom->filled = 0;
	map->ants[i].curoom = tmp->next->cur;
	if (ft_strcmp(map->ants[i].curoom->name, map->end))
		map->ants[i].curoom->filled = 1;
	if (!map->opt->min)
	{
		if (map->opt->color)
		{
			ft_printf("\x1B[%dm ", map->ants[i].color);
			ft_printf("L%d-%s", i + 1, map->ants[i].curoom->name);
		}
		else
			ft_printf("L%d-%s", i + 1, map->ants[i].curoom->name);
	}
}

char		ants_travel(t_map *map)
{
	int	i;

	i = 0;
	while (i < map->antn)
	{
		if (ft_strcmp(map->ants[i].curoom->name, map->end))
			return (1);
		++i;
	}
	return (0);
}

int			move_ants(int nturn, t_map *map)
{
	int		i;
	t_path	*tmp;

	i = 0;
	while (i < map->antn)
	{
		if (ft_strcmp(map->ants[i].curoom->name, map->end))
		{
			tmp = map->ants[i].path;
			while (tmp->cur != map->ants[i].curoom)
				tmp = tmp->next;
			if (!tmp->next->cur->filled)
			{
				if (!map->opt->min && nturn == map->turns)
					write(1, " ", 1);
				move_ant(map, tmp, i);
				nturn = map->turns;
			}
		}
		++i;
	}
	return (nturn);
}

void		move_print(t_map *map)
{
	int		nturn;

	nturn = 1;
	if (map->opt->paths)
		print_paths(map);
	makeants(map);
	assign_path(map);
	while (ants_travel(map))
	{
		nturn = move_ants(nturn, map);
		if (!map->opt->min)
		{
			if (map->opt->color)
				ft_printf("\x1B[0m");
			ft_putendl("");
		}
		map->turns++;
	}
}
