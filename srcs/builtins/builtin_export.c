/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_export.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aoumad <abderazzakoumad@gmail.com>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/01 11:54:41 by aoumad            #+#    #+#             */
/*   Updated: 2022/06/27 19:06:43 by aoumad           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

char	*skip_symbol(char *argv)
{
	int		i;
	int		j;
	char	*str;

	str = malloc(ft_strlen(argv));
	i = 0;
	j = 0;
	while (argv[i] != '\0')
	{
		if (argv[i + 1] == '=' && cherche_symbol(argv[i], "+"))
		{
			i++;
			continue ;
		}
		str[j++] = argv[i];
		i++;
	}
	return (str);
}

bool	error_symbol(char *argv)
{
	int	i;

	i = 0;
	while (argv[i] != '\0' && argv[i] != '=')
	{
		if (cherche_symbol(argv[i], "!$%'()*+,-./:;<>?@[]^`{|}~"))
			return (false);
		i++;
	}
	return (true);
}

int	builtin_export(int argc, char **argv)
{
	int		status;
	int		i;
	char	*new;
	int		test;

	test = 0;
	if (argc == 1)
		exported_vars();
	if (argc > 1)
	{
		i = 1;
		while (argv[i])
		{
			new = skip_symbol(argv[i]);
			if (ft_strcmp(new, argv[i]))
				test = 1;
			export_2(argv, new, test, i);
			i++;
		}
	}
	return (status);
}

char	**sort_env(char **env)
{
	int		i;
	int		j;
	char	*tmp;
	int		count;

	count = env_count(env);
	i = 0;
	while (i < count - 1)
	{
		j = 0;
		while (j < (count - 1))
		{
			if (ft_strcmp(env[j], env[j + 1]) > 0)
			{
				tmp = env[j];
				env[j] = env[j + 1];
				env[j + 1] = tmp;
			}
			j++;
		}
		i++;
	}
	return (env);
}

bool	check_arg(char *argv)
{
	int	i;

	i = 0;
	if (argv[0] == '\0' || argv[0] == '=')
		return (false);
	while (argv[i] != '\0' && argv[i] != '=')
		i++;
	if (argv[i] == '=' || argv[i] == '\0')
		return (true);
	else
		return (false);
}
