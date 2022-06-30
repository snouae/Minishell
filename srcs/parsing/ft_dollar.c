/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_dollar.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: snouae <snouae@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/28 20:39:11 by snouae            #+#    #+#             */
/*   Updated: 2022/06/30 14:05:16 by snouae           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

char	*check_dollar(int *j, char *str, char *new, char **env)
{
	int		start;
	char	*dlr;
	char	*expndr;
	char	*ptr_status;

	start = *j;
	(*j)++;
	if (str[*j] == '?')
	{
		ptr_status = ft_itoa(g_status);
		new = ft_strjoin_n(new, ptr_status);
		free(ptr_status);
	}
	else if (!(str[*j] <= '9' && str[*j] >= '0'))
	{
		while (str[*j] != '\"' && str[*j] != ' ' && str[*j] != tab && str[*j]
			&& str[*j] != dollar && search_token(str[*j]) == -1
			&& !cherche_symbol(str[*j], "\t!$%'()*+,-./:;<=>?@[]^`{|}~"))
			(*j)++;
		(*j)--;
	}
	dlr = fill_array(str, start, *j);
	expndr = expander(dlr, env);
	new = ft_strjoin_n(new, expndr);
	return (new);
}

void	ft_handler_dollar(t_list **tmp, char **env, char **join)
{
	char	*tmps1;
	char	*tmps;
	char	*ptr_status;
	int		t;

	tmps1 = NULL;
	t = 0;
	if ((*tmp)->next)
		t = 1;
	if (((*tmp)->str && (*tmp)->str[1] != '\0' && (*tmp)->str[1] != '?')
		|| (t && (*tmp)->next->type == double_quo))
	{
		tmps = (*tmp)->str;
		tmps1 = expander(ft_strdup(tmps), env);
		if (tmps1)
			*join = ft_strjoin_n(*join, tmps1);
	}
	else if ((*tmp)->str[1] == '\0' && t && (*tmp)->next->type != double_quo)
		*join = ft_strjoin_n(*join, (*tmp)->str);
	else if ((*tmp)->str[1] == '?')
	{
		ptr_status = ft_itoa(g_status);
		*join = ft_strjoin_n(*join, ptr_status);
		free(ptr_status);
	}
}
