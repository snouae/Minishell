/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aoumad <abderazzakoumad@gmail.com>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/31 07:39:12 by aoumad            #+#    #+#             */
/*   Updated: 2022/06/05 18:36:03 by aoumad           ###   ########.fr       */
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
	return (ERROR);
}
