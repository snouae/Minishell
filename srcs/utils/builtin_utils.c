/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_utils.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: snouae <snouae@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/31 07:41:08 by aoumad            #+#    #+#             */
/*   Updated: 2022/06/28 15:31:33 by snouae           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

static	char	*ft_strchr_export(const char *s, int c)
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

	new_env = (char **)malloc((env_count(*env) + 1) * sizeof(char *));
	if (!new_env)
		ft_error_malloc("minishell", NULL, strerror(ENOMEM));
	i = 0;
	printf("the string %s\n",str);
	while ((*env)[i])
	{
		new_env[i] = (*env)[i];
		i++;
	}
	new_env[i] = str;
	new_env[i + 1] = NULL;
	i = 0;
	//free(*env);
	//copy_env()
	*env = new_env;
	while((*env)[i])
	{
		printf("------%s\n",(*env)[i]);
		i++;
	}
	//free(new_env);
	return (0);
}

int	remove_from_env(char *str)
{
	char	**new_env;
	int		i;
	int		j;

	new_env = malloc(env_count(g_env) * sizeof(char *));
	if (new_env == NULL)
		ft_error_malloc("minishell", NULL, strerror(ENOMEM));
	i = 0;
	j = 0;
	while (g_env[i])
	{
		if (!ft_strcmp(g_env[i], str))
			i++;
		new_env[j++] = g_env[i++];
	}
	new_env[j] = NULL;
	//free(g_env);
	g_env = new_env;
	//free(new_env);
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
	//free(old_str);
	if (test == 1)
	{
		new_str = ft_strchr_export(new_str, '=');
		(*env)[i] = ft_strjoin((*env)[i], new_str);
	}
	else
		(*env)[i] = new_str;
	return (0);
}

void	ft_free_env(char ***env)
{
	// int	i;

	// i = 0;
	// while ((*env)[i] != NULL)
	// {
	// 	free((*env)[i]);
	// 	(*env)[i] = NULL;
	// 	i++;
	// }
	// free(*env);
	// *env = NULL;
}
