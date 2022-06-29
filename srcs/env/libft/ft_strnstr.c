/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strnstr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aoumad <abderazzakoumad@gmail.com>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/15 13:13:27 by aoumad            #+#    #+#             */
/*   Updated: 2022/06/15 15:00:26 by aoumad           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

char	*ft_strnstr(const char *haystack, const char *needle, size_t len)
{
	size_t	j;
	size_t	i;

	j = 0;
	if (!needle[0])
		return ((char *)haystack);
	while (haystack[j] && j < len)
	{
		if (haystack[j] == needle[0])
		{
			i = 0;
			while (haystack[j + i] == needle[i]
				&& haystack[j + i]
				&& j + i < len)
				i++;
			if (j + i > len)
				return (NULL);
			if (!needle[i])
				return ((char *)(haystack + j));
		}
		j++;
	}
	return (NULL);
}
