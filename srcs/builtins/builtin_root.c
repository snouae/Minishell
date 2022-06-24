/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_root.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aoumad <abderazzakoumad@gmail.com>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/24 15:15:39 by aoumad            #+#    #+#             */
/*   Updated: 2022/06/23 19:41:39 by aoumad           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include"../../includes/minishell.h"
#include <stdio.h>

const struct s_builtins	g_builtins[] = {
	{"echo", builtin_echo},
	{"cd", builtin_cd},
	{"pwd", builtin_pwd},
	{"env", builtin_env},
	{"export", builtin_export},
	{"unset", builtin_unset},
	{NULL, NULL},
};

int builtin_check(char  *str)
{
    int cmd_len;
    int is_builtin;
    int i;
    
    i = 0;
    is_builtin = 0;
    if (!str || !ft_strcmp(str, "exit"))
        is_builtin = -1;
    while (g_builtins[i].name != NULL)
    {
        cmd_len = ft_strlen(g_builtins[i].name);
        if (str && !ft_strncmp(str, g_builtins[i].name, cmd_len + 1))
            is_builtin = i + 1; // avoid returning the value 0 since it's known for NULL in builtin_root func and not in the struct
        i++;
    }
    return (is_builtin);
}

int    builtin_root(char **argv)
{
    int   i;

    i = builtin_check(argv[0]);
    if (i == -1)
        return (builtin_exit(env_count(argv), argv));
    if (i == 0)
        return (ERROR);
    return (g_builtins[i - 1].func(env_count(argv), argv));                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                               
}

