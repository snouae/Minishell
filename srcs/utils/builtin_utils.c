/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_utils.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aoumad <abderazzakoumad@gmail.com>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/31 07:41:08 by aoumad            #+#    #+#             */
/*   Updated: 2022/06/17 04:12:49 by aoumad           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

int env_count(char **env)
{
    int i;

    i = 0;
        // while (env && env[i])
    while (env[i])
        i++;
    return (i);
}

int add_to_env(char ***env, char *str)
{
    char    **new_env;
    int     i;

    new_env = (char **)malloc((env_count(*env) + 2) * sizeof(char *));
    // if (new_env == NULL)
    //     return an error message
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

int remove_from_env(char ***env, char *str)
{
    char    **new_env;
    int     i;
    
    new_env = malloc(env_count(*env) * sizeof(char *));
    // if (new_env == NULL)
    //     RETURN AN ERROR MESSAGE
    i = 0;
    while ((*env)[i] != str)
    {
        new_env[i] = (*env)[i];
        i++;
    }
    new_env[i] = NULL;
    free(*env);
    *env = new_env;
    return (0);
}

int replace_str_env(char ***env, char *old_str, char *new_str)
{
    int i;

    if (*env == NULL || old_str == NULL)
        return (ERROR);
    i = 0;
    while ((*env)[i] && (*env)[i] != old_str)
        i++;
    if ((*env)[i] != old_str)
        return (ERROR); // -1 definition in status means there is nothing
        // to replace in env and we gonna create new env_str
    free(old_str);
    (*env)[i] = new_str;
    return (0);    
}

void	ft_free_env(char ***env)
{
	int	i;

	i = 0;
	while ((*env)[i] != NULL)
	{
		free((*env)[i]);
		(*env)[i] = NULL;
		i++;
	}
	free(*env);
	*env = NULL;
}