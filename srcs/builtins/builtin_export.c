/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_export.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: snouae <snouae@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/01 11:54:41 by aoumad            #+#    #+#             */
/*   Updated: 2022/06/30 22:52:56 by snouae           ###   ########.fr       */
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

	status = EXIT_SUCCESS;
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
			status = export_2(argv, new, test, i);
			i++;
		}
	}
	return (status);
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
