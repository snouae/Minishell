/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_export.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aoumad <abderazzakoumad@gmail.com>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/01 11:54:41 by aoumad            #+#    #+#             */
/*   Updated: 2022/06/22 10:29:17 by aoumad           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

static char **sort_env(char **env);
static bool check_arg(char *argv);

int builtin_export(int argc, char **argv)
{
    int status;
    int  i;

    status = EXIT_SUCCESS;
    if (argc == 1)
        exported_vars();
    if (argc > 1)
    {
        i = 1;
        while (argv[i])
        {
            if (check_arg(argv[i]) == false)
            {
                ft_error("minishell", argv[i], "not a valid identifier\n");
                status = EXIT_FAILURE;
            }
            else if (ft_strchr(argv[i], '='))
                status = put_the_var(argv[i]);
            i++;
        }
    }
    return (status);
}

void exported_vars(void)
{
    char    **dup_env;
    int     i;
    
    dup_env = (char **)malloc((env_count(g_env) + 1) * sizeof(char *)); // +1 for NULL
    if (dup_env == NULL)
    {
        ft_error("minishell", NULL, strerror(ENOMEM)); // "Cannot allocate memory" message
        return ;
    }
    if (g_env == NULL)
        return ;
    ft_memcpy(dup_env, g_env, (env_count(g_env) + 1) * sizeof(char *));
    i = 0;
    dup_env = sort_env(dup_env);
    i = 0;
    while (dup_env[i])
    {
        g_env[i] = ft_strdup(dup_env[i]);
        i++;
    }
    i = 0;
    while (g_env[i])
	{
        ft_putendl_fd(g_env[i], 1);
		i++;
	}
    free(dup_env);
}

static char **sort_env(char **env)
{
    int     i;
    int     j;
    char    *tmp;
    int     count;
    
    count = env_count(env);
    i = 0;
    while(i < count - 1)
    {
        j = 0;
        while (j < (count - 1))
        {
            if (ft_strcmp(env[j], env[j + 1]) > 0)
            {
                tmp = env[j];
                env[j] = env[j + 1];
                env[j + 1] = tmp;
            }
            j++;
        }
        i++;
    }
    return (env);
}

static bool check_arg(char *argv)
{
    int i;

    i = 0;
    if (argv[0] == '\0' || argv[0] == '=')
        return (false);
    while (argv[i] != '\0'  && argv[i] != '=')
        i++;
    if (argv[i] == '=' || argv[i] == '\0')
        return (true);
    else
        return (false);
    
}