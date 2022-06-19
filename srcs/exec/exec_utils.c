/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aoumad <abderazzakoumad@gmail.com>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/07 20:34:15 by aoumad            #+#    #+#             */
/*   Updated: 2022/06/18 16:03:14 by aoumad           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

char    *get_path(char **envp,  t_command *data, int index)
{
    char    **paths;
    char    *path;
    int     i;
    char    *part_path;

    i = 0;
    while (ft_strnstr(envp[i], "PATH", 4) == NULL)
        i++;
    paths = ft_split(envp[i] + 5, ':');
    i = 0;
    while (paths[i])
    {
        part_path = ft_strjoin(paths[i], "/");
        path = ft_strjoin(part_path, data[index].cmd[0]);
        free(part_path);
        if (access(path, F_OK) == 0)
            return (path);
        free(path);
        i++;
    }
    ft_command_not_found(paths, data[index].cmd[0]);
    return (0);
}

void ft_command_not_found(char **paths, char *cmd)
{
    int i;
    
    i = 0;
    while (paths[i++])
        free(paths[i]);
    free(paths);
    ft_putstr_fd(cmd, 2);
    ft_putstr_fd(": command not found", 2);
    // i need to free the t_command to avoid leaks
    exit(EXIT_FAILURE);
}