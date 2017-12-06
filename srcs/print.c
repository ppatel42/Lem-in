/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ppatel <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/08/23 18:42:50 by ppatel            #+#    #+#             */
/*   Updated: 2017/08/23 18:42:52 by ppatel           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lemin.h"

void		print_paths(t_map *map)
{
	t_paths	*paths;
	t_path	*print;
	int		i;

	ft_printf("'%d' Path(s) found by the program :\n", map->pcur);
	if (map->opt->one)
		ft_printf("(There may be more, but option -s has been selected.)");
	else
		ft_printf("(There may be more, but it won't result in less move(s).)");
	ft_printf("\n***********************************\n");
	paths = map->paths;
	while (paths)
	{
		i = 0;
		print = paths->path;
		while (print)
		{
			if (i++ > 0)
				ft_printf(" - ");
			ft_printf("%s", print->cur->name);
			print = print->next;
		}
		ft_printf("\n***********************************\n");
		paths = paths->next;
	}
}

void		print_details(t_map *map)
{
	ft_printf("The total of %d ant(s) has reached ", map->antn);
	ft_printf("from the start room '%s' ", map->start);
	ft_printf("to end room '%s' ", map->end);
	ft_printf("through %d path(s) in %d move(s).\n", map->pcur, map->turns);
}
