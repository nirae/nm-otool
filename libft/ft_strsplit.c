/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strsplit.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ndubouil <ndubouil@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/11/20 22:19:28 by ndubouil          #+#    #+#             */
/*   Updated: 2018/12/23 00:12:10 by ndubouil         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static int	ft_count_letters(char *str, char sep)
{
	int i;
	int result;

	i = 0;
	result = 0;
	while (str[i] == sep)
		i++;
	while (str[i] != sep && str[i++] != '\0')
		result++;
	return (result);
}

char		**ft_strsplit(char const *s, char c)
{
	char	**arr;
	int		i;
	int		j;
	int		k;

	if (s == NULL)
		return (NULL);
	if (!(arr = ft_memalloc((ft_count_words((char *)s, c) + 1) * sizeof(*arr))))
		return (0);
	i = 0;
	j = 0;
	while (i < ft_count_words((char *)s, c))
	{
		k = 0;
		if (!(arr[i] = ft_strnew(ft_count_letters((char *)&s[j], c) + 1)))
			return (0);
		while (s[j] == c)
			j++;
		while (s[j] != c && s[j] != '\0')
			arr[i][k++] = s[j++];
		arr[i++][k] = '\0';
	}
	arr[i] = 0;
	return (arr);
}
