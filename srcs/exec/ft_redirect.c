/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_redirect.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aoumad <abderazzakoumad@gmail.com>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/25 10:44:17 by aoumad            #+#    #+#             */
/*   Updated: 2022/06/27 16:36:11 by aoumad           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

void	read_handler(t_command *data, int i, int c, int n)
{
	t_redirection	*red;

	red = data[i].redirect;
	while (red != NULL)
	{
		if (red->type == HEREDOC)
			c++;
		red = red->next;
	}
	red = data[i].redirect;
	while (red != NULL)
	{
		if (red->type == HEREDOC)
			n++;
		if (red && red->type == HEREDOC && n == c)
		{
			dup2(red->fd, STDIN_FILENO);
			close(red->fd);
			break ;
		}
		red = red->next;
	}
}

void	redirect_handler(t_command *data, int i)
{
	int	index;
	int	c;
	int	n;

	c = 0;
	n = 0;
	index = i;
	read_handler(data, i, c, n);
	while (data[i].redirect->next)
		data[i].redirect = data[i].redirect->next;
	if (data[i].redirect->type == IN)
	{
		dup2(data[i].redirect->fd, STDIN_FILENO);
		close(data[i].redirect->fd);
	}
	if (data[i].redirect->type == OUT || data[i].redirect->type == APPEND)
	{
		dup2(data[i].redirect->fd, STDOUT_FILENO);
		close(data[i].redirect->fd);
	}
	if (data[index].redirect->fd == HEREDOC)
	{
		dup2(data[i].redirect->fd, STDOUT_FILENO);
		close(data[i].redirect->fd);
	}
}
