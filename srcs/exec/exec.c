/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aoumad <abderazzakoumad@gmail.com>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/07 21:47:12 by aoumad            #+#    #+#             */
/*   Updated: 2022/06/20 18:13:56 by aoumad           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

char    **execute_command(t_command *data, char **envp, int index)
{
    char    *path;
    int     pid;
    path = get_path(envp, data, index);
    pid = -1;
    printf("%s\n", path);
    if (data[index].redirect != NULL)
    {
        pid = fork();
        if (pid == 0)
            execve(path, data[index].cmd, envp);
        waitpid(-1, NULL, 0);
    }
    else
    {
        pid = fork();
        if (pid == 0)
            execve(path, data[index].cmd, envp);
        waitpid(-1, NULL, 0);
    }
    return (envp);
}

char    **exec_1(t_command *data, int index, char **envp)
{
    if (index > 0 && data[index].num_cmds > 1)
    {
        dup2(data[index].pipe_fd[0], STDIN_FILENO);
        // close(data[index].pipe_fd[0]);
        //close(data[index].pipe_fd[1]);
    }
    if (data[index].num_cmds != 0  && index != data[index].num_cmds - 1)
    {
        dup2(data[index].pipe_fd[1], STDOUT_FILENO);
       //close(data[index].pipe_fd[0]);
       //close(data[index].pipe_fd[1]);
    }
    // if (data[index].redirect->file)
    //     redirect_execution(data, envp);
    if (data[index].is_builtin_in != 0)
    {
        builtin_root(data[index].cmd);
    }
    else if (data[index].is_builtin_in == 0)
    {
        envp = execute_command(data, envp, index);
        printf(" the bulting %d\n",data[index].is_builtin_in);
    }
    return (envp);
}

void execute_root(t_command *data, char **envp) //, t_list *list need it later
{
    int status;
    int i;
    int pid;
    int nb_args;

    i = 0; // ch7al mne data[index] 3ndi
    status = 0;
    nb_args = 0;
    pid = -1;

    while(i < data[0].num_cmds)
    {
       // if (i > 0)
        pid  = ft_pipe_built(data, pid, i);
   // puts("heeeeeere");
        printf("is built %d\n", data[i].is_builtin_in);
        if (pid == 0 || (data[i].is_builtin_in >= 0 && data[i].fork == 0))
        {
            printf("the pid is %d\n",pid);
            envp = exec_1(data, i, envp);
        }
        else
        {
           close(data[i].pipe_fd[0]);
           close(data[i].pipe_fd[1]);
           
        }
        i++;
    }
    // while (--i)
    // {
    //     	waitpid(-1, &status, 0);
	// 	// if (WIFEXITED(status))
	// 	// 	g_exit_value = WEXITSTATUS(status);
    // }
   //return (envp);
}

int ft_pipe_built(t_command *data, int pid, int index)
{
    data[index].is_builtin_in = builtin_check(data[index].cmd[0]);
    printf("the nbr %d\n",data[index].is_builtin_in);
    if (data[index].num_cmds > 1 && index > 0)
        pipe(data[index].pipe_fd);
    if (data[index].is_builtin_in == 0 && data[index].num_cmds > 1)
    {
        pid = fork();
        data[index].fork = 1; // nchofo blano
    }
    return (pid);
}