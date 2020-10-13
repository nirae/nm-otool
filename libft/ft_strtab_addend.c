/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strtab_addend.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ndubouil <ndubouil@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/01/20 20:32:48 by ndubouil          #+#    #+#             */
/*   Updated: 2019/01/20 20:40:18 by ndubouil         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int		ft_strtab_addend(char ***arr, char *elem)
{
	int		i;
	char	**tmp;

	if (*arr == NULL || !elem)
		return (0);
	i = -1;
	while ((*arr)[++i])
		;
	if (!(tmp = ft_memalloc((i + 2) * sizeof(char *))))
		return (0);
	i = -1;
	while ((*arr)[++i])
		if (!(tmp[i] = ft_strdup((*arr)[i])))
			return (0);
	if (!(tmp[i] = ft_strdup(elem)))
		return (0);
	tmp[i + 1] = NULL;
	ft_strtab_del(arr);
	*arr = tmp;
	return (1);
}
