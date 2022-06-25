/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lexer.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: snouae <snouae@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/21 14:34:27 by snouae            #+#    #+#             */
/*   Updated: 2022/06/25 18:49:29 by snouae           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

int	search_token(char token)
{
	if (token == ' ')
		return (white_space);
	else if (token == '\n')
		return (new_lin);
	else if (token == '\t')
		return (tab);
	else if (token == '|')
		return (pipe_token);
	else if (token == '>')
		return (redirect_out);
	else if (token == '<')
		return (redirect_in);
	else if (token == '$')
		return (dollar);
	else if (token == '\'')
		return (single_quo);
	else if (token == '\"')
		return (double_quo);
	else if (token == '\0')
		return (char_null);
	else
		return (-1);
}

void	deleteList(t_list **head)
{
	t_list	*current;
	t_list	*next;

	current = *head;
	while (current)
	{
		next = current->next;
		free(current->str);
		free(current);
		current = next;
	}
	*head = NULL;
}

void	ft_lstadd_back(t_list **lst, t_list *new)
{
	t_list	*list;

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

void	ft_mark_redirect(char *line, int *i, int type, t_list **head)
{
	int	start;

	start = *i;
	while (search_token(line[*i]) == type)
		(*i)++;
	while (search_token(line[*i]) == ' ')
		(*i)++;
	while (search_token(line[*i]) == -1)
		(*i)++;
	(*i)--;
	ft_lstadd_back(head, ft_add(line, start, *i, type));
}

void	add_qoute(int type, int test, int *i, char *line)
{
	int	k;

	k = *i + 1;
	if (test == 1)
	{
		while (search_token(line[k]))
		{
			if (search_token(line[k]) == type)
			{
				*i = k;
				break ;
			}
			k++;
		}
	}
}

void	ft_mark_quote(char *line, int *i, int type, t_list **head)
{
	int	l;
	int	test;
	int	start;

	start = *i;
	test = 0;
	l = *i + 1;
	while (search_token(line[l]))
	{
		if (search_token(line[l]) == type)
		{
			test = 1;
			break ;
		}
		l++;
	}
	add_qoute(type, test, i, line);
	ft_lstadd_back(head, ft_add(line, start, *i, type));
}

void	ft_mark_dollar(char *line, int *i, int type, t_list **head)
{
	int	start;

	start = *i;
	(*i)++;
	if (line[*i] <= '9' && line[*i] >= '0')
		ft_lstadd_back(head, ft_add(line, start, *i, type));
	else
	{
		while (line[*i] != double_quo && line[*i] != ' ' && line[*i] != tab
			&& line[*i] && line[*i] != dollar && search_token(line[*i]) == -1
			&& !cherche_symbol(line[*i], "\t!%'()*+,-./:;<=>@[]^`{|}~"))
			(*i)++;
		(*i)--;
		ft_lstadd_back(head, ft_add(line, start, *i, type));
	}
}

void	ft_mark(char *line, int *i, int type, t_list **head)
{
	int	start;

	start = *i;
	if (type != char_null)
	{
		while (search_token(line[*i]) == type)
			(*i)++;
		(*i)--;
		ft_lstadd_back(head, ft_add(line, start, *i, type));
	}
	else
		ft_lstadd_back(head, ft_add("\0", 0, 1, type));
}

void	affich_token(t_list **head)
{
	t_list	*tmp;

	tmp = *head;
	while (tmp != NULL)
	{
		printf("the list : %s -------> type : %d \n", tmp->str, tmp->type);
		tmp = tmp->next;
	}
}

void	check_lexer(char *line, t_list **head, int *i)
{
	if (search_token(line[*i]) == -1)
		ft_mark(line, i, -1, head);
	else if (search_token(line[*i]) == new_lin)
		ft_mark(line, i, new_lin, head);
	else if (search_token(line[*i]) == pipe_token)
		ft_mark(line, i, pipe_token, head);
	else if (search_token(line[*i]) == redirect_out)
		ft_mark_redirect(line, i, redirect_out, head);
	else if (search_token(line[*i]) == redirect_in)
		ft_mark_redirect(line, i, redirect_in, head);
	else if (search_token(line[*i]) == double_quo)
		ft_mark_quote(line, i, double_quo, head);
	else if (search_token(line[*i]) == dollar)
		ft_mark_dollar(line, i, dollar, head);
	else if (search_token(line[*i]) == single_quo)
		ft_mark_quote(line, i, single_quo, head);
	else if (search_token(line[*i]) == tab)
		ft_mark(line, i, tab, head);
	else if (search_token(line[*i]) == white_space)
		ft_mark(line, i, white_space, head);
}

t_list	*ft_lexer(char *line, char **env)
{
	int		i;
	t_list	*head;

	i = 0;
	head = NULL;
	while (line[i])
	{
		check_lexer(line, &head, &i);
		i++;
	}
	ft_mark(line, &i, char_null, &head);
	//affich_token(&head);
	return (head);
}
