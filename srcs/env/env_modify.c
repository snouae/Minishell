/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env_modify.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aoumad <abderazzakoumad@gmail.com>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/30 17:01:28 by aoumad            #+#    #+#             */
/*   Updated: 2022/06/26 22:51:56 by aoumad           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

int unset_the_var(char  *name)
{
	char    *env_var;
		
	env_var = search_env(name);
	if (env_var == NULL)
		return (ERROR);
	remove_from_env(env_var);
	return (0);
}

int put_the_var(char *str, int test)
{
	char    *new_var;
	char    *old_var;
	int     status;
	int i;

	if (str == NULL || ft_strchr(str, '=') == NULL)
		return (ERROR);
	new_var = ft_strdup(str);
	if (new_var == NULL)
		return (ft_error("minishell", NULL, strerror(ENOMEM)));
	old_var = search_env(str);
	status = replace_str_env(&g_env, old_var, new_var, test);
	if (status == ERROR)
	{
		printf("hello\n");
		status = add_to_env(&g_env, new_var);
		if (status == ERROR)
			return (ft_error("minishell", NULL, strerror(ENOMEM)));
	}
	return (0);
}

int set_the_env(char *name, char *value)
{
	char    *var;
	int     status;
	
	if (name == NULL || value == NULL)
		return (ERROR);
	var = ft_strjoin(name, "=");
	if (var == NULL)
		return (ft_error("minishell", NULL, strerror(ENOMEM)));
	var = ft_strjoin(var, value);
	if (var == NULL)
		return (ft_error("minishell", NULL, strerror(ENOMEM)));
	status = put_the_var(var, 0);
	free(var);
	return (status);
}

static	int	ft_isspace(char c)
{
	if (c == '\f' || c == '\t' || c == '\n' || c == '\r'
		|| c == '\v' || c == ' ')
		return (1);
	return (0);
}

long long	ft_atoi_exit(const char *str, int i, int *status_error)
{
	int			j;
	long		neg;
	long long	sum;
	
	neg = 1;
	sum = 0;
	j = 0;
	if (!str)
		return (0);
	if ((str[i] == '-' || str[i] == '+'))
		if (str[i++] == '-')
			neg *= -1;
	while (str[i] && (ft_isspace(str[i]) || str[i] == '0'))
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
	return (sum * neg);
}