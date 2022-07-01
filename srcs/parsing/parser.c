/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: snouae <snouae@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/27 14:52:59 by snouae            #+#    #+#             */
/*   Updated: 2022/07/01 11:34:45 by snouae           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

t_list	*ft_count_args(t_list *current, int *count)
{
	*count = 0;
	while (current != NULL)
	{
		if (current->type != 124)
		{
			current = current->next;
			(*count)++;
		}
		else
		{
			current = current->next;
			break ;
		}
	}
	return (current);
}

int	fill_arg(t_list **tmp, t_command *cmd, int *j, char **join)
{
	if ((*tmp)->type == -1 && !cherche_symbol((*tmp)->str[0], " \t\n\v\f\r"))
		*join = ft_strjoin_n(*join, (*tmp)->str);
	else if ((*tmp)->type == single_quo)
	{
		(*tmp)->str = remove_single_quote((*tmp)->str);
		*join = ft_strjoin_n(*join, (*tmp)->str);
	}
	else if ((*tmp)->type == double_quo)
	{
		(*tmp)->str = remove_double_quote((*tmp)->str, g_env);
		*join = ft_strjoin_n(*join, (*tmp)->str);
	}
	else if ((*tmp)->type == dollar)
		ft_handler_dollar(tmp, g_env, join);
	else if ((*tmp)->type == redirect_in || (*tmp)->type == redirect_out)
		ft_lstadd_back1(&cmd->redirect, fill_riderect((*tmp)->str, tmp, g_env));
	else if ((cherche_symbol((*tmp)->str[0], " \t\n\v\f\r")
			|| (*tmp)->type == char_null) && *join)
	{
		cmd->cmd[(*j)++] = *join;
		*join = NULL;
		return (1);
	}
	return (0);
}

void	check_malloc(t_command **cmd, char **args)
{
	if (!args)
		ft_error_malloc("minishell", NULL, strerror(ENOMEM));
	(*cmd)->redirect = NULL;
}

void	fill_cmd(t_command *cmd, char **env, int nbr_args, t_list *tmp)
{
	int		j;
	t_list	*next;
	char	*join;

	j = 0;
	join = NULL;
	cmd->cmd = (char **)malloc(sizeof(char *) * (nbr_args + 1));
	check_malloc(&cmd, cmd->cmd);
	while (tmp != NULL)
	{
		if (tmp->type != 124)
		{
			if (fill_arg(&tmp, cmd, &j, &join))
				join = NULL;
		}
		else
		{
			cmd->cmd[j++] = join;
			join = NULL;
			break ;
		}
		tmp = tmp->next;
	}
	free (join);
	cmd->cmd[j] = 0;
}

void	affich(int nbr_cmds, t_command *cmd)
{
	int				i;
	int				j;
	t_redirection	*head1;

	i = 0;
	j = 0;
	while (i < nbr_cmds)
	{
		j = 0;
		printf("\nthe caommande number %d\n", i + 1);
		while (cmd[i].cmd[j])
		{
			printf("%s ", cmd[i].cmd[j]);
			j++;
		}
		head1 = cmd[i].redirect;
		printf("\nlist of redirections\n");
		while (head1 != NULL)
		{
			printf("%s ------------> type : %d \n", head1->file, head1->type);
			head1 = head1->next;
		}
		i++;
	}
}

t_command	*ft_parser(t_list **head, char *line, char **env)
{
	t_list		*current;
	t_list		*tmp;
	t_command	*cmd;
	int			i;
	int			nbr_args;

	i = -1;
	nbr_args = 0;
	current = *head;
	cmd = (t_command *)malloc(sizeof(t_command) * count_commads(head));
	while (++i < count_commads(head))
	{
		cmd[i].num_cmds = count_commads(head);
		cmd[i].exec = 0;
		tmp = current;
		current = ft_count_args(current, &nbr_args);
		if (nbr_args)
			fill_cmd(cmd + i, env, nbr_args, tmp);
	}
	//affich(count_commads(head), cmd);
	return (cmd);
}
