/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tools2.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ppatel <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/08/23 16:37:07 by ppatel            #+#    #+#             */
/*   Updated: 2017/08/23 16:37:10 by ppatel           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lemin.h"

void		free_basic(t_map *map)
{
	free(map->opt);
	free(map->paths);
	free(map);
}

void		map_getout(char **tab, char *str, t_map *map)
{
	if (tab)
		ft_tabfree(tab);
	free_basic(map);
	map_exit(str);
}

char		*ft_strcatnfree(char *str, char *from)
{
	char	*new;
	int		i;
	int		j;
	int		len;

	i = 0;
	j = 0;
	len = 0;
	if (str)
		len = ft_strlen(str);
	if (!(new = (char *)malloc(sizeof(*new) * (len + ft_strlen(from) + 2))))
		map_error("Malloc Error; Exiting lemin");
	while (str && str[i])
	{
		new[i] = str[i];
		i++;
	}
	while (from && from[j])
		new[i++] = from[j++];
	new[i++] = '\n';
	new[i] = '\0';
	free(str);
	return (new);
}

t_room		*searchroom(t_map *map, char *str)
{
	t_room	*current;

	current = map->room;
	while (current)
	{
		if (!ft_strcmp(str, current->name))
			return (current);
		current = current->next;
	}
	return (NULL);
}
