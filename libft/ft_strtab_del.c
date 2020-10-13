/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strtab_del.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ndubouil <ndubouil@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/01/20 20:34:01 by ndubouil          #+#    #+#             */
/*   Updated: 2019/01/20 20:34:25 by ndubouil         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_strtab_del(char ***arr)
{
	int		i;

	if (!(*arr))
		return ;
	if (!(*arr)[0])
	{
		ft_memdel((void **)arr);
		*arr = NULL;
		return ;
	}
	i = -1;
	while ((*arr)[++i])
		ft_strdel(&(*arr)[i]);
	ft_strdel(&(*arr)[i]);
	ft_memdel((void **)arr);
	*arr = NULL;
}
