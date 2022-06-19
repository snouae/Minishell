/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_env.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aoumad <abderazzakoumad@gmail.com>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/01 13:17:15 by aoumad            #+#    #+#             */
/*   Updated: 2022/06/16 02:10:22 by aoumad           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

int builtin_env(int argc __attribute((unused)),
    char **argv __attribute((unused)))
{
    int i;
    i = 0;
    
    if (g_env == NULL)
    {
        ft_error("minishell", "env", "environ not set");
        return (EXIT_FAILURE);
    }
    while (g_env[i++])
    {
        ft_putendl_fd(g_env[i], STDOUT_FILENO);
    }
    return (0);
}