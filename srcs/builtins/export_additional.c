/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export_additional.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aoumad <abderazzakoumad@gmail.com>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/26 23:31:11 by aoumad            #+#    #+#             */
/*   Updated: 2022/06/27 14:23:09 by aoumad           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

int	export_2(char **argv, char *new, int test, int i)
{
	int	status;

	status = EXIT_SUCCESS;
	if (check_arg(new) == false || error_symbol(new) == false)
	{
		ft_error("minishell", argv[i], "not a valid identifier\n");
		status = EXIT_FAILURE;
	}
	else if (ft_strchr(new, '='))
		status = put_the_var(new, test);
	return (status);
}

void	exported_vars(void)
{
	char	**dup_env;
	int		i;

	dup_env = (char **)malloc((env_count(g_env) + 1) * sizeof(char *));
	if (dup_env == NULL)
		return ;
	if (g_env == NULL)
		return ;
	ft_memcpy(dup_env, g_env, (env_count(g_env) + 1) * sizeof(char *));
	i = 0;
	dup_env = sort_env(dup_env);
	i = 0;
	while (dup_env[i])
	{
		g_env[i] = ft_strdup(dup_env[i]);
		i++;
	}
	i = 0;
	while (g_env[i])
	{
		ft_putstr_fd("declare -x ", 1);
		ft_putendl_fd(g_env[i], 1);
		i++;
	}
	free(dup_env);
}
