/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse1.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ppatel <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/08/23 16:53:14 by ppatel            #+#    #+#             */
/*   Updated: 2017/08/23 16:53:17 by ppatel           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lemin.h"

void		makeants(t_map *map)
{
	int		i;
	char	c;

	if (!(map->ants = (t_ants *)malloc(sizeof(*map->ants) * map->antn)))
		map_error("Malloc Error; Exiting lemin");
	i = 0;
	c = (map->opt->color) ? 31 : 0;
	while (i < map->antn)
	{
		if (map->opt->color)
			c = (c < 37) ? c + 1 : 31;
		map->ants[i].color = c;
		map->ants[i].nb = i + 1;
		map->ants[i].curoom = searchroom(map, map->start);
		map->ants[i].path = NULL;
		++i;
	}
}

int			map_rooms(int i, char **tabline, t_parse *parse, t_map *map)
{
	char	ret;

	while ((ret = parseroom(map, parse, tabline[i])))
	{
		if (!map->opt->min)
			ft_printf("%s\n", tabline[i]);
		++i;
	}
	return (i);
}

int			map_pipes(int i, char **tabline, t_parse *parse, t_map *map)
{
	char	ret;

	while ((ret = makepipes(map, tabline[i])))
	{
		if (!map->opt->min && ret != 2)
			ft_printf("%s\n", tabline[i]);
		++i;
		if (ret == 2)
		{
			if (map->opt->details)
			{
				ft_printf("-> Link Format Error, Reading stopped ");
				ft_printf("(on line %d).\n", i);
			}
			ft_putendl("");
			ft_tabfree(tabline);
			free(parse);
			return (-1);
		}
	}
	return (i);
}

t_parse		*parseinit(void)
{
	t_parse	*parse;

	if (!(parse = (t_parse *)malloc(sizeof(t_parse))))
		map_error("Malloc Error; Exiting lemin");
	parse->start = 0;
	parse->end = 0;
	return (parse);
}

void		parse(char *input, t_map *map)
{
	int		i;
	char	**tabline;
	t_parse	*parse;

	tabline = ft_strsplit(input, '\n');
	free(input);
	i = 0;
	while (tabline[i][0] == '#' && strcmp(tabline[i], "##start")
			&& strcmp(tabline[i], "##end"))
		ft_printf("%s\n", tabline[i++]);
	get_antnb(tabline[i], map);
	if (!map->opt->min)
		ft_printf("%s\n", tabline[i]);
	++i;
	parse = parseinit();
	if ((i = map_rooms(i, tabline, parse, map)) == -1)
		return ;
	if ((i = map_pipes(i, tabline, parse, map)) == -1)
		return ;
	if (!map->opt->min)
		ft_putendl("");
	ft_tabfree(tabline);
	free(parse);
}
