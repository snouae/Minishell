/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_exit.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aoumad <abderazzakoumad@gmail.com>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/26 18:37:52 by aoumad            #+#    #+#             */
/*   Updated: 2022/06/26 23:23:59 by aoumad           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

static	void	exit_numeric_error(char *arg)
{
	ft_putstr_fd("minishell: exit: ", 2);
	ft_putstr_fd(arg, 2);
	ft_putstr_fd(": numeric argument required\n", 2);
	g_status = 255;
	exit (g_status);
}

static	void	check_numeric(char *arg, int *rtn_numeric)
{
	int	i;

	i = 0;
	if (arg[i] == '-' || arg[i] == '+')
		i++;
	while (arg[i])
	{
		if (arg[i] != '\f' && arg[i] != '\t' && arg[i] != '\r'
			&& arg[i] != '\v' && arg[i] != ' ')
		{
			if (arg[i] < 48 || arg[i] > 57)
			{
				exit_numeric_error(arg);
				*rtn_numeric = 1;
				break ;
			}
		}
		i++;
	}
}

int	builtin_exit(int argc, char **argv)
{
	int	rtn_numeric;

	rtn_numeric = 0;
	if (argc == 1)
	{
		ft_putstr_fd("exit\n", STDERR_FILENO);
		exit (0);
	}
	if (argv[1] != NULL)
		check_numeric(argv[1], &rtn_numeric);
	builtin_exit_2(argv, rtn_numeric);
	return (0);
}

void	builtin_exit_2(char **argv, int rtn_numeric)
{
	int			i;
	long long	rtn_atoi;
	int			status_error;

	status_error = 0;
	g_status = 0;
	i = 1;
	while (argv[i])
		i++;
	if (i > 2)
	{
		ft_putstr_fd("minishell: exit: too many arguments\n", 2);
		g_status = 1;
	}
	else
	{
		rtn_atoi = ft_atoi_exit(argv[1], 0, &status_error);
		if (status_error == 1)
			exit_numeric_error(argv[1]);
		g_status = rtn_atoi % 256;
	}
	if (status_error != 1 || rtn_numeric == 1)
		ft_putstr_fd("exit\n", STDERR_FILENO);
	exit(g_status);
	return ;
}
