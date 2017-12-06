/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   options.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ppatel <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/08/23 16:29:20 by ppatel            #+#    #+#             */
/*   Updated: 2017/08/23 16:29:22 by ppatel           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lemin.h"

void		optinit(t_map *map)
{
	if (!(map->opt = (t_options *)malloc(sizeof(t_options))))
		map_error("Malloc Error; Exiting lemin");
	map->opt->details = 0;
	map->opt->paths = 0;
	map->opt->min = 0;
	map->opt->color = 0;
}

void		help(t_map *map)
{
	ft_printf("The lem-in program accepts the following options :\n");
	ft_printf("	-d : Details (Shows the resolution summary, ");
	ft_printf("and Reading Errors (if any)).\n");
	ft_printf("	-p : Displays all the paths used.\n");
	ft_printf("	-o : Output is restricted to display the options ");
	ft_printf("selected above.\n");
	ft_printf("	-c : Distinct color is given to every ants while navigating ");
	ft_printf("through the map. (Repeats after every seven ants).\n");
	ft_printf("	-s : Single Shortest path available is only used.\n");
	ft_printf("	-h : Help.\n");
	ft_printf("usage: lem-in [-dpocsh] < [file]\n");
	ft_printf("       lem-in [-dpocsh]\n");
	free_basic(map);
	exit(0);
}

void		map_get_options(char **argv, int i, t_map *map)
{
	int	j;

	j = 1;
	while (argv[i][j])
	{
		if (argv[i][j] == 'h')
			help(map);
		else if (argv[i][j] == 's')
			map->opt->one = 1;
		else if (argv[i][j] == 'd')
			map->opt->details = 1;
		else if (argv[i][j] == 'c')
			map->opt->color = 1;
		else if (argv[i][j] == 'p')
			map->opt->paths = 1;
		else if (argv[i][j] == 'o')
			map->opt->min = 1;
		else
		{
			free_basic(map);
			map_exit("lem-in: Unknown option, use -h for help");
		}
		++j;
	}
}

void		options(int argc, char **argv, t_map *map)
{
	int	i;

	i = 1;
	while (i < argc)
	{
		if (argv[i][0] == '-')
			map_get_options(argv, i, map);
		else
		{
			free_basic(map);
			map_exit("lem-in: Unknown option, use -h for help");
		}
		++i;
	}
}
