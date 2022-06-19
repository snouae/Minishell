/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aoumad <abderazzakoumad@gmail.com>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/28 10:50:41 by aoumad            #+#    #+#             */
/*   Updated: 2022/06/16 21:07:10 by aoumad           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

int env_init(char **env)
{
    int i;
    
    i = 0;
    while (env[i])
    {
        i++;
    }
    if (i == 0)
        return (0);
    g_env = (char **)malloc((i + 1) * sizeof(char *));
    if (!g_env)
            printf("g_env is empty");
    i = 0;
    while (env[i])
    {
        g_env[i] = ft_strdup(env[i]);
        if (!g_env[i])
        {
            ft_free_env(&g_env);
            return (ft_error("minishell", NULL, strerror(ENOMEM)));
        }
        i++;
    }
    g_env[i] = NULL;
    return (0);
}

char    *get_value(char *name)
{
    char    *env;
    env = search_env(name);
    if (env != 0)
        return (ft_strchr(env, '=') + 1); // HOME=/USER/AOUMAD (input) ==> /USER/AOUMAD (output)
    else
        return (NULL);
}
// khasni nchof blan dyal len_name likaduir operations dyal char pointer
char    *search_env(char *name)
{
    int len_name;
    int i;
    if (name == NULL || g_env == NULL)
        return (NULL);
    if (ft_strchr(name, '=') != NULL)
        len_name = ft_strchr(name, '=') - name; // ABC=a ===> 3 of ABC 
    else
        len_name = ft_strlen(name);
    i = 0;
    while (g_env[i])
    {
        if (!ft_strncmp(name, g_env[i], len_name) && g_env[i][len_name] == '=')
            return (g_env[i]);
        i++;
    }
    return (NULL);
}

bool    check_var_is_char(char c)
{
    return (ft_isalnum(c) || c == '_');
}