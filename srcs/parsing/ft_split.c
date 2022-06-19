/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: snouae <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/12 16:53:28 by snouae            #+#    #+#             */
/*   Updated: 2021/11/13 17:51:16 by snouae           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

static	int	count_str(char const *s, char c)
{
	int	nbw;
	int	j;

	nbw = 0;
	j = 0;
	while (s[j])
	{
		if (j == 0 && s[j] != c)
			nbw++;
		if (s[j] != c && (j > 0 && s[j - 1] == c))
			nbw++;
		j++;
	}
	return (nbw);
}

static	int	count_char(char const *s, char c, int i)
{
	int	count;

	count = 0;
	while (s[i] != c && s[i])
	{
		i++;
		count++;
	}
	return (count);
}

static	char	**ft_free(char **tab, int i)
{
	i--;
	while (i >= 0)
		free(tab[i--]);
	free(tab);
	return (tab);
}

static	char	**ft_rem(const char *s, char **tab, char c, int i)
{
	int		i2;
	int		i3;

	i2 = 0;
	while (s[i] != '\0')
	{
		if ((i == 0 && s[i] != c) || (s[i] != c && (i > 0 && s[i - 1] == c)))
		{
			i3 = 0;
			tab[i2] = (char *)malloc(sizeof(char) * (count_char(s, c, i) + 1));
			if (!tab[i2])
				return (ft_free(tab, i2));
			while (s[i] != c && s[i])
			{
				tab[i2][i3] = s[i++];
				i3++;
			}
			tab[i2++][i3] = '\0';
		}
		else
			i++;
	}
	tab[i2] = 0;
	return (tab);
}

char	**ft_split(char const *s, char c)
{
	char	**tab;
	int		i;

	i = 0;
	if (!s)
		return (0);
	tab = (char **)malloc(sizeof(char *) * (count_str(s, c) + 1));
	if (!tab)
		return (0);
	return (ft_rem(s, tab, c, i));
}

/*#include <stdio.h>
int main()
{
    char *str = "HELLO WORLD";
    char **split = ft_split(str, ' ');
    int i = count_str(str, ' ');
    int n = 0;
    printf("%d\n",i);
    while (i > n)
    printf("-->%s\n", split[n++]);
}*/
