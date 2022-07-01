/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_exit.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: snouae <snouae@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/26 18:37:52 by aoumad            #+#    #+#             */
/*   Updated: 2022/06/30 16:36:43 by snouae           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

// static	void	exit_numeric_error(char *arg)
// {
// 	ft_putstr_fd("minishell: exit: ", 2);
// 	ft_putstr_fd(arg, 2);
// 	ft_putstr_fd(": numeric argument required\n", 2);
// 	g_status = 255;
// 	exit (g_status);
// }

// static	void	check_numeric(char *arg, int *rtn_numeric)
// {
// 	int	i;

// 	i = 0;
// 	if (arg[i] == '-' || arg[i] == '+')
// 		i++;
// 	while (arg[i])
// 	{
// 		if (arg[i] != '\f' && arg[i] != '\t' && arg[i] != '\r'
// 			&& arg[i] != '\v' && arg[i] != ' ')
// 		{
// 			if (arg[i] < 48 || arg[i] > 57)
// 			{
// 				exit_numeric_error(arg);
// 				*rtn_numeric = 1;
// 				break ;
// 			}
// 		}
// 		i++;
// 	}
// }

// int	builtin_exit(int argc, char **argv)
// {
// 	int	rtn_numeric;

// 	rtn_numeric = 0;
// 	if (argc == 1)
// 	{
// 		ft_putstr_fd("exit\n", STDERR_FILENO);
// 		exit (0);
// 	}
// 	if (argv[1] != NULL)
// 		check_numeric(argv[1], &rtn_numeric);
// 	builtin_exit_2(argv, rtn_numeric);
// 	return (0);
// }

// void	builtin_exit_2(char **argv, int rtn_numeric)
// {
// 	int			i;
// 	long long	rtn_atoi;
// 	int			status_error;

// 	status_error = 0;
// 	g_status = 0;
// 	i = 1;
// 	while (argv[i])
// 		i++;
// 	if (i > 2)
// 	{
// 		ft_putstr_fd("minishell: exit: too many arguments\n", 2);
// 		g_status = 1;
// 	}
// 	else
// 	{
// 		rtn_atoi = ft_atoi_exit(argv[1], 0, &status_error);
// 		if (status_error == 1)
// 			exit_numeric_error(argv[1]);
// 		g_status = rtn_atoi % 256;
// 	}
// 	if (status_error != 1 || rtn_numeric == 1)
// 		ft_putstr_fd("exit\n", STDERR_FILENO);
// 	exit(g_status);
// 	return ;
// }

static long long    ft_atoi_exit11(const char *str, int i, int *status_error)
{
    int            j;
    long        neg;
    long long    sum;

    neg = 1;
    sum = 0;
    j = 0;
    if (!str)
        return (0);
    if ((str[i] == '-' || str[i] == '+'))
        if (str[i++] == '-')
            neg *= -1;
    while (str[i] && ( str[i] == '0'))
        i++;
    while (str[i] >= '0' && str[i] <= '9' && ++j)
    {
        sum = (sum * 10) + (str[i] - 48);
        if (sum > INT_MAX || sum < INT_MIN)
            *status_error = 1;
        i++;
    }
    while (str[i++])
        j++;
    // if ((j > 19 && neg == 1) || (j > 20 && neg == -1))
    //     *status_error = 1;
    return (sum * neg);
}

static void    exit_numeric_error(char *arg)
{
    ft_putstr_fd("minishell: exit: ", 2);
    ft_putstr_fd(arg, 2);
    ft_putstr_fd(": numeric argument required\n", 2);
    g_status = 255;
    exit (g_status);
}

static void    check_numeric(char *arg, int *rtn_numeric)
{
    int i;

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
                break;
            }
        }
        i++;
    }
}

int builtin_exit(int argc, char **argv)
{
    int         i;
    long long   rtn_atoi;
    int         status_error;
    int         rtn_numeric;
    
    
    g_status = 0;
    rtn_numeric = 0;
    status_error = 0;
    i = 1;
    if (argc == 1)
    {
        ft_putstr_fd("exit\n", STDERR_FILENO);
        exit (0);
    }
    if (argv[1] != NULL)
        check_numeric(argv[1], &rtn_numeric);
    while (argv[i])
        i++;
    if (i > 2)
    {
        ft_putstr_fd("minishell: exit: too many arguments\n", 2);
        g_status = 1;
    }
    else
    {
        rtn_atoi = ft_atoi_exit11(argv[1], 0, &status_error);
        if (status_error == 1)
            exit_numeric_error(argv[1]);
        g_status = rtn_atoi % 256;
    }
    if (status_error != 1 || rtn_numeric == 1)
        ft_putstr_fd("exit\n", STDERR_FILENO);
    exit(g_status);
    //puts("her");
    return (0);
}