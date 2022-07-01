/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: snouae <snouae@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/28 10:50:41 by aoumad            #+#    #+#             */
/*   Updated: 2022/06/30 17:37:06 by snouae           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

char	*get_value(char *name)
{
	char	*env;

	env = search_env(name);
	if (env != 0)
		return (ft_strchr(env, '=') + 1);
	else
		return (NULL);
}

char	*search_env(char *name)
{
	int	len_name;
	int	i;

	if (name == NULL || g_env == NULL)
		return (NULL);
	if (ft_strchr(name, '=') != NULL)
		len_name = ft_strchr(name, '=') - name;
	else
		len_name = ft_strlen(name);
	i = 0;
	while (g_env[i])
	{
		if (!ft_strncmp(name, g_env[i], len_name))
			return (g_env[i]);
		i++;
	}
	return (NULL);
}

bool	check_var_is_char(char c)
{
	return (ft_isalnum(c) || c == '_');
}
