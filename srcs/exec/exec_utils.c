/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aoumad <abderazzakoumad@gmail.com>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/07 20:34:15 by aoumad            #+#    #+#             */
/*   Updated: 2022/06/28 17:44:16 by aoumad           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

char	*return_path(t_command *data, int index, char **envp, char *path)
{
	char	**paths;
	char	*part_path;
	int		i;

	i = 0;
	while (ft_strnstr(envp[i], "PATH", 4) == NULL)
	{
		if (ft_strnstr(envp[i], "PATH", 4) == NULL && envp[i + 1] == NULL)
			ft_error("minishell", data[index].cmd[0],
				": No such file or directory\n");
		i++;
	}
	paths = ft_split(envp[i] + 5, ':');
	i = 0;
	while (paths[i])
	{
		part_path = ft_strjoin(paths[i], "/");
		path = ft_strjoin(part_path, data[index].cmd[0]);
		free(part_path);
		if (access(path, F_OK) == 0)
			return (path);
		i++;
	}
	ft_command_not_found(paths, data[index].cmd[0]);
	return (path);
}

char	*get_path(char **envp, t_command *data, int index)
{
	char	*path;

	g_status = 0;
	if (data[index].cmd[0][0] == '/')
	{
		if (opendir(data[index].cmd[0]) != NULL)
		{
			ft_error("minishell", data[index].cmd[0], " is a directory\n");
			g_status = 126;
		}
		else if (access(data[index].cmd[0], F_OK) == 0)
			return (data[index].cmd[0]);
		else if (access(data[index].cmd[0], F_OK) == -1)
		{
			ft_error("minishell", data[index].cmd[0],
				"No such file or directory\n");
			g_status = 127;
		}
	}
	else
		path = return_path(data, index, envp, path);
	free(path);
	return (path);
}

void	ft_command_not_found(char **paths, char *cmd)
{
	int	i;

	i = 0;
	while (paths[i++])
		free(paths[i]);
	free(paths);
	ft_putstr_fd(cmd, STDERR_FILENO);
	ft_putstr_fd(": command not found\n", STDERR_FILENO);
	g_status = 127;
}
