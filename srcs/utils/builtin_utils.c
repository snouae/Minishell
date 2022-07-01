/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_utils.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: snouae <snouae@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/31 07:41:08 by aoumad            #+#    #+#             */
/*   Updated: 2022/06/30 22:40:48 by snouae           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

char	*ft_strchr_export(const char *s, int c)
{
	while (*s)
	{
		if (*s == (char )c)
			return ((char *)s + 1);
		s++;
	}
	if ((char )c == 0)
		return ((char *)s + 1);
	return (NULL);
}

int	env_count(char **env)
{
	int	i;

	i = 0;
	while (env[i])
		i++;
	return (i);
}

int	add_to_env(char ***env, char *str)
{
	char	**new_env;
	int		i;

	new_env = (char **)malloc((env_count(*env) + 2) * sizeof(char *));
	if (!new_env)
	{
		ft_error("minishell", NULL, strerror(ENOMEM));
		printf("\n");
		return (0);
	}
	i = 0;
	while (*env && (*env)[i])
	{
		new_env[i] = (*env)[i];
		i++;
	}
	new_env[i] = str;
	new_env[i + 1] = NULL;
	free(*env);
	*env = new_env;
	return (0);
}

int	remove_from_env(char *str)
{
	char	**new_env;
	int		i;
	int		j;

	new_env = malloc(env_count(g_env) * sizeof(char *));
	if (new_env == NULL)
	{
		ft_error("minishell", NULL, strerror(ENOMEM));
		return (0);
	}
	i = 0;
	j = 0;
	while (g_env[i])
	{
		if (!ft_strcmp(g_env[i], str))
			i++;
		new_env[j++] = g_env[i++];
	}
	new_env[j] = NULL;
	free(g_env);
	free(str);
	g_env = new_env;
	return (0);
}

int	replace_str_env(char ***env, char *old_str, char *new_str, int test)
{
	int	i;

	if (*env == NULL || old_str == NULL)
		return (ERROR);
	i = 0;
	while ((*env)[i] && ft_strcmp((*env)[i], old_str))
		i++;
	if (ft_strcmp((*env)[i], old_str))
		return (ERROR);
	if (test == 1)
	{
		new_str = ft_strchr_export(new_str, '=');
		(*env)[i] = ft_strjoin((*env)[i], new_str);
	}
	else if (check_replace(old_str, new_str) == true)
		(*env)[i] = ft_strdup(new_str);
	else
		return (0);
	free(old_str);
	//free (new_str);
	return (0);
}

bool	check_replace(char *old_str, char *new_str)
{
	if (ft_strchr(old_str, '=') && ft_strchr(new_str, '='))
		return (true);
	else if (!ft_strchr(old_str, '=') && ft_strchr(new_str, '='))
		return (true);
	else if (ft_strchr(old_str, '=') && !ft_strchr(new_str, '='))
		return (false);
	return (true);
}