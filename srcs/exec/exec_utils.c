/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: snouae <snouae@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/07 20:34:15 by aoumad            #+#    #+#             */
/*   Updated: 2022/06/26 16:53:10 by snouae           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"
#include <dirent.h>

char    *get_path(char **envp,  t_command *data, int index)
{
    g_status = 0;
    char    **paths;
    char    *path;
    int     i;
    char    *part_path;
    if(data[index].cmd[0][0] == '/')
    {
        if(opendir(data[index].cmd[0]) != NULL)
        {
            ft_error("minishell", data[index].cmd[0], " is a directory\n");
            g_status = 126;
        }
        else if (access(data[index].cmd[0], F_OK) == 0)
            return (data[index].cmd[0]);
        else if (access(data[index].cmd[0], F_OK) == -1)
        {
            ft_error("minishell", data[index].cmd[0], "No such file or directory\n");
            g_status = 127;
        }
    }
    else
    {
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
    }
    return (0);
}

void ft_command_not_found(char **paths, char *cmd)
{
    int i;
    
    i = 0;
    while (paths[i++])
        free(paths[i]);
    free(paths);
    ft_putstr_fd(cmd, STDERR_FILENO);
    ft_putstr_fd(": command not found\n", STDERR_FILENO);
    puts("here");
    g_status = 127;
    printf("%d\n", g_status);
    // exit(g_status);
    // i need to free the t_command to avoid leaks
    //exit(EXIT_FAILURE);
}