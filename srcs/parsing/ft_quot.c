/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_quot.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: snouae <snouae@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/28 12:34:10 by snouae            #+#    #+#             */
/*   Updated: 2022/06/30 06:27:20 by snouae           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

char	*remove_single_quote(char *str)
{
	char	*new;
	char	*tmp;
	int		leng;
	int		i;

	i = 1;
	new = NULL;
	leng = ft_strlen(str);
	tmp = (char *)malloc(sizeof(char) * 2);
	if (!tmp)
		ft_error_malloc("minishell", NULL, strerror(ENOMEM));
	tmp[1] = '\0';
	while (i < leng - 1)
	{
		tmp[0] = str[i];
		new = ft_strjoin_n(new, tmp);
		i++;
	}
	free(tmp);
	free(str);
	return (new);
}

char	*join_dollar(char *tmp, char *new, int j, char *str)
{
	tmp[0] = str[j];
	new = ft_strjoin_n(new, tmp);
	return (new);
}

char	*remove_double_quote(char *str, char **env)
{
	char	*new;
	int		leng;
	int		j;
	int		start;
	char	*tmp;

	j = 0;
	new = NULL;
	leng = ft_strlen(str);
	tmp = (char *)malloc(sizeof(char) * 2);
	if (!tmp)
		ft_error_malloc("minishell", NULL, strerror(ENOMEM));
	tmp[1] = '\0';
	while (++j < leng - 1)
	{
		if (str[j] == dollar
			&& !cherche_symbol(str[j + 1], "\t!$%'() *\"+,-./:;<=>@[]^`{|}~"))
			new = check_dollar(&j, str, new, env);
		else
			new = join_dollar(tmp, new, j, str);
	}
	free(tmp);
	free(str);
	return (new);
}
