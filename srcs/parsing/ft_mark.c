/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_mark.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: snouae <snouae@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/28 12:03:02 by snouae            #+#    #+#             */
/*   Updated: 2022/06/28 17:18:07 by snouae           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

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
	if (line[*i] == '?')
		ft_lstadd_back(head, ft_add(line, start, *i, type));
	else if (line[*i] <= '9' && line[*i] >= '0')
		ft_lstadd_back(head, ft_add(line, start, *i, type));
	else
	{
		while (line[*i] != double_quo && line[*i] != ' ' && line[*i] != tab
			&& line[*i] && line[*i] != dollar && search_token(line[*i]) == -1
			&& !cherche_symbol(line[*i], "\t!%'()*+,-./?:;<=>@[]^`{|}~"))
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
