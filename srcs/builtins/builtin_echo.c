/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_echo.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aoumad <abderazzakoumad@gmail.com>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/25 17:12:36 by aoumad            #+#    #+#             */
/*   Updated: 2022/06/26 22:04:45 by aoumad           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

int	builtin_echo(int argc __attribute((unused)), char **argv)
{
	int	i;
	int	n_flag;

	i = 1;
	n_flag = false;
	while (argv[i] && !ft_strncmp(argv[i], "-n", 3))
		i++;
	if (i == 1)
		n_flag = true;
	while (argv[i])
	{
		ft_putstr_fd(argv[i], 1);
		if (argv[i + 1])
			ft_putstr_fd(" ", 1);
		i++;
	}
	if (n_flag == true)
		ft_putchar_fd('\n', 1);
	return (0);
}

void	capital_handler(char *str)
{
	char	*old_str;
	char	*rtn_str;
	int		i;

	old_str = ft_strdup(str);
	i = 0;
	while (i < ft_strlen(str))
	{
		if (str[i] >= 'A' && str[i] <= 'Z')
			str[i] += 32;
		i++;
	}
	if (ft_strcmp(str, "unset") && ft_strcmp(str, "cd")
		&& ft_strcmp(str, "export") && ft_strcmp(str, "exit"))
		rtn_str = ft_strdup(str);
	return ;
}
