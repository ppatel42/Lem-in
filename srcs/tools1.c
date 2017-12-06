/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tools1.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ppatel <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/08/23 16:31:51 by ppatel            #+#    #+#             */
/*   Updated: 2017/08/23 16:31:56 by ppatel           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lemin.h"

void		map_error(char *str)
{
	perror(str);
	exit(-1);
}

void		map_exit(char *str)
{
	ft_putendl(str);
	exit(-1);
}

char		ft_strisascii(char *str)
{
	int	i;

	i = 0;
	while (str && str[i])
		if (!ft_isascii(str[i++]))
			return (0);
	return (1);
}

char		ft_strisdigit(char *str)
{
	int	i;

	i = 0;
	if (str[i] == '-')
		i++;
	while (str && str[i])
		if (!ft_isdigit(str[i++]))
			return (0);
	return (1);
}

void		ft_tabfree(char **tab)
{
	int	i;

	i = 0;
	while (tab[i])
		free(tab[i++]);
	free(tab);
}
