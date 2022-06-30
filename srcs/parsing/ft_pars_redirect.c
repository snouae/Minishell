/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_pars_redirect.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: snouae <snouae@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/28 12:39:00 by snouae            #+#    #+#             */
/*   Updated: 2022/06/30 14:16:36 by snouae           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

void	ft_lstadd_back1(t_redirection **lst, t_redirection *new)
{
	t_redirection	*list;

	if (!new)
		return ;
	if (!(*lst))
	{
		*lst = new;
		return ;
	}
	list = *lst;
	while (list->next)
		list = list->next;
	list->next = new;
}

void check_not_herdoc(char **new, char **env, t_list **tmp, int *test)
{
	if (*test == 11)
		*new = ft_strjoin_n(*new, (*tmp)->str);
	else
	{
		ft_handler_dollar(tmp, env, new);
		*test = 1;
	}
}

int	add_string_red(char **new, char **env, t_list **tmp, int *test)
{
	if ((*tmp)->type == -1 && !cherche_symbol((*tmp)->str[0], " \t\n\v\f\r"))
		*new = ft_strjoin_n(*new, (*tmp)->str);
	else if ((*tmp)->type == single_quo)
	{
	(*tmp)->str = remove_single_quote((*tmp)->str);
		*new = ft_strjoin_n(*new, (*tmp)->str);
	}
	else if ((*tmp)->type == double_quo)
	{
	(*tmp)->str = remove_double_quote((*tmp)->str, env);
		*new = ft_strjoin_n(*new, (*tmp)->str);
	}
	else if ((*tmp)->type == dollar)
		check_not_herdoc(new, env, tmp, test);
	else if ((cherche_symbol((*tmp)->str[0], " \t\n\v\f\r") || (*tmp)->type == 0
			|| ((*tmp)->type == 60 || (*tmp)->type == 62) && new))
		return (1);
	return (0);
}

char	*check(char *str, char **env, t_list **tmp, int *test)
{
	char	*new;

	new = NULL;
	new = ft_strjoin_n(new, str);
	(*tmp) = (*tmp)->next;
	while ((*tmp) != NULL)
	{
		if (add_string_red(&new, env, tmp, test) == 1)
			break ;
		(*tmp) = (*tmp)->next;
	}
	return (new);
}

t_redirection	*fill_riderect(char *str, t_list **tmp, char **env)
{
	t_redirection	*new;
	int				test;
	int				i;

	test = 0;
	i = skip_redirect(str);
	new = (t_redirection *)malloc(sizeof(t_redirection));
	if (!new)
		ft_error_malloc("minishell", NULL, strerror(ENOMEM));
	if (str[0] == '<' && str[1] == '<')
		test = 11;
	new->file = check(str + i, env, tmp, &test);
	new->status = 0;
	if (test == 1)
		new->status = 1;
	if (str[0] == '<' && str[1] == '<')
		new->type = HEREDOC;
	else if (str[0] == '>' && str[1] == '>')
		new->type = APPEND;
	else if (str[0] == '<')
		new->type = IN;
	else if (str[0] == '>')
		new->type = OUT;
	new->next = NULL;
	return (new);
}
