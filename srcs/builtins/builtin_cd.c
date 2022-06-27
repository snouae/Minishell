/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_cd.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aoumad <abderazzakoumad@gmail.com>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/01 13:25:11 by aoumad            #+#    #+#             */
/*   Updated: 2022/06/25 15:55:14 by aoumad           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

static	char	*get_the_print_working_dir(int argc, char **argv);
static	int	update_pwd(void);

int	builtin_cd(int argc, char **argv)
{
	char	*dir;

	dir = get_the_print_working_dir(argc, argv);
	if (dir == NULL)
		return (EXIT_FAILURE);
	if (chdir(dir) == -1)
	{
		printf("minishell: cd: %s: No such file or directory\n", dir);
		return (ERROR);
	}
	if (argv[1] && !ft_strcmp(argv[1], "-"))
		ft_putendl_fd(dir, STDOUT_FILENO);
	if (update_pwd() == ERROR)
		return (EXIT_FAILURE);
	return (0);
}

static	char	*get_the_print_working_dir(int argc, char **argv)
{
	char	*dir;

	dir = NULL;
	if (argc == 1)
	{
		dir = get_value("HOME");
		if (dir == NULL)
			ft_error("minishell", "cd", " HOME not set");
	}
	else if (argv[1] && ft_strcmp(argv[1], "-") == 0)
	{
		dir = get_value("OLDPWD");
		if (dir == NULL)
			ft_error("minishell", "cd", "OLDPWD not set");
	}
	else
		dir = argv[1];
	return (dir);
}

static	int	update_pwd(void)
{
	char	path[MAX_BUF];

	if (get_value("PWD"))
	{
		if (set_the_env("OLDPWD", get_value("PWD")) == ERROR)
			return (ERROR);
	}
	else
		unset_the_var("OLDPWD");
	if (getcwd(path, MAX_BUF) == NULL)
	{
		ft_putstr_fd("minishell: ", 1);
		ft_putstr_fd("cd: error retrieving current directory: getcwd: ", 1);
		ft_putstr_fd("error retrieving current directory: getcwd: cannot ", 1);
		ft_putstr_fd("access parent directories: ", 1);
		ft_putstr_fd("No such file or directory\n", 1);
		return (ERROR);
	}
	if (set_the_env("PWD", path) == ERROR)
		return (ERROR);
	return (0);
}
