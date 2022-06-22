/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: snouae <snouae@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/21 11:14:44 by aoumad            #+#    #+#             */
/*   Updated: 2022/06/22 17:43:00 by snouae           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

static void    fd_generator(t_command *data, int index)
{
    if (index == 0)
    {
        data[0].prev = NULL;
        data[0].next = NULL;
        if (data[0].num_cmds > 1)
            data[0].next = data[0].pipe;
    }
    else if (index == data[0].num_cmds - 1)
    {
        data[index].prev = data[index - 1].pipe;
        data[index].next = NULL;
    }
    else
    {
        data[index].prev = data[index - 1].pipe;
        data[index].next = data[index].pipe;
    }
}

void    execute_root(t_command *data, char **envp)
{
    int status;
    int i;
    int pid;
    int fd[2];
    char *path;
    int rtn_execve;

    rtn_execve = 0;
    status = 0;
    pid = -1;
    i = 0;
    while (i < data[0].num_cmds)
        fd_generator(data, i++);
    i = 0;
    while (i < data[0].num_cmds)
    {
        data[i].is_builtin_in = builtin_check(data[i].cmd[0]);
        if (data[i].next)
            pipe(data[i].next);
        ft_save_io(fd);
        if (data[i].prev)
        {
            dup2(data[i].prev[0], STDIN_FILENO);
            close(data[i].prev[0]);
        }
        if (data[i].next)
        {
            dup2(data[i].next[1], STDOUT_FILENO);
            close(data[i].next[1]);
        }
        if (data[i].is_builtin_in)
        {
            builtin_root(data[i++].cmd);
            ft_reset_io(fd);
            // if (i == data[0].num_cmds - 1)
            //     waitpid(pid, &status, 0);
            // while (1)
            // {
            //     if (waitpid(-1, 0, 0) == -1)
            //         break;
            // }
            continue;
        }
            pid = fork();
            if (pid == 0)
            {
                if (data[i].prev)
                    close(data[i].prev[1]);
                if (data[i].next)
                    close(data[i].next[0]);
                path = get_path(envp, data, i);
                rtn_execve = execve(path, data[i].cmd, envp);
                exit(126);
            }
            ft_reset_io(fd);
            // if (i == data[0].num_cmds - 1)
            //     waitpid(pid, &status, 0);
            // while (1)
            // {
            //     if (waitpid(-1, 0, 0) == -1)
            //         break;
            // }
        i++;
    } 
     while (1)
    {
        if (waitpid(-1, 0, 0) == -1)
            break;
    }
}