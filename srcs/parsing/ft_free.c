/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_free.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: snouae <snouae@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/28 12:26:55 by snouae            #+#    #+#             */
/*   Updated: 2022/06/30 08:44:37 by snouae           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

void	free_all(t_command *cmd)
{
	int			i;
	int			j;
	t_command	*ptr;
	int			nbr;

	i = 0;
	nbr = cmd[0].num_cmds;
	while (i < nbr)
	{
		j = 0;
		while (cmd[i].cmd[j])
		{
			free(cmd[i].cmd[j]);
			j++;
		}
		if (cmd[i].redirect)
			deleteredir(&cmd[i].redirect);
		free(cmd[i].cmd);
		i++;
	}
	free(cmd);
}

void	deleteredir(t_redirection **head_ref)
{
	t_redirection	*current;
	t_redirection	*next;

	current = *head_ref;
	while (current)
	{
		next = current->next;
		free(current->file);
		free(current);
		current = next;
	}
	*head_ref = NULL;
}

void	deletelist(t_list **head)
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
