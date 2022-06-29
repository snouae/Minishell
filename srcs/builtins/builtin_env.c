/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_env.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aoumad <abderazzakoumad@gmail.com>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/01 13:17:15 by aoumad            #+#    #+#             */
/*   Updated: 2022/06/29 00:43:30 by aoumad           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

int	builtin_env(int argc __attribute((unused)), char **argv)
{
	int	i;

	i = 0;
	while (ft_strnstr(g_env[i], "PATH", 4) == NULL)
	{
		if (ft_strnstr(g_env[i], "PATH", 4) == NULL && g_env[i + 1] == NULL)
		{
			ft_error("minishell", argv[0],
				": No such file or directory\n");
			return (0);
		}
		i++;
	}
	if (g_env == NULL)
	{
		ft_error("minishell", "env", "environ not set");
		return (EXIT_FAILURE);
	}
	i = 0;
	while (g_env[i])
	{
		if (ft_strchr(g_env[i], '='))
			ft_putendl_fd(g_env[i], STDOUT_FILENO);
		i++;
	}
	return (0);
}
