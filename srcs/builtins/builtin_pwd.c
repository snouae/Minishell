/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_pwd.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aoumad <abderazzakoumad@gmail.com>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/26 09:50:51 by aoumad            #+#    #+#             */
/*   Updated: 2022/06/29 13:37:13 by aoumad           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

int	builtin_pwd(int argc __attribute((unused)),
	char **argv __attribute((unused)))
{
	int	i;

	i = 0;
	char buf[MAX_BUF];
	if (getcwd(buf, sizeof(buf)))
	{
		ft_putendl_fd(buf, STDOUT_FILENO);
		return (0);
	}
	else if (!getcwd(NULL, 0))
	{
		while (g_env[i])
		{
			if (!ft_strncmp(g_env[i], "PWD", 3))
			{
				printf("%s\n", g_env[i] + 4);
			}
			i++;
		}
	}
	return (0);		
}