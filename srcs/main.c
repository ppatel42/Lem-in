/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ppatel <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/08/23 18:46:23 by ppatel            #+#    #+#             */
/*   Updated: 2017/08/31 16:54:29 by ppatel           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lemin.h"

t_map		*map_init(void)
{
	t_map *map;

	if (!(map = (t_map *)malloc(sizeof(*map))))
		map_error("Malloc Error; Exiting lemin");
	map->ants = NULL;
	map->start = NULL;
	map->maxcount = 0;
	map->count = 1;
	map->end = NULL;
	map->room = NULL;
	map->paths = NULL;
	map->check = NULL;
	map->pmax = 0;
	map->pcur = 0;
	map->turns = 0;
	if (!(map->paths = (t_paths *)malloc(sizeof(t_paths))))
		map_error("Malloc Error; Exiting lemin");
	map->paths->path = NULL;
	map->paths->size = 0;
	map->paths->next = NULL;
	optinit(map);
	return (map);
}

char		*map_get_input(t_map *map)
{
	int		ret;
	char	*line;
	char	*input;

	line = NULL;
	input = NULL;
	while ((ret = get_next_line(0, &line)))
	{
		if (ret == -1 || !ft_strisascii(line))
		{
			if (input)
				free(input);
			free(line);
			free_basic(map);
			map_error("Map reading error");
		}
		if (ft_strstr("\n\n", line))
			return (input);
		input = ft_strcatnfree(input, line);
		free(line);
		line = NULL;
	}
	free(line);
	return (input);
}

int			main(int argc, char **argv)
{
	char	*input;
	t_map	*map;

	input = NULL;
	map = map_init();
	if (argc > 1)
		options(argc, argv, map);
	input = map_get_input(map);
	if (!input)
		map_error("Map reading error");
	parse(input, map);
	find_paths(map);
	move_print(map);
	if (map->opt->details)
		print_details(map);
	free_all(map);
	return (0);
}
