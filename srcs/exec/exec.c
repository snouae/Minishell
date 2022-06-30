/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: snouae <snouae@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/21 11:14:44 by aoumad            #+#    #+#             */
/*   Updated: 2022/06/30 15:14:09 by snouae           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

static	void	fd_generator(t_command *data, int index)
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

void	dup_io(t_command *data, int i)
{
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
}

void	execute_root(t_command *data, char **envp)
{
	int	status;
	int	i;
	int	pid;
	int	fd[2];
	char	*path;
	int		rtn_execve;
	int		check;

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
		if (data[i].exec == 0)
	   {
		ft_save_io(fd);
		dup_io(data, i);
		check = 0;
		if (data[i].redirect)
			redirect_handler(data, i);
		if (data[i].is_builtin_in  && data[i].redirect == NULL)
		{
			g_status = builtin_root(data[i++].cmd);
			ft_reset_io(fd);
			continue;
		}
		pid = fork();
		
	   signal(SIGINT, SIG_IGN);
		if (pid == 0)
		{
		signal(SIGINT, SIG_DFL);
		signal(SIGQUIT, SIG_DFL);
			if (data[i].prev)
				close(data[i].prev[1]);
			if (data[i].next)
				close(data[i].next[0]);
			if (!ft_strncmp(data[i].cmd[0], "./", 2))
			{
					if(opendir(data[i].cmd[0]) != NULL)
					{
						check = 1;
						ft_error("minishell", data[i].cmd[0], " is a directory");
						g_status = 126;
					}
					path = data[i].cmd[0];
			}
			else
					path = get_path(envp, data, i);
			if(check == 0)
			{
				rtn_execve = execve(path, data[i].cmd, envp);
				if (rtn_execve == -1)
				{
					if (errno == 13)
					{
						ft_putstr_fd("minishell: ", 2);
						ft_putstr_fd(data[i].cmd[0], 2);   
						perror(" ");
						g_status = 126;
					}
					else
						g_status = 127;
				}
			}
			exit(g_status);
			
		}
		ft_reset_io(fd);
	   }
	   else
	   {
		   if (data[i].prev)
		   		close(data[i].prev[1]);
			if (data[i].next)
				close(data[i].next[1]);
	   }
		if (data[i].prev)
		   	close(data[i].prev[1]);
		if (data[i].next)
			close(data[i].next[1]);
		i++;
	}
	if (i == data[0].num_cmds)
		waitpid(pid, &g_status, 0);
	while (1)
	{
		if (waitpid(-1, 0, 0) == -1)
			break;
	}
	if (g_status == 3)
	{
		printf("Quit: 3\n");
		g_status = 131;
	}
	else if(g_status == 2)
		g_status = 130;
	else if (g_status == 126 || g_status == 127)
		return ;
	else
		g_status = WEXITSTATUS(g_status);
}
