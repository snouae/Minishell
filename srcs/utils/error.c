/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: snouae <snouae@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/31 07:39:12 by aoumad            #+#    #+#             */
/*   Updated: 2022/06/29 16:31:01 by snouae           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

int	ft_error(char *shell_name, char *s1, char *message)
{
	if (shell_name)
	{
		ft_putstr_fd(shell_name, 2);
		ft_putstr_fd(": ", 2);
	}
	if (s1)
		ft_putstr_fd(s1, 2);
	if (message)
		ft_putstr_fd(message, 2);
	ft_putstr_fd("\n", 2);
	return (ERROR);
}

int	ft_error_malloc(char *shell_name, char *s1, char *message)
{
	if (shell_name)
	{
		ft_putstr_fd(shell_name, 2);
		ft_putstr_fd(": ", 2);
	}
	if (s1)
		ft_putstr_fd(s1, 2);
	if (message)
		ft_putstr_fd(message, 2);
	ft_putstr_fd("\n", 2);
	exit (1);
}

void	ft_free_env(char ***env)
{
	int	i;

	i = 0;
	while ((*env)[i] != NULL)
	{
		free((*env)[i]);
		i++;
	}
	//free(*env);
	//*env = NULL;
}
